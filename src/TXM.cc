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

extern int ASN;

namespace tsch {

Define_Module(TXM);

void TXM::initialize()
{
    numSent = 0;
    nodeId = this->getParentModule()->getIndex();
    parentId = this->getParentModule()->par("parent").intValue();

    initSchedule();

    for(int i=0;i<par("queueNum").intValue();i++)
        queue[i].setName("queue");

    nextWakeUpTime = -1;
}

void TXM::handleMessage(cMessage *msg)
{
    if(!msg->isSelfMessage())
    {
        // insert to pkt queue
        Job *job = check_and_cast<Job *>(msg);
        int queueIndex = classify(job);
        queue[queueIndex].insert(job);
    }

    if(checkSchedule()!=-1 && !queue[1].isEmpty())
    {
        Job *job = (Job *)queue[1].pop();

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
                EV << "[+]ASN: " << ASN << " - #" << nodeId << " sent " << job->getName() << " to #" << nextHop  << endl;
                if(job->getSrc() == nodeId)
                    job->setSentASN(ASN);
                send(job, "out", g);
                numSent++;
                break;
            }
        }
    }

    // wake up again in the next slot
    if(nextWakeUpTime!=(ASN+1)*SLOT_DURATION)
    {
        nextWakeUpTime = (ASN+1)*SLOT_DURATION;
        scheduleAt(nextWakeUpTime, new cMessage("dummy"));
    }

}


void TXM::refreshDisplay() const
{
    char buf[40];
    sprintf(buf, " sent: %ld", numSent);
    this->getParentModule()->getDisplayString().setTagArg("t", 0, buf);
}

void TXM::initSchedule()
{
    for(int s=0; s<SLOTFRAME_LEN;s++)
    {
        if(s == (10-nodeId)*2)
        {
            for(int c=0;c<CHANNELS;c++)
            {
                if(c == 0)
                {
                    schedule[s][c] = {CELL_TX, CELL_UPLINK, nodeId, parentId};
                }

            }
        }
    }
//    schedule[5][0] = {CELL_TX, CELL_UPLINK, 6, 5};
//    schedule[5][1] = {CELL_TX, CELL_UPLINK, 3, 1};
}

int TXM::classify(Job *job)
{
    return job->getPriority();
}

int TXM::checkSchedule()
{
    int slot = ASN%SLOTFRAME_LEN;
    for(int c=0;c<CHANNELS;c++)
    {
        if(schedule[slot][c].Opt == CELL_TX &&
           schedule[slot][c].Sender == nodeId)
            return 1;
    }

    return -1;
}

} //namespace
