package presenters

import java.io.File
import java.util.*

enum class ToolbarViewElement {
    START,
    SAVE,
    DOWNLOAD,
    CLEAR,
    NEXT_STEP,
    PREVIOUS_STEP,
    GENERATE,
    END_ALGORITHM
}

interface ToolbarView {
    fun lockElement(element: ToolbarViewElement)
    fun unlockElement(element: ToolbarViewElement)
    fun getFilePath() : String?
    fun showLog(logMsg: String)
}

class ToolbarPresenter(private val toolbarView: ToolbarView) : EventSubscriber {

    fun chainToolbarEvent(event: Event) {
        BroadcastPresenter.generateEvent(event)
    }

    init {
        BroadcastPresenter.registerSubscriber(this)
    }

    override fun handleEvent(event: Event) {
        when (event) {
            is Event.AfterAlgorithmStarted -> {
                toolbarView.unlockElement(ToolbarViewElement.NEXT_STEP)
                toolbarView.unlockElement(ToolbarViewElement.PREVIOUS_STEP)
                toolbarView.unlockElement(ToolbarViewElement.END_ALGORITHM)
            }

            is Event.AfterAlgorithmEnded -> {
                toolbarView.lockElement(ToolbarViewElement.NEXT_STEP)
                toolbarView.lockElement(ToolbarViewElement.PREVIOUS_STEP)
                toolbarView.lockElement(ToolbarViewElement.END_ALGORITHM)
            }

            is Event.LogEvent -> {
                toolbarView.showLog(getCurrentDateString() + "\n" + event.logInfo + "\n")
            }
        }
    }

    fun getCurrentDateString() : String { return Date().toString() }

    fun getFilePath() = toolbarView.getFilePath()
}