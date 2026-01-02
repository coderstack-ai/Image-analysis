#include "page.h"

GtkWidget* Page2::Create() {
  /* 创建页面容器 */
  GtkWidget* page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_margin_start(page, 20);
  gtk_widget_set_margin_end(page, 20);
  gtk_widget_set_margin_top(page, 20);
  gtk_widget_set_margin_bottom(page, 20);

  /* 添加高级功能标签 */
  GtkWidget* advanced_label = gtk_label_new("高级功能页面");
  gtk_label_set_markup(GTK_LABEL(advanced_label), "<span size='xx-large' weight='bold'>高级功能</span>");
  gtk_box_append(GTK_BOX(page), advanced_label);

  /* 在这里可以添加更多高级功能的组件 */

  return page;
}
