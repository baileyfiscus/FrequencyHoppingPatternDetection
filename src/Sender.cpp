#include <algorithm>
#include <chrono>
#include <climits>
#include <iostream>
#include <thread>

#include "Sender.h"

Sender::Sender(Pattern* pattern)
    : mPattern(pattern)
{
    SetPatternKnown(true);
    mRemainingDuration = mPattern->GetDurationAt(mCurrentIndex);
}

Device::Operation Sender::GetOperation(int& frequency)
{
    if (mRemainingDuration-- <= 0) {
        mCurrentIndex = (mCurrentIndex + 1) % mPattern->GetLength();
        mRemainingDuration = mPattern->GetDurationAt(mCurrentIndex) - 1;
    }

    frequency = mPattern->GetFrequencyAt(mCurrentIndex);
    return Operation::SEND;
}

void Sender::SetListenResponse(bool bHeard)
{

}

bool Sender::IsSender()
{
    return true;
}