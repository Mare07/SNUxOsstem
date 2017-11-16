/*
 * ui.cpp
 */

#include "ui.h"

struct SeedPoint {
	int image;
	int file;
	Point left;
	Point right;
	bool ok;
} seed_point[MAXNUM];

static char* directory = NULL;
static char* mha_file = NULL;

static int image_cnt = 0;
static int point_cnt = 0;

static bool success = false;
static Point vol; // vol.x = left, vol.y = right

void make_mha(const char *path, const char *outputFilename) {
	typedef unsigned char PixelType;
  const unsigned int Dimension = 3;

  typedef itk::Image< PixelType, Dimension > ImageType;
	typedef itk::ImageSeriesReader< ImageType > ReaderType;
	typedef itk::ImageFileWriter< ImageType > WriterType;

	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();

	const unsigned int first = BEGIN;
	const unsigned int last = END;

	//const char *path = "./results/ct.res.%d.jpg";
	//const char *outputFilename = "result.mha";

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
		g_print("[Success] Please check %s.\n", outputFilename);
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

	// voxel -> cc
	float left_vol, right_vol;
	float total_cc = 232.45318 * 4;
	float total_vo = 12556800;
	left_vol = total_cc * vol.x / total_vo;
	right_vol = total_cc * vol.y / total_vo;

	char str[MAXCHAR];
	sprintf(str, "[Volume]\nleft: %.3f cc\nright: %.3f cc", left_vol, right_vol);
	gtk_label_set_text(GTK_LABEL((GtkWidget *)data), str);

	const gchar *btn = gtk_button_get_label(GTK_BUTTON(widget));
	
	pid_t pid = fork();
	if (pid == 0) {
		if (btn[2] == '1') {
			execl( "../3dconstruction/MedicalDemo4/build/MedicalDemo4", "../3dconstruction/MedicalDemo4/build/MedicalDemo4", "result0.mha", (const char *) 0);
		} else {
			execl( "../3dconstruction/MedicalDemo4/build/MedicalDemo4", "../3dconstruction/MedicalDemo4/build/MedicalDemo4", "result1.mha", (const char *) 0);
		}
	}
}

void start_processing(GtkWidget *widget, gpointer data) {
	/*
	if (image_cnt != MAXNUM) {
		g_print("Please open images. (REQUIRE %d)\n", MAXNUM);
		return;
	}
	*/
	if (point_cnt != MAXNUM) {
		g_print("Please input seed points. (REQUIRE %d)\n", MAXNUM);
		return;
	}
	/*
	if (directory == NULL) {
		g_print("Please select directory.\n");
		return;
	}
	*/

	// start processing
	
	// add '/' at the end of directory
	string dir = directory;
	dir += '/';

	vol.x = 0;
	vol.y = 0;

	/*
	int i;
	for (i = 0; i < MAXNUM; i++) {
		int begin, end;
		if (i == 0) {
			begin = seed_point[i].file;
			end = seed_point[i+1].file;
		} else if (i == MAXNUM-1) {
			begin = seed_point[i].file+1;
			end = seed_point[i-1].file;
		} else {
			begin = BEGIN;
			end = END;
		}

		if (i != 1) {
			Point tmp = floodfill(seed_point[i].left, seed_point[i].right, dir, begin, end);
			vol.x += tmp.x;
			vol.y += tmp.y;
		}
	}
	*/

	Point res;

  /* BEGIN - MID1 */
	res = floodfill(seed_point[0].left, seed_point[0].right, dir, BEGIN, MID1);
	vol.x += res.x;
	vol.y += res.y;
	
	/* MID1  - MID2 */
	res = floodfill(seed_point[1].left, seed_point[1].right, dir, MID1, MID2);
	vol.x += res.x;
	vol.y += res.y;

	/* MID2  - END  */
	res = floodfill(seed_point[2].left, seed_point[2].right, dir, MID2, END+1);
	vol.x += res.x;
	vol.y += res.y;

	g_print("[Success] Please check results0 & results1 directory.\n");
	success = true;

	// make mha file
	const char *path1   = "./results0/ct.res.%d.jpg";
	const char *path2   = "./results1/ct.res.%d.jpg";
	const char *output1 = "result0.mha";
	const char *output2 = "result1.mha";

	make_mha(path1, output1);
	make_mha(path2, output2);

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

void show_image(GtkWidget *widget, gpointer data) {
	if ((mha_file == NULL) || (directory == NULL)) {
		g_print("Please select mha file and directory.\n");
		return;
	}

	GtkWidget *window;
	GtkWidget *box1, *box2, *box3, *box4;
	GtkWidget *event_box1, *event_box2, *event_box3;
	GtkWidget *image1, *image2, *image3;
	GtkWidget *label1, *label2, *label3;

	g_print("Select Image ...\n");

	/* window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_title(GTK_WINDOW(window), "Input Seed Point");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy_widget), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 1);

	/* box1 */
	box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(window), box1);

	/* box2 */
	box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(box1), box2);

	/* box3 */
	box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(box1), box3);

	/* box4 */
	box4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(box1), box4);

	/* label1 */
	label1 = gtk_label_new("[Image 1] Click Image");
	gtk_box_pack_start(GTK_BOX(box2), label1, FALSE, FALSE, 0);

	/* event_box1 */
	event_box1 = gtk_event_box_new();
	g_signal_connect(event_box1, "button-press-event", G_CALLBACK(get_seed_point), label1);
	gtk_box_pack_start(GTK_BOX(box2), event_box1, FALSE, FALSE, 0);

	/* image1 */
	char file[MAXCHAR];
	sprintf(file, "%s/ct.%03d.jpg", directory, BEGIN);
	g_print("[Image 1] %s\n", file);
	image1 = gtk_image_new_from_file(file);
	gtk_container_add(GTK_CONTAINER(event_box1), image1);

	/* seed point initialize */
	/* filename format: (dir)/ct.xxx.jpg */
	seed_point[0].image = 1;
	seed_point[0].file  = BEGIN;
	seed_point[0].left  = Point(-1, -1);
	seed_point[0].right = Point(-1, -1);
	seed_point[0].ok    = false;

	/* label2 */
	label2 = gtk_label_new("[Image 2] Click Image");
	gtk_box_pack_start(GTK_BOX(box3), label2, FALSE, FALSE, 0);

	/* event_box2 */
	event_box2 = gtk_event_box_new();
	g_signal_connect(event_box2, "button-press-event", G_CALLBACK(get_seed_point), label2);
	gtk_box_pack_start(GTK_BOX(box3), event_box2, FALSE, FALSE, 0);

	/* image2 */
	sprintf(file, "%s/ct.%03d.jpg", directory, MID1);
	g_print("[Image 2] %s\n", file);
	image2 = gtk_image_new_from_file(file);
	gtk_container_add(GTK_CONTAINER(event_box2), image2);

	/* seed point initialize */
	/* filename format: (dir)/ct.xxx.jpg */
	seed_point[1].image = 2;
	seed_point[1].file  = MID1;
	seed_point[1].left  = Point(-1, -1);
	seed_point[1].right = Point(-1, -1);
	seed_point[1].ok    = false;

	/* label3 */
	label3 = gtk_label_new("[Image 3] Click Image");
	gtk_box_pack_start(GTK_BOX(box4), label3, FALSE, FALSE, 0);

	/* event_box3 */
	event_box3 = gtk_event_box_new();
	g_signal_connect(event_box3, "button-press-event", G_CALLBACK(get_seed_point), label3);
	gtk_box_pack_start(GTK_BOX(box4), event_box3, FALSE, FALSE, 0);

	/* image3 */
	sprintf(file, "%s/ct.%03d.jpg", directory, END);
	g_print("[Image 3] %s\n", file);
	image3 = gtk_image_new_from_file(file);
	gtk_container_add(GTK_CONTAINER(event_box3), image3);

	/* seed point initialize */
	/* filename format: (dir)/ct.xxx.jpg */
	seed_point[2].image = 3;
	seed_point[2].file  = END;
	seed_point[2].left  = Point(-1, -1);
	seed_point[2].right = Point(-1, -1);
	seed_point[2].ok    = false;

	/* show */
	gtk_widget_show_all(window);
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

