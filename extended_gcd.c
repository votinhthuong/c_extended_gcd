#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

int extended_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extended_gcd(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return gcd;
}


void on_calculate_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const char *a_text = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const char *b_text = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    int a = atoi(a_text);
    int b = atoi(b_text);

    int x, y;
    int gcd = extended_gcd(a, b, &x, &y);

    char result[256];
    snprintf(result, sizeof(result), "GCD(%d, %d) = %d\nx = %d\ny = %d", a, b, gcd, x, y);
    gtk_label_set_text(GTK_LABEL(entries[2]), result);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *a_label, *b_label;
    GtkWidget *a_entry, *b_entry;
    GtkWidget *calculate_button;
    GtkWidget *result_label;
    GtkWidget *entries[3];

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Extended GCD Calculator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    a_label = gtk_label_new("Enter A:");
    b_label = gtk_label_new("Enter B:");

    a_entry = gtk_entry_new();
    b_entry = gtk_entry_new();

    calculate_button = gtk_button_new_with_label("Calculate");
    result_label = gtk_label_new("Result will be displayed here");

    gtk_grid_attach(GTK_GRID(grid), a_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), a_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), b_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), b_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), calculate_button, 0, 2, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), result_label, 0, 3, 2, 1);

    entries[0] = a_entry;
    entries[1] = b_entry;
    entries[2] = result_label;

    g_signal_connect(calculate_button, "clicked", G_CALLBACK(on_calculate_button_clicked), entries);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
