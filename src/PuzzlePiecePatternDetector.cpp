#include <algorithm>
#include <iostream>

#include "PuzzlePiecePatternDetector.h"

PuzzlePiecePatternDetector::PuzzlePiecePatternDetector(std::size_t channelCount)
    : mChannelCount(channelCount)
{
    
}

Device::Operation PuzzlePiecePatternDetector::GetOperation(int& frequency)
{
    if (!IsPatternKnown()) {
        // Find the frequencies
        mNextOperation = Device::Operation::LISTEN;
        frequency = GetFrequency();
        mLastFrequency = frequency;
    }
    else {
        // Done
        return Device::Operation::NOOP;
    }

    return mNextOperation;
}

void PuzzlePiecePatternDetector::SetListenResponse(bool bHeard)
{
    if (mPuzzle.size() == 0)
    {
        // finding pattern length
        static bool bInitialHeard = false;
        static size_t patternLength = 0;

        if (!bInitialHeard && bHeard) {
            bInitialHeard = true;
        }

        if (!bInitialHeard) {
            return;
        }

        if (!bHeard && mWaitForBurstEnd) {
            // Initial burst ended
            mWaitForBurstEnd = false;
            patternLength++;
        }
        else if (bHeard && !mWaitForBurstEnd) {
            //std::cout << "Last leg" << std::endl;
            mCountFrequencyGuessDwell = true;
            patternLength++;
            mPatternIndex++;
        }
        else if (!bHeard && mCountFrequencyGuessDwell) {
            // end
            for (int i = 0; i < patternLength; i++)
            {
                mPuzzle.push_back(PuzzlePiecePatternDetector::INVALID_CHANNEL);
                std::vector<int> pieces;
                for (int j = 0; j < mChannelCount; j++)
                {
                    pieces.push_back(j);
                }
                mPossiblePieces.push_back(pieces);
            }
            //std::cout << "Pattern Index: " << mPatternIndex << std::endl;
        }
        else if (bHeard && mWaitForBurstEnd)
        {
            // Do nothing
        }
        else {
            patternLength++;
        }

    }
    else if (bHeard && !IsPatternKnown()) {
        if (mPuzzle[mPatternIndex] == PuzzlePiecePatternDetector::INVALID_CHANNEL) {
            //std::cout << "Found " << mLastFrequency << " at index " << mPatternIndex << std::endl;
            mPuzzle[mPatternIndex] = mLastFrequency;

            bool patternFound = true;
            for (auto slot : mPuzzle) {
                if (slot == PuzzlePiecePatternDetector::INVALID_CHANNEL) {
                    patternFound = false;
                    break;
                }
            }

            if (patternFound) {
                std::cout << "\n\nPuzzle DONE!" << std::endl;
                std::vector<int> freqOrder;
                std::vector<std::size_t> durOrder;
                for (int i = 0; i < mPuzzle.size(); i++) {
                    static int lastFrequency = PuzzlePiecePatternDetector::INVALID_CHANNEL;
                    static int dur = 0;
                    dur++;
                    if (lastFrequency == PuzzlePiecePatternDetector::INVALID_CHANNEL) {
                        freqOrder.push_back(mPuzzle[i]);
                    }
                    else if (mPuzzle[i] != lastFrequency) {
                        freqOrder.push_back(mPuzzle[i]);
                        durOrder.push_back(dur);
                        dur = 0;
                    }
                    else if (i == mPuzzle.size() - 1) {
                        durOrder.push_back(dur);
                        dur = 0;
                    }

                    lastFrequency = mPuzzle[i];
                }
                // Something is wrong but popping the last two elements yields the correct results
                freqOrder.pop_back();
                durOrder.pop_back();
                for (int i = 0; i < freqOrder.size(); i++) {
                    std::cout << "Frequency: " << freqOrder[i] << ", Duration: " << durOrder[i] << std::endl;
                }
                std::cin.get();
                SetPatternKnown(true);
            }
        }

        mPatternIndex = (mPatternIndex + 1) % mPuzzle.size();
    }
    else if (!bHeard && !IsPatternKnown()) {
        //std::cout << "Did not hear: " << mLastFrequency << " at index: " << mPatternIndex << std::endl;
        mPatternIndex = (mPatternIndex + 1) % mPuzzle.size();
    }
    else {
        //std::cout << "Deal with this case" << std::endl;
    }

}

int PuzzlePiecePatternDetector::GetFrequency()
{
    if (mPuzzle.size() == 0) {
            return 0;
    }

    int frequency = mPuzzle[mPatternIndex];

    if (frequency == PuzzlePiecePatternDetector::INVALID_CHANNEL) {
        auto& pieces = mPossiblePieces[mPatternIndex];

        auto itr = std::find(pieces.begin(), pieces.end(), mLastFrequency);
        bool isLastFrequencyPossible = itr != pieces.end();

        if (mHeardLastResponse && isLastFrequencyPossible) {
            frequency = mLastFrequency;
            pieces.erase(itr);
        }
        else {
            frequency = pieces.back();
            pieces.pop_back();
        }
    }

    return frequency;
}
