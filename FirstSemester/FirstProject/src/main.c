#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h> // This is a Linux library 
#include "path.h" // This is also a Linux library
#include "list.h"
#include "SVG.h"
#include "TXT.h"

typedef struct item {
	char id[40];
	double width, height;
	double x, y; //coordinates 
	char stroke_color[30]; 
	char fill_color[30]; 
}ITEM;

// Global variables:
type_txt FILE_TXT; 
type_svg FILE_SVG1;
type_svg FILE_SVG2;
type_svg FILE_SVG_GRAPH;
ITEM *tpr_rect; // Global variable to use in the function 'tpr' 
int COLOR; // Global variable to vary the color in the function 'changing_rectangles_fill_color'
int sizeoflist;

/* PROTOTYPES: */
type_structure read_geo_and_create_list(char *filename);
void read_geo_and_saves_rect_info(char *filename, type_structure list);
void read_qry_and_call_functions(char *filename, type_structure list);
int point_in_rect(ITEM *rect, double px, double py);
int rect_in_rect(ITEM *reference_rect, ITEM *second_rect);
int intersection_of_lines(double x1, double y1, double w1, double x2, double y2, double h2);
int intersection_of_rectangles(ITEM *first_rect, ITEM *second_rect);
void calculate_max(type_structure list, double *maxx, double *maxy);
ITEM* find_rectangle(type_structure list, char *name);
void dpi(type_structure list, float px, float py);
void dr(type_structure list, ITEM *reference_rect);
void tpr(type_structure list, double x, double y, double width, double height);
void bbid(type_structure list, ITEM *reference_rect);
void bbi(type_structure list, float x, float y, double *maxx, double *maxy, double *minx, double *miny);
void iid(type_structure list, ITEM *rect, int k); 
void diid(type_structure list, ITEM *rect, int k);
void insert_rects_in_svg(type_svg svgfile, type_structure list);
void create_svg_graph(char* txtfilename, char *svgfilename);	


