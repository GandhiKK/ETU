package views

import presenters.MainPresenter
import views.graphview.GraphViewHolder
import views.toolbarview.ToolbarView
import java.awt.BorderLayout
import java.awt.Dimension
import javax.swing.JPanel
import javax.swing.border.EmptyBorder

class MainWindow : JPanel() {
    init {
        layout = BorderLayout()
        border = EmptyBorder(10, 10, 10,10)

        val graphViewHolder = GraphViewHolder()
        add(graphViewHolder)

        val toolbarView = ToolbarView()
        toolbarView.preferredSize = Dimension(325, 200)
        add(toolbarView, BorderLayout.EAST)
    }
}