package views.graphview

sealed class GraphViewState {
    object DefaultState : GraphViewState()
    class NodeDraggingState(val draggingOffset: Coordinate, val draggingNode: UINode) : GraphViewState()
    class SheetMovingState(val draggingStartPoint: Coordinate) : GraphViewState()
    object EmptyDraggingState : GraphViewState()

    class CreatingEdgeState(val sourceNode: UINode, val edgeWeight: Int): GraphViewState() {
        val creatingEdge = UIBuildingEdge(sourceNode.coordinate, sourceNode.coordinate)
    }

    class CreatingEdgeAndSheetMovingState(val creatingEdgeState: CreatingEdgeState,
                                          val sheetMovingState: SheetMovingState) : GraphViewState()

}