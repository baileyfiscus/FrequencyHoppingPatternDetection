#pragma once

#include <vector>

#include "Medium.h"
#include "Device.h"

class Controller
{
public:
    Controller(Medium* medium, std::vector<Device*> devices, long timeSlots);
    void Start();
private:
    long mTimeSlots;
    Medium* mMedium;
    std::vector<Device*> mDevices;
    long timeSlots;
};