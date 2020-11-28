//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "TXM.h"
namespace tsch {

Define_Module(TXM);

void TXM::initialize()
{
    nodeId = this->getParentModule()->getIndex();
    parentId = this->getParentModule()->par("parent").intValue();

    queue.setName("queue");
    nextWakeUpTime = -1;
}

void TXM::handleMessage(cMessage *msg)
{
    if(!msg->isSelfMessage())
    {
        // insert to pkt queue
        Job *job = check_and_cast<Job *>(msg);
        queue.insert(job);
    }

    if(checkSchedule()!=-1 && !queue.isEmpty())
    {
        Job *job = (Job *)queue.pop();

        int nextHop;
        if(job->getDst() == 0)
            nextHop = parentId;
        // TODO - downlink routing


        // iterate connected gate and send out
        for(int g=0;g<gateSize("out");g++)
        {
            cGate *outGate = gate("out", g)->getPathEndGate();
            int neighbor = outGate->getOwnerModule()->getParentModule()->getIndex();

            if(neighbor == nextHop)
            {
                EV << "[+]" << simTime() << " send out " << " " << nodeId << "->" << nextHop  << endl;
                send(job, "out", g);
                break;
            }
        }
    }

    // wake up again in the next slot
    if(nextWakeUpTime!=simTime()+SLOT_DURATION)
    {
        scheduleAt(simTime()+SLOT_DURATION, new cMessage("dummy"));
        nextWakeUpTime = simTime()+SLOT_DURATION;
    }

}

int TXM::checkSchedule()
{

    ASN *asnModule = check_and_cast<ASN *>(this->getParentModule()->getParentModule()->getSubmodule("asn"));
    int curASN = asnModule->getASN();

//    localCell x = localSch[ curASN%SLOTFRAME_LEN ];
//
//    if(x.linkOpt == 1)
//    {
//        if(pktList[x.taskId]!=nullptr)
//            return x.taskId;
//    }

    if(curASN%SLOTFRAME_LEN == (10-nodeId)*8)
        return 1;
    return -1;
}

} //namespace