int main(int argc, char *argv[]) {
	int i; 
	char *input_path = NULL;
	char *geofile = NULL;
	char *qryfile = NULL;
	char *output_path = NULL;
	char *visited_items_command = NULL;
	char *visited_items_filename = NULL;

	type_structure list;
	char *geofullpath = NULL;
	char *qryfullpath = NULL;
	char *outputfilename = NULL;
	char *firstsvgfullpath = NULL;
	char *secondsvgfullpath = NULL;
	char *txtfullpath = NULL;
	char *geoname_without_suffix = NULL;
	char *qryname_without_suffix = NULL;
	char *svgname_with_suffix = NULL;
	char *txtoutputname = NULL;
	char *svgoutputname = NULL;

	int visited_items;
	int missing_qry = 0;

	i = 1; // Motive to start 'i' in 1: first file, with the index equal to zero, is the name of the compiling file aka this file!
	while(i < argc){
		if(strcmp("-e", argv[i]) == 0){
			i++; // After the "-e" comes the input path 
			input_path = malloc((strlen(argv[i])+1) *sizeof(char));
			sprintf(input_path, "%s", argv[i]); // Copies the value of argv
		}
		else if(strcmp("-f", argv[i]) == 0){
			i++; // After the "-f" comes the geo filename
			geofile = malloc((strlen(argv[i])+1) *sizeof(char));
			sprintf(geofile, "%s", argv[i]); // Copies the value of argv
			}
			else if(strcmp("-q", argv[i]) == 0){
					i++; // After the "-q" comes the qry filename
					qryfile = malloc((strlen(argv[i])+1) *sizeof(char));
					sprintf(qryfile, "%s", argv[i]); // Copies the value of argv
				}
				else if(strcmp("-o", argv[i]) == 0){
						i++; // After the "-o" comes the output path
						output_path = malloc((strlen(argv[i])+1) *sizeof(char)); 
						sprintf(output_path, "%s", argv[i]); // Copies the value of argv
					}
					else if(strcmp("-ib\0", argv[i]) == 0){
							visited_items_command = malloc((strlen(argv[i]) + 1) * sizeof(char));
							sprintf(visited_items_command, "%s%s", argv[i], "\0");
						}
						else if(strcmp("-cb\0", argv[i]) == 0){
								visited_items_command = malloc((strlen(argv[i]) + 1) * sizeof(char));
								sprintf(visited_items_command, "%s%s", argv[i], "\0");
							}
							else if(strcmp("-fb\0", argv[i]) == 0){
									visited_items_command = malloc((strlen(argv[i]) + 1) * sizeof(char));
									sprintf(visited_items_command, "%s%s", argv[i], "\0");
									i++;
									visited_items_filename = malloc((strlen(argv[i]) + 1) * sizeof(char));
									sprintf(visited_items_filename, "%s%s", argv[i], "\0");
								}
								else{
									i++;
								}	
								i++;
	}

	if(input_path == NULL){
		geofullpath = malloc(sizeof(char) * strlen(geofile) + 1);
		sprintf(geofullpath, "%s%s", geofile, "\0");
	}
	else{
		geofullpath = concat_path_filename(input_path, geofile);
	}
	
	if(qryfile ==  NULL){
		missing_qry = 1;
	} 
	else{
		if(input_path == NULL){
			qryfullpath = malloc(sizeof(char) * strlen(geofile) + 1);
			sprintf(qryfullpath, "%s%s", qryfile, "\0");
		}
		else{
			qryfullpath = concat_path_filename(input_path, qryfile);
		}
	}

	// Opening geo file and saving infos
	list = read_geo_and_create_list(geofullpath);
	read_geo_and_saves_rect_info(geofullpath, list);
	
	// Concatenating path with first svg name, and creating the file
	geoname_without_suffix = get_filename_without_suffix(basename(geofile));
	svgname_with_suffix = concat_name_suffix(geoname_without_suffix, ".svg");
	firstsvgfullpath = concat_path_filename(output_path, svgname_with_suffix);
	FILE_SVG1 = start_new_svg_file(firstsvgfullpath);
	insert_rects_in_svg(FILE_SVG1, list);
	end_svg_file(FILE_SVG1);

	if(!missing_qry){
		// Concatenating output path with filename (for .svg and .txt)
		qryname_without_suffix = get_filename_without_suffix(basename(qryfile));
		outputfilename = malloc(sizeof(char) * (strlen(geoname_without_suffix) + strlen(qryname_without_suffix) + 2));
		sprintf(outputfilename, "%s%s%s", geoname_without_suffix, "-", qryname_without_suffix);

		// Starting .txt file
		txtoutputname = concat_name_suffix(outputfilename, ".txt");
		txtfullpath = concat_path_filename(output_path, txtoutputname);
		FILE_TXT = start_new_txt_file(txtfullpath); // FILE_TXT is a global variable

		// Starting .svg second file
		svgoutputname = concat_name_suffix(outputfilename, ".svg");
		secondsvgfullpath = concat_path_filename(output_path, svgoutputname);
		FILE_SVG2 = start_new_svg_file(secondsvgfullpath);

		// Reading and executing .qry functions
		read_qry_and_call_functions(qryfullpath, list);

		// Ending .svg second file
		if(!empty_list(list)) insert_rects_in_svg(FILE_SVG2, list);
		end_svg_file(FILE_SVG2);

		// Ending .txt file
		end_txt_file(FILE_TXT);
	}

	// In case of the collecting data of visits and size!
	if(visited_items_command != NULL){
		type_txt FILE_TXT_TEMP;
		char *thirdsvgfullpath = NULL;
		char *sizeoflist_str = NULL;
		char *visited_items_str = NULL;
		char *svgreportfilename = NULL;

		visited_items = number_of_list_items_effectively_visited();
		visited_items_str = malloc(snprintf(NULL, 0, "%d", visited_items) + 1);
		sprintf(visited_items_str, "%s%d%s", "visits: ", visited_items, "\0");
		
		sizeoflist_str = malloc(snprintf(NULL, 0, "%d", sizeoflist) + 1);
		sprintf(sizeoflist_str, "%s%d%s", "size: ", sizeoflist, "\0");

		if(strcmp(visited_items_command, "-ib\0") == 0){
			FILE_TXT_TEMP = start_new_txt_file("arquivotempdadenise.txt");
			insert_string_in_txt(FILE_TXT_TEMP, visited_items_str);
			insert_string_in_txt(FILE_TXT_TEMP, sizeoflist_str);
			end_txt_file(FILE_TXT_TEMP);
		}
		else if(strcmp(visited_items_command, "-cb\0") == 0){
			FILE_TXT_TEMP = open_a_pre_existing_txt_file("arquivotempdadenise.txt");
			insert_string_in_txt(FILE_TXT_TEMP, visited_items_str);
			insert_string_in_txt(FILE_TXT_TEMP, sizeoflist_str);
			end_txt_file(FILE_TXT_TEMP);
		}
		else if(strcmp(visited_items_command, "-fb\0") == 0){
			FILE_TXT_TEMP = open_a_pre_existing_txt_file("arquivotempdadenise.txt");
			insert_string_in_txt(FILE_TXT_TEMP, visited_items_str);
			insert_string_in_txt(FILE_TXT_TEMP, sizeoflist_str);
			end_txt_file(FILE_TXT_TEMP);

			svgreportfilename = concat_name_suffix(visited_items_filename, ".svg");
			thirdsvgfullpath = concat_path_filename(output_path, svgreportfilename);
			create_svg_graph("arquivotempdadenise.txt", thirdsvgfullpath);
			remove("arquivotempdadenise.txt");

			free(svgreportfilename);
			free(thirdsvgfullpath);
			free(visited_items_filename);
		}
		free(sizeoflist_str);
		free(visited_items_command);
		free(visited_items_str);
	}

	destroi_list(list);
	free(geofile);
	free(output_path);
	free(geofullpath);
	free(firstsvgfullpath);
	free(geoname_without_suffix);
	free(svgname_with_suffix);

	if(input_path != NULL){
		free(input_path);	
	}
	if(!missing_qry){
		free(qryfile);
		free(qryfullpath);
		free(outputfilename);
		free(secondsvgfullpath);
		free(txtfullpath);
		free(qryname_without_suffix);
		free(txtoutputname);
		free(svgoutputname);
	}
	
	return 0;
}

