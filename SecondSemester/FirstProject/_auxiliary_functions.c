
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

long verify_property_found(type_property property){
    if(strcmp(QAF_ID, get_property_cep(property)) == 0) return 1;
    return 0;
}

long verify_person_found(type_person person){
    char *person_cpf = get_person_cpf(person);
    if(strcmp(QAF_ID, person_cpf) == 0) return 1;
    return 0;
}

long verify_property_leases(type_property property){
    if(strcmp(QAF_ID, get_property_cep(property)) == 0) return 1;
    return 0;
}


long verify_property_leases_by_id(type_property property){
    if(strcmp(QAF_ID, get_property_lease_id(property)) == 0) return 1;
    return 0;
}

void set_txt_file(type_txt txtfile){
    QAF_TXTFILE = txtfile;
}

void _report_property_txt_(type_property property){
    char *cardinal_direction = malloc(sizeof(char)*3);
    sprintf(cardinal_direction, "%c%c", get_property_cardinal_direction(property), '\0');
    insert_string_in_txt(QAF_TXTFILE, "");
    insert_string_in_txt(QAF_TXTFILE, "CASA:");
    char *cep = get_property_cep(property);
    char *add = get_property_additional_address_data(property);
    int number = get_property_house_number(property);

    char *tmp = malloc(sizeof(char) *(strlen(cep) + strlen(add) + 40));
    sprintf(tmp, "CEP: %s  Nº: %d  Face: %s  Complemento: %s", cep, number, cardinal_direction, add);
    insert_string_in_txt(QAF_TXTFILE, tmp);

    free(cardinal_direction);
    free(tmp);
}

void _report_property_lease_txt_(type_property property){
    _report_property_txt_(property);
    char *property_id = get_property_lease_id(property);
    char *property_id_string = malloc(sizeof(char) * strlen(property_id) + 17);
    sprintf(property_id_string, "ID da locação: %s%c", property_id, '\0');
    insert_string_in_txt(QAF_TXTFILE, property_id_string);    
    
    char *area = malloc(sizeof(char) * QAF_SIZE_DOUBLESTR + 6);
    sprintf(area, "Área: %.2lf%c", get_property_area(property), '\0');
    insert_string_in_txt(QAF_TXTFILE, area);

    char *monthly_rent = malloc(sizeof(char) * QAF_SIZE_DOUBLESTR + 15);
    sprintf(monthly_rent, "Preço Mensal: %.2lf%c", get_property_monthly_rent(property), '\0');
    insert_string_in_txt(QAF_TXTFILE, monthly_rent);

    free(area);
    free(monthly_rent);
    free(property_id_string);
}

void _report_person_txt_(type_person person){
    char *name = get_person_full_name(person);
    insert_string_in_txt(QAF_TXTFILE, "");
    insert_string_in_txt(QAF_TXTFILE, "PESSOA:");
    char *cpf = get_person_cpf(person);
    char *cpf_string = malloc(sizeof(char) + strlen(cpf) + 10);
    sprintf(cpf_string, "CPF: %s%c", cpf, '\0');
    insert_string_in_txt(QAF_TXTFILE, cpf_string);

    char *string_name_with_gender = malloc(sizeof(char) * strlen(name) + 20);
    sprintf(string_name_with_gender, "Nome: %s  Gênero: %c%c", name, get_person_gender(person), '\0');
    insert_string_in_txt(QAF_TXTFILE, string_name_with_gender);
    
    char *birthday = get_person_birthday(person);
    char *birthday_string = malloc(sizeof(birthday) + 20);
    sprintf(birthday_string, "Data de nascimento: %s%c", birthday, '\0');
    insert_string_in_txt(QAF_TXTFILE, birthday_string);
    
    free(name);
    free(string_name_with_gender);
    free(birthday_string);
    free(cpf_string);
}

void _report_block_txt_(type_rect block_rect){
    insert_string_in_txt(QAF_TXTFILE, "BLOCO:");
    type_block block_data = get_rect_data(block_rect);
    insert_string_in_txt(QAF_TXTFILE, get_block_cep(block_data));

    char *x_string = malloc(sizeof(char) * QAF_SIZE_DOUBLESTR);
    sprintf(x_string, "%.2lf%c", get_rect_x(block_rect), '\0');
    insert_string_in_txt(QAF_TXTFILE, x_string);

    char *y_string = malloc(sizeof(char) * QAF_SIZE_DOUBLESTR);
    sprintf(y_string, "%.2lf%c", get_rect_y(block_rect), '\0');
    insert_string_in_txt(QAF_TXTFILE, y_string);

    char *w_string = malloc(sizeof(char) * QAF_SIZE_DOUBLESTR);
    sprintf(w_string, "%.2lf%c", get_rect_width(block_rect), '\0');
    insert_string_in_txt(QAF_TXTFILE, w_string);

    char *h_string = malloc(sizeof(char) * QAF_SIZE_DOUBLESTR);
    sprintf(h_string, "%.2lf%c", get_rect_height(block_rect), '\0');
    insert_string_in_txt(QAF_TXTFILE, h_string);
}

void _report_property_lease_available(){
    char *string = malloc(sizeof(char) * 12);
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