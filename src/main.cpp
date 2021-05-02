#include <chrono>
#include <cmath>
#include <iostream>
#include <pthread.h>
#include <thread>

#include "Controller.h"
#include "Medium.h"
#include "PatternDetector.h"
#include "PatternGenerator.h"
#include "Sender.h"

static constexpr int NUMBER_OF_CHANNELS = 10;
static constexpr int MIN_DURATION_FRAMES = 1;
static constexpr int MAX_DURATION_FRAMES = 125;
static constexpr int US_PER_FRAME = 10;

static constexpr long BAND_START_HZ = 2 * std::pow(10, 9);
static constexpr long BAND_END_HZ = 3 * std::pow(10, 9);
static constexpr long CHANNEL_WIDTH_HZ = (BAND_END_HZ - BAND_START_HZ) / NUMBER_OF_CHANNELS;
static constexpr long CHANNEL_CENTER_HZ = CHANNEL_WIDTH_HZ / 2;

int main()
{
    auto patternGen = PatternGenerator(NUMBER_OF_CHANNELS, MIN_DURATION_FRAMES, MAX_DURATION_FRAMES);
    auto pattern = patternGen.GetPattern();
    std::cout << "Pattern to detect:" << std::endl;
    pattern->Print();
    std::cout << "Total pattern length: " << pattern->GetTotalDuration() << std::endl;

    auto medium = Medium(NUMBER_OF_CHANNELS);
    auto sender = Sender(pattern);
    auto detector = PatternDetector(NUMBER_OF_CHANNELS);

    std::vector<Device*> devices;
    devices.push_back(&sender);
    devices.push_back(&detector);

    auto controller = Controller(&medium, devices, pattern->GetTotalDuration());
    controller.Start();

    // TODO if (isRotation(pattern->GetVector(), detector->GetVector())) { std::cout << "Detected pattern is correct!" << std::endl; }

    return 0;
}
