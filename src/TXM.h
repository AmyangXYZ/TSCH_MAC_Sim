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

#ifndef __TSCH_TXM_H_
#define __TSCH_TXM_H_

#include <omnetpp.h>
#include "Job_m.h"
#include "ASN.h"
#include "Source.h"

using namespace omnetpp;


namespace tsch {

/**
 * TODO - Generated class
 */
class TXM : public cSimpleModule
{
  protected:
    simtime_t nextWakeUpTime;
    cQueue queue;

    int nodeId;
    int parentId;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual int checkSchedule();

};

} //namespace


#endif
