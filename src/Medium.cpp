#include "Medium.h"

bool Medium::IsChannelActive(int channel) const { return channel == mActiveChannel; }

void Medium::SetChannelActive(int channel) { mActiveChannel = channel; }

void Medium::SetChannelInactive() { mActiveChannel = INACTIVE; }