#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

void destroy_widget(GtkWidget *widget, gpointer data) {
	gtk_widget_destroy(widget);
}

void start_processing(GtkWidget *widget, gpointer data) {
	// TODO
}

void open_image(GtkWidget *widget, gpointer data) {
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *button;
	GtkWidget *image;
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	GtkFileFilter *filter = gtk_file_filter_new();
	gint res;
	char *filename = NULL;

	/* window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window, 512, 512);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_title(GTK_WINDOW(window), "Input Seed Point");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy_widget), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 1);

	/* dialog */
	dialog = gtk_file_chooser_dialog_new("Select File",
			NULL, action, "_Cancel", GTK_RESPONSE_CANCEL,
			"_Open", GTK_RESPONSE_ACCEPT, NULL);

	gtk_file_filter_add_pixbuf_formats(filter);
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

	gtk_window_set_title(GTK_WINDOW(dialog), "Select File");
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	
	if (res == GTK_RESPONSE_ACCEPT) {
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
	  printf("%s\n", filename);
	
	  /* box */
	  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	  gtk_container_add(GTK_CONTAINER(window), box);

	  /* button */
	  button = gtk_button_new_with_label("Start Processing");
	  g_signal_connect(button, "clicked", G_CALLBACK(start_processing), window);
	  gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
		
		/* image */
	  image = gtk_image_new_from_file(filename);
		gtk_box_pack_start(GTK_BOX(box), image, TRUE, TRUE, 0);

		/* destroy */
		gtk_widget_destroy((GtkWidget *)data);

		/* show */
		gtk_widget_show_all(window);
	}
	gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *button;

	gtk_init(&argc, &argv);

	/* window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_title(GTK_WINDOW(window), "SNU");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy_widget), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	
	/* box */
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(window), box);

	/* button */
	button = gtk_button_new_with_label("Upload Image");
	g_signal_connect(button, "clicked", G_CALLBACK(open_image), window);
	gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);

	/* show */
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
