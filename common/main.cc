#include "main.h"
#include "logger.h"

Main* Main::GetInstance() {
  static Main instance;
  return &instance;
}

void Main::OpenGrayFile(const std::string& path) {
  LOG_INFO("打开灰度图片: {}", path);
}

void Main::OpenColorFile(const std::string& path) {
  LOG_INFO("打开彩色图片: {}", path);
}