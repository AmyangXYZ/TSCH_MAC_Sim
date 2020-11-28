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

#include "ASN.h"

namespace tsch {

Define_Module(ASN);

void ASN::initialize()
{
    scheduleAt(0+SLOT_DURATION, new cMessage("dummy"));
}

void ASN::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        scheduleAt(simTime()+SLOT_DURATION, new cMessage("dummy"));
        ASN++;
    }
}

int ASN::getASN()
{
    return ASN;
}

} //namespace
