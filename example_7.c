#include <cairo.h>
#include <gtk/gtk.h>

void draw_gradient1(cairo_t *);
void draw_gradient2(cairo_t *);
void draw_gradient3(cairo_t *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    draw_gradient1(cr);
    draw_gradient2(cr);
    draw_gradient3(cr);

    return FALSE;
}

void draw_gradient1(cairo_t *cr) {
    cairo_pattern_t *pat1;
    pat1 = cairo_pattern_create_linear(0.0, 0.0, 350.0, 350.0);

    gdouble j;
    gint count = 1;
    for (j = 0.1; j < 1; j += 0.1) {
        if ((count % 2)) {
            cairo_pattern_add_color_stop_rgb(pat1, j, 0, 0, 0);
        } else {
            cairo_pattern_add_color_stop_rgb(pat1, j , 1, 0, 0);
        }
        count++;
    }

    cairo_rectangle(cr, 20, 20, 300, 100);
    cairo_set_source(cr, pat1);
    cairo_fill(cr);

    cairo_pattern_destroy(pat1);
}

void draw_gradient2(cairo_t *cr) {
    cairo_pattern_t *pat2;
    pat2 = cairo_pattern_create_linear(0.0, 0.0, 350.0, 0.0);

    gdouble i;
    gint count = 1;
    for (i = 0.05; i < 0.95; i += 0.025) {
        if ((count % 2)) {
            cairo_pattern_add_color_stop_rgb(pat2, i, 0, 0, 0);
        } else {
            cairo_pattern_add_color_stop_rgb(pat2, i, 0, 0, 1);
        }
        count++;
    }

    cairo_rectangle(cr, 20, 140, 300, 100);
    cairo_set_source(cr, pat2);
    cairo_fill(cr);

    cairo_pattern_destroy(pat2);
}

void draw_gradient3(cairo_t *cr) {
    cairo_pattern_t *pat3;
    pat3 = cairo_pattern_create_linear(20.0, 260.0, 20.0, 360.0);

    cairo_pattern_add_color_stop_rgb(pat3, 0.1, 0, 0, 0);
    cairo_pattern_add_color_stop_rgb(pat3, 0.5, 1, 1, 0);
    cairo_pattern_add_color_stop_rgb(pat3, 0.9, 0, 0, 0);

    cairo_rectangle(cr, 20, 260, 300, 100);
    cairo_set_source(cr, pat3);
    cairo_fill(cr);

    cairo_pattern_destroy(pat3);
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
    gtk_window_set_default_size(GTK_WINDOW(window), 340, 390);
    gtk_window_set_title(GTK_WINDOW(window), "Linear gradients");

    gtk_widget_show_all(window);

    gtk_main();
}