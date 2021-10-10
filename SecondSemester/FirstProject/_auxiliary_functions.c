
#include "_auxiliary_functions.h"
#include <stdio.h>
#include <string.h>


char QAF_ID[40];
double QAF_x1, QAF_x2;
double QAF_y1, QAF_y2;

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
    printf("no traverse side 0\n");

    double lmin = get_rect_x(lminimum);
    double lmax = get_rect_x(lmaximum);
    double rmin = get_rect_x(rminimum);
    double rmax = get_rect_x(rmaximum);

    int go_left = 0, go_right = 0;

    printf("no traverse side\n");

    if(lmin < QAF_x2 && lmax > QAF_x1) go_left = 1;
    if(rmin < QAF_x2 && rmax > QAF_x1) go_right = 1;
    
    if(go_left && go_right) return 11;
    if(!go_left && go_right) return 01;
    if(go_left && !go_right) return 10;
    else return 00;
}

long condition_rect_in_rect_(type_mMlavlitems item){
    printf("no condition_rect_in_rect_ \n");

    double x = get_rect_x(item);
    double height = get_rect_height(item);
    double y = get_rect_y(item);
    double width = get_rect_width(item);
    printf("%lf\n", x);

    printf("%lf\n", QAF_x1);

    // Verifying if x coordinate is inside the given parameters
    if(x > QAF_x1 && x+width < QAF_x2){
        // Verifying if y coordinate is inside the given parameters
        if(y > QAF_y1 && y+height< QAF_y2){
            printf("retornando 1\n");
            return 1;
        }
    }
    printf("retornando 0\n");
    return 0;
}

long get_key_from_block(type_rect block){
    type_block block_data = get_rect_data(block);
    return(get_block_formatted_cep(block_data));
}

long verify_block_found(type_rect block){
    type_block block_data = get_rect_data(block);
    if(strcmp(QAF_ID, get_block_cep(block_data)) == 0) return 1;
    return 0;
}

long verify_property_found(type_property property){
    if(strcmp(QAF_ID, get_property_cep(property)) == 0) return 1;
    return 0;
}

long verify_person_found(type_person person){
    if(strcmp(QAF_ID, get_person_cpf(person)) == 0) return 1;
    return 0;
}

long verify_property_leases(type_property property){
    if(strcmp(QAF_ID, get_property_cep(property)) == 0) return 1;
    return 0;
}

