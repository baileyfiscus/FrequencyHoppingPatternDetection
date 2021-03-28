#include "Medium.h"

Medium::Medium(int channels) : mChannels(channels) {}

bool Medium::IsChannelActive(int channel) const { return channel == mActiveChannel; }

void Medium::SetChannelActive(int channel) { mActiveChannel = channel; }

void Medium::SetChannelInactive() { mActiveChannel = INACTIVE; }

int Medium::GetChannels() { return mChannels; }