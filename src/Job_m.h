//
// Generated file, do not edit! Created by nedtool 5.6 from Job.msg.
//

#ifndef __TSCH_JOB_M_H
#define __TSCH_JOB_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif


namespace tsch {

/**
 * Class generated from <tt>Job.msg:21</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * packet Job
 * {
 *     int src;
 *     int dst;
 *     int type;
 *     int priority;
 *     int sentASN;
 *     char payload[128];
 * }
 * </pre>
 */
class Job : public ::omnetpp::cPacket
{
  protected:
    int src;
    int dst;
    int type;
    int priority;
    int sentASN;
    char payload[128];

  private:
    void copy(const Job& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Job&);

  public:
    Job(const char *name=nullptr, short kind=0);
    Job(const Job& other);
    virtual ~Job();
    Job& operator=(const Job& other);
    virtual Job *dup() const override {return new Job(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getSrc() const;
    virtual void setSrc(int src);
    virtual int getDst() const;
    virtual void setDst(int dst);
    virtual int getType() const;
    virtual void setType(int type);
    virtual int getPriority() const;
    virtual void setPriority(int priority);
    virtual int getSentASN() const;
    virtual void setSentASN(int sentASN);
    virtual unsigned int getPayloadArraySize() const;
    virtual char getPayload(unsigned int k) const;
    virtual void setPayload(unsigned int k, char payload);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Job& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Job& obj) {obj.parsimUnpack(b);}

} // namespace tsch

#endif // ifndef __TSCH_JOB_M_H

