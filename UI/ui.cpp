#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;

#define MAXCHAR 256
#define MAXNUM  3

struct SeedPoint {
	int image;
	int file;
	Point point;
} seed_point[3];

static char* directory = NULL;

static int image_cnt = 0;
static int point_cnt = 0;

void destroy_widget(GtkWidget *widget, gpointer data) {
	gtk_widget_destroy(widget);
}

void start_processing(GtkWidget *widget, gpointer data) {
	if (point_cnt != MAXNUM) {
		g_print("Please input seed points. (REQUIRE %d)\n", MAXNUM);
		return;
	}
	if (directory == NULL) {
		g_print("Please select directory.\n");
		return;
	}
}

void get_seed_point(GtkWidget *widget, GdkEventButton *event, gpointer data) {
	const gchar *label_txt = gtk_label_get_text(GTK_LABEL((GtkWidget *)data));
	int image_num;
	sscanf(label_txt, "%*s %d", &image_num);

	char str[MAXCHAR];
	sprintf(str, "[Image %d] x:%.2f, y:%.2f", image_num, event->x, event->y);
	gtk_label_set_text(GTK_LABEL((GtkWidget *)data), str);

	if (seed_point[image_num-1].point.x == -1) {
		point_cnt++;
	}
	seed_point[image_num-1].point.x = event->x;
	seed_point[image_num-1].point.y = event->y;
}

void open_image(GtkWidget *widget, gpointer data) {
	if (image_cnt == MAXNUM) {
		g_print("Please start processing. (MAX IMG = %d)\n", MAXNUM);
		return;
	}

	image_cnt++;
	
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *event_box;
	GtkWidget *image;
	GtkWidget *dialog;
	GtkWidget *label;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	GtkFileFilter *filter = gtk_file_filter_new();
	gint res;
	char *filename;

	/* window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
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
	
	  /* box */
	  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	  gtk_container_add(GTK_CONTAINER(window), box);
		
		/* label */
		char label_txt[MAXCHAR];
		sprintf(label_txt, "[Image %d] Click Image", image_cnt);
		label = gtk_label_new(label_txt);
		gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

		/* event_box */
		event_box = gtk_event_box_new();
		g_signal_connect(event_box, "button-press-event", G_CALLBACK(get_seed_point), label);
		gtk_box_pack_start(GTK_BOX(box), event_box, FALSE, FALSE, 0);

		/* image */
	  image = gtk_image_new_from_file(filename);
		gtk_container_add(GTK_CONTAINER(event_box), image);

		/* seed point initialize */
		/* filename format: (dir)/ct.xxx.jpg */
		char *name = strstr(filename, "ct.");
		int file_num;
		sscanf(name, "ct.%d.jpg", &file_num);
		
		seed_point[image_cnt-1].image = image_cnt;
		seed_point[image_cnt-1].file  = file_num;
		seed_point[image_cnt-1].point = Point(-1, -1);

		/* show */
		gtk_widget_show_all(window);
	}
	gtk_widget_destroy(dialog);
}

void select_directory(GtkWidget *widget, gpointer data) {
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
	gint res;

	/* dialog */
	dialog = gtk_file_chooser_dialog_new("Select Directory",
			NULL, action, "_Cancel", GTK_RESPONSE_CANCEL,
			"_Open", GTK_RESPONSE_ACCEPT, NULL);

	gtk_window_set_title(GTK_WINDOW(dialog), "Select Directory");
	res = gtk_dialog_run(GTK_DIALOG(dialog));

	if (res == GTK_RESPONSE_ACCEPT) {
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		directory = gtk_file_chooser_get_filename(chooser);

		gtk_label_set_text(GTK_LABEL((GtkWidget *)data), directory);
	}
	gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *button1;
	GtkWidget *button2;
	GtkWidget *button3;
	GtkWidget *label;

	gtk_init(&argc, &argv);

	/* window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_title(GTK_WINDOW(window), "SNU");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	
	/* box */
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(window), box);

	/* button1 */
	button1 = gtk_button_new_with_label("Select Image");
	g_signal_connect(button1, "clicked", G_CALLBACK(open_image), window);
	gtk_box_pack_start(GTK_BOX(box), button1, FALSE, FALSE, 0);
	
	/* label */
  label = gtk_label_new("Directory: ...");
 	gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

	/* button2 */
	button2 = gtk_button_new_with_label("Select Directory");
	g_signal_connect(button2, "clicked", G_CALLBACK(select_directory), label);
	gtk_box_pack_start(GTK_BOX(box), button2, FALSE, FALSE, 0);
	
	/* button3 */
	button3 = gtk_button_new_with_label("Start Processing");
	g_signal_connect(button3, "clicked", G_CALLBACK(start_processing), window);
	gtk_box_pack_start(GTK_BOX(box), button3, FALSE, FALSE, 0);
		
	/* show */
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
