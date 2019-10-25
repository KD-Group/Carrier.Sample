//
// Created by wangcong on 2019/10/23.
//

//#include <glog/logging.h>
#include <fstream>

//const char* DUMP_FILE = "carrier_dump.log";

class GlogConfig {
public:
  GlogConfig(){};

  ~GlogConfig() {
    // google::ShutdownGoogleLogging();
  }

  // void init_glog(char** argv) {
  //   google::InitGoogleLogging(argv[0]);
  //   google::SetStderrLogging(google::GLOG_INFO); //设置级别高于 google::INFO 的日志同时输出到屏幕
  //   google::SetStderrLogging(google::GLOG_FATAL);//设置级别高于 google::FATAL 的日志同时输出到屏幕
  //   FLAGS_colorlogtostderr = true; //设置输出到屏幕的日志显示相应颜色
  //   // 设置 google::FATAL 级别的日志存储路径和文件名前缀
  //   google::SetLogDestination(google::GLOG_FATAL, "./log_fatal_");
  //   //设置 google::ERROR 级别的日志存储路径和文件名前缀
  //   google::SetLogDestination(google::GLOG_ERROR, "./log_error_");
  //   //设置 google::WARNING 级别的日志存储路径和文件名前缀
  //   google::SetLogDestination(google::GLOG_WARNING, "./log_warning_");
  //   //设置 google::INFO 级别的日志存储路径和文件名前缀
  //   google::SetLogDestination(google::GLOG_INFO, "./log_info_");
  //   //缓冲日志输出，默认为30秒，此处改为立即输出
  //   FLAGS_logbufsecs = 0;
  //   //最大日志大小为 10MB
  //   FLAGS_max_log_size = 10;
  //   //当磁盘被写满时，停止日志输出
  //   FLAGS_stop_logging_if_full_disk = true;
  //   //捕捉 core dumped (linux)
  //   google::InstallFailureSignalHandler();
  //   google::InstallFailureWriter([](const char*data, int size){
  //     std::ofstream fs(DUMP_FILE, std::ios::app);
  //     fs<<std::string(data, size);
  //     fs.close();
  //   });
  // }
};
