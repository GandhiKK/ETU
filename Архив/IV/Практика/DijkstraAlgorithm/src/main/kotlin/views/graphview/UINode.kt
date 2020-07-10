package views.graphview

import views.UIConstants

class UINode(
    var coordinate: Coordinate
) {
    val radius = UIConstants.circleRadius + UIConstants.circleStrokeWidth
    var isActive: Boolean = false
    var bestWay: String = "-"
    var nodeFrom: String = "-"

    fun reset() {
        isActive = false
        bestWay = "-"
        nodeFrom = "-"
    }


    override fun toString() = "${coordinate.x}, ${coordinate.y}"

}