package models

import org.junit.jupiter.api.Assertions
import org.junit.jupiter.api.Assertions.*
import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.function.Executable
import java.util.*
import javax.xml.stream.events.StartDocument
import kotlin.collections.HashMap
import kotlin.properties.Delegates
import org.junit.jupiter.api.DynamicTest
import org.junit.jupiter.api.DynamicTest.dynamicTest
import org.junit.jupiter.api.TestFactory

internal class GraphTest() {

    lateinit var GRAPH: kotlin.collections.List<Edge>
    var START: Int = 0
    var END: Int = 0

    @org.junit.jupiter.api.BeforeEach
    fun setUp(){
        GRAPH = listOf(
            Edge(1, 2, 7),
            Edge(1, 3, 9),
            Edge(2, 3, 1)
        )
        START = 1
        END = 3
    }

    @org.junit.jupiter.api.AfterEach
    fun tearDown() {
        if(GRAPH.isNotEmpty())
            GRAPH = listOf(
                Edge(1, 1, 0)
            )
    }

    @Test
    fun testCorrectEdges() {
        with(Graph(GRAPH)){
            dijkstra(START)
            assertTrue(edges::isNotEmpty)
            assertEquals(3, edges.size)
        }
    }

    @Test
    fun testCorrectGraph() {
        with(Graph(GRAPH)){
            dijkstra(START)
            assertTrue(graph::isNotEmpty)
            assertEquals(2, graph[1]!!.neighbours.size)
            assertEquals(1, graph[2]!!.neighbours.size)
            assertEquals(0, graph[3]!!.neighbours.size)
            assertTrue{
                graph[1]!!.dist < Int.MAX_VALUE && graph[1]!!.dist >= 0
                graph[2]!!.dist < Int.MAX_VALUE && graph[2]!!.dist >= 0
                graph[3]!!.dist < Int.MAX_VALUE && graph[3]!!.dist >= 0
            }
            assertEquals(0, graph[1]!!.dist)
            assertEquals(8, graph[3]!!.dist) //поменялось минимальное расстояние а процессе алгоритма
            assertEquals(2, graph[3]!!.previous?.name)
            assertEquals(1, graph[2]!!.previous?.name)
        }
    }
}


internal class IncorrectGraphTest() {

    lateinit var GRAPH: kotlin.collections.List<Edge>
    var START: Int = 0
    var END: Int = 0

    @org.junit.jupiter.api.BeforeEach
    fun setUp(){
        START = 1
        END = 3
    }

    @Test
    fun testCorrectDist() {
        val exception = assertThrows(IllegalArgumentException::class.java) {
            Edge(1, 2, -3)
        }
        assertEquals("Dist < 0", exception.message)
    }

    @Test
    fun testCorrectVertex() {
        val exceptionVertex1 = assertThrows(IllegalArgumentException::class.java) {
            Edge(1, -2, 3)
        }
        val exceptionVertex2 = assertThrows(IllegalArgumentException::class.java) {
            Edge(-1, 2, 3)
        }
        assertEquals("Value < 0", exceptionVertex1.message)
        assertEquals("Value < 0", exceptionVertex2.message)
    }

    @Test
    fun testCorrectStartVertex() {
        GRAPH = listOf(
            Edge(1, 2, 7),
            Edge(1, 3, 9),
            Edge(2, 3, 1)
        )
        START = -1
        END = 3
        with(Graph(GRAPH)) {
            dijkstra(START)
            assertEquals("Граф не содержит стартовую вершину '${START}'", testOutput)
        }
    }

    @Test
    fun testCorrectEndVertex() {
        GRAPH = listOf(
            Edge(1, 2, 7),
            Edge(1, 3, 9),
            Edge(2, 3, 1)
        )
        START = 1
        END = 4
        with(Graph(GRAPH)) {
            val str = printPath(END)
            assertEquals("Граф не содержит конечную вершину '${END}'", str)
        }
    }
}


internal class IncorrectAutoGraphTest() {

    lateinit var GRAPH: kotlin.collections.List<Edge>
    var START: Int = 0
    var END: Int = 0

