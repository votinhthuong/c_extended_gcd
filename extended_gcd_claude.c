#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int gcd(int a, int b, int *x, int *y);
void on_calculate_clicked(GtkWidget *widget, gpointer data);

// Global variables for GUI elements
GtkWidget *entry_a, *entry_b, *label_result;

int main(int argc, char *argv[]) {
    GtkWidget *window, *grid, *button;

    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GCD and Bezout's Identity Calculator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a grid to organize the widgets
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create and add input fields
    entry_a = gtk_entry_new();
    entry_b = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Enter A:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_a, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Enter B:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_b, 1, 1, 1, 1);

    // Create and add the calculate button
    button = gtk_button_new_with_label("Calculate");
    g_signal_connect(button, "clicked", G_CALLBACK(on_calculate_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 2, 1);

    // Create and add the result label
    label_result = gtk_label_new("Result will appear here");
    gtk_grid_attach(GTK_GRID(grid), label_result, 0, 3, 2, 1);

    // Show all widgets and start the main loop
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

// Function to calculate GCD and find x, y for Bezout's identity
int gcd(int a, int b, int *x, int *y) {
    // Base case
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcd_value = gcd(b % a, a, &x1, &y1);

    // Update x and y using results of recursive call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd_value;
}

// Callback function for the calculate button
void on_calculate_clicked(GtkWidget *widget, gpointer data) {
    int a, b, x, y, result;
    char output[100];

    // Get values from entry fields
    a = atoi(gtk_entry_get_text(GTK_ENTRY(entry_a)));
    b = atoi(gtk_entry_get_text(GTK_ENTRY(entry_b)));

    // Calculate GCD and find x, y
    result = gcd(a, b, &x, &y);

    // Format and display the result
    snprintf(output, sizeof(output), "GCD(%d, %d) = %d\nx = %d, y = %d\n%d * %d + %d * %d = %d",
             a, b, result, x, y, a, x, b, y, result);
    gtk_label_set_text(GTK_LABEL(label_result), output);
}