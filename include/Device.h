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
};