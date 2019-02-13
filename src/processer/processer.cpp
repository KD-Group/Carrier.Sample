#include <map>
#include <cmath>
#include <algorithm>
#include "processer.hpp"
#include "../constant.hpp"
#include "../global/global.hpp"

namespace Commander {
namespace Processer {

bool align(const Config::SamplingConfig &config, Result::SamplingResult &result) {
    result.max_voltage = *std::max_element(result.buffer.begin(), result.buffer.begin() + config.current_sampling_count);
    result.min_voltage = *std::min_element(result.buffer.begin(), result.buffer.begin() + config.current_sampling_count);

    if (result.max_voltage < Constant::MinVoltageAmplitude) {
        result.error_code = Error::VOLTAGE_NOT_ENOUGH;
        return false;
    }

    return true;
}

bool summation(const Config::SamplingConfig &config, Result::SamplingResult &result) {
    // Transfer States : High <----> Low
    const double high_threshold = result.max_voltage * Constant::UpperBound + result.min_voltage * Constant::LowerBound;
    const double low_threshold = result.max_voltage * Constant::LowerBound + result.min_voltage * Constant::UpperBound;

    // find the start point with a low voltage
    // !!! add one wave length in order to get full wave
    size_t valid_sampling_count = (config.current_sampling_count * config.number_of_waveforms) /
                                   config.number_of_waveforms + 1;
    size_t start = 0, siz = valid_sampling_count;
    while (start < siz && result.buffer[start] > low_threshold) start++;

    int state = 0;
    double maximum = 0;
    int maximum_position = -1;
    int last_maximum_position = -1;
    int copy_length = 0;
    int copy_times = 0;

    // add multi-waves
    auto data = result.buffer.begin() + start;
    for (int i = 0; i < valid_sampling_count - start; ++i) {
        if (state == 0) { // Low state
            if (data[i] >= high_threshold) {
                state = 1;
                maximum = data[i];

                last_maximum_position = maximum_position;
                maximum_position = i;
            }
        } else if (state == 1) { // High state
            if (maximum < data[i]) { // update maximum with its position
                maximum = data[i];
                maximum_position = i;
            } else if (data[i] <= low_threshold) { // into low state
                state = 0;
                if (copy_length == 0) {
                    copy_length = std::min((i - maximum_position) * 6, int(Constant::WaveformCount));
                }

                if (~last_maximum_position) {
                    copy_length = std::min(copy_length, (maximum_position - last_maximum_position) * 3 / 4);
                }

                // last wave lenth is not enough
                if (copy_length + maximum_position >= valid_sampling_count - start) {
                    break;
                }

                // add wave
                for (int j = 0; j < copy_length; j++) {
                    result.wave[j] += data[maximum_position + j];
                }
                copy_times++;
            }
        }
        if (copy_times >= config.number_of_waveforms) { break; }
    }

    if (copy_times < config.number_of_waveforms * 0.9 || copy_times == 0) {
        result.error_code = Error::WAVE_NOT_FOUND;
        return false;
    }
    for (int i=0; i<copy_length; ++i) {
        result.wave[i] /= copy_times;
    }
    result.copy_length = copy_length;
	return true;
}

bool average(const Config::SamplingConfig &config, Result::SamplingResult &result) {
    // get a average wave
    const int copy_length = result.copy_length;
    std::vector<double> average_wave;
    int average_times = copy_length / 1000 + 1;

    double first_percent_voltage = result.wave[0] * config.first_percent +
                                   result.wave[copy_length - 1] * (1.0 - config.first_percent);
    double second_percent_voltage = result.wave[0] * config.second_percent +
                                    result.wave[copy_length - 1] * (1.0 - config.second_percent);

    size_t first_percent_position = UINT64_MAX;
    size_t second_percent_position = UINT64_MAX;

    double sum = 0;
    for (size_t i=0; i<copy_length; ++i) {
        // average wave again...
        sum += result.wave[i];
        if ((i + 1) % average_times == 0) {
            average_wave.push_back(sum / average_times);
            sum = 0;
        }

        if (result.wave[i] < first_percent_voltage) first_percent_position = std::min(first_percent_position, i);
        if (result.wave[i] < second_percent_voltage) second_percent_position = std::min(second_percent_position, i);
    }

    if (first_percent_position == UINT64_MAX || second_percent_position == UINT64_MAX) {
        result.error_code = Error::VOLTAGE_NOT_ENOUGH;
        return false;
    }

    result.tau = (second_percent_position - first_percent_position) * 1e6 / Constant::SafeSamplingFrequency;
    result.error_code = Error::SUCCESS;
    return true;
}

} // namespace Processer
} // namespace Commander
