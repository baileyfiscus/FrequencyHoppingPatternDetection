#pragma once

class Medium
{
public:
    Medium(int channels);
    bool IsChannelActive(int channel) const;
    void SetChannelActive(int channel);
    void SetChannelInactive();
    int GetChannels();
    bool TestChannelActive(int channel, long testDurationMicroseconds) const;
private:
    int mChannels = 0;
    static constexpr int INACTIVE = -1;
    int mActiveChannel = INACTIVE;
};