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

#include "Sink.h"

extern int ASN;

namespace tsch {

Define_Module(Sink);

void Sink::initialize()
{
    if(this->getParentModule()->par("isRoot"))
    {
        latencySignalAll = registerSignal("latencyAll");
        for(int i=0;i<10;i++)
        {
            char signalName[32];
            sprintf(signalName, "latency of Node%d", i);
            simsignal_t signal = registerSignal(signalName);
            cProperty *statisticTemplate = getProperties()->get("statisticTemplate", "latencyTemplate");
            getEnvir()->addResultRecorders(this, signal, signalName,  statisticTemplate);
            latencySignals[i] = signal;
        }
    }
}

void Sink::handleMessage(cMessage *msg)
{
    if(this->getParentModule()->par("isRoot"))
    {
        Job* job = check_and_cast<Job *>(msg);
        emit(latencySignalAll, (ASN - job->getSentASN())*SLOT_DURATION*1000);
        emit(latencySignals[job->getSrc()], (ASN - job->getSentASN())*SLOT_DURATION*1000);
    }
}

} //namespace
