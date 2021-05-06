#pragma once

class Device
{
public:
    enum Operation {
        SEND,
        LISTEN,
        NOOP
    };
    virtual Operation GetOperation(int& frequency) = 0;
    virtual void SetListenResponse(bool bHeard) = 0;
    virtual bool IsSender() { return false; }
    bool IsPatternKnown() { return mbIsPatternKnown; }
    void SetPatternKnown(bool bIsKnown) { mbIsPatternKnown = bIsKnown; }
protected:
    bool mbIsPatternKnown = false;
};