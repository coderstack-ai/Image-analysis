#pragma once
#include <gtk/gtk.h>
#include <gio/gio.h>

class BtnOpenColorFile {
 public:
  static GtkWidget* Create();

 private:
  static void OnClicked(GtkButton* button, gpointer user_data);
  static void OnFileDialogResponse(GObject* source_object, GAsyncResult* result, gpointer user_data);
};