/* -------------------- INPUT FUNCTIONS THAT DEALS WITH GEO AND QRY FILES -------------------- */

// Reads geo file gets the total number of rectangles and creates list
type_structure read_geo_and_create_list(char *filename){
	FILE *geofile = fopen(filename, "r");
	if (geofile == NULL) {
		return NULL;
	}

	type_structure list;
	char *line = malloc(sizeof(char) * 15);	
	char *helper = malloc(sizeof(char) * 5);	

	fscanf(geofile, "\n%[^\n]s\n", line);
	if(strncmp(line, "nx ", 3) == 0){
		sscanf(line, "%s %d", helper, &sizeoflist);
		set_list_max_size(sizeoflist);
	}
	list = create_list();
	free(line);
	free(helper);
	fclose(geofile);
	return list;
}

// Reads geo file gets the rectangles and inserts them in the list
void read_geo_and_saves_rect_info(char *filename, type_structure list){
	FILE *geofile = fopen(filename, "r");
	if (geofile == NULL) {
		return;
	}

	char *line = malloc(80 * sizeof(char));
	char *helper = malloc(3 *sizeof(char));
	ITEM *rect = (ITEM*) malloc(sizeof(ITEM));
	ITEM *oldrect = (ITEM*) malloc(sizeof(ITEM));

	while(!feof(geofile)){
		fscanf(geofile, "\n%[^\n]s\n", line);
		
		if(strncmp(line, "cc", 2) == 0){
			memset(oldrect->stroke_color, 0, sizeof(oldrect->stroke_color));
			memcpy(oldrect->stroke_color, line + 3, strlen(line) - 3);
		}
		else{ 
			if(strncmp(line, "cp", 2) == 0){
				memset(oldrect->fill_color, 0, sizeof(oldrect->fill_color));
				memcpy(oldrect->fill_color, line + 3, strlen(line) - 3);
			}
			else{
				if(strncmp(line, "r", 1) == 0){
					if(full_list(list)){ printf("Not enough space in the list.\nCheck if the size set is right.\n"); break;}		
					
					sscanf(line, "%s %s %lf %lf %lf %lf", helper, rect->id, &rect->x, &rect->y, &rect->width, &rect->height);
					strcpy(rect->stroke_color, oldrect->stroke_color);
					strcpy(rect->fill_color, oldrect->fill_color);									
					insert_item_at_the_end_of_list(list, rect);
					rect = (ITEM*) malloc(sizeof(ITEM));
				}
				else{
					if(strncmp(line, "nx", 2) == 0){
						// No need to do anything, because I already got this data!
					}
					else{
						break;
					}
				}
			}
		}
		// "Resets" the string
		strcpy(line, "\0");
	}
	free(line);
	free(helper);
	free(rect);
	free(oldrect);
	fclose(geofile);
}

