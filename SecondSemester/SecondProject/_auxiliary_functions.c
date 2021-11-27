
#include "_auxiliary_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char QAF_ID[41];
double QAF_x1, QAF_x2;
double QAF_y1, QAF_y2;
type_txt QAF_TXTFILE;
#define QAF_SIZE_DOUBLESTR 10

void set_id(char id[]){
    sprintf(QAF_ID, "%s%c", id, '\0');
}

void set_x1_x2_y1_y2(double x1, double x2, double y1, double y2){
    QAF_x1 = x1;
    QAF_x2 = x2;
    QAF_y1 = y1;
    QAF_y2 = y2;
}

long traverse_side_rect_in_rect_(type_mMlavlitems item, type_mMlavlitems lminimum, type_mMlavlitems lmaximum, type_mMlavlitems rminimum, type_mMlavlitems rmaximum){
    double lmin = get_rect_x(lminimum);
    double lmax = get_rect_x(lmaximum);
    double rmin = get_rect_x(rminimum);
    double rmax = get_rect_x(rmaximum);

    int go_left = 0, go_right = 0;

    if(lmin <= QAF_x2 && lmax >= QAF_x1) go_left = 1;
    if(rmin <= QAF_x2 && rmax >= QAF_x1) go_right = 1;
    
    if(go_left && go_right) return 11;
    if(!go_left && go_right) return 01;
    if(go_left && !go_right) return 10;
    else return 00;
}

long condition_rect_in_rect_(type_mMlavlitems item){
    double x = get_rect_x(item);
    double height = get_rect_height(item);
    double y = get_rect_y(item);
    double width = get_rect_width(item);

    // Verifying if x coordinate is inside the given parameters
    if(x >= QAF_x1 && x+width <= QAF_x2){
        // Verifying if y coordinate is inside the given parameters
        if(y >= QAF_y1 && y+height<= QAF_y2){
            return 1;
        }
    }
    return 0;
}

long get_key_from_block(type_rect block){
    type_block block_data = get_rect_data(block);
    return(get_block_formatted_cep(block_data));
}

long compare_rect_blocks_cep(type_rect block1, type_rect block2){
    type_block block_data1 = get_rect_data(block1);
    type_block block_data2 = get_rect_data(block2);
    return compare_blocks_cep(block_data1, block_data2);
}


long verify_block_found(type_rect block){
    type_block block_data = get_rect_data(block);
    if(strcmp(QAF_ID, get_block_cep(block_data)) == 0) return 1;
    return 0;
}

void set_txt_file(type_txt txtfile){
    QAF_TXTFILE = txtfile;
}

void _report_block_txt_(type_rect block_rect){
    insert_string_in_txt(QAF_TXTFILE, "");
    insert_string_in_txt(QAF_TXTFILE, "BLOCO:");
    type_block block_data = get_rect_data(block_rect);
    char *cep = get_block_cep(block_data);
    char *cep_string = malloc(sizeof(char) * strlen(cep) + 10);
    sprintf(cep_string, "CEP: %s%c", cep, '\0');
    insert_string_in_txt(QAF_TXTFILE, cep_string);

    char *x_y_string = malloc(sizeof(char) * (QAF_SIZE_DOUBLESTR + 6 + QAF_SIZE_DOUBLESTR + 6));
    sprintf(x_y_string, "x: %.2lf \t y:%.2lf%c", get_rect_x(block_rect), get_rect_y(block_rect), '\0');
    insert_string_in_txt(QAF_TXTFILE, x_y_string);

    char *w_h_string = malloc(sizeof(char) * (QAF_SIZE_DOUBLESTR + 10 + QAF_SIZE_DOUBLESTR + 10));
    sprintf(w_h_string, "Largura: %.2lf  Altura: %.2lf%c", get_rect_width(block_rect), get_rect_height(block_rect), '\0');
    insert_string_in_txt(QAF_TXTFILE, w_h_string);

    free(cep_string);
    free(x_y_string);
    free(w_h_string);
}

void _report_property_lease_available(){
    char *string = malloc(sizeof(char) * 15);
    sprintf(string, "Disponível%c", '\0');
    insert_string_in_txt(QAF_TXTFILE, string);
    free(string);
}


void _report_property_lease_not_available(){
    char *string = malloc(sizeof(char) * 85);
    sprintf(string, "Não há oferta de locação com esse ID: locação inexistente ou encerrada.%c", '\0');
    insert_string_in_txt(QAF_TXTFILE, string);
    free(string);
}


void _report_vertex_txt_(type_vertex vertex){
    insert_string_in_txt(QAF_TXTFILE, "");
    insert_string_in_txt(QAF_TXTFILE, "VERTEX:");
    char *id = get_vertex_id(vertex);
    double x = get_vertex_x(vertex);
    double y = get_vertex_y(vertex);
    
    char *id_string = malloc(sizeof(char) * strlen(id) + 10);
    sprintf(id_string, "ID: %s%c", id, '\0');
    insert_string_in_txt(QAF_TXTFILE, id_string);
    
    char *x_y_string = malloc(sizeof(char) * (QAF_SIZE_DOUBLESTR + 6 + QAF_SIZE_DOUBLESTR + 6));
    sprintf(x_y_string, "x: %.2lf \t y:%.2lf%c", x, y, '\0');
    insert_string_in_txt(QAF_TXTFILE, x_y_string);

    free(id_string);
    free(x_y_string);
}

void _report_edge_txt_(type_edge edge){
    insert_string_in_txt(QAF_TXTFILE, "");
    insert_string_in_txt(QAF_TXTFILE, "EDGE:");
    
    char *id = get_edge_id(edge);
    double length = get_edge_length(edge);
    double speed_limit = get_edge_speed_limit(edge);
    
    char *id_string = malloc(sizeof(char) * strlen(id) + 10);
    sprintf(id_string, "ID: %s%c", id, '\0');
    insert_string_in_txt(QAF_TXTFILE, id_string);
    
    char *x_y_string = malloc(sizeof(char) * (QAF_SIZE_DOUBLESTR + 12 + QAF_SIZE_DOUBLESTR + 12));
    sprintf(x_y_string, "Comprimento: %.2lf \t Velocidade: %.2lf%c", length, speed_limit, '\0');
    insert_string_in_txt(QAF_TXTFILE, x_y_string);

    free(id_string);
    free(x_y_string);
}