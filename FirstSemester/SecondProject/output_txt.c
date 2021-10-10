#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "output_txt.h"

type_txt OT_TXT_FILE;

// Struct to save id of each circle moved inside a rect
typedef struct rectid_circleid_struct{
    char rectid[40];
    char circleid[20][40];
    int last;
    int first;
}RECTCIRCLEID;

void destroi_bstree_aux(type_bstitems key){
    RECTCIRCLEID *rc = key;
    free(rc);    
}

long compare_rectangles_by_id_auxrc(type_bstitems key1, type_bstitems key2){
    RECTCIRCLEID *rc1 = key1;
    RECTCIRCLEID *rc2 = key2;

    int i = 0;
    while(rc1->rectid[i] == rc2->rectid[i] && i < strlen(rc1->rectid) && i < strlen(rc2->rectid)){
        i = i + 1;
    }
    if(i < strlen(rc1->rectid) && i < strlen(rc2->rectid)){
        if(rc1->rectid[i] > rc2->rectid[i]) return 1;
        return -1;
    }
    if(strlen(rc1->rectid) == strlen(rc2->rectid)) return 0;
    if(strlen(rc1->rectid) > strlen(rc2->rectid)) return 1;
    return -1;
}

// Saving in a binary search tree the id of the building and the id of the person who went in
// this function will be used for producing the txt
void save_rectid_circleid_for_txt(type_bstree tree, type_rect rectangle, type_circle circle){
    
    long(*ptr_compare_rectid)(type_bstitems, type_bstitems);
    ptr_compare_rectid = compare_rectangles_by_id_auxrc;

    RECTCIRCLEID *rectc = malloc(sizeof(RECTCIRCLEID));
    char *rectangleid = get_rect_id(rectangle);
    sprintf(rectc->rectid, "%s%c", rectangleid, '\0');

    // Verifing if the rectangle is already in the tree
    // if it's not I add it, if it is I only add the circle
    type_bstitems item = search_in_binary_search_tree(tree, rectc, (void*)ptr_compare_rectid);    
    if(item == NULL){
        RECTCIRCLEID *rc = malloc(sizeof(RECTCIRCLEID)); 
        char *rectid = get_rect_id(rectangle);
        char *circleid = get_circle_id(circle);
        sprintf(rc->rectid, "%s%c", rectid, '\0');        
        sprintf(rc->circleid[0], "%s%c", circleid, '\0');
        rc->last = 0;
        rc->first = 0;    
        insert_item_in_binary_search_tree(tree, rc, (void*)ptr_compare_rectid);
    }
    else{
        RECTCIRCLEID *rc = item;
        char *circleid = get_circle_id(circle);
        rc->last = rc->last + 1;
        sprintf(rc->circleid[rc->last], "%s%c", circleid, '\0');
    }
    free(rectc);
}

// Auxiliary function to compare two strings character by character
// for the qsort function
int str_cmp_aux(const void *a, const void *b){  
    const char *ca = (const char *)a; // casting pointer types 
    const char *cb = (const char *)b;
    int i = 0;
    while(ca[i] == cb[i] && i < strlen(ca) && i < strlen(cb)){
        i = i + 1;
    }
    return(ca[i] > cb[i]);
}

void insert_rectid_circleid_in_txt_action_aux(type_bstitems key){
    RECTCIRCLEID *rc = key;    
    char *strrect = (char*)malloc(sizeof(char) * strlen(rc->rectid) + 5);
    char *strcircle;

    // Sorting the circles with qsort
    qsort(rc->circleid, rc->last+1, sizeof(char)*40, str_cmp_aux);
    
    // Inserting the rect id in the txt file
    sprintf(strrect, "%s : %c", rc->rectid, '\0');    
    insert_string_without_skipping_line_in_txt(OT_TXT_FILE, strrect);
    
    // Inserting all the circles id in the txt file
    for(int i = 0; i <= rc->last; i++){
        strcircle = malloc(sizeof(char) * strlen(rc->circleid[i]) + 3);
        sprintf(strcircle, "%s %c", rc->circleid[i], '\0');
        insert_string_without_skipping_line_in_txt(OT_TXT_FILE, strcircle);
        free(strcircle);        
    }
    insert_string_in_txt(OT_TXT_FILE, "\n");
    free(strrect);  
}

void free_structure_rectidcircleid_aux(type_bstitems item){
    RECTCIRCLEID *rc = item;
    free(rc); 
}

// Inserting in txt the ids previously saved
void insert_rectid_circleid_in_txt(type_bstree tree, type_txt txtfile){
    OT_TXT_FILE = txtfile;
    if(empty_binary_search_tree(tree)) return;

    // Creating a pointer to the function action for the second traverse
    void(*ptr_insert_in_txt)(type_bstitems);
    ptr_insert_in_txt = insert_rectid_circleid_in_txt_action_aux;  

    in_order_traversal_binary_search_tree(tree, (void*)ptr_insert_in_txt);

    void(*ptr_remove_struct)(type_bstitems);
    ptr_remove_struct = free_structure_rectidcircleid_aux;

    destroi_binary_search_tree(tree, (void*)ptr_remove_struct);
}