// Reads qry file and calls the respective functions
void read_qry_and_call_functions(char *filename, type_structure list){
	FILE *qryfile = fopen(filename, "r");
	if (qryfile == NULL) {
		return;
	}

	char *line = malloc(60 * sizeof(char));
	char *helper = malloc(5 * sizeof(char));
	char *rectname = malloc(40 * sizeof(char));
	ITEM *rect_refer = malloc(sizeof(ITEM));
	double x, y, w, h;
	int k;
	double maxw, maxh, minw, minh;

	while(!feof(qryfile)){ 
		fscanf(qryfile, "\n%[^\n]\ns", line);

		if(strncmp(line, "tp ", 3) == 0 || strncmp(line, "tp\0", 3) == 0){
			// Saving function name to .txt file, remember FILE_TXT is a global variable
			insert_string_in_txt(FILE_TXT, "tp");
			calculate_max(list, &maxw, &maxh);
			tpr(list, 0, 0, maxw+1, maxh+1);			
		}
		else{ 
			if(strncmp(line, "tpr", 3) == 0){
				// Saving function name to .txt file, remember FILE_TXT is a global variable
				insert_string_in_txt(FILE_TXT, "tpr");
				sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
				tpr(list, x, y, w, h);				
			}
			else{
				if(strncmp(line, "dpi", 3) == 0){
					// Saving function name to .txt file, remember FILE_TXT is a global variable
					insert_string_in_txt(FILE_TXT, "dpi");
					sscanf(line, "%s %lf %lf", helper, &x, &y);
					dpi(list, x, y);
				}
				else{
					if(strncmp(line, "dr", 2) == 0){
						// Saving function name to .txt file, remember FILE_TXT is a global variable
						insert_string_in_txt(FILE_TXT, "dr");
						sscanf(line, "%s %s", helper, rectname);
						rect_refer = find_rectangle(list, rectname);
						if(rect_refer == NULL){
							printf("The id given is not in the list.\n");
							break;
						}
						dr(list, rect_refer);
					}
					else{
						if(strncmp(line, "bbi ", 4) == 0){
							// Saving function name to .txt file, remember FILE_TXT is a global variable
							insert_string_in_txt(FILE_TXT, "bbi");

							sscanf(line, "%s %lf %lf", helper, &x, &y);	
							insert_circle_in_svg(FILE_SVG2, x, y, 1, "deeppink", "lawngreen", 1); //não ta ficando na frente
							
							bbi(list, x, y, &maxw, &maxh, &minw, &minh);
							insert_dasharray_rect_based_in_opposite_corners_in_svg(FILE_SVG2, minw, minh, maxw, maxh, "transparent", "red", 2, 5);

						}
						else{
							if(strncmp(line, "bbid", 4) == 0){
								// Saving function name to .txt file, remember FILE_TXT is a global variable
								insert_string_in_txt(FILE_TXT, "bbid");

								sscanf(line, "%s %s", helper, rectname);
								rect_refer = find_rectangle(list, rectname);
								if(rect_refer == NULL){
									printf("The id given is not in the list.\n");
									break;
								}
								bbid(list, rect_refer);
								insert_dasharray_rect_based_in_opposite_corners_in_svg(FILE_SVG2, rect_refer->x-1,  rect_refer->y-1,  rect_refer->width+rect_refer->x+1, rect_refer->height+rect_refer->y+1, "transparent", "red", 4, 5);
							}
							else{
								if(strncmp(line, "iid", 3) == 0){
									// Saving function name to .txt file, remember FILE_TXT is a global variable
									insert_string_in_txt(FILE_TXT, "iid");
									sscanf(line, "%s %s %d", helper, rectname, &k);	
									rect_refer = find_rectangle(list, rectname);
									iid(list, rect_refer, k);				
								}
								else{
									if(strncmp(line, "diid", 4) == 0){
										// Saving function name to .txt file, remember FILE_TXT is a global variable
										insert_string_in_txt(FILE_TXT, "diid");	
										sscanf(line, "%s %s %d", helper, rectname, &k);	
										rect_refer = find_rectangle(list, rectname);
										diid(list, rect_refer, k);			
									}
								}
							}
						}
					}
				}
			}
		}
		// "Resets" the string
		strcpy(line, "\0");
	}
	free(line);
	free(helper);
	free(rectname);
	free(rect_refer);
	fclose(qryfile);
}


