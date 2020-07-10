package views.graphview

import presenters.MainPresenter
import views.UIConstants
import java.awt.Dimension
import javax.swing.JScrollPane
import javax.swing.ScrollPaneConstants

class GraphViewHolder : JScrollPane(GraphSheet()), GraphViewObserver {

    init {

        //достаём переданный graphview
        (viewport.view as GraphSheet).sheetDraggingObserver = this
        viewport.view.preferredSize = Dimension(UIConstants.graphScreenSheetWidth, UIConstants.graphScreenSheetHeight)

        horizontalScrollBarPolicy = ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS
        verticalScrollBarPolicy = ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS

        verticalScrollBar.unitIncrement = UIConstants.verticalScrollIncrement
        horizontalScrollBar.unitIncrement = UIConstants.horizontalScrollIncrement
    }

    override fun onSheetDragged(offsetX: Int, offsetY: Int) {
        horizontalScrollBar.value -= offsetX
        verticalScrollBar.value -= offsetY
    }
}