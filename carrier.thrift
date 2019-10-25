// Create by wangcong 2019/10/22

namespace cpp TCarrier

struct TResult {
    1: required map<string, string> ErrorMessageMapper,
    2: required bool error,
    3: required string message,
    4: required string sampler_name,
    5: required bool measuring,
    6: required double max_voltage,
    7: required double min_voltage,
    8: required double sampling_interval,
    9: required list<double> wave,
    10: required double tau
}

struct TSamplingConfig {
    1: required i8 number_of_waveforms,
    2: required double first_percent,
    3: required double second_percent
}


enum TReturnCode {
    SUCCESS=0,

    // error of human
    COMMAND_NOT_FOUND,
    SAMPLER_NOT_FOUND,
    IN_MEASURING,

    // error of sampling
    VOLTAGE_NOT_ENOUGH,
    REAL_SAMPLER_ERROR,
    WAVE_NOT_FOUND,
    APPROPRIATE_PERCENT_WAVE_NOT_FOUND,
}

service TCarrier {
    // 所有设置操作均需对返回码做检查, to_query需要对Result.error做检查, 若有错误则查看message错误信息
    TReturnCode set_sampler(1: string sampler_name),
    string get_sampler(),
    TReturnCode set_sampler_value(1: string key, 2: double value),
    string get_sampler_value(1: string key),

    bool is_measuring(),
    TReturnCode measure(1: TSamplingConfig config),
    TResult to_query()
}

