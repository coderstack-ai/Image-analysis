#include "logger.h"
#include "version.h"
#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>

std::shared_ptr<spdlog::logger> global_log;
std::atomic<bool> logger_is_init = false;

void LoggerInit(std::string log_path) {
  global_log = spdlog::rotating_logger_mt<spdlog::async_factory>("file_logger", log_path, 1024 * 1024 * 10, 10);
  global_log->set_level(spdlog::level::debug);
  global_log->flush_on(spdlog::level::debug);
  global_log->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%P:%t%$] [%^%l%$] %v");
  logger_is_init.store(true);

  LOG_INFO("日志初始化");
  std::string version = COMLETE_VERSION;
  LOG_INFO("软件版本:{}", version);
}

void LoggerShutdown() {
  if (logger_is_init.load()) {
    if (global_log) {
      global_log->flush();
      global_log.reset();
    }
    /* 关闭 spdlog 异步日志的后台线程 */
    spdlog::shutdown();
    logger_is_init.store(false);
  }
}
