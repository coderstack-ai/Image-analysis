#pragma once
#include <gtk/gtk.h>

class MainWindow {
 public:
  static GtkApplication* Create();

 private:
  static void OnActivate(GtkApplication* app, gpointer user_data);
};
