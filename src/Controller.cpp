#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>

#include "Controller.h"

Controller::Controller(Medium* medium, std::vector<Device*> devices, long timeSlots)
    : mMedium(medium)
    , mDevices(devices)
    , mTimeSlots(timeSlots)
{

}

void Controller::Start()
{
    std::vector<bool> doesDeviceKnowPattern;
    for (auto device : mDevices) {
        doesDeviceKnowPattern.push_back(device->IsPatternKnown());
    }

    unsigned long long loopCount = 0;
    while (true) {
        for (int i = 0; i < mTimeSlots; i++) {
            loopCount++;
            //std::cout << "Time slot: " << i << std::endl;
            bool bAllDevicesKnowPattern = true;
            for (int deviceIndex = 0; deviceIndex < mDevices.size(); deviceIndex++) {
                auto device = mDevices[deviceIndex];
                bool bDidDeviceKnowPattern = doesDeviceKnowPattern[deviceIndex];
                bAllDevicesKnowPattern &= bDidDeviceKnowPattern;
                int frequency = -1;
                switch (device->GetOperation(frequency)) {
                    case Device::Operation::SEND:
                    {
                        mMedium->SetChannelInactive();
                        mMedium->SetChannelActive(frequency);
                        //std::cout << "Set channel " << frequency << " to active." << std::endl;
                        break;
                    }
                    case Device::Operation::LISTEN:
                    {
                        bool isChannelHeard = mMedium->IsChannelActive(frequency);
                        device->SetListenResponse(isChannelHeard);
                        if (isChannelHeard) {
                            //std::cout << "Channel " << frequency << " was heard." << std::endl;
                        }
                        else {
                            //std::cout << "Channel " << frequency << " was NOT heard." << std::endl;
                        }
                        break;
                    }
                    case Device::Operation::NOOP:
                        //std::cout << "NOOP" << std::endl;
                        break;
                    default:
                        break;
                }

                std::string str = device->IsPatternKnown() ? "Knows pattern" : "Does NOT know pattern";
                //std::cout << str << std::endl;

                if (bDidDeviceKnowPattern != device->IsPatternKnown()) {
                    // Device learned pattern
                    doesDeviceKnowPattern[deviceIndex] = device->IsPatternKnown();
                    std::cout << "Pattern Detected in " << loopCount << " frames." << std::endl;
                }
            }
            if (bAllDevicesKnowPattern) {
                std::cout << "All devices know pattern. Exiting." << std::endl;
                return;
            }
        }
    }
}
