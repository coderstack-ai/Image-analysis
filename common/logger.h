#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>
#include <atomic>
#include <string>
#include <iostream>

extern std::shared_ptr<spdlog::logger> global_log;
extern std::atomic<bool> logger_is_init;
#define __FILENAME__ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1) : __FILE__)

#define LOG_INFO(fmt_str, ...)                                                                                     \
  do {                                                                                                             \
    std::string message = fmt::format("[{}:{}] {}:" fmt_str, __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
    if (logger_is_init.load()) {                                                                                   \
      global_log->info(message);                                                                                   \
    } else {                                                                                                       \
      std::cout << message << std::endl;                                                                           \
    }                                                                                                              \
  } while (0)

#define LOG_WARN(fmt_str, ...)                                                                                     \
  do {                                                                                                             \
    std::string message = fmt::format("[{}:{}] {}:" fmt_str, __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
    if (logger_is_init.load()) {                                                                                   \
      global_log->warn(message);                                                                                   \
    } else {                                                                                                       \
      std::cout << message << std::endl;                                                                           \
    }                                                                                                              \
  } while (0)

#define LOG_ERROR(fmt_str, ...)                                                                                    \
  do {                                                                                                             \
    std::string message = fmt::format("[{}:{}] {}:" fmt_str, __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
    if (logger_is_init.load()) {                                                                                   \
      global_log->error(message);                                                                                  \
    } else {                                                                                                       \
      std::cout << message << std::endl;                                                                           \
    }                                                                                                              \
  } while (0)

extern void LoggerInit(std::string log_path);
extern void LoggerShutdown();