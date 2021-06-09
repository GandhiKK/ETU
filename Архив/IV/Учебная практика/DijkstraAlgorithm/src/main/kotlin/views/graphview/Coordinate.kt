package views.graphview

data class Coordinate(
    val x: Int,
    val y: Int
) {
    operator fun minus(anotherCoordinate: Coordinate) : Coordinate {
        return Coordinate(x - anotherCoordinate.x, y - anotherCoordinate.y)
    }

    operator fun plus(anotherCoordinate: Coordinate) : Coordinate {
        return Coordinate(x + anotherCoordinate.x, y + anotherCoordinate.y)
    }
}