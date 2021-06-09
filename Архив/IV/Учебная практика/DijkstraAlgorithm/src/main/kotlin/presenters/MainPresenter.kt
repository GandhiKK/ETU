package presenters

import models.Edge
import models.Graph
import views.UIConstants
import views.graphview.*
import java.io.File
import java.util.*
import javax.swing.JOptionPane
import kotlin.collections.ArrayList
import kotlin.collections.HashMap

interface GraphView {
    fun update()
    fun displayDijkstraAlgorithmResult(result: String)
    fun setAlgorithmRunningFlag(isAlgorithmRunning: Boolean)
}

class MainPresenter(
    private val graphView: GraphView
) : EventSubscriber {

    init {
        BroadcastPresenter.registerSubscriber(this)
    }

    private fun printLogs(log:String){
        val logEvent = Event.LogEvent(log)
        BroadcastPresenter.generateEvent(logEvent)
    }

    fun onAlgorithmEndConfirmed() {
        resetNodesAndEdges()
        graphView.setAlgorithmRunningFlag(false)
        graphView.update()
        BroadcastPresenter.generateEvent(Event.AfterAlgorithmEnded)
    }

    override fun handleEvent(event: Event) {
        when (event) {
            is Event.OnStartAlgorithm -> {

                val node: Int? = requestStartNodeNumber()

                if (node != null) {
                    printLogs("Алгоритм запущен")
                    resetNodesAndEdges()
                    graphView.setAlgorithmRunningFlag(true)
                    BroadcastPresenter.generateEvent(Event.AfterAlgorithmStarted)
                    startAlgorithm(node)
                    graphView.update()
                }
                else {
                    return
                }
            }
            is Event.Clear -> {
                clearScene()
                printLogs("Выполнена очистка сцены")
            }
            is Event.NextStep->{
                nextStep()
            }

            is Event.PreviousStep->{
                previousStep()
            }
            is Event.DownloadGraph->{
                printLogs("Загрузка графа из файла ${event.fileName}")
                downloadGraph(event.fileName)
            }
            is Event.SaveGraph->{
                printLogs("Сохранение графа в файл ${event.fileName}")
                saveGraph(event.fileName)
            }
            is Event.EndAlgorithm-> {
                printLogs("Окончание алгоритма\nПосещены все вершины, до которых\nсуществует путь от стартовой вершины")
                finishAlgorithm()
            }
            is Event.GenerateGraph->{
                requestGeneratingGraphParameters()
            }
        }
    }

    private fun requestGeneratingGraphParameters(){
        val parametersRequester = GeneratingGraphParametersRequestPane()
        val responseCode = JOptionPane.showConfirmDialog(
            null, parametersRequester, "Данные генерации", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE)

        when (responseCode) {
            0 -> {
                val density = parametersRequester.paramPanel.densitySlider.value
                val verticiesAmount = parametersRequester.paramPanel.verticesAmountSpinner.value.toString().toInt()
                val offset = parametersRequester.areaPicker.squareZoomFactor * UIConstants.areaChooseCoordinateUnit
                generateGraph(density,verticiesAmount,offset)
               graphView.update()
            }
        }

    }

    private fun clearScene() {
        nodes.clear()
        dualEdges.clear()
        edges.clear()
        graphView.setAlgorithmRunningFlag(false)
        graphView.update()
    }

    private fun resetNodesAndEdges() {
        nodes.forEach { it.reset() }
        dualEdges.forEach{
            it.edge1.reset()
            it.edge2.reset()
        }
        edges.forEach {
            it.reset()
        }
    }

    private fun requestStartNodeNumber() : Int? {
        val numbers = ArrayList<Int>()
        for(i in 1..nodes.size)
            numbers.add(i)
        val optionsHolder = EndNodeRequestPane(numbers)
        val responseCode =
            JOptionPane.showConfirmDialog(null, optionsHolder, "Исходные данные", JOptionPane.OK_CANCEL_OPTION)

        return when (responseCode) {
            //Нажата "Ок"
            0 -> {
                if (numbers.size == 0) null
                else numbers[optionsHolder.startNodeNumber.selectedIndex]
            }
            else -> {
                null
            }
        }
    }

    val nodes = ArrayList<UINode>()
    val edges = ArrayList<UIEdge>()
    val dualEdges = ArrayList<UIDualEdge>()
    private val dijkstraAlgorithmController = DijkstraAlgorithmController()

    fun addNode(new:UINode){
        nodes.add(new)
        graphView.update()
    }

    fun addEdge(new:UIEdge){
        for (e in edges) {
            if (new.sourceNode == e.sourceNode && new.endNode == e.endNode)
                return
        }
        for(e in edges)
        {
            if(new.sourceNode == e.endNode && new.endNode == e.sourceNode) {
                dualEdges.add(UIDualEdge(new, e))
                edges.remove(e)
                graphView.update()
                return
            }
        }
        
        for(dualEdge in dualEdges) {
            if (dualEdge.edge1.sourceNode == new.sourceNode && dualEdge.edge1.endNode == new.endNode
                || dualEdge.edge2.sourceNode == new.sourceNode && dualEdge.edge2.endNode == new.endNode)
                return
        }
        
        edges.add(new)
        graphView.update()
    }


    fun addEdge_(new:UIEdge){
        for (e in edges) {
            if (new.sourceNode == e.sourceNode && new.endNode == e.endNode)
                return
        }
        for(e in edges)
        {
            if(new.sourceNode == e.endNode && new.endNode == e.sourceNode) {
                dualEdges.add(UIDualEdge(new, e))
                edges.remove(e)
                graphView.update()
                return
            }
        }
        edges.add(new)
    }

    fun deleteEdge(deleted:UIEdge){
        val isDeleted = edges.remove(deleted)
        if(!isDeleted)
        {
            dualEdges.forEach {
                if(it.edge1 == deleted){
                    edges.add(it.edge2)
                    dualEdges.remove(it)
                    graphView.update()
                    return
                }
                if(it.edge2 == deleted)
                {
                    edges.add(it.edge1)
                    dualEdges.remove(it)
                    graphView.update()
                    return
                }
            }
        }
        else graphView.update()
    }

    fun deleteNode(deleted:UINode){
        val removableEdges = ArrayList<UIEdge>()
        for (e in edges){
            if (e.sourceNode == deleted || e.endNode == deleted)
                removableEdges.add(e)
        }
        edges.removeAll(removableEdges)

        val removableDualEdges = ArrayList<UIDualEdge>()
        dualEdges.forEach {
            if(it.edge1.sourceNode == deleted || it.edge2.sourceNode == deleted) {
                removableDualEdges.add(it)
            }
        }
        dualEdges.removeAll(removableDualEdges)

        nodes.remove(deleted)
        graphView.update()
    }

    private fun isNodeHaveEdges(startNode:Int):Boolean{
        for(e in edges)
            if (nodes.indexOf(e.sourceNode) == startNode || nodes.indexOf(e.endNode) == startNode)
                return true

        for(e in dualEdges)
            if (nodes.indexOf(e.edge1.sourceNode) == startNode || nodes.indexOf(e.edge1.endNode) == startNode || nodes.indexOf(e.edge2.sourceNode) == startNode || nodes.indexOf(e.edge2.endNode) == startNode)
                return true

        return false
    }


    private fun isAllNodesConnected(): String {
        val goodNodes:TreeSet<Int> = TreeSet()
        for (n in nodes){
            for(e in edges){
                if (e.sourceNode == n || e.endNode == n)
                    goodNodes.add(nodes.indexOf(n)+1)
            }
            for (e in dualEdges){
                if (e.edge1.sourceNode == n || e.edge1.endNode ==n||e.edge2.sourceNode==n||e.edge2.endNode==n)
                    goodNodes.add(nodes.indexOf(n)+1)
            }
        }
        goodNodes.toSortedSet()
        val allNodes = ArrayList<Int>()
        val badNodes = ArrayList<Int>()
        for (n in nodes){
            allNodes.add(nodes.indexOf(n)+1)
            badNodes.add(nodes.indexOf(n)+1)
        }
        for (n in allNodes){
            for(n_ in goodNodes){
                if (n ==n_){
                    badNodes.remove(n)
                }
            }
        }
       return badNodes.joinToString()
    }


    private fun startAlgorithm(startNode:Int){ //где хранить конечный и начальный узел
        //проверка на существование вершины в массиве ребер
        if (!isNodeHaveEdges(startNode-1)){
            printLogs("Данная вершина не имеет ребер\nАлгоритм прерван")
            onAlgorithmEndConfirmed()
            return
        }
        val emptyNodes = isAllNodesConnected()
        if (emptyNodes.isNotEmpty()){
            printLogs("Соедините вершины:\n$emptyNodes\nАлгоритм прерван")
            onAlgorithmEndConfirmed()
            return
        }

        val gr= ArrayList<Edge>()
        for (e in edges){
            gr.add(Edge(nodes.indexOf(e.sourceNode),nodes.indexOf(e.endNode),e.weight.toInt()))
        }
        for (e in dualEdges){
            gr.add(Edge(nodes.indexOf(e.edge1.sourceNode),nodes.indexOf(e.edge1.endNode),e.edge1.weight.toInt()))
            gr.add(Edge(nodes.indexOf(e.edge2.sourceNode),nodes.indexOf(e.edge2.endNode),e.edge2.weight.toInt()))
        }

        val graph = Graph(gr)
        graph.dijkstra(startNode-1) //прогнали алгоритм
        dijkstraAlgorithmController.initStart(startNode,graph.getSnapshotHistory(),graph.getPath(startNode)) // здесь принимаю ответ
    }

    private fun updateAllNodes(snapMap:HashMap<Int,List<String>>){
        // snapMap[0][0] - текущий узел, snapMap[0][1] - prevNode, snapMap[0][2] - relax
        // snapMap[3+] - список из 3 элементов, где элемент с индексом 0 - номер вершины, 1 - текущее лучшее расстояние до нее, 2 - номер вершины, из которого пришли в текущую

        val curNode = snapMap[0]!![0].toInt()
        val prevNode = snapMap[0]!![1].toInt()

        nodes[curNode].isActive = true
        for (i in 1 until snapMap.size){
            nodes[snapMap[i]!![0].toInt()].bestWay = snapMap[i]!![1]
            nodes[snapMap[i]!![0].toInt()].nodeFrom = snapMap[i]!![2]
        }

        //выделяем ребро
        for (e in edges){
            if (nodes.indexOf(e.endNode) == curNode && nodes.indexOf(e.sourceNode)==prevNode){
                e.isActive = true
                return
            }
        }
        for (e in dualEdges){
            if (nodes.indexOf(e.edge1.endNode) == curNode && nodes.indexOf(e.edge1.sourceNode)==prevNode) {
                e.edge1.isActive = true
                return
            }
            if (nodes.indexOf(e.edge2.endNode) == curNode && nodes.indexOf(e.edge2.sourceNode)==prevNode) {
                e.edge2.isActive = true
                return
            }
        }
    }

    private fun getLogs(snapMap:HashMap<Int,List<String>>):String{
        val logs = StringBuilder("")
        val indexCurNode = snapMap[0]!![0].toInt() +1
        val prevNode = snapMap[0]!![1].toInt() +1
        val isRelax = snapMap[0]!![2].toBoolean()

        if (snapMap[indexCurNode]!![2].toInt() == indexCurNode){
            logs.append("Исходная вершина")
            return logs.toString()
        }
        logs.append("Ребро: (${prevNode},${indexCurNode})\n")
        if (isRelax){
            logs.append("Произошла релаксация\n")
        }
        else{
            logs.append("Не произошла релаксация\n")
        }
        var prevBestWay = ""
        val previousSnapMap = dijkstraAlgorithmController.getPreviousSnap()?.toMap()
        if (previousSnapMap!=null){
            prevBestWay = previousSnapMap[indexCurNode]!![1]
        }
        logs.append("Лучшее расстояние до узла: ${snapMap[indexCurNode]!![1].toInt()} (было $prevBestWay)")
        return logs.toString()
    }

    private fun nextStep(){
        if (!dijkstraAlgorithmController.isNextStepPossible()){
            printLogs("Посещены все вершины, до которых\nсуществует путь от стартовой вершины\nСледующий шаг невозможен\nТекущий шаг последний")
            return
        }
        printLogs("Выполнен следующий шаг")

        resetNodesAndEdges()

        val snapMap = dijkstraAlgorithmController.getNextStep()?.toMap()

        if (snapMap==null){
            printLogs("Ошибка со снимками")
            return
        }
        updateAllNodes(snapMap)

        val logEvent = Event.LogEvent(getLogs(snapMap))
        BroadcastPresenter.generateEvent(logEvent)

        graphView.update()
    }

    private fun previousStep(){
        if (!dijkstraAlgorithmController.isPreviousStepPossible()){
            printLogs("Предыдущий шаг невозможен:\nТекущий шаг первый")
            return
        }
        printLogs("Выполнен предыдущий шаг")
        resetNodesAndEdges()
        val snapMap = dijkstraAlgorithmController.getPreviousStep()?.toMap()

        if (snapMap==null){
            printLogs("Ошибка со снимками")
            return
        }

        updateAllNodes(snapMap)

        val logEvent = Event.LogEvent(getLogs(snapMap))
        BroadcastPresenter.generateEvent(logEvent)
        graphView.update()
    }

    private fun finishAlgorithm(){
        resetNodesAndEdges()
        val snapMap = dijkstraAlgorithmController.getLast()?.toMap()

        if (snapMap==null){
            printLogs("Ошибка со снимками")
            return
        }

        updateAllNodes(snapMap)
        graphView.displayDijkstraAlgorithmResult(dijkstraAlgorithmController.answer)

        //printLogs("Результат работы:\n${dijkstraAlgorithmController.answer}")

        graphView.update()
    }

    private fun downloadGraph(fileName:String) {
        val file = File(fileName)
        if(!file.exists()) {
            printLogs("Ошибка в чтении файла, файл не существует")
            return
        }

        val fileHandler = GraphFileHandler(fileName)
        val graphInfo = fileHandler.downloadGraphInfo()
        if (graphInfo==null){
            printLogs("Ошибка в чтении файла, неверный формат")
            return
        }

        nodes.clear()
        edges.clear()
        dualEdges.clear()

        //graphInfo.first - информация о вершинах, graphInfo.second - информация о ребрах
        //инициализируем вершины
        for (n in graphInfo.first!!) {
            addNode(UINode(Coordinate(n[0].toInt(), n[1].toInt())))
        }
        //инициализируем ребра
        if (graphInfo.second != null) //если есть информация о ребрах
            for (e in graphInfo.second!!) {
                addEdge(UIEdge(nodes[e[0].toInt()], nodes[e[1].toInt()], e[2]))
            }
        graphView.update()
    }

    override fun toString():String{
        //создаем строку из графа
        val graphAsString = StringBuilder("")
        for (n in nodes)
            graphAsString.append("($n), ")
        if(graphAsString.isEmpty()){
            return ""
        }
        graphAsString.delete(graphAsString.length - 2, graphAsString.length).append("")
        graphAsString.append("\n")
        for (e in edges)
            graphAsString.append("(${nodes.indexOf(e.sourceNode)}, ${nodes.indexOf(e.endNode)}, ${e.weight}), ")
        for (e in dualEdges){
            graphAsString.append("(${nodes.indexOf(e.edge1.sourceNode)}, ${nodes.indexOf(e.edge1.endNode)}, ${e.edge1.weight}), ")
            graphAsString.append("(${nodes.indexOf(e.edge2.sourceNode)}, ${nodes.indexOf(e.edge2.endNode)}, ${e.edge2.weight}), ")
        }
        if(!(edges.isEmpty() && dualEdges.isEmpty()))
            graphAsString.delete(graphAsString.length - 2, graphAsString.length).append("")
        return graphAsString.toString()
    }

    private fun saveGraph(fileName:String){
        val graphAsString = this.toString()
        if (graphAsString.isEmpty()){
            printLogs("Ошибка в чтении файла, неверный формат")
            return
        }
        //Записываем в файл
        val fileHandler = GraphFileHandler(fileName)
        fileHandler.saveGraphInfo(graphAsString)
    }

    private fun generateGraph(density_:Int,verticiesAmount:Int,offset:Int){
        nodes.clear()
        dualEdges.clear()
        edges.clear()

        val range = offset/100 - 2
        val numbNodes = verticiesAmount
        val density =(Math.ceil(((numbNodes-1)*density_.toDouble())/100)).toInt()
        val weight = 100
        val randomNodes = ArrayList<Coordinate>()
        for(i in 1..range){
            for (j in 1..range){
                randomNodes.add(Coordinate(i*100,j*100))
            }
        }
        //генерируем узлы
        for (i in 0 .. numbNodes-1){
            val randN = (0 .. randomNodes.size-1).random()
            nodes.add(UINode((randomNodes[randN])))
            randomNodes.remove(randomNodes[randN])
        }
        val new= ArrayList<Int>()
        //генерируем ребра
        for (n in nodes){
            new.clear()
            for (i in 0 until nodes.size) {
                new.add(i)
            }
            new.remove(nodes.indexOf(n))
            for(i in 1..density){
                val randC = (0 until new.size).random()
                val randW = (1..weight).random().toString()
                addEdge_(UIEdge(n,nodes[new[randC]],randW))
                new.remove(new[randC])
            }
        }
    }
}
