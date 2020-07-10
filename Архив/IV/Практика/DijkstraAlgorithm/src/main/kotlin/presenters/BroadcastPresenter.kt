package presenters

interface EventSubscriber {
    fun handleEvent(event: Event)
}


object BroadcastPresenter {

    private val subscribers = ArrayList<EventSubscriber>()

    fun registerSubscriber(subscriber: EventSubscriber) {
        subscribers.add(subscriber)
    }

    fun generateEvent(event: Event) {
        subscribers.forEach() { it.handleEvent(event) }
    }
}