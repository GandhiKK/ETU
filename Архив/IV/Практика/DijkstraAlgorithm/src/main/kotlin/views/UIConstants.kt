package views

import com.sun.org.apache.xpath.internal.functions.FunctionOneArg
import java.awt.Color
import java.awt.Font

object UIConstants {
    const val circleRadius = 32
    const val circleStrokeWidth = 3
    const val spaceBetweenButtonsInToolbar = 5
    const val spaceBetweenContentInParametersRequester = 5
    const val graphScreenSheetWidth = 3000
    const val graphScreenSheetHeight = 3000
    const val horizontalScrollIncrement = 20
    const val verticalScrollIncrement = 20
    const val edgeWidth = 6
    const val activeEdgeWidth = 12
    const val arrowHeight = 10
    const val arrowWidth = 10
    const val edgeWeightTextOffsetHeight = 25

    const val dualEdgeRotationAngleInGrads = Math.PI / 4

    val nodeFillColor = Color(106, 233, 114)
    val passedNodeFillColor = Color(232, 233, 33)
    val nodeActiveFillColor = Color(233, 85, 87)
    val nodeStrokeFillColor = Color(112, 112, 112)
    val activeNodeTextColor = Color(255, 255, 255)
    val textColor = Color(112, 112, 112)
    val edgeColor = Color(112, 112, 112)
    val activeEdgeColor = Color(120, 115, 235)

    val nodeTextFont = Font("Segoe UI", Font.PLAIN, 40)
    val edgeWeightTextFont = Font("Segoe UI", Font.PLAIN, 20)
    val nodeSignTextFont = Font("Segoe UI", Font.PLAIN, 15)
    val logsOutputTextFont = Font("Sans Serif", Font.PLAIN, 15)

    const val areaChooseCoordinateUnit = 100
    const val areaChooseSquareSize = 10
    const val areaPickerScreenWidth = graphScreenSheetWidth / areaChooseSquareSize
    const val areaPickedScreenHeight = graphScreenSheetHeight / areaChooseSquareSize
}