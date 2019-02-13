cmake_minimum_required(VERSION 3.12)
project(Carrier_Sample)

set(CMAKE_CXX_STANDARD 17)

add_executable(Carrier_Sample main.cpp constant.hpp commander/base.cpp commander/base.hpp error/error.hpp config/sampling_config.cpp config/sampling_config.hpp error/error.cpp sampler/bdaqctrl.h sampler/sampler_factory.cpp sampler/sampler_factory.hpp sampler/sampler.hpp result/sampling_result.hpp sampler/mock_sampler.cpp sampler/mock_sampler.hpp sampler/real_sampler.hpp global/global.cpp global/global.hpp commander/commander.cpp commander/commander.hpp commander/measure.cpp commander/measure.hpp processer/processer.hpp processer/processer.cpp)