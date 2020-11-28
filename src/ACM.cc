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

#include "ACM.h"

int ASN;

namespace tsch {

Define_Module(ACM);

void ACM::initialize()
{
    scheduleAt(0+SLOT_DURATION, new cMessage("dummy"));
}

void ACM::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        scheduleAt(simTime()+SLOT_DURATION, new cMessage("dummy"));
        ASN++;
    }
}

void ACM::refreshDisplay() const
{
    char buf[40];
    sprintf(buf, "ASN: %d", ASN);
    getDisplayString().setTagArg("t", 0, buf);
}

} //namespace
