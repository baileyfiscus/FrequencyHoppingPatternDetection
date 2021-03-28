#include <cmath>
#include <iostream>

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

void SenderThread(Sender& sender);
void DetectorThread(PatternDetector& detector);

int main()
{
    auto medium = Medium();
    auto patternGen = PatternGenerator(NUMBER_OF_CHANNELS, MIN_DURATION_FRAMES, MAX_DURATION_FRAMES);
    auto pattern = patternGen.GetPattern();
    auto sender = Sender(medium, pattern, US_PER_FRAME);
    auto detector = PatternDetector(medium);

    SenderThread(sender);
    return 0;
}

void SenderThread(Sender& sender)
{
    sender.SendLoop();
}

void DetectorThread(PatternDetector& detector)
{

}