typedef struct rectidstruct{
    char rectid[40];
}RECTID;

long compare_rectangles_by_id_auxr(type_bstitems key1, type_bstitems key2){
    RECTID *rect1 = key1;
    RECTID *rect2 = key2;

    int i = 0;
    while(rect1->rectid[i] == rect2->rectid[i] && i < strlen(rect1->rectid) && i < strlen(rect2->rectid)){
        i = i + 1;
    }
    if(i < strlen(rect1->rectid) && i < strlen(rect2->rectid)){
        if(rect1->rectid[i] > rect2->rectid[i]) return 1;
        return -1;
    }
    if(strlen(rect1->rectid) == strlen(rect2->rectid)) return 0;
    if(strlen(rect1->rectid) > strlen(rect2->rectid)) return 1;
    return -1;
}

void save_rectid_for_txt(type_bstree tree, type_rect rectangle){
    
    RECTID *rect = malloc(sizeof(RECTID)); 

    long(*ptr_compare_rectid)(type_bstitems, type_bstitems);
    ptr_compare_rectid = compare_rectangles_by_id_auxr;

    char *rectid = get_rect_id(rectangle);
    sprintf(rect->rectid, "%s%c", rectid, '\0');        
    insert_item_in_binary_search_tree(tree, rect, (void*)ptr_compare_rectid);
}

void insert_rectid_in_txt_aux(type_bstitems key){
    RECTID *rect = key;    
    char *strrect = (char*)malloc(sizeof(char) * strlen(rect->rectid) + 4);
    
    // Inserting the rect id in the txt file
    sprintf(strrect, "%s %c", rect->rectid, '\0');    
    insert_string_in_txt(OT_TXT_FILE, strrect);
    free(strrect);  
}

void free_structure_rectid_aux(type_bstitems item){
    RECTID *rect = item;
    free(rect);    
}

void insert_rectid_in_txt(type_bstree tree, type_txt txtfile){
    if(empty_binary_search_tree(tree)) return;

    OT_TXT_FILE = txtfile;
    
    // Creating a pointer to the function action for the second traverse
    void(*ptr_insert_in_txt)(type_bstitems);
    ptr_insert_in_txt = insert_rectid_in_txt_aux;  

    in_order_traversal_binary_search_tree(tree, (void*)ptr_insert_in_txt);

    void(*ptr_remove_struct)(type_bstitems);
    ptr_remove_struct = free_structure_rectid_aux;

    destroi_binary_search_tree(tree, (void*)ptr_remove_struct);
}





typedef struct circleidstruct{
    char circleid[40];
}CIRCLEID;

long compare_circles_by_id_auxc(type_bstitems key1, type_bstitems key2){
    CIRCLEID *circle1 = key1;
    CIRCLEID *circle2 = key2;

    int i = 0;
    while(circle1->circleid[i] == circle2->circleid[i] && i < strlen(circle1->circleid) && i < strlen(circle2->circleid)){
        i = i + 1;
    }
    if(i < strlen(circle1->circleid) && i < strlen(circle2->circleid)){
        if(circle1->circleid[i] > circle2->circleid[i]) return 1;
        return -1;
    }
    if(strlen(circle1->circleid) == strlen(circle2->circleid)) return 0;
    if(strlen(circle1->circleid) > strlen(circle2->circleid)) return 1;
    return -1;
}

void save_circleid_for_txt(type_bstree tree, type_circle circle){

    CIRCLEID *circlesave = malloc(sizeof(CIRCLEID)); 

    long(*ptr_compare_circleid)(type_bstitems, type_bstitems);
    ptr_compare_circleid = compare_circles_by_id_auxc;

    char *circleid = get_circle_id(circle);
    sprintf(circlesave->circleid, "%s%c", circleid, '\0');
    insert_item_in_binary_search_tree(tree, circlesave, (void*)ptr_compare_circleid);
}

void insert_circleid_in_txt_action_aux(type_bstitems key){
    CIRCLEID *circle = key;    
    char *strcircle = (char*)malloc(sizeof(char) * strlen(circle->circleid) + 2);
    
    // Inserting the rect id in the txt file
    sprintf(strcircle, "%s%c", circle->circleid, '\0');    
    insert_string_without_skipping_line_in_txt(OT_TXT_FILE, strcircle);

    insert_string_in_txt(OT_TXT_FILE, "\n");
    free(strcircle);  
}

void free_structure_circleid_aux(type_bstitems item){
    CIRCLEID *circle = item;
    free(circle);    
}

void insert_circleid_in_txt(type_bstree tree, type_txt txtfile){
    if(empty_binary_search_tree(tree)) return;

    OT_TXT_FILE = txtfile;

    // Creating a pointer to the function action for the second traverse
    void(*ptr_insert_in_txt)(type_bstitems);
    ptr_insert_in_txt = insert_circleid_in_txt_action_aux;  

    in_order_traversal_binary_search_tree(tree, (void*)ptr_insert_in_txt);

    void(*ptr_remove_struct)(type_bstitems);
    ptr_remove_struct = free_structure_circleid_aux;

    destroi_binary_search_tree(tree, (void*)ptr_remove_struct);
}





