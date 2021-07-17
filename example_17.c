#include <gtk/gtk.h>

void window_first();
void enter_window2(GtkWidget* w, gpointer data);
void window_second();
void show_widget();

void av_plot()
{
    show_widget(window_first);
}

void show_widget(void (*window_func)()) {
    gtk_init(0, NULL);
    window_func();
    gtk_main();
}

void enter_window2(GtkWidget* w, gpointer data)
{
    GtkWindow *window1 = GTK_WINDOW(data);
    g_signal_handlers_disconnect_by_func(window1, gtk_main_quit, NULL);
    gtk_widget_destroy(GTK_WIDGET(window1));
    window_second();
}

void window_first()
{
    GtkWidget *window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *enter_window2_button = gtk_button_new_with_label("enter_window2");
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

    gtk_box_pack_start(GTK_BOX(vbox),enter_window2_button, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window1), vbox);

    g_signal_connect(window1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(enter_window2_button, "clicked", G_CALLBACK(enter_window2), window1);

    gtk_widget_show_all(window1);
}

void window_second()
{
    GtkWidget *window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show_all(window2);

    g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}