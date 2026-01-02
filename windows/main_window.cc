#include "main_window.h"
#include "page1/page.h"
#include "page2/page.h"
#include "page3/page.h"
#include "common/logger.h"
#include <gdk/win32/gdkwin32.h>
#include <gio/gfile.h>
#include <windows.h>

GtkApplication* MainWindow::Create() {
  /* 使用 G_APPLICATION_NON_UNIQUE 标志，允许应用程序在窗口关闭时退出 */
  GtkApplication* app = gtk_application_new("com.example.gtk4.cpp", G_APPLICATION_NON_UNIQUE);
  g_signal_connect(app, "activate", G_CALLBACK(MainWindow::OnActivate), nullptr);
  return app;
}

void MainWindow::OnActivate(GtkApplication* app, gpointer user_data) {
  static GtkWindow* window_ = nullptr;
  if (!window_) {
    window_ = GTK_WINDOW(gtk_application_window_new(app));
    gtk_window_set_title(window_, "图像分析工具");

    /* 固定窗口尺寸为 1920x1080 */
    gtk_window_set_default_size(window_, 1920, 1080);

    gtk_window_set_resizable(window_, FALSE); /* 不允许调整大小 */
    gtk_window_set_decorated(window_, TRUE);  /* 设置窗口有装饰 */

    /* 创建主容器 */
    GtkWidget* main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(window_, main_box);

    /* 创建堆栈和切换器 */
    GtkWidget* stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    GtkWidget* switcher = gtk_stack_switcher_new();
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(switcher), GTK_STACK(stack));

    /* 将切换器添加到主容器 */
    gtk_box_append(GTK_BOX(main_box), switcher);

    /* 创建页面并添加到堆栈 */
    GtkWidget* page1 = Page1::Create();
    GtkWidget* page2 = Page2::Create();
    GtkWidget* page3 = Page3::Create();

    gtk_stack_add_titled(GTK_STACK(stack), page1, "page1", "图像读取");
    gtk_stack_add_titled(GTK_STACK(stack), page2, "page2", "直方图");
    gtk_stack_add_titled(GTK_STACK(stack), page3, "page3", "叶脉检测");

    /* 将堆栈添加到主容器 */
    gtk_box_append(GTK_BOX(main_box), stack);
  }
  gtk_window_present(window_);
}
