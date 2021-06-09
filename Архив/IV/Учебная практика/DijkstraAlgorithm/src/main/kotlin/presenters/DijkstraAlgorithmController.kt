package presenters

import models.Snapshot
import models.SnapshotKeeper

class DijkstraAlgorithmController{
    private var snapshotKeeper : SnapshotKeeper = SnapshotKeeper()
    private var startNode : Int = -1
    private var currentStep : Int = 0
    var answer:String = ""
    fun initStart(startNode:Int, snapshots : SnapshotKeeper, answer:String){
        this.startNode = startNode-1
        this.snapshotKeeper = snapshots
        this.answer = answer
        currentStep = -1
    }

    fun getNextStep(): Snapshot?{
        if (currentStep>=snapshotKeeper.getSize()-1) return null
        currentStep++
        return snapshotKeeper.getSnapshot(currentStep)
    }

    fun getPreviousStep(): Snapshot?{
        if (currentStep<=0) return null
        currentStep--
        return snapshotKeeper.getSnapshot(currentStep)
    }

    fun getLast(): Snapshot?{
        currentStep = snapshotKeeper.getSize()-1
        return snapshotKeeper.getSnapshot(snapshotKeeper.getSize()-1)
    }

    fun isNextStepPossible():Boolean{
        if(currentStep>=snapshotKeeper.getSize()-1) return false
        return true
    }
    fun isPreviousStepPossible():Boolean{
        if(currentStep<=0) return false
        return true
    }
    fun getPreviousSnap():Snapshot?{
        if (currentStep<=0) return null
        return snapshotKeeper.getSnapshot(currentStep-1)
    }


}
