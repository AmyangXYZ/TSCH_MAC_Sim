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

#include "RXM.h"

namespace tsch {

Define_Module(RXM);

void RXM::initialize()
{
    nodeId = this->getParentModule()->getIndex();
}

void RXM::handleMessage(cMessage *msg)
{

    Job* job = check_and_cast<Job *>(msg);

    if(job->getDst() == nodeId)
        send(job, "out", 0);
    else
        send(job, "out", 1);
}

} //namespace
