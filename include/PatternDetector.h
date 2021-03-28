#pragma once

#include <vector>

#include "Medium.h"

class PatternDetector
{
public:
    PatternDetector(Medium& medium);
    void DetectLoop();
private:
    Medium* mMedium;
    int GetInitialFrequency();
};