/* ------------------------ AUXILIARY FUNCTIONS FOR MY QRY OPERATIONS ------------------------ */

int point_in_rect(ITEM *rect, double px, double py){
	if((rect->x <= px) && px <= (rect->x + rect->width)){
		if((rect->y <= py) && py <= (rect->y + rect->height)){
			return 1;
		}
	}
	return 0;
}

int rect_in_rect(ITEM *reference_rect, ITEM *second_rect){
	if(point_in_rect(reference_rect, second_rect->x, second_rect->y) && point_in_rect(reference_rect, (second_rect->x + second_rect->width), (second_rect->y + second_rect->height))){
		return 1;
	}
	return 0;
}

int intersection_of_lines(double x1, double y1, double w1, double x2, double y2, double h2){
	// (x1, y1) -> (x1+w1, y1) horizontal
	// (x2, y2) -> (x2, y2+h2) vertical
	if((x1 <= x2 && x2 <= x1+w1) && (y2 <= y1 && y1 <= y2+h2)){
		return 1;
	}
	return 0;
}

int intersection_of_rectangles(ITEM *first_rect, ITEM *second_rect){
	if(intersection_of_lines(first_rect->x, first_rect->y, first_rect->width, second_rect->x, second_rect->y, second_rect->height) || 
		intersection_of_lines(first_rect->x, first_rect->y, first_rect->width,(second_rect->x + second_rect->width), second_rect->y, second_rect->height) || 
		intersection_of_lines(first_rect->x, (first_rect->y + first_rect->height), first_rect->width, second_rect->x, second_rect->y, second_rect->height) || 
		intersection_of_lines(first_rect->x, (first_rect->y + first_rect->height), first_rect->width,(second_rect->x + second_rect->width), second_rect->y, second_rect->height) || 
		intersection_of_lines(second_rect->x, second_rect->y, second_rect->width, first_rect->x, first_rect->y, first_rect->height) || 
		intersection_of_lines(second_rect->x, second_rect->y, second_rect->width,(first_rect->x + first_rect->width), first_rect->y, first_rect->height) || 
		intersection_of_lines(second_rect->x, (second_rect->y + second_rect->height), second_rect->width, first_rect->x, first_rect->y, first_rect->height) || 
		intersection_of_lines(second_rect->x, (second_rect->y + second_rect->height), second_rect->width,(first_rect->x + first_rect->width), first_rect->y, first_rect->height)){
		return 1;
	}
	return 0;
}

void calculate_max(type_structure list, double *maxx, double *maxy){
	ITEM *rect;		
	*maxx = 0;
	*maxy = 0;
	int done = 0;
	set_current_to_first_item_in_list(list);
	do{
		done = is_current_last_item_in_list(list);
		rect = (ITEM*) get_current_item_in_list(list);
		if(rect->x + rect->width > *maxx){
			*maxx = (rect->x + rect-> width);
		}
		if(rect->y + rect->height > *maxy){
			*maxy = (rect->y + rect->height);
		}
		if(!done) move_current_forward_in_list(list);
	}while(!done);
}

