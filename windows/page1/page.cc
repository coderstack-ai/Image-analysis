#include "page.h"
#include "btn_open_gray_file.h"
#include "btn_open_color_file.h"
#include <cstdio>
#include <gdk/gdk.h>

GtkWidget* Page1::Create() {
  /* 创建页面容器 - 使用水平盒子布局 */
  GtkWidget* page = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_widget_set_margin_start(page, 20);
  gtk_widget_set_margin_end(page, 20);
  gtk_widget_set_margin_top(page, 20);
  gtk_widget_set_margin_bottom(page, 20);

  /* 创建左右两列 */
  GtkWidget* left_box = CreateLeftBox();
  GtkWidget* right_box = CreateRightBox();

  /* 设置背景颜色 */
  // SetBackgroundColor(page, "#f50000");      /* 页面背景：浅灰色 */
  // SetBackgroundColor(left_box, "#ffffff");  /* 左侧背景：白色 */
  // SetBackgroundColor(right_box, "#e8e8e8"); /* 右侧背景：浅灰色 */

  /* 添加到主容器 */
  gtk_box_append(GTK_BOX(page), left_box);
  gtk_box_append(GTK_BOX(page), right_box);

  return page;
}

GtkWidget* Page1::CreateLeftBox() {
  /* 添加图片显示组件 */
  GtkPicture* picture = GTK_PICTURE(gtk_picture_new());
  gtk_picture_set_content_fit(picture, GTK_CONTENT_FIT_CONTAIN);
  gtk_picture_set_can_shrink(picture, TRUE);
  gtk_widget_set_hexpand(GTK_WIDGET(picture), TRUE);
  gtk_widget_set_vexpand(GTK_WIDGET(picture), TRUE);

  /* 创建滚动窗口以容纳图片 */
  GtkWidget* scrolled_window = gtk_scrolled_window_new();
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), GTK_WIDGET(picture));
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  /* 设置左侧固定宽度为800px */
  gtk_widget_set_size_request(scrolled_window, 1200, -1);

  return scrolled_window;
}

GtkWidget* Page1::CreateRightBox() {
  /* 创建右侧垂直盒子 */
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  gtk_widget_set_margin_top(box, 20);
  gtk_widget_set_margin_bottom(box, 20);
  gtk_widget_set_margin_start(box, 20);
  gtk_widget_set_margin_end(box, 20);
  gtk_widget_set_hexpand(box, TRUE);

  GtkWidget* btn_open_gray_file = BtnOpenGrayFile::Create();
  GtkWidget* btn_open_color_file = BtnOpenColorFile::Create();
  gtk_box_append(GTK_BOX(box), GTK_WIDGET(btn_open_color_file));
  gtk_box_append(GTK_BOX(box), GTK_WIDGET(btn_open_gray_file));

  return box;
}

void Page1::SetBackgroundColor(GtkWidget* widget, const char* color) {
  /* 为widget添加唯一的CSS类名 */
  static int counter = 0;
  char class_name[32];
  snprintf(class_name, sizeof(class_name), "bg-color-%d", counter++);
  gtk_widget_add_css_class(widget, class_name);

  /* 创建CSS样式 */
  char css[256];
  snprintf(css, sizeof(css), ".%s { background-color: %s; }", class_name, color);

  GtkCssProvider* provider = gtk_css_provider_new();
  gtk_css_provider_load_from_string(provider, css);

  GdkDisplay* display = gtk_widget_get_display(widget);
  gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  g_object_unref(provider);
}
