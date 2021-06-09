package presenters

sealed class Event {
    //Нажатие на кнопку начать алгоритм
    object OnStartAlgorithm : Event()
    //Подтверждение начала алгоритма (выбор стартовой вершины и запуск)
    object AfterAlgorithmStarted : Event()

    //Полное завершение работы с алгоритмом (после подтверждения)
    object AfterAlgorithmEnded : Event()

    class SaveGraph(val fileName: String): Event()
    class DownloadGraph (val fileName: String): Event()
    object Clear : Event()
    object PreviousStep : Event()
    object NextStep : Event()
    object GenerateGraph : Event()
    object EndAlgorithm : Event()

    class LogEvent(val logInfo: String) : Event()
}