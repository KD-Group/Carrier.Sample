//
// Created by 10189 on 2019/1/5.
//

#include <algorithm>

#include "measure.hpp"
#include "base.hpp"
#include "../global/global.hpp"
#include "../processer/processer.hpp"

#ifdef _WIN32
    #include "Windows.h"
#else
    #include <thread>
    #include <chrono>
#endif

namespace Commander {

void measure() {
    bool &success = Global::result.success;
    success = true;

    do {
        // Step 1: Get Maximum and Minimum Voltage
        Global::config.set_sampling_count(Constant::WaveformCount * 2);
        success = Global::sampler->sample(Global::config, Global::result);
        if (!success) break;
        success = Processer::align(Global::config, Global::result);
        if (!success) break;

        // Step 2: Adjust Value Range and Sample Full Times
        Global::config.set_sampling_count(Constant::WaveformCount * (Global::config.number_of_waveforms + 1));
        success = Global::sampler->sample(Global::config, Global::result);
        if (!success) break;

        // Step 3: Transfer States : High <----> Low
        success = Processer::summation(Global::config, Global::result);
        if (!success) break;

        // Step 4: Get a Average Wave
        success = Processer::average(Global::config, Global::result);
        if (!success) break;
    } while (false);

    Global::result.measuring = false;
}

#ifdef _WIN32
DWORD WINAPI measure(void *) {
measure();
return 0;
}
#endif

void to_query() {
    bool success = Global::result.success;
    Base::variable(success);

    if (success) {
        double max_voltage = Global::result.max_voltage;
        double min_voltage = Global::result.min_voltage;
        Base::variable(max_voltage);
        Base::variable(min_voltage);

        const double sampling_interval = Global::config.sampling_interval;
        Base::variable(sampling_interval);

        const double tau = Global::result.tau;
        Base::variable(tau);

        printf("wave = [");
        const auto &values = Global::result.average_wave;
        std::for_each(values.begin(), values.end(), [](double value){printf("%.3f,", value);});
        printf("]\n");
    } else {
        std::string message = Error::error_code_to_string(Global::result.error_code);
        Base::variable(message);
    }
}

void to_measure() {
    int number_of_waveforms;
    double first_percent;
    double second_percent;
    std::cin >> number_of_waveforms;
    std::cin >> first_percent;
    std::cin >> second_percent;

    Global::config.update(number_of_waveforms, first_percent, second_percent);

    if (!Global::sampler.get()) {
        Base::error(Error::SAMPLER_NOT_FOUND);
        return;
    }

    bool &measuring = Global::result.measuring;
    if (measuring) {
        Base::error(Error::IN_MEASURING);
        return;
    }

    measuring = true;
    Base::variable(measuring);

    #ifdef _WIN32
        DWORD handle;
        CreateThread(NULL, 0, measure, NULL, 0, &handle);
    #else
        // start a thread to do measure
        std::thread(measure).detach();
    #endif
}

void is_measuring() {
    bool &measuring = Global::result.measuring;
    Base::variable(measuring);
}

} // namespace Commander
