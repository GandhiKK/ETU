package views.toolbarview

import presenters.Event
import presenters.ToolbarPresenter
import presenters.ToolbarView
import presenters.ToolbarViewElement
import views.UIConstants
import java.awt.Color
import javax.swing.*
import javax.swing.border.EmptyBorder
import javax.swing.filechooser.FileNameExtensionFilter

class ToolbarView : JPanel(), ToolbarView {

    private val toolbarPresenter = ToolbarPresenter(this)

    private val btn1 = JButton("Запустить алгоритм")
    private val btn2 = JButton("Сохранить граф")
    private val btn3 = JButton("Загрузить граф")
    private val btn4 = JButton("Очистить сцену")
    private val btn5 = JButton("Предыдущий шаг алгоритма")
    private val btn6 = JButton("Следующий шаг алгоритма")
    private val btn7 = JButton("Сгенерировать граф")
    private val btn8 = JButton("Закончить алгоритм")

    private val logTextView = JTextArea()

    init {
        border = EmptyBorder(0, 10, 0,0)
        layout = BoxLayout(this, BoxLayout.Y_AXIS)

        btn1.addActionListener { toolbarPresenter.chainToolbarEvent(Event.OnStartAlgorithm)}
        add(btn1)
        add(Box.createVerticalStrut(UIConstants.spaceBetweenButtonsInToolbar))

        btn2.addActionListener {
            val filePath: String? = toolbarPresenter.getFilePath()

            if (filePath != null) {
                toolbarPresenter.chainToolbarEvent(Event.SaveGraph(filePath))
            }
        }
        add(btn2)
        add(Box.createVerticalStrut(UIConstants.spaceBetweenButtonsInToolbar))

        btn3.addActionListener {
            val filePath: String? = toolbarPresenter.getFilePath()

            if (filePath != null) {
                toolbarPresenter.chainToolbarEvent(Event.DownloadGraph(filePath))
            }
        }
        add(btn3)
        add(Box.createVerticalStrut(UIConstants.spaceBetweenButtonsInToolbar))

        btn4.addActionListener {
            toolbarPresenter.chainToolbarEvent(Event.Clear)
        }
        add(btn4)
        add(Box.createVerticalStrut(UIConstants.spaceBetweenButtonsInToolbar))

        btn5.addActionListener {
            toolbarPresenter.chainToolbarEvent(Event.PreviousStep)
        }
        add(btn5)
        add(Box.createVerticalStrut(UIConstants.spaceBetweenButtonsInToolbar))

        btn6.addActionListener {
            toolbarPresenter.chainToolbarEvent(Event.NextStep)
        }
        add(btn6)
        add(Box.createVerticalStrut(UIConstants.spaceBetweenButtonsInToolbar))

        btn7.addActionListener {
            toolbarPresenter.chainToolbarEvent(Event.GenerateGraph)
        }
        add(btn7)
        add(Box.createVerticalStrut(UIConstants.spaceBetweenButtonsInToolbar))


        btn8.addActionListener {
            toolbarPresenter.chainToolbarEvent(Event.EndAlgorithm)
        }
        add(btn8)
        add(Box.createVerticalStrut(UIConstants.spaceBetweenButtonsInToolbar))

        btn5.isEnabled = false
        btn6.isEnabled = false
        btn8.isEnabled = false


        logTextView.background = Color.WHITE
        logTextView.isEditable = true
        add(JScrollPane(logTextView))
        logTextView.lineWrap = true
        logTextView.font = UIConstants.logsOutputTextFont
        logTextView.text += ">> ${toolbarPresenter.getCurrentDateString()}\nПрограмма запущена\n"
    }

    override fun lockElement(element: ToolbarViewElement) {
        when (element) {
            ToolbarViewElement.START -> btn1.isEnabled = false
            ToolbarViewElement.SAVE -> btn2.isEnabled = false
            ToolbarViewElement.DOWNLOAD -> btn3.isEnabled = false
            ToolbarViewElement.CLEAR -> btn4.isEnabled = false
            ToolbarViewElement.NEXT_STEP -> btn5.isEnabled = false
            ToolbarViewElement.PREVIOUS_STEP -> btn6.isEnabled = false
            ToolbarViewElement.GENERATE -> btn7.isEnabled = false
            ToolbarViewElement.END_ALGORITHM -> btn8.isEnabled = false
        }
    }

    override fun unlockElement(element: ToolbarViewElement) {
        when (element) {
            ToolbarViewElement.START -> btn1.isEnabled = true
            ToolbarViewElement.SAVE -> btn2.isEnabled = true
            ToolbarViewElement.DOWNLOAD -> btn3.isEnabled = true
            ToolbarViewElement.CLEAR -> btn4.isEnabled = true
            ToolbarViewElement.NEXT_STEP -> btn5.isEnabled = true
            ToolbarViewElement.PREVIOUS_STEP -> btn6.isEnabled = true
            ToolbarViewElement.GENERATE -> btn7.isEnabled = true
            ToolbarViewElement.END_ALGORITHM -> btn8.isEnabled = true
        }
    }

    override fun getFilePath() : String? {
        val fileChooser = JFileChooser()
        fileChooser.fileFilter = FileNameExtensionFilter(".txt", "txt")
        fileChooser.isAcceptAllFileFilterUsed = false
        val action = fileChooser.showDialog(null, "Выберите файл")

        if (action == JFileChooser.APPROVE_OPTION)
        {
            val file = fileChooser.selectedFile

            return if (file.exists()) file.absolutePath
            else {
                "${file.absolutePath}.txt"
            }
        }

        return null
    }

    override fun showLog(logMsg: String) {
        logTextView.text += ">> $logMsg"
    }
}