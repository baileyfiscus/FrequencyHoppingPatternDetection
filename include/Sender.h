#pragma once

#include <string>
#include <vector>

#include "Device.h"
#include "Pattern.h"

class Sender : public Device
{
public:
    Sender(Pattern* pattern);
    virtual Operation GetOperation(int& frequency) override;
    virtual void SetListenResponse(bool bHeard) override;
private:
    Pattern* mPattern;
    int mCurrentIndex = 0;
    long mRemainingDuration;
};