void select_mha(GtkWidget *widget, gpointer data) {
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	/* dialog */
	dialog = gtk_file_chooser_dialog_new("Select Image",
			NULL, action, "_Cancl", GTK_RESPONSE_CANCEL,
			"_Open", GTK_RESPONSE_ACCEPT, NULL);

	gtk_window_set_title(GTK_WINDOW(dialog), "Select Image");
	res = gtk_dialog_run(GTK_DIALOG(dialog));

	if (res == GTK_RESPONSE_ACCEPT) {
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		mha_file = gtk_file_chooser_get_filename(chooser);
		
		gtk_label_set_text(GTK_LABEL((GtkWidget *)data), mha_file);
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
	GtkWidget *button5;
	GtkWidget *button6;
	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *label3;

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

	/* label3*/
	label3 = gtk_label_new("Image: ... ");
	gtk_box_pack_start(GTK_BOX(box), label3, FALSE, FALSE, 0);

	/* button1 */
	button1 = gtk_button_new_with_label("1. Select Image");
	g_signal_connect(button1, "clicked", G_CALLBACK(select_mha), label3);
	gtk_box_pack_start(GTK_BOX(box), button1, FALSE, FALSE, 0);
	
	/* label1 */
  label1 = gtk_label_new("Directory: ...");
 	gtk_box_pack_start(GTK_BOX(box), label1, FALSE, FALSE, 0);

	/* button2 */
	button2 = gtk_button_new_with_label("2. Select Directory");
	g_signal_connect(button2, "clicked", G_CALLBACK(select_directory), label1);
	gtk_box_pack_start(GTK_BOX(box), button2, FALSE, FALSE, 0);
	
	/* button5 */
	button5 = gtk_button_new_with_label("3. Show Image");
	g_signal_connect(button5, "clicked", G_CALLBACK(show_image), window);
	gtk_box_pack_start(GTK_BOX(box), button5, FALSE, FALSE, 0);

	/* button3 */
	button3 = gtk_button_new_with_label("4. Start Processing");
	g_signal_connect(button3, "clicked", G_CALLBACK(start_processing), window);
	gtk_box_pack_start(GTK_BOX(box), button3, FALSE, FALSE, 0);
		
	/* label2 */
	label2 = gtk_label_new("[Volume]\nleft: ...\nright: ...");
	gtk_box_pack_start(GTK_BOX(box), label2, FALSE, FALSE, 0);

	/* button4 */
	button4 = gtk_button_new_with_label("5-1. Show Volume (all)");
	g_signal_connect(button4, "clicked", G_CALLBACK(show_vol_loc), label2);
	gtk_box_pack_start(GTK_BOX(box), button4, FALSE, FALSE, 0);

	/* button6 */
	button6 = gtk_button_new_with_label("5-2. Show Volume (partial)");
	g_signal_connect(button6, "clicked", G_CALLBACK(show_vol_loc), label2);
	gtk_box_pack_start(GTK_BOX(box), button6, FALSE, FALSE, 0);
	
	/* show */
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
