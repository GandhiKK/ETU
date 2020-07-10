import views.MainWindow
import java.awt.Dimension
import javax.swing.JFrame

class Main {
    companion object{
        @JvmStatic
        fun main(args: Array<String>) {
            val frame = JFrame()
            frame.size = Dimension(1200, 800)

            frame.extendedState = JFrame.MAXIMIZED_BOTH;
            frame.defaultCloseOperation = JFrame.EXIT_ON_CLOSE

            frame.add(MainWindow())
            frame.isVisible = true
        }
    }
}