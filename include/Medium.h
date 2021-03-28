#pragma once

class Medium
{
public:
    Medium(int channels);
    bool IsChannelActive(int channel) const;
    void SetChannelActive(int channel);
    void SetChannelInactive();
    int GetChannels();
private:
    int mChannels = 0;
    static constexpr int INACTIVE = -1;
    int mActiveChannel = INACTIVE;
};