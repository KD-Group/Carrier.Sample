//
// Created by 10189 on 2019/1/4.
//

#ifndef CARRIER_SAMPLE_SAMPLING_CONFIG_HPP
#define CARRIER_SAMPLE_SAMPLING_CONFIG_HPP

#include <cstddef>

namespace Config {

struct SamplingConfig {
    int number_of_waveforms;
    double first_percent;
    double second_percent;
    double sampling_interval;
    size_t current_sampling_count;

    void update(int number_of_waveforms, double first_percent, double second_percent);
    void set_sampling_count(size_t count);
};

}


#endif //CARRIER_SAMPLE_SAMPLING_CONFIG_HPP
