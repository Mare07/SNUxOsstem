/*
 * ui.cpp
 */

#include "ui.h"
//#include "../3dconstruction/MedicalDemo4/MedicalDemo4.cxx"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


struct SeedPoint {
	int image;
	int file;
	Point left;
	Point right;
	bool ok;
} seed_point[MAXNUM];

static char* directory = NULL;

static int image_cnt = 0;
static int point_cnt = 0;

static bool success = false;
static Point vol; // vol.x = left, vol.y = right

void make_mha() {
	typedef unsigned char PixelType;
  const unsigned int Dimension = 3;

  typedef itk::Image< PixelType, Dimension > ImageType;
	typedef itk::ImageSeriesReader< ImageType > ReaderType;
	typedef itk::ImageFileWriter< ImageType > WriterType;

	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();

	const unsigned int first = BEGIN;
	const unsigned int last = END;

	const char *path = "./results/ct.res.%d.jpg";
	const char *outputFilename = "result.mha";

	typedef itk::NumericSeriesFileNames NameGeneratorType;

	NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();

	nameGenerator->SetSeriesFormat(path);
	nameGenerator->SetStartIndex(first);
	nameGenerator->SetEndIndex(last);
	nameGenerator->SetIncrementIndex(1);
	std::vector<std::string> names = nameGenerator->GetFileNames();

	reader->SetFileNames(names);
	writer->SetFileName(outputFilename);
	writer->SetInput(reader->GetOutput());

	try {
		writer->Update();
		g_print("[Success] Please check result.mha.\n");
	} catch (itk::ExceptionObject & err) {
		std::cerr << "error" << std::endl;
		std::cerr << err << std::endl;
		return;
	}
	return;
}

void destroy_widget(GtkWidget *widget, gpointer data) {
	gtk_widget_destroy(widget);
}

void show_vol_loc(GtkWidget *widget, gpointer data) {
	if (!success) {
		g_print("Please start processing\n");
		return;
	}

	char str[MAXCHAR];
	sprintf(str, "[Volume]\nleft: %d\nright: %d", vol.x, vol.y);
	gtk_label_set_text(GTK_LABEL((GtkWidget *)data), str);

        
        pid_t pid = fork();
        if(pid == 0){
            execl( "../3dconstruction/MedicalDemo4/build/MedicalDemo4", "../3dconstruction/MedicalDemo4/build/MedicalDemo4", "result.mha", (const char *) 0);
        }
        else{
            waitpid(pid, 0, 0);
        }


}

void start_processing(GtkWidget *widget, gpointer data) {
	if (image_cnt != MAXNUM) {
		g_print("Please open images. (REQUIRE %d)\n", MAXNUM);
		return;
	}
	if (point_cnt != MAXNUM) {
		g_print("Please input seed points. (REQUIRE 2 * %d)\n", MAXNUM);
		return;
	}
	if (directory == NULL) {
		g_print("Please select directory.\n");
		return;
	}

	// start processing
	
	// add '/' at the end of directory
	string dir = directory;
	dir += '/';

	vol.x = 0;
	vol.y = 0;

	int i;
	for (i = 0; i < MAXNUM; i++) {
		/*
		int begin = seed_point[i].file;
		if (begin < BEGIN) begin = BEGIN;
		int end = END;
		if (i != MAXNUM-1) end = seed_point[i+1].file-1;
		*/
		int begin, end;
		if (i == 0) {
			begin = seed_point[i].file;
			end = seed_point[i+1].file;
		} else if (i == MAXNUM-1) {
			begin = seed_point[i].file;
			end = seed_point[i-1].file;
		} else {
			begin = BEGIN;
			end = END;
		}
		/*
		if (begin >= end) {
			g_print("[Fail] Please check the order of the images.\n");
			return;
		}*/

		if (i != 1) {
			Point tmp = floodfill(seed_point[i].left, seed_point[i].right, dir, begin, end);
			vol.x += tmp.x;
			vol.y += tmp.y;
		}
	}

	g_print("[Success] Please check results directory.\n");
	success = true;
	make_mha();
	//gtk_widget_destroy(widget);
	return;
}

void get_seed_point(GtkWidget *widget, GdkEventButton *event, gpointer data) {
	const gchar *label_txt = gtk_label_get_text(GTK_LABEL((GtkWidget *)data));
	int image_num;
	sscanf(label_txt, "%*s %d", &image_num);
	
	bool ok = seed_point[image_num-1].ok;
	int width = gtk_widget_get_allocated_width(widget);

	if (event->x <= width / 2) {
		// left
		seed_point[image_num-1].left.x = event->x;
		seed_point[image_num-1].left.y = event->y;
	} else {
		// right
		seed_point[image_num-1].right.x = event->x;
		seed_point[image_num-1].right.y = event->y;
	}

	if ((seed_point[image_num-1].left.x >= 0) && (seed_point[image_num-1].right.x >= 0)) {
		if (!ok) {
			seed_point[image_num-1].ok = true;
			point_cnt++;
		}
	}

	char str[MAXCHAR];
	sprintf(str, "[Image %d] left: (%d, %d) right: (%d, %d)",
			image_num, seed_point[image_num-1].left.x, seed_point[image_num-1].left.y,
			seed_point[image_num-1].right.x, seed_point[image_num-1].right.y);
	gtk_label_set_text(GTK_LABEL((GtkWidget *)data), str);
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
		seed_point[image_cnt-1].left = Point(-1, -1);
		seed_point[image_cnt-1].right = Point(-1, -1);
		seed_point[image_cnt-1].ok = false;

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
	GtkWidget *button4;
	GtkWidget *label1;
	GtkWidget *label2;

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
	
	/* label1 */
  label1 = gtk_label_new("Directory: ...");
 	gtk_box_pack_start(GTK_BOX(box), label1, FALSE, FALSE, 0);

	/* button2 */
	button2 = gtk_button_new_with_label("Select Directory");
	g_signal_connect(button2, "clicked", G_CALLBACK(select_directory), label1);
	gtk_box_pack_start(GTK_BOX(box), button2, FALSE, FALSE, 0);
	
	/* button3 */
	button3 = gtk_button_new_with_label("Start Processing");
	g_signal_connect(button3, "clicked", G_CALLBACK(start_processing), window);
	gtk_box_pack_start(GTK_BOX(box), button3, FALSE, FALSE, 0);
		
	/* label2 */
	label2 = gtk_label_new("[Sinus Volume]\nleft: ...\nright: ...");
	gtk_box_pack_start(GTK_BOX(box), label2, FALSE, FALSE, 0);

	/* button4 */
	button4 = gtk_button_new_with_label("Show volume");
	g_signal_connect(button4, "clicked", G_CALLBACK(show_vol_loc), label2);
	gtk_box_pack_start(GTK_BOX(box), button4, FALSE, FALSE, 0);
	
	/* show */
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
