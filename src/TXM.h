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

#include "ACM.h"
#include "Job_m.h"
#include "Source.h"

using namespace omnetpp;

#define CELL_IDLE 0
#define CELL_RX 1
#define CELL_TX 2
#define CELL_UPLINK 0
#define CELL_DOWNLINK 1

struct cell {
    int Opt; // idle 0, rx 1, tx 2
    int Type; // uplink 0, downlink 1;
    int Sender;
    int Receiver;
};

namespace tsch {

/**
 * TODO - Generated class
 */
class TXM : public cSimpleModule
{
  protected:
    simtime_t nextWakeUpTime;
    cQueue queue[4];
    int nodeId;
    int parentId;
    cell schedule[SLOTFRAME_LEN][CHANNELS];

    long numSent;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual void initSchedule();
    virtual int classify(Job *job);
    virtual int checkSchedule();
    virtual void refreshDisplay() const override;
};

} //namespace


#endif
