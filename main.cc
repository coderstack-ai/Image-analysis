#include "main_window.h"
#include "common/logger.h"
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  fs::path log_path = fs::current_path() / "log.txt";
  LoggerInit(log_path.string());

  LOG_INFO("程序启动");
  g_log_set_handler(
      "GLib-GIO", (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL), [](const gchar*, GLogLevelFlags, const gchar*, gpointer) {}, nullptr);
  int ret = g_application_run(G_APPLICATION(MainWindow::Create()), argc, argv);
  LOG_INFO("程序退出");
  /* 确保日志系统正确关闭 */
  LoggerShutdown();
  return ret;
}