    @org.junit.jupiter.api.BeforeEach
    fun setUp(){
        GRAPH = listOf(
            Edge(1, 2, 7),
            Edge(1, 3, 9),
            Edge(2, 3, 1)
        )
    }

    @TestFactory
    fun autoTestCorrectEndVertex() = listOf(
        -1 to "Граф не содержит конечную вершину '-1'",
         2 to "не существует",
         6 to "Граф не содержит конечную вершину '6'"
    ).map { (input, expected) ->
        dynamicTest("Конечная вершина $input: $expected") {
            with(Graph(GRAPH)) {
                START = 1
                val str = printPath(input)
                assertEquals(expected, str)
                testOutput = ""
            }
        }
    }

    @TestFactory
    fun autoTestCorrectStartVertex() = listOf(
        -11 to "Граф не содержит стартовую вершину '-11'",
        1 to "",
        66 to "Граф не содержит стартовую вершину '66'"
    ).map { (input, expected) ->
        dynamicTest("Стартовая вершина $input: $expected") {
            with(Graph(GRAPH)) {
                END = 3
                dijkstra(input)
                assertEquals(expected, testOutput)
                testOutput = ""
            }
        }
    }
}


internal class DijkstraAlgorithmTest(){
    lateinit var GRAPH1: kotlin.collections.List<Edge>
    lateinit var GRAPH2: kotlin.collections.List<Edge>
    lateinit var GRAPH3: kotlin.collections.List<Edge>
    lateinit var GRAPH4: kotlin.collections.List<Edge>
    lateinit var GRAPH5: kotlin.collections.List<Edge>
    var START: Int = 1
    var END: Int = 5

    @org.junit.jupiter.api.BeforeEach
    fun setUp(){
        GRAPH1 = listOf(
            Edge(1, 2, 7),
            Edge(1, 3, 9),
            Edge(1, 6, 14),
            Edge(2, 3, 10),
            Edge(2, 4, 15),
            Edge(3, 4, 11),
            Edge(3, 6, 2),
            Edge(4, 5, 6),
            Edge(5, 6, 9)
        )
        GRAPH2 = listOf(
            Edge(1,7,2),
            Edge(1,2,4),
            Edge(1,4,6),
            Edge(2,3,5),
            Edge(3,4,6),
            Edge(3,6,6),
            Edge(7,6,4),
            Edge(6,5,1),
            Edge(1,6,8),
            Edge(1,5,15),
            Edge(4,5,8)
        )
        GRAPH3 = listOf(
            Edge(1,7,2),
            Edge(1,2,4),
            Edge(1,4,4),
            Edge(2,3,5),
            Edge(3,4,6),
            Edge(3,6,6),
            Edge(7,6,4),
            Edge(6,5,1),
            Edge(1,6,8),
            Edge(1,5,15),
            Edge(4,5,2)
        )
        GRAPH4 = listOf(
            Edge(1,7,2),
            Edge(1,2,1),
            Edge(1,4,4),
            Edge(2,3,5),
            Edge(3,4,6),
            Edge(3,6,6),
            Edge(7,6,4),
            Edge(6,5,1),
            Edge(1,6,8),
            Edge(1,5,15),
            Edge(4,5,2),
            Edge(2,8,1),
            Edge(8,3,1),
            Edge(3,5,1)
        )
        GRAPH5 = listOf(
            Edge(1,2,1),
            Edge(1,9,8),
            Edge(1,8,6),
            Edge(2,9,9),
            Edge(2,10,5),
            Edge(2,3,15),
            Edge(3,4,5),
            Edge(4,5,1),
            Edge(6,5,3),
            Edge(7,6,9),
            Edge(8,7,5),
            Edge(9,7,7),
            Edge(9,6,8),
            Edge(9,5,9),
            Edge(9,10,7),
            Edge(10,3,1),
            Edge(10,4,5),
            Edge(10,5,1)
        )
    }

