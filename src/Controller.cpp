#include <iostream>

#include "Controller.h"

Controller::Controller(Medium* medium, std::vector<Device*> devices, long timeSlots)
    : mMedium(medium)
    , mDevices(devices)
    , mTimeSlots(timeSlots)
{

}

void Controller::Start()
{
    unsigned long long loopCount = 0;
    while (true) {
        for (int i = 0; i < mTimeSlots; i++) {
            loopCount++;
            //std::cout << "Time slot: " << i << std::endl;
            for (auto device : mDevices) {
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
                        std::cout << "Pattern Detected in " << loopCount << " frames." << std::endl;
                        return;
                        break;
                    default:
                        break;
                }
                //std::cin.get();
            }
        }
    }
}