ITEM* find_rectangle(type_structure list, char *name){
	ITEM *rect;	
	int done = 0;
	set_current_to_first_item_in_list(list);
	do{
		done = is_current_last_item_in_list(list);
		rect = (ITEM*) get_current_item_in_list(list);
		if(strcmp(name, rect->id) == 0){
			return rect;
		}
		if(!done) move_current_forward_in_list(list);
	}while(!done);
	return NULL;
}

// Verifies if the "second rect" is in the "reference rect"
int overlapping_rectangles(ITEM *rect, ITEM *rect2){
	if(rect_in_rect(tpr_rect, rect2)){
		return(intersection_of_rectangles(rect, rect2) || rect_in_rect(rect, rect2) || rect_in_rect(rect2, rect));
	}
	return 0;
}

void changing_rectangles_fill_color(ITEM *rect, ITEM *rect2){
	char *string;
	char colors[10][22] = {"lightblue", "lightcoral", "lightcyan", "lightgoldenrodyellow", "tomato", "lightgrey", "lightpink", "lightsalmon", "lightseagreen", "peachpuff"};
	// Changing colors, remember COLOR is a global variable
	strcpy(rect->fill_color, colors[COLOR]); 
	strcpy(rect2->fill_color, colors[COLOR]);
	
	// Saving data in .txt, remember FILE_TXT is a global variable
	string = malloc(sizeof(char) * (strlen(rect->id) + strlen(rect2->id) + 1));
	sprintf(string, "%s %s", rect->id, rect2->id);
	insert_string_in_txt(FILE_TXT, string);
	free(string);
}


/* --------------------------------- QRY OPERATIONS FUNCTIONS: --------------------------------- */

// tp = tpr(0, 0, maxwidth+1, maxheight+1);
void tpr(type_structure list, double x, double y, double width, double height){
	ITEM *current_rect;

	tpr_rect = malloc(sizeof(ITEM));
	tpr_rect->x = x;
	tpr_rect->y = y;
	tpr_rect->width = width;
	tpr_rect->height = height;

	// Creating a pointer to the function overlapping_rectangles
	int(*compare)(ITEM*, ITEM*); 
	compare = overlapping_rectangles;

	// Creating a pointer to the function changing_rectangles_fill_color
	void(*action)(ITEM*, ITEM*);
	action = changing_rectangles_fill_color;

	set_current_to_first_item_in_list(list);

	COLOR = 0;
	while(!is_current_last_item_in_list(list)){
		current_rect = (ITEM*)get_current_item_in_list(list);
		// Check if current is in the reference rectangle aka tpr_rect
		if(rect_in_rect(tpr_rect, current_rect)){
			traverse_from_current_with_conditional_action_in_list(list, (void*)compare, (void*)action);
			COLOR = (COLOR+1) % 10;
		}
		move_current_forward_in_list(list);
	}
	free(tpr_rect);
}

void dr(type_structure list, ITEM *reference_rect){
	ITEM *rect;
	int done;
	char *string;
	
	set_current_to_first_item_in_list(list);
	do{
		done = is_current_last_item_in_list(list);
		
		rect = (ITEM*) get_current_item_in_list(list);
		if(rect_in_rect(reference_rect, rect) && (strcmp(reference_rect->id, rect->id) != 0)){
			string = malloc(sizeof(char) * (strlen(rect->id) + 1));
			sprintf(string, "%s", rect->id);
			// Saving data in .txt, remember FILE_TXT is a global variable
			insert_string_in_txt(FILE_TXT, string);
			free(string);
			// Deleting the element
			delete_current_item_in_list(list);
		}
		if(!empty_list(list)){
			if(is_current_undefined_in_list(list)) set_current_to_first_item_in_list(list);
			else move_current_forward_in_list(list);
		}
		else break;	
	}while(!done);
}

