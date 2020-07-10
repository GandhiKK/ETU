package models


class Snapshot (graph: HashMap<Int, Vertex>, private val currentVertex: Int,private val prevVertex:Int,private val relax:Boolean)
{
    private val vertexAsString = StringBuilder("")

    init{
        for(v in graph) {
            vertexAsString.append(v.value.toString()+", ")
        }
        vertexAsString.delete(vertexAsString.length - 2, vertexAsString.length).append("")
    }

    fun getStringVertex(): String {
        return vertexAsString.toString()
    }

    fun getCurrentVertex(): Int {
        return currentVertex
    }

    fun getRelax():Boolean {
        return relax
    }

    fun getAllInfo(): String{
        return ("($currentVertex,$prevVertex,$relax), ${vertexAsString.toString()}")
    }

    fun toMap():HashMap<Int,List<String>>{
        val list = this.getAllInfo().substring(1,this.getAllInfo().length-1).split("), (")
        val double = HashMap<Int,List<String>>(list.size)
        for (e in list){
            double[list.indexOf(e)] = e.split(",")
        }
        return double
    }

}

class SnapshotKeeper{
    private var snapshotArray = emptyArray<Snapshot>()
    private var arraySize :Int = 0
    fun putSnapshot(new:Snapshot){
        snapshotArray+=new
        arraySize++
    }
    fun getSnapshot(index:Int):Snapshot?{
        if (index<0||index>=arraySize) return null
        return snapshotArray[index]
    }
    fun getSize():Int{
        return arraySize
    }
}

