package views.graphview

import presenters.GraphView
import presenters.MainPresenter
import views.UIConstants
import java.awt.*
import java.awt.event.MouseEvent
import java.awt.event.MouseListener
import java.awt.event.MouseMotionListener
import java.awt.geom.Ellipse2D
import java.lang.NumberFormatException
import javax.swing.*

interface GraphViewObserver {
    fun onSheetDragged(offsetX: Int, offsetY: Int)
}

class GraphSheet: JPanel(), MouseListener, MouseMotionListener, GraphView {

    init {
        background = Color.WHITE

        addMouseListener(this)
        addMouseMotionListener(this)
    }

    private val presenter = MainPresenter(this)

    override fun update() = repaint()

    var sheetDraggingObserver: GraphViewObserver? = null

    private val nodes = presenter.nodes
    private val edges = presenter.edges
    private val dualEdges = presenter.dualEdges

    private val mathProvider = GraphMathProvider()

    private var isAlgorithmRunning = false

    private var currentGraphViewState: GraphViewState = GraphViewState.DefaultState
        set(newGraphViewState) {
            when(newGraphViewState)
            {
                GraphViewState.DefaultState -> {
                    resetCursorToArrow()
                }

                is GraphViewState.SheetMovingState -> {
                    setCursorHand()
                }

                is GraphViewState.NodeDraggingState -> {
                    setCursorHand()
                }
            }
            field = newGraphViewState
        }


    override fun paintComponent(graphics: Graphics) {
        super.paintComponent(graphics)

        val graphics2D = graphics as Graphics2D

        graphics2D.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON)

        when(currentGraphViewState)
        {
            is GraphViewState.CreatingEdgeState, is GraphViewState.CreatingEdgeAndSheetMovingState -> {
                val currentCreatingEdgeState: GraphViewState.CreatingEdgeState =
                    if(currentGraphViewState is GraphViewState.CreatingEdgeState)
                        currentGraphViewState as GraphViewState.CreatingEdgeState
                    else (currentGraphViewState as GraphViewState.CreatingEdgeAndSheetMovingState).creatingEdgeState

                drawBuildingEdge(currentCreatingEdgeState.creatingEdge, graphics2D)
            }
        }
        //Сначала рисуем рёбра, чтобы вершины были сверху них.

        edges.forEach {
            if (!mathProvider.areNodesColliding(it.sourceNode, it.endNode))
                drawEdge(it, graphics2D)
        }

        dualEdges.forEach {
            if (!mathProvider.areNodesColliding(it.edge1.sourceNode, it.edge1.endNode))
                drawDualEdge(it, graphics2D)
        }

