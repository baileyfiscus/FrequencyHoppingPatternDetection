#pragma once

#include <string>
#include <vector>

#include "Medium.h"

class Sender
{
public:
    Sender(Medium& medium, std::vector<std::pair<int, int>> pattern, int usPerFrame);
    void SendLoop();
private:
    Medium* mMedium;
    int mUsPerFrame = 0;
    std::vector<std::pair<int, int>> mPattern;
};
