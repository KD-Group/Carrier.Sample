//
// Created by 10189 on 2019/1/5.
//

#ifndef CARRIER_SAMPLE_REAL_SAMPLER_HPP
#define CARRIER_SAMPLE_REAL_SAMPLER_HPP

#include "sampler.hpp"

#include "windows.h"
#include "bdaqctrl.h"
#include "../error/error.hpp"

using namespace std;
using namespace Automation::BDaq;

#define deviceDescription L"PCI-1714,BID#0"
#define check_code(code) if (BioFailed(code)) { result.error_code = Error::REAL_SAMPLER_ERROR; return false; }

namespace Sampler {
    class RealSampler : public Sampler {
    public:
        bool sample(const Config::SamplingConfig &config, Result::SamplingResult &result) override {
            ErrorCode code = Success;
            BufferedAiCtrl *bfdAiCtrl = AdxBufferedAiCtrlCreate();

            // connect device
            DeviceInformation devInfo(deviceDescription);
            code = bfdAiCtrl->setSelectedDevice(devInfo);
            check_code(code);

            // dynamic range setting
            AiChannelCollection* channels = bfdAiCtrl->getChannels();
            channels->getItem(0).setValueRange(V_Neg15To15);

            // sampling rate setting
            ConvertClock * convertClock = bfdAiCtrl->getConvertClock();
            convertClock->setRate(Constant::SafeSamplingFrequency);

            // sampling data
            ScanChannel* scanChannel = bfdAiCtrl->getScanChannel();
            code = scanChannel->setChannelStart(0);
            check_code(code);
            code = scanChannel->setChannelCount(1);
            check_code(code);
            code = scanChannel->setSamples(config.current_sampling_count);
            check_code(code);
            code = bfdAiCtrl->Prepare();
            check_code(code);
            code = bfdAiCtrl->RunOnce();
            check_code(code);
            code = bfdAiCtrl->GetData(config.current_sampling_count, &result.buffer[0]);
            check_code(code);

            bfdAiCtrl->Dispose();
            return true;
        }

        string name() override {
            return "real_sampler";
        }

        double get_value(const string& key) override {
            return 0.0;
        }

        bool set_value(const string& key, const double value) override {
            return true;
        }

    };
}

#endif //CARRIER_SAMPLE_REAL_SAMPLER_HPP
