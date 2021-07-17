#include <gtk/gtk.h>
#include <cairo.h>
#include "example.h"

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

static void do_drawing(cairo_t *cr) {
    cairo_set_source_rgb(cr, 0.5, 0, 0);
    cairo_paint(cr);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 40.0);

    cairo_move_to(cr, 10.0, 50.0);
    cairo_show_text(cr, "Yudha Styawan");

}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_Data) {
    do_drawing(cr);
    return FALSE;
}

void mywidget() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "av plot");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 90);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);

    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);

    gtk_widget_show_all(window);
}

void show_plot(void (*thewidget)()) {
    gtk_init(0, NULL);
    thewidget();
    gtk_main();
}

void av_plot() {
    cairo_surface_t *mysurface;
    show_plot(mywidget);
}