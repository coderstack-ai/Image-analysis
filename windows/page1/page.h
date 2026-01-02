#pragma once
#include <gtk/gtk.h>

class Page1 {
 public:
  static GtkWidget* Create();

 private:
  static GtkWidget* CreateLeftBox();
  static GtkWidget* CreateRightBox();
  static void SetBackgroundColor(GtkWidget* widget, const char* color);
};