    @TestFactory
    fun autoTestCorrectAlgorithmForDifferentGraphs() = listOf(
        GRAPH1 to "1 ➔ 3(9) ➔ 4(20) ➔ 5(26)",
        GRAPH2 to "1 ➔ 7(2) ➔ 6(6) ➔ 5(7)",
        GRAPH3 to "1 ➔ 4(4) ➔ 5(6)",
        GRAPH4 to "1 ➔ 2(1) ➔ 8(2) ➔ 3(3) ➔ 5(4)",
        GRAPH5 to "1 ➔ 2(1) ➔ 10(6) ➔ 5(7)"
    ).map { (input, expected) ->
        dynamicTest("Для графа $input: $expected") {
            with(Graph(input)) {
                dijkstra(START)
                val dijkstraStr = printPath(END)
                assertEquals(expected, dijkstraStr)
            }
        }
    }
}


internal class DijkstraAlgorithmEndTest(){
    lateinit var GRAPH: kotlin.collections.List<Edge>
    var START: Int = 1
    var END1: Int = 2
    var END2: Int = 3
    var END3: Int = 4
    var END4: Int = 5
    var END5: Int = 6

    @org.junit.jupiter.api.BeforeEach
    fun setUp(){
        GRAPH = listOf(
            Edge(1, 2, 7),
            Edge(1, 3, 9),
            Edge(1, 6, 14),
            Edge(2, 3, 10),
            Edge(2, 4, 15),
            Edge(3, 4, 11),
            Edge(3, 6, 2),
            Edge(4, 5, 6),
            Edge(5, 6, 9)
        )
    }

    @TestFactory
    fun autoTestCorrectAlgorithmForDifferentEnd() = listOf(
        END1 to "1 ➔ 2(7)",
        END2 to "1 ➔ 3(9)",
        END3 to "1 ➔ 3(9) ➔ 4(20)",
        END4 to "1 ➔ 3(9) ➔ 4(20) ➔ 5(26)",
        END5 to "1 ➔ 3(9) ➔ 6(11)"
    ).map { (input, expected) ->
        dynamicTest("Для вершины $input: $expected") {
            with(Graph(GRAPH)) {
                dijkstra(START)
                val dijkstraStr = printPath(input)
                assertEquals(expected, dijkstraStr)
            }
        }
    }
}


internal class DijkstraAlgorithmStartTest(){
    lateinit var GRAPH: kotlin.collections.List<Edge>
    var END: Int = 5
    var START1: Int = 1
    var START2: Int = 2
    var START3: Int = 3
    var START4: Int = 4
    var START5: Int = 6
    var START6: Int = 7
    var START7: Int = 8
    var START8: Int = 9
    var START9: Int = 10

    @org.junit.jupiter.api.BeforeEach
    fun setUp(){
        GRAPH = listOf(
            Edge(1,2,1),
            Edge(1,9,8),
            Edge(1,8,6),
            Edge(2,9,9),
            Edge(2,10,5),
            Edge(2,3,15),
            Edge(3,4,5),
            Edge(4,5,1),
            Edge(6,5,3),
            Edge(7,6,9),
            Edge(8,7,5),
            Edge(9,7,7),
            Edge(9,6,8),
            Edge(9,5,9),
            Edge(9,10,7),
            Edge(10,3,1),
            Edge(10,4,5),
            Edge(10,5,1),
            Edge(3,2,8)
        )
    }

    @TestFactory
    fun autoTestCorrectAlgorithmForDifferentStart() = listOf(
        START1 to "1 ➔ 2(1) ➔ 10(6) ➔ 5(7)",
        START2 to "2 ➔ 10(5) ➔ 5(6)",
        START3 to "3 ➔ 4(5) ➔ 5(6)",
        START4 to "4 ➔ 5(1)",
        START5 to "6 ➔ 5(3)",
        START6 to "7 ➔ 6(9) ➔ 5(12)",
        START7 to "8 ➔ 7(5) ➔ 6(14) ➔ 5(17)",
        START8 to "9 ➔ 10(7) ➔ 5(8)",
        START9 to "10 ➔ 5(1)"
    ).map { (input, expected) ->
        dynamicTest("Для вершины $input: $expected") {
            with(Graph(GRAPH)) {
                dijkstra(input)
                val dijkstraStr = printPath(END)
                assertEquals(expected, dijkstraStr)
            }
        }
    }
}