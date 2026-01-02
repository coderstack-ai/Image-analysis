#include "btn_open_color_file.h"
#include <cstdio>
#include <gio/gfile.h>
#include "common/main.h"
#include "common/logger.h"

GtkWidget* BtnOpenColorFile::Create() {
  GtkWidget* button = gtk_button_new_with_label("打开彩色图片");
  g_signal_connect(button, "clicked", G_CALLBACK(BtnOpenColorFile::OnClicked), nullptr);
  return button;
}

void BtnOpenColorFile::OnClicked(GtkButton* button, gpointer user_data) {
  /* 获取按钮的顶层窗口 */
  GtkWindow* parent = GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(button)));

  /* 创建文件选择对话框 */
  GtkFileDialog* dialog = gtk_file_dialog_new();
  gtk_file_dialog_set_title(dialog, "选择图片文件");
  gtk_file_dialog_set_accept_label(dialog, "打开");

  /* 设置初始文件夹 */
  GFile* folder = g_file_new_for_path("C:/");
  gtk_file_dialog_set_initial_folder(dialog, folder);
  g_object_unref(folder);

  /* 创建文件过滤器 - 使用MIME类型和suffix双保险 */
  GtkFileFilter* filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter, "图片文件 (*.jpg, *.jpeg, *.png)");
  /* 推荐：MIME + 后缀 双保险 */
  gtk_file_filter_add_mime_type(filter, "image/jpeg");
  gtk_file_filter_add_mime_type(filter, "image/png");
  gtk_file_filter_add_suffix(filter, "jpg");
  gtk_file_filter_add_suffix(filter, "jpeg");
  gtk_file_filter_add_suffix(filter, "png");
  gtk_file_filter_add_suffix(filter, "JPG");
  gtk_file_filter_add_suffix(filter, "JPEG");
  gtk_file_filter_add_suffix(filter, "PNG");

  /* 添加过滤器到对话框 */
  GListStore* filters = g_list_store_new(GTK_TYPE_FILE_FILTER);
  g_list_store_append(filters, filter);
  gtk_file_dialog_set_filters(dialog, G_LIST_MODEL(filters));
  gtk_file_dialog_set_default_filter(dialog, filter);
  g_object_unref(filters);

  /* GtkFileDialog默认就是单选模式，无需设置 */

  /* 显示对话框并处理响应 */
  gtk_file_dialog_open(dialog, parent, nullptr, BtnOpenColorFile::OnFileDialogResponse, nullptr);
  g_object_unref(dialog);
}

void BtnOpenColorFile::OnFileDialogResponse(GObject* source_object, GAsyncResult* result, gpointer user_data) {
  GtkFileDialog* dialog = GTK_FILE_DIALOG(source_object);
  GError* error = nullptr;
  GFile* file = gtk_file_dialog_open_finish(dialog, result, &error);

  if (!file) {
    if (error) {
      /* 用户取消或出错 */
      g_error_free(error);
    }
    return; /* 用户取消 */
  }

  char* file_path = g_file_get_path(file);
  if (file_path) {
    std::string file_path_str = file_path;
    LOG_INFO("选择的文件: {}", file_path_str);
    /* 在这里可以添加加载图片的逻辑 */
    Main::GetInstance()->OpenColorFile(file_path_str);
    g_free(file_path);
  }

  g_object_unref(file);
}