void bbid(type_structure list, ITEM *reference_rect){
	ITEM *rect;
	char color[25];
	int done;
	char *string;

	set_current_to_first_item_in_list(list);
	do{
		done = is_current_last_item_in_list(list);
		
		rect = (ITEM*) get_current_item_in_list(list);
		if(rect_in_rect(reference_rect, rect) && (strcmp(reference_rect->id, rect->id) != 0)){
			// Inverting rectangles colors (stroke <-> fill) 
			sprintf(color, "%s", rect->stroke_color);
			sprintf(rect->stroke_color, "%s", rect->fill_color);
			sprintf(rect->fill_color, "%s", color);

			// Saving data in .txt, remember FILE_TXT is a global variable
			string = malloc(sizeof(char) * (strlen(rect->id) + strlen(rect->fill_color) + strlen(rect->stroke_color) + 3)); // +3 includes the '\0' and the spaces below
			sprintf(string, "%s %s %s", rect->id, rect->fill_color, rect->stroke_color);
			insert_string_in_txt(FILE_TXT, string);
			free(string);
		}
		move_current_forward_in_list(list);
	}while(!done);
}

void bbi(type_structure list, float x, float y, double *maxx, double *maxy, double *minx, double *miny){
	ITEM *rect;
	char color[25];
	int done;
	char *string;
	*maxx = x; 
	*maxy = y; 
	*minx = x;
	*miny = y;
	
	set_current_to_first_item_in_list(list);
	do{
		done = is_current_last_item_in_list(list);
		
		rect = (ITEM*) get_current_item_in_list(list);
		if(point_in_rect(rect, x, y)){			
			// Inverting rectangles colors (stroke <-> fill)
			sprintf(color, "%s", rect->stroke_color);
			sprintf(rect->stroke_color, "%s", rect->fill_color);
			sprintf(rect->fill_color, "%s", color);

			// Getting values for the bounding box
			if((rect->x + rect->width) > *maxx) *maxx = rect->x + rect->width;
			if((rect->y + rect->height) > *maxy) *maxy = rect->y + rect->height;
			if(rect->x < *minx) *minx = rect->x;
			if(rect->y < *miny) *miny = rect->y;

			// Saving data in .txt, remember FILE_TXT is a global variable
			string = malloc(sizeof(char) * (strlen(rect->id) + strlen(rect->fill_color) + strlen(rect->stroke_color) + 3)); // +3 includes the '\0' and the spaces below
			sprintf(string, "%s %s %s", rect->id, rect->fill_color, rect->stroke_color);
			insert_string_in_txt(FILE_TXT, string);
			free(string);
		}
		move_current_forward_in_list(list);
	}while(!done);
}
 
void iid(type_structure list, ITEM *rect, int k){
	int i, increase;
	char *string;

	if(k > 0) increase = +1;
	else increase = -1;
	if(!find_item_in_list(list, rect)) return; // The id sent was not in the list of items
	i = 0;
	do{
		rect = (ITEM*) get_current_item_in_list(list);

		// Saving data in .txt, remember FILE_TXT is a global variable
		string = malloc(sizeof(char) * (strlen(rect->id) + strlen(rect->fill_color) + strlen(rect->stroke_color)) + (24 * 4) + 7); // +7 includes the '\0' and the spaces below
		sprintf(string, "%s %lf %lf %lf %lf %s %s", rect->id, rect->x, rect->y, rect->width, rect->height, rect->fill_color, rect->stroke_color);
		insert_string_in_txt(FILE_TXT, string);
		free(string);

		if(!is_current_last_item_in_list(list)) move_current_forward_in_list(list);	
		else break;
		i = i + increase;
		
	}while(i != (k + increase));	
}

void diid(type_structure list, ITEM *rect, int k){ 
	int i, increase;
	char *string;

	if(k > 0) increase = +1;
	else increase = -1;
	
	if(!find_item_in_list(list, rect)) return; // The id sent was not in the list of items
	
	i = 0;
	do{
		rect = (ITEM*) get_current_item_in_list(list);

		// Saving data in .txt, remember FILE_TXT is a global variable
		string = malloc(sizeof(char) * (strlen(rect->id) + strlen(rect->fill_color) + strlen(rect->stroke_color)) + (24 * 4) + 7); // +7 includes the '\0' and the spaces below
		sprintf(string, "%s %lf %lf %lf %lf %s %s", rect->id, rect->x, rect->y, rect->width, rect->height, rect->fill_color, rect->stroke_color);
		insert_string_in_txt(FILE_TXT, string);
		free(string);

		// Deletes all items except the first one
		if(i != 0){
			delete_current_item_in_list(list);
		}
		if(!empty_list(list)){
			if(!is_current_last_item_in_list(list)) move_current_forward_in_list(list);	
			else break;
		}
		else{
			break;
		}
		i = i + increase;

	}while(i != (k + increase));
} 

