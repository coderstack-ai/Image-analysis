#include "main_window.h"
#include <gdk/win32/gdkwin32.h>
#include <gio/gfile.h>
#include <windows.h>

MainWindow* MainWindow::GetInstance() {
  static MainWindow instance;
  return &instance;
}

MainWindow::MainWindow() {
  app_ = gtk_application_new("com.example.gtk4.cpp", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app_, "activate", G_CALLBACK(MainWindow::OnActivateStatic), this);
}

MainWindow::~MainWindow() {
  if (app_) {
    g_object_unref(app_);
    app_ = nullptr;
  }
}

void MainWindow::OnActivateStatic(GtkApplication* app, gpointer user_data) {
  auto* self = static_cast<MainWindow*>(user_data);
  self->OnActivate(app);
}

void MainWindow::OnActivate(GtkApplication* app) {
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
    GtkWidget* page1 = CreatePage1();
    GtkWidget* page2 = CreatePage2();
    GtkWidget* page3 = CreatePage3();

    gtk_stack_add_titled(GTK_STACK(stack), page1, "page1", "图像读取");
    gtk_stack_add_titled(GTK_STACK(stack), page2, "page2", "直方图");
    gtk_stack_add_titled(GTK_STACK(stack), page3, "page3", "叶脉检测");

    /* 将堆栈添加到主容器 */
    gtk_box_append(GTK_BOX(main_box), stack);
  }

  gtk_window_present(window_);
}

GtkWidget* MainWindow::CreatePage1() {
  /* 创建页面容器 */
  GtkWidget* page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_margin_start(page, 20);
  gtk_widget_set_margin_end(page, 20);
  gtk_widget_set_margin_top(page, 20);
  gtk_widget_set_margin_bottom(page, 20);

  /* 添加图片显示组件 */
  picture_ = GTK_PICTURE(gtk_picture_new());
  gtk_picture_set_content_fit(picture_, GTK_CONTENT_FIT_CONTAIN);
  gtk_picture_set_can_shrink(picture_, TRUE);
  gtk_widget_set_hexpand(GTK_WIDGET(picture_), TRUE);
  gtk_widget_set_vexpand(GTK_WIDGET(picture_), TRUE);

  /* 创建滚动窗口以容纳图片 */
  GtkWidget* scrolled_window = gtk_scrolled_window_new();
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), GTK_WIDGET(picture_));
  gtk_scrolled_window_set_policy(
      GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_box_append(GTK_BOX(page), scrolled_window);

  return page;
}

GtkWidget* MainWindow::CreatePage2() {
  /* 创建页面容器 */
  GtkWidget* page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_margin_start(page, 20);
  gtk_widget_set_margin_end(page, 20);
  gtk_widget_set_margin_top(page, 20);
  gtk_widget_set_margin_bottom(page, 20);

  /* 添加高级功能标签 */
  GtkWidget* advanced_label = gtk_label_new("高级功能页面");
  gtk_label_set_markup(GTK_LABEL(advanced_label),
                       "<span size='xx-large' weight='bold'>高级功能</span>");
  gtk_box_append(GTK_BOX(page), advanced_label);

  /* 在这里可以添加更多高级功能的组件 */

  return page;
}

GtkWidget* MainWindow::CreatePage3() {
  /* 创建页面容器 */
  GtkWidget* page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_margin_start(page, 20);
  gtk_widget_set_margin_end(page, 20);
  gtk_widget_set_margin_top(page, 20);
  gtk_widget_set_margin_bottom(page, 20);

  /* 添加高级功能标签 */
  GtkWidget* advanced_label = gtk_label_new("高级功能页面3");
  gtk_label_set_markup(GTK_LABEL(advanced_label),
                       "<span size='xx-large' weight='bold'>高级功能</span>");
  gtk_box_append(GTK_BOX(page), advanced_label);

  /* 在这里可以添加更多高级功能的组件 */

  return page;
}