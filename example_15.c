#include <cairo.h>
#include <gtk/gtk.h>

static void do_drawing(cairo_t *, GtkWidget *widget);

int points[11][2] = { 
    { 0, 85 }, 
    { 75, 75 }, 
    { 100, 10 }, 
    { 125, 75 }, 
    { 200, 85 },
    { 150, 125 }, 
    { 160, 190 },
    { 100, 150 }, 
    { 40, 190 },
    { 50, 125 },
    { 0, 85 } 
};

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{      
  do_drawing(cr, widget);

  return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget)
{
  static gdouble angle = 0;
  static gdouble scale = 1;
  static gdouble delta = 0.01;

  GtkWidget *win = gtk_widget_get_toplevel(widget);
  
  gint width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);

  cairo_set_source_rgb(cr, 0, 0.44, 0.7);
  cairo_set_line_width(cr, 1);

  cairo_translate(cr, width/2, height/2 );
  cairo_rotate(cr, angle);
  cairo_scale(cr, scale, scale);

  gint i;

  for ( i = 0; i < 10; i++ ) {
      cairo_line_to(cr, points[i][0], points[i][1]);
  }

  cairo_close_path(cr);
  cairo_fill(cr);
  cairo_stroke(cr);

  if ( scale < 0.01 ) {
      delta = -delta;
  } else if (scale > 0.99) {
      delta = -delta;
  }

  scale += delta;
  angle += 0.01;    
}

static gboolean time_handler(GtkWidget *widget)
{
  gtk_widget_queue_draw(widget);
  
  return TRUE;
}


void av_plot()
{
  GtkWidget *window;
  GtkWidget *darea;

  gtk_init(0, NULL);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), darea);  

  g_signal_connect(G_OBJECT(darea), "draw", 
      G_CALLBACK(on_draw_event), NULL); 
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);
 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); 
  gtk_window_set_title(GTK_WINDOW(window), "Star");

  g_timeout_add(10, (GSourceFunc) time_handler, (gpointer) window);  

  gtk_widget_show_all(window);

  gtk_main();

}