#pragma once
#include <gio/gio.h>
#include <gtk/gtk.h>

class MainWindow {
 public:
  static MainWindow* GetInstance();

  GtkApplication* app() const { return app_; }
  void OnActivate(GtkApplication* app);

 private:
  MainWindow();
  ~MainWindow();

  MainWindow(const MainWindow&) = delete;
  MainWindow& operator=(const MainWindow&) = delete;

  static void OnActivateStatic(GtkApplication* app, gpointer user_data);

  // 页面创建函数
  GtkWidget* CreatePage1();
  GtkWidget* CreatePage2();
  GtkWidget* CreatePage3();

 private:
  GtkApplication* app_ = nullptr;
  GtkWindow* window_ = nullptr;

  GtkPicture* picture_ = nullptr;  // 用于显示图片
};
