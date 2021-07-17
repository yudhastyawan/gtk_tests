#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

static void do_drawing(cairo_t *, GtkWidget *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    do_drawing(cr, widget);
    return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget) {
    static gdouble const trs[8][8] = {
        {0.0, 0.15, 0.30, 0.5, 0.65, 0.80, 0.9, 1.0},
        {1.0, 0.0, 0.15, 0.30, 0.5, 0.65, 0.80, 0.9},
        {0.9, 1.0, 0.0, 0.15, 0.30, 0.5, 0.65, 0.80},
        {0.80, 0.9, 1.0, 0.0, 0.15, 0.30, 0.5, 0.65},
        {0.65, 0.80, 0.9, 1.0, 0.0, 0.15, 0.30, 0.5},
        {0.5, 0.65, 0.80, 0.9, 1.0, 0.0, 0.15, 0.30},
        {0.30, 0.5, 0.65, 0.80, 0.9, 1.0, 0.0, 0.15},
        {0.15, 0.30, 0.5, 0.65, 0.80, 0.9, 1.0, 0.0}
    };

    GtkWidget *win = gtk_widget_get_toplevel(widget);

    gint width, height;
    gtk_window_get_size(GTK_WINDOW(win), &width, &height);

    cairo_translate(cr, width/2, height/2);

    cairo_set_line_width(cr, 3);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_source_rgba(cr, 0, 0, 0, trs[0][7]);

    cairo_move_to(cr, 0.0, -10.0);
    cairo_line_to(cr, 0.0, -40.0);
    cairo_rotate(cr, M_PI/4); // yang dirotate itu sumbunya, bukan bendanya

    cairo_stroke(cr);

    cairo_set_line_width(cr, 3);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_source_rgba(cr, 0, 0, 0, trs[0][7]);

    cairo_move_to(cr, 0.0, -10.0);
    cairo_line_to(cr, 0.0, -40.0);
    cairo_rotate(cr, M_PI/4);

    cairo_stroke(cr);
}

void av_plot() {
    GtkWidget *window, *darea;

    gtk_init(0, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);

    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 150);
    gtk_window_set_title(GTK_WINDOW(window), "waiting demo");

    gtk_widget_show_all(window);

    gtk_main();
}