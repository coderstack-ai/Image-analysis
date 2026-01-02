#pragma once
#include <string>
#include <opencv2/opencv.hpp>

class Main {
 public:
  static Main* GetInstance();

  // 禁止复制和赋值
  Main(const Main&) = delete;
  Main& operator=(const Main&) = delete;

  void OpenGrayFile(const std::string& path);
  void OpenColorFile(const std::string& path);

 private:
  Main() = default;
  ~Main() = default;

  cv::Mat gray_image_;
};