        var nodeIndex = 1
        nodes.forEach {
            drawNode(it, nodeIndex, graphics2D)
            nodeIndex++
        }
    }

    private fun drawNode(node: UINode, nodeNumber: Int, panelGraphics: Graphics2D) {
        val strokeCircle = Ellipse2D.Double((node.coordinate.x-node.radius).toDouble(),
            (node.coordinate.y-node.radius).toDouble(),
            (2*node.radius).toDouble(),
            (2*node.radius).toDouble())

        val graphicsCircle = Ellipse2D.Double((node.coordinate.x-UIConstants.circleRadius).toDouble(),
            (node.coordinate.y-UIConstants.circleRadius).toDouble(),
            (2*UIConstants.circleRadius).toDouble(),
            (2*UIConstants.circleRadius).toDouble())

        val nodeNumberString = nodeNumber.toString()
        panelGraphics.font = UIConstants.nodeTextFont
        val fontMetrics = panelGraphics.fontMetrics
        val textWidth = fontMetrics.getStringBounds(nodeNumberString, panelGraphics).width.toInt()
        val textHeight = fontMetrics.getStringBounds(nodeNumberString, panelGraphics).height.toInt()

        panelGraphics.color = UIConstants.nodeStrokeFillColor
        panelGraphics.fill(strokeCircle)

        if(node.isActive) panelGraphics.color = UIConstants.nodeActiveFillColor
        else {
            if (isAlgorithmRunning) {
                if(node.bestWay != "-") panelGraphics.color = UIConstants.passedNodeFillColor
                else panelGraphics.color = UIConstants.nodeFillColor
            }
            else panelGraphics.color = UIConstants.nodeFillColor
        }

        panelGraphics.fill(graphicsCircle)

        if(node.isActive) panelGraphics.color = UIConstants.activeNodeTextColor
        else panelGraphics.color = UIConstants.textColor
        panelGraphics.drawString(nodeNumberString,
            node.coordinate.x - textWidth/2,
            node.coordinate.y + textHeight/4)


        if(isAlgorithmRunning) {
            if(!node.isActive) {
                val sign =
                    "[${node.bestWay}/ ${node.nodeFrom}]"
                panelGraphics.font = UIConstants.nodeSignTextFont
                val signHeight = fontMetrics.getStringBounds(sign, panelGraphics).height.toInt()
                val signWidth = fontMetrics.getStringBounds(sign, panelGraphics).width.toInt()
                panelGraphics.drawString(
                    sign,
                    node.coordinate.x - signWidth / 5,
                    node.coordinate.y + node.radius + signHeight / 2
                )
            }
        }
    }

    private fun drawEdge(edge: UIEdge, panelGraphics: Graphics2D)
    {
        if(edge.isActive) {
            panelGraphics.color = UIConstants.activeEdgeColor
            panelGraphics.stroke = BasicStroke((UIConstants.activeEdgeWidth/2).toFloat())
        }
        else {
            panelGraphics.color = UIConstants.edgeColor
            panelGraphics.stroke = BasicStroke((edge.width/2).toFloat())
        }
        panelGraphics.drawLine(edge.sourceNode.coordinate.x,
            edge.sourceNode.coordinate.y,
            edge.endNode.coordinate.x,
            edge.endNode.coordinate.y)

        val arrow = mathProvider.calculateEdgeArrow(edge)
        drawEdgeArrow(arrow, panelGraphics)

        val textCoordinate = mathProvider.calculateEdgeWeightTextPosition(edge)
        panelGraphics.color = UIConstants.textColor
        panelGraphics.font = UIConstants.edgeWeightTextFont
        panelGraphics.drawString(edge.weight,
            textCoordinate.x, textCoordinate.y)
    }

    private fun drawEdgeArrow(arrow: UIEdgeArrow, panelGraphics: Graphics2D)
    {
        panelGraphics.drawLine(arrow.point2.x,
            arrow.point2.y,
            arrow.point1.x,
            arrow.point1.y)

        panelGraphics.drawLine(arrow.point3.x,
            arrow.point3.y,
            arrow.point1.x,
            arrow.point1.y)
    }

    private fun drawDualEdge(dualEdge: UIDualEdge, panelGraphics: Graphics2D){
        panelGraphics.stroke = BasicStroke((UIConstants.edgeWidth/2).toFloat())

        if (dualEdge.edge1.isActive){
            panelGraphics.color = UIConstants.activeEdgeColor
            panelGraphics.stroke = BasicStroke((UIConstants.activeEdgeWidth/2).toFloat())
        }
        else {
            panelGraphics.color = UIConstants.edgeColor
            panelGraphics.stroke = BasicStroke((dualEdge.edge1.width/2).toFloat())
        }

        val coordinates = mathProvider.calculateDualEdgeCoordinates(dualEdge)
        val arrow1 = mathProvider.calculateArrowForEdge(
            coordinates.first.first, coordinates.second.second
        )
        val weightPosition1 = mathProvider.calculateEdgeWeightTextPosition(coordinates.first.first,
            coordinates.second.second)
        panelGraphics.drawLine(
            coordinates.first.first.x,
            coordinates.first.first.y,
            coordinates.second.second.x,
            coordinates.second.second.y
        )
        drawEdgeArrow(arrow1, panelGraphics)
        panelGraphics.color = UIConstants.textColor
        panelGraphics.font = UIConstants.edgeWeightTextFont
        panelGraphics.drawString(dualEdge.edge1.weight,
            weightPosition1.x, weightPosition1.y)


        if (dualEdge.edge2.isActive){
            panelGraphics.color = UIConstants.activeEdgeColor
            panelGraphics.stroke = BasicStroke((UIConstants.activeEdgeWidth/2).toFloat())
        }
        else {
            panelGraphics.color = UIConstants.edgeColor
            panelGraphics.stroke = BasicStroke((dualEdge.edge2.width/2).toFloat())
        }

        val arrow2 = mathProvider.calculateArrowForEdge(
            coordinates.second.first,
            coordinates.first.second
        )
        val weightPosition2 = mathProvider.calculateEdgeWeightTextPosition(coordinates.first.second,
            coordinates.second.first)
        panelGraphics.drawLine(
            coordinates.first.second.x,
            coordinates.first.second.y,
            coordinates.second.first.x,
            coordinates.second.first.y
        )
        drawEdgeArrow(arrow2, panelGraphics)
        panelGraphics.color = UIConstants.textColor
        panelGraphics.drawString(dualEdge.edge2.weight,
            weightPosition2.x, weightPosition2.y)
    }

    private fun drawBuildingEdge(buildingEdge: UIBuildingEdge, panelGraphics: Graphics2D)
    {
        panelGraphics.stroke = BasicStroke((buildingEdge.width/2).toFloat())
        panelGraphics.color = UIConstants.edgeColor
        panelGraphics.drawLine(buildingEdge.startCoordinate.x,
            buildingEdge.startCoordinate.y,
            buildingEdge.endCoordinate.x,
            buildingEdge.endCoordinate.y)
    }

    override fun mouseReleased(mouseEvent: MouseEvent) {
        when(currentGraphViewState)
        {
            is GraphViewState.CreatingEdgeState -> {
                //ничего не делаем, т.к. mouseClick обрабатывается ПОСЛЕ mouseReleased
            }

            is GraphViewState.CreatingEdgeAndSheetMovingState -> {
                currentGraphViewState = (currentGraphViewState as GraphViewState.CreatingEdgeAndSheetMovingState)
                    .creatingEdgeState
            }

            is GraphViewState.NodeDraggingState, is GraphViewState.SheetMovingState ->
            { currentGraphViewState = GraphViewState.DefaultState}


            else -> {
                currentGraphViewState = GraphViewState.DefaultState
            }

        }
    }

    override fun mouseEntered(mouseEvent: MouseEvent) { }

    //Нажатие любой кнопки мышки (и колёсика)
    @ExperimentalUnsignedTypes
    override fun mouseClicked(mouseEvent: MouseEvent) {
        when(mouseEvent.clickCount) {

            //одиночное нажатие
            1 -> {
                when(mouseEvent.button) {
                    //Правая кнопка
                    MouseEvent.BUTTON3 -> {
                        when(currentGraphViewState)
                        {
                            is GraphViewState.DefaultState -> {
                                if(isAlgorithmRunning) return

                                val node: UINode? = findNodeUnderMouse(Coordinate(mouseEvent.x, mouseEvent.y))
                                if(node != null)
                                    createAndShowPopupMenuOnNode(mouseEvent, node)

                                else {
                                    val edge: UIEdge? = findEdgeUnderMouse(Coordinate(mouseEvent.x, mouseEvent.y))
                                    edge ?: return

                                    createAndShowPopupMenuOnEdge(mouseEvent, edge)
                                }
                            }

                        }
                    }

                    //Левая кнопка
                    MouseEvent.BUTTON1 -> {

                        when(currentGraphViewState)
                        {
                            is GraphViewState.CreatingEdgeState -> {
                                val node: UINode? = findNodeUnderMouse(Coordinate(mouseEvent.x, mouseEvent.y))
                                if(node == null) {
                                    currentGraphViewState = GraphViewState.DefaultState
                                    repaint()
                                    return
                                }

                                val currentCreatingEdgeState = currentGraphViewState as GraphViewState.CreatingEdgeState

                                addEdge(currentCreatingEdgeState.sourceNode, node, currentCreatingEdgeState.edgeWeight.toString())

                                currentGraphViewState = GraphViewState.DefaultState
                            }
                        }
                    }

                }
            }

            //Двойной клик
            2 -> {
                //Левая кнопка
                if(mouseEvent.button == MouseEvent.BUTTON1)
                    if(currentGraphViewState is GraphViewState.DefaultState)
                    {
                        if(isAlgorithmRunning) return
                        else {
                            if(findNodeUnderMouse(Coordinate(mouseEvent.x, mouseEvent.y)) == null)
                                presenter.addNode(UINode(Coordinate(mouseEvent.x, mouseEvent.y)))
                        }
                    }
            }
        }
    }

    override fun mouseExited(mouseEvent: MouseEvent) { }

    override fun mousePressed(mouseEvent: MouseEvent) { }

    override fun mouseMoved(mouseEvent: MouseEvent) {
        if(findNodeUnderMouse(Coordinate(mouseEvent.x, mouseEvent.y)) != null)
        {
            setCursorHand()

        }
        else resetCursorToArrow()

        updateCreatingEdge(Coordinate(mouseEvent.x, mouseEvent.y))
    }

    override fun mouseDragged(mouseEvent: MouseEvent) {
        val dragCoordinate = Coordinate(mouseEvent.x, mouseEvent.y)

        if(SwingUtilities.isRightMouseButton(mouseEvent)){
            if (currentGraphViewState == GraphViewState.DefaultState ||
                currentGraphViewState is GraphViewState.SheetMovingState ||
                currentGraphViewState is GraphViewState.CreatingEdgeState ||
                currentGraphViewState is GraphViewState.CreatingEdgeAndSheetMovingState)
                onRightMouseButtonDragging(dragCoordinate)
        }

        if(SwingUtilities.isLeftMouseButton(mouseEvent)) {
            if (currentGraphViewState == GraphViewState.DefaultState ||
                    currentGraphViewState is GraphViewState.NodeDraggingState)
                onLeftMouseButtonDragging(dragCoordinate)
        }

        repaint()
    }

    private fun onRightMouseButtonDragging(dragCoordinate: Coordinate){
        when(currentGraphViewState)
        {
            GraphViewState.DefaultState, is GraphViewState.CreatingEdgeState-> {

                currentGraphViewState =
                    if(currentGraphViewState is GraphViewState.DefaultState)
                        GraphViewState.SheetMovingState(dragCoordinate)
                    else
                        GraphViewState.CreatingEdgeAndSheetMovingState(
                            currentGraphViewState as GraphViewState.CreatingEdgeState,
                            GraphViewState.SheetMovingState(dragCoordinate))

            }

            is GraphViewState.SheetMovingState, is GraphViewState.CreatingEdgeAndSheetMovingState -> {

                val currentSheetMovingState: GraphViewState.SheetMovingState =
                    if (currentGraphViewState is GraphViewState.SheetMovingState)
                        currentGraphViewState as GraphViewState.SheetMovingState
                    else (currentGraphViewState as GraphViewState.CreatingEdgeAndSheetMovingState).sheetMovingState

                val offsetX = dragCoordinate.x - currentSheetMovingState.draggingStartPoint.x
                val offsetY = dragCoordinate.y - currentSheetMovingState.draggingStartPoint.y

                sheetDraggingObserver?.onSheetDragged(offsetX, offsetY)
                updateCreatingEdge(dragCoordinate)
            }
        }

    }

    private fun onLeftMouseButtonDragging(dragCoordinate: Coordinate) {
        when(currentGraphViewState)
        {
            is GraphViewState.NodeDraggingState -> {
                val draggableState = currentGraphViewState as GraphViewState.NodeDraggingState

                draggableState.draggingNode.coordinate = dragCoordinate + draggableState.draggingOffset
            }

            is GraphViewState.DefaultState -> {
                val node: UINode? = findNodeUnderMouse(dragCoordinate)

                if(node == null) {
                    currentGraphViewState = GraphViewState.EmptyDraggingState
                    return
                }

                val coordinateOffset = node.coordinate - dragCoordinate
                currentGraphViewState = GraphViewState.NodeDraggingState(coordinateOffset, node)
            }

        }
    }

    private fun findNodeUnderMouse(cursorCoordinate: Coordinate): UINode? {
        nodes.forEach() {
            if(mathProvider.isPointInsideNodeCircle(cursorCoordinate, it))
            {
                return it
            }
        }
        return null
    }

    private fun findEdgeUnderMouse(cursorCoordinate: Coordinate) : UIEdge? {
        edges.forEach {
            if(mathProvider.isPointInsideEdgeRectangle(it, cursorCoordinate))
                return it
        }

        dualEdges.forEach {
            val edgesPoints = mathProvider.calculateDualEdgeCoordinates(it)

            if(mathProvider.isPointInsideEdgeRectangle(
                    edgesPoints.first.first, edgesPoints.second.second, cursorCoordinate))
                return it.edge1

            if(mathProvider.isPointInsideEdgeRectangle(
                    edgesPoints.first.second, edgesPoints.second.first, cursorCoordinate))
                return it.edge2
        }

        return null
    }

    private fun addEdge(sourceNode: UINode, endNode: UINode, edgeWeight: String) {
        presenter.addEdge(UIEdge(sourceNode, endNode, edgeWeight))
        repaint()
    }

    private fun updateCreatingEdge(newEndCoordinate: Coordinate) {
        when(currentGraphViewState) {
            is GraphViewState.CreatingEdgeState, is GraphViewState.CreatingEdgeAndSheetMovingState -> {
                val currentCreatingEdgeState: GraphViewState.CreatingEdgeState =
                    if (currentGraphViewState is GraphViewState.CreatingEdgeState)
                        currentGraphViewState as GraphViewState.CreatingEdgeState
                    else (currentGraphViewState as GraphViewState.CreatingEdgeAndSheetMovingState).creatingEdgeState

                currentCreatingEdgeState.creatingEdge.endCoordinate = newEndCoordinate
                repaint()
            }
        }
    }

    private fun setCursorHand() = run { cursor = Cursor.getPredefinedCursor(Cursor.HAND_CURSOR) }
    private fun resetCursorToArrow() = run { cursor = Cursor.getDefaultCursor() }

    @ExperimentalUnsignedTypes
    private fun createAndShowPopupMenuOnNode(sourceMouseEvent: MouseEvent, affectedNode: UINode) {
        val popupMenu = JPopupMenu()

        val addEdgeItem = JMenuItem("Добавить ребро")
        addEdgeItem.addActionListener {
            val edgeWeightString: String? = JOptionPane.showInputDialog(null, "Введите вес ребра",
                "Ввод веса ребра", JOptionPane.QUESTION_MESSAGE)

            if(edgeWeightString != null) {
                try {
                    val edgeWeight: UInt = edgeWeightString.toUInt()
                    currentGraphViewState = GraphViewState.CreatingEdgeState(affectedNode, edgeWeight.toInt())
                } catch (exception: NumberFormatException) {
                    JOptionPane.showMessageDialog(
                        null, "Вы ввели некорректное значение веса ребра",
                        "Ошибка ввода", JOptionPane.ERROR_MESSAGE
                    )
                }
            }
        }
        popupMenu.add(addEdgeItem)

        val removeNodeItem = JMenuItem("Удалить вершину")
        removeNodeItem.addActionListener { presenter.deleteNode(affectedNode) }
        popupMenu.add(removeNodeItem)

        popupMenu.show(sourceMouseEvent.component, sourceMouseEvent.x, sourceMouseEvent.y)
    }

    private fun createAndShowPopupMenuOnEdge(sourceMouseEvent: MouseEvent, affectedEdge: UIEdge)
    {
        val popupMenu = JPopupMenu()

        val removeEdgeItem = JMenuItem("Удалить ребро")
        removeEdgeItem.addActionListener { presenter.deleteEdge(affectedEdge)}
        popupMenu.add(removeEdgeItem)
        popupMenu.show(sourceMouseEvent.component, sourceMouseEvent.x, sourceMouseEvent.y)
    }

    override fun displayDijkstraAlgorithmResult(result: String) {
        val resultTextArea = JTextArea(result)
        resultTextArea.isEditable = false
        resultTextArea.lineWrap = true
        val scrollResultField = JScrollPane(resultTextArea)
        scrollResultField.preferredSize = Dimension(400, 150)
        JOptionPane.showMessageDialog(null, scrollResultField, "Результат алгоритма", JOptionPane.PLAIN_MESSAGE)

        val response = JOptionPane.showConfirmDialog(null, "Закончить алгоритм?",
            "Подтвердите действие", JOptionPane.YES_NO_OPTION)

        if(response == 0) {
            presenter.onAlgorithmEndConfirmed()
        }
    }

    override fun setAlgorithmRunningFlag(isAlgorithmRunning: Boolean) {
        this.isAlgorithmRunning = isAlgorithmRunning
    }
}