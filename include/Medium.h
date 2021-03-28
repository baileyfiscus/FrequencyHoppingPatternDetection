#pragma once

class Medium
{
public:
    bool IsChannelActive(int channel) const;
    void SetChannelActive(int channel);
    void SetChannelInactive();

private:
    static constexpr int INACTIVE = -1;
    int mActiveChannel = INACTIVE;
};