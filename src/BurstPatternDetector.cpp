#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "BurstPatternDetector.h"

BurstPatternDetector::BurstPatternDetector(size_t channelCount)
    : mChannelCount(channelCount)
{
}

Device::Operation BurstPatternDetector::GetOperation(int& frequency)
{
    switch (mStatus) {
        case FIND_FREQUENCY:
            mNextOperation = Device::Operation::LISTEN;
            frequency = GetFrequency();
            mLastFrequency = frequency;
            break;
        case FIND_DURATION:
            mNextOperation = Device::Operation::LISTEN;
            frequency = mFrequencyOrder.back();
            mLastFrequency = frequency;
            break;
        case FIND_PATTERN_LENGTH:
            mNextOperation = Device::Operation::LISTEN;
            frequency = mFrequencyOrder.back();
            mLastFrequency = frequency;
            break;
        case DONE:
        default:
            mNextOperation = Operation::NOOP;
    }

    return mNextOperation;
}

void BurstPatternDetector::SetListenResponse(bool bHeard)
{
    if ((mFrequencyOrder.size() == 0) && bHeard) {
        // Find first frequency
        mFrequencyOrder.push_back(mFrequencyGuess);
        mStatus = Status::FIND_PATTERN_LENGTH;
    }
    else if (mStatus == Status::FIND_PATTERN_LENGTH) {
        static size_t patternLength = 0;

        if (!bHeard && mWaitForBurstEnd) {
            // Initial burst ended
            mWaitForBurstEnd = false;
            patternLength++;
        }
        else if (bHeard && !mWaitForBurstEnd) {
            mCountFrequencyGuessDwell = true;
            patternLength++;
        }
        else if (!bHeard && mCountFrequencyGuessDwell) {
            // end
            mPatternLength = patternLength;
            mStatus = Status::FIND_DURATION;
        }
        else if (bHeard && mWaitForBurstEnd) {
            // Do nothing
        }
        else {
            patternLength++;
        }
    }
    else if (mDurationOrder.size() == 0) {
        // Find first duration
        static size_t duration = 0;
        if (bHeard) {
            duration++;
        }
        else if (!bHeard && mHeardLastResponse && (duration > 0)) {
            //std::cout << "Found duration " << duration << ", for frequency " << mFrequencyOrder.back() << std::endl;
            //std::cin.get();
            mDurationOrder.push_back(duration);
            duration = 0;

            if (mDurationOrder.size() < mChannelCount) {
                mStatus = Status::FIND_FREQUENCY;
                mGetNewGuess = true;
            }
            else {
                mStatus = Status::DONE;
                std::cout << "Burst DONE!" << std::endl;
                SetPatternKnown(true);
            }
        }
    }
    else if (mStatus == Status::FIND_FREQUENCY) {
        if (mCheckIfHeard) {
            if (bHeard) {
                mFrequencyOrder.push_back(mFrequencyGuess);
                mStatus = Status::FIND_DURATION;
                mWaitForBurstEnd = true;
                //std::cout << "Found frequency " << mFrequencyOrder.back() << std::endl;
                //std::cin.get();
            }
            else {
                mGetNewGuess = true;
            }
        }
    }
    else if (mStatus == Status::FIND_DURATION) {
        if (bHeard && mWaitForBurstEnd) {
            // do nothing
        }
        else if (!bHeard && mWaitForBurstEnd) {
            mWaitForBurstEnd = false;
        }
        else {
            static size_t duration = 0;
            if (bHeard) {
                duration++;
            }
            else if (!bHeard && mHeardLastResponse && (duration > 0)) {
                //std::cout << "Found duration " << duration << ", for frequency " << mFrequencyOrder.back() << std::endl;
                //std::cin.get();
                mDurationOrder.push_back(duration);
                duration = 0;

                if (mDurationOrder.size() < mChannelCount) {
                    mStatus = Status::FIND_FREQUENCY;
                    mGetNewGuess = true;
                }
                else {
                    mStatus = Status::DONE;
                    std::cout << "\n\nBurst DONE!" << std::endl;
                    SetPatternKnown(true);
                    for (int i = 0; i < mFrequencyOrder.size(); i++) {
                        std::cout << "Frequency: " << mFrequencyOrder[i] << ", Duration: " << mDurationOrder[i] << std::endl;
                    }
                }
            }
        }
    }

    mHeardLastResponse = bHeard;
}

int BurstPatternDetector::GetFrequency()
{
    if (mFrequencyOrder.size() == 0) {
        mFrequencyGuess = 0;
        return mFrequencyGuess;
    }

    if (mGetNewGuess) {
        static int lastGuess = 0;
        while (true) {
            mFrequencyGuess = (mFrequencyGuess + 1) % mChannelCount;
            if (std::count(mFrequencyOrder.begin(), mFrequencyOrder.end(), mFrequencyGuess) == 0) {
                // The guess was not in vector, therefore valid guess
                lastGuess = mFrequencyGuess;
                mWaitForEndOfSequence = true;
                mCurrentIndex = 0;
                mGetNewGuess = false;
                break;
            }
        }
    }

    if (mWaitForEndOfSequence) {
        if (mHeardLastResponse) {
            mCurrentDuration++;
            if (mCurrentDuration >= mDurationOrder[mCurrentIndex]) {
                mCurrentDuration = 0;
                auto previousIndex = mCurrentIndex;
                mCurrentIndex = (mCurrentIndex + 1) % mDurationOrder.size();

                if (((previousIndex != mCurrentIndex) && (mCurrentIndex == 0)) || (mDurationOrder.size() == 1)) {
                    mCheckIfHeard = true;
                    return mFrequencyGuess;
                }
            }
        }
        mCheckIfHeard = false;
        return mFrequencyOrder[mCurrentIndex];
    }

    return 0;
}
