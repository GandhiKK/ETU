package presenters

import java.io.File
import java.io.InputStream
import java.nio.file.Files
import java.nio.file.StandardOpenOption

class GraphFileHandler(private val fileName: String) {
    private fun convertStringInfotoArrayList(info_:String,isNodeInfo:Boolean): ArrayList<List<String>>?{
        val string = info_.replace(" ","")
        val match: Sequence<MatchResult>
        match = if(!isNodeInfo){
            val reg = (Regex("^(\\(\\d+,\\d+,\\d+\\),)*\\(\\d+,\\d+,\\d+\\)\$"))
            if (!string.matches(reg)) return null
            Regex("(\\d+,\\d+,\\d+)").findAll(string)
        } else{
            val reg = (Regex("^(\\(\\d+,\\d+\\),)*\\(\\d+,\\d+\\)\$"))
            if (!string.matches(reg)) return null
            Regex("(\\d+,\\d+)").findAll(string)
        }
        val list = ArrayList<List<String>>()
        for(e in match){
            val temp = e.destructured.toList().toString()
            list.add(temp.substring(1,temp.length-1).split(","))
        }
        return list
    }

    fun downloadGraphInfo():Pair<ArrayList<List<String>>?,ArrayList<List<String>>?>?{
        val inputStream: InputStream = File(fileName).inputStream()
        val allInfo = mutableListOf<String>()
        inputStream.bufferedReader().forEachLine { allInfo.add(it) }

        if(allInfo.size !in 1..2) return null //если в файле больше, чем нужно строк

        val nodeInfoList = (convertStringInfotoArrayList(allInfo[0].replace(" ",""),true)) ?: return null//ошибка в записи информации об узлах

        var edgeInfoList : ArrayList<List<String>>? = null

        if (allInfo.size==2) //нет информации о ребрах
            edgeInfoList = (convertStringInfotoArrayList(allInfo[1].replace(" ",""),false)) ?: return null//ошибка в записи информации о ребрах

        return Pair(nodeInfoList,edgeInfoList)

    }

    fun saveGraphInfo(graphAsString: String){
        val resultFile = File(fileName)
        if(Files.exists(resultFile.toPath())) Files.delete(resultFile.toPath())
        Files.write(resultFile.toPath(), graphAsString.toByteArray(), StandardOpenOption.CREATE)
    }
}