void dpi(type_structure list, float px, float py){
	ITEM *rect;
	int done;
	char *string;

	set_current_to_first_item_in_list(list);
	do{
		done = is_current_last_item_in_list(list);
		rect = (ITEM*) get_current_item_in_list(list);
		if(point_in_rect(rect, px, py)){
			string = malloc(sizeof(char) * (strlen(rect->id) + 1));
			sprintf(string, "%s", rect->id);
			// Saving data in .txt, remember FILE_TXT is a global variable
			insert_string_in_txt(FILE_TXT, string);
			free(string);
			// Deleting the element
			delete_current_item_in_list(list);
		}
		
		if(!empty_list(list)){
			if(is_current_undefined_in_list(list)) set_current_to_first_item_in_list(list);
			else move_current_forward_in_list(list);
		}
		else break;
	}while(!done);
}


/* ------------------------- OUTPUT FUNCTIONS THAT DEALS WITH SVG FILES  ------------------------- */
void insert_rects_in_svg(type_svg svgfile, type_structure list){
	ITEM *rect;
	int done;
	set_current_to_first_item_in_list(list);
	do{
		done = is_current_last_item_in_list(list);
		rect = (ITEM*) get_current_item_in_list(list);
		insert_rectangle_in_svg(svgfile, rect->x, rect->y, rect->width, rect->height, rect->fill_color, rect->stroke_color, 1);
		if(!done) move_current_forward_in_list(list);
	}while(!done);
}



/* --------------------- AUXILIARY FUNCTION FOR THE PROGRAM PERFORMANCE REPORT --------------------- */
void create_svg_graph(char* txtfilename, char *svgfilename){	
	FILE *txtfile = fopen(txtfilename, "r");
	if (txtfile == NULL) {
		return;
	}
	FILE_SVG_GRAPH = start_new_svg_file(svgfilename);
	char *line = malloc(30 * sizeof(char));
	double max_visits = 0, visits = 0;
	double max_size = 0, size = 0;
	char *tempstr = malloc(sizeof(char) * 50);

	insert_cartesian_axis_in_svg(FILE_SVG_GRAPH, 150, 550, 600, 300);
	insert_text_in_svg(FILE_SVG_GRAPH, 770, 550, "black", "tamanho", 20);
	insert_text_in_svg(FILE_SVG_GRAPH, 130, 230, "black", "visitas", 20);

	//find the my bigest visists number and my bigest size number
	while(!feof(txtfile)){
		fscanf(txtfile, "\n%[^\n]s\n", line);
		if(strncmp(line, "visits: ", 8) == 0){
			visits = atof(&line[8]);			
			if(visits > max_visits) max_visits = (double)visits;

		}
		else if(strncmp(line, "size: ", 6) == 0){
			size = atof(&line[6]);
			if(size > max_size) max_size = (double)size;
		}
		// "Resets" the string.
		strcpy(line, "\0");
	}
	set_max_size_for_cartesian_coordinates_in_svg(max_size,  max_visits);
	insert_reference_line_in_cartesian_system_in_svg(FILE_SVG_GRAPH, 20, 10);
	insert_numbers_in_reference_lines_in_svg(FILE_SVG_GRAPH, 20, 10);
	
	fclose(txtfile);	
	txtfile = fopen(txtfilename, "r");
	
	visits = 0;
	size = 0;
	while(!feof(txtfile)){
		fscanf(txtfile, "\n%[^\n]s\n", line);
		if(strncmp(line, "visits: ", 8) == 0){
			visits = atof(&line[8]);
		}
		else if(strncmp(line, "size: ", 6) == 0){
			size = atof(&line[6]);
		}
		if(visits != 0 && size != 0){
			insert_point_in_cartesian_system_in_svg(FILE_SVG_GRAPH, size, visits);
			visits = 0;
			size = 0;
		}
		// "Resets" the string.
		strcpy(line, "\0");
	}

	end_svg_file(FILE_SVG_GRAPH);
	free(line);
	free(tempstr);
}
