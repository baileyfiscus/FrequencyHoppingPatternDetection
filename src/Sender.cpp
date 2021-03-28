#include <chrono>
#include <climits>
#include <iostream>
#include <thread>

#include "Sender.h"

Sender::Sender(Medium& medium, std::vector<std::pair<int, int>> pattern, int usPerFrame)
    : mMedium(&medium)
    , mPattern(pattern)
    , mUsPerFrame(usPerFrame)
{}

void Sender::SendLoop()
{
    while (true) {
        for (auto pair : mPattern) {
            auto channel = pair.first;
            auto durationFrames = pair.second;
            auto durationMicroseconds = durationFrames * mUsPerFrame;
            auto endtime = std::chrono::high_resolution_clock::now() + std::chrono::microseconds(durationMicroseconds);
            //std::cout << "Sending on channel " << channel << " for " << durationFrames << " frames." << std::endl;
            mMedium->SetChannelActive(channel);
            while (std::chrono::high_resolution_clock::now() < endtime) {}
            mMedium->SetChannelInactive();
            std::this_thread::sleep_for(std::chrono::microseconds(50));
        }
    }
}