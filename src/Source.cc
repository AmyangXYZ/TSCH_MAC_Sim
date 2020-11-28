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

#include "Source.h"

namespace tsch {

Define_Module(Source);

void Source::initialize()
{
    jobCounter = 0;
    nodeId = this->getParentModule()->getIndex();

    if(!this->getParentModule()->par("isRoot").boolValue())
//        scheduleAt(intuniform(0,60)*SLOT_DURATION, new cMessage("init"));
        scheduleAt(0, new cMessage("init"));
}

void Source::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()) {
        Job *job = createJob();

        if(strlen(job->getName())>0)
        {
            send(job, "out");
        }
        scheduleAt(simTime()+SLOT_DURATION*SLOTFRAME_LEN, new cMessage("dummy"));
    }
}

Job* Source::createJob()
{
    jobCounter++;

    int src = nodeId;
    int dst = 0;
    char name[32]="";
    sprintf(name, "Job #%d (%d->%d)", jobCounter, src, dst);
    Job *job = new Job(name);
    job->setSrc(src);
    job->setDst(dst);
    job->setType(1);
    job->setPriority(1);
    return job;
}

} //namespace
