package models

import java.util.*
import kotlin.collections.HashMap

var testOutput: String = ""

class Edge(v1: Int, v2: Int, dist: Int){
    val v1 = if (v1 < 0) throw IllegalArgumentException("Value < 0") else v1
    val v2 = if (v2 < 0) throw IllegalArgumentException("Value < 0") else v2
    val dist = if (dist < 0) throw IllegalArgumentException("Dist < 0") else dist
}

class Vertex(val name: Int) : Comparable<Vertex> {
    var dist = Int.MAX_VALUE
    var previous: Vertex? = null
    val neighbours = HashMap<Vertex, Int>()
    fun printPath(): String{
        var endString: String
        endString = when(previous){
            this -> (name).toString()
            null -> "не существует"
            else -> {
                val str: String = previous!!.printPath()
                "$str ➔ ${name}($dist)"
            }
        }
        return endString
    }
    override fun compareTo(other: Vertex): Int {
        if (dist == other.dist) return name.compareTo(other.name)
        return dist.compareTo(other.dist)
    }
}

class Graph(val edges: List<Edge>){
    val graph = HashMap<Int, Vertex>(edges.size)
    init {
        for (e in edges) {
            if (!graph.containsKey(e.v1))
                graph.put(e.v1, Vertex(e.v1))
            if (!graph.containsKey(e.v2))
                graph.put(e.v2, Vertex(e.v2))
        }
        for (e in edges)
            graph[e.v1]!!.neighbours.put(graph[e.v2]!!, e.dist)
    }
    fun dijkstra(startName: Int) {
        if (!graph.containsKey(startName)) {
            testOutput = "Граф не содержит стартовую вершину '${startName}'"
            return
        }
        val source: Vertex? = graph[startName]
        val treeSet: TreeSet<Vertex> = TreeSet<Vertex>()
        for (v in graph.values) {
            v.previous = if (v == source) source else null
            v.dist = if (v == source) 0 else Int.MAX_VALUE
            treeSet.add(v)
        }
        dijkstra(treeSet)
    }
    private fun dijkstra(treeSet: TreeSet<Vertex>) {
        while (!treeSet.isEmpty()) {
            val currV = treeSet.pollFirst()
            if (currV!!.dist == Int.MAX_VALUE)
                break
            for (ngb in currV.neighbours) {
                val currentNgb = ngb.key
                val alternateDist = currV.dist + ngb.value
                if (alternateDist < currentNgb.dist) {
                    treeSet.remove(currentNgb)
                    currentNgb.dist = alternateDist
                    currentNgb.previous = currV
                    treeSet.add(currentNgb)
                }
            }
        }
    }
    fun printPath(endName: Int): String {

        if (!graph.containsKey(endName))
            return "Граф не содержит конечную вершину '${endName}'"

        return graph[endName]!!.printPath()
    }
}