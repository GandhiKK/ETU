package views.graphview

import java.awt.GridLayout
import javax.swing.JComboBox
import javax.swing.JLabel
import javax.swing.JPanel
import javax.swing.JTextField

class EndNodeRequestPane(numbersRange: ArrayList<Int>) : JPanel() {

    val startNodeNumber = JComboBox(numbersRange.toArray())

    init {
        layout = GridLayout(2, 2)

        val startNodeTextField = JLabel("Начальная вершина: ")

        add(startNodeTextField)
        add(startNodeNumber)
    }
}