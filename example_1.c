#include <gtk/gtk.h>
#include "example.h"

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

static void button_clicked(GtkWidget *button, gpointer data) {
    g_print("Button clicked\n");
}

void av_plot() {
    gtk_init(0, NULL);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "av plot");

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

    GtkWidget *button = gtk_button_new_with_label("new button");
    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);

    GtkWidget *label = gtk_label_new("this is label");
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);

    gtk_main();
}