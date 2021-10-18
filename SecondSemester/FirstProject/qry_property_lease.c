

#include <stdio.h>
#include <string.h>
#include "qry_property_lease.h"
#include <stdlib.h>

#define FONTSIZE 20
double QPL_x1, QPL_x2;
double QPL_y1, QPL_y2;
double QPL_height, QPL_width;
type_hashtable QPL_property_leases;
char QPL_CPF[40];
char QPL_ID[40];
type_svg QPL_SVGFILE;
double QPL_VIEWBOX[4];

// Oferta de locação. 
// Imóvel do endereço especificado, de área ar m2 é ofertado para locação por R$ v mensais.
void oloc(type_hashtable property_leases, char property_lease_id[], char cep[], char cardinal_direction, int house_number, char addicional_data[], double property_area, double monthly_rent){
    type_property new_lease = new_property(cep, cardinal_direction, house_number, addicional_data);
    add_lease_id_to_property(new_lease, property_lease_id);
    add_property_area(new_lease, property_area);
    add_property_monthly_rent(new_lease, monthly_rent);
    change_property_rent_status(new_lease, 1);

    long(*get_key_ptr)(type_property);
    get_key_ptr = get_property_lease_key;

    insert_item_in_hash_table(property_leases, new_lease, get_property_lease_key(new_lease), (void*)get_key_ptr, (void*)compare_properties_leases_id);
}





void _oloc_txt(type_property property){
    _report_property_lease_txt_(property);
}

void _oloc_svg(type_property property){
    int number = get_property_house_number(property);
    char color[8];
    sprintf(color, "black%c", '\0');
    char *string = malloc(sizeof(char) * 2);
    sprintf(string, "*%c", '\0');
    insert_text_in_svg(QPL_SVGFILE, (double)QPL_x1+number, (double)QPL_y1+number, color, string, FONTSIZE);
    free(string);
}

void action_property_oloc_(type_hashitem property){
    _oloc_txt(property);
    _oloc_svg(property);
}

long action_oloc_(type_mMlavlitems item){
    type_block block = get_rect_data(item);

    QPL_x1 = get_rect_x(item);
    QPL_x2 = QPL_x1 + get_rect_width(item);
    QPL_y1 = get_rect_y(item);
    QPL_y2 = QPL_y1 + get_rect_height(item);

    void(*action_property_ptr)(type_property);
    action_property_ptr = action_property_oloc_;

    set_id(get_block_cep(block));
    traverse_full_hash_table_with_conditional_action(QPL_property_leases, (void*)verify_property_leases, (void*)action_property_ptr);
    return 0;
}

// Quais são os imóveis disponíveis para locação na região especificada.
// TXT: relatar dados do imóvel e da locação 
// SVG: marcar no svg a região (um retângulo com bordas tracejadas) e os imóveis disponíveis (com ‘*’)
void oloc_(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks, type_hashtable property_leases, double x, double y, double w, double h){
    // Setting up global variables
    QPL_SVGFILE = SVGFILE;
    set_txt_file(TXTFILE);
    QPL_property_leases = property_leases;

    long(*action_ptr)(type_property);
    action_ptr = action_oloc_;

    set_x1_x2_y1_y2(x, x+w, y, y+h);
    traverse_mMlavltree_with_conditional_action(blocks, (void*)traverse_side_rect_in_rect_, (void*)condition_rect_in_rect_, (void*)action_ptr);
    
    // Inserting dashy rectangle 
    char color[8];
    sprintf(color, "green%c", '\0');
    insert_dasharray_rect_with_different_opacity_in_svg(QPL_SVGFILE, x, y, w, h, color, color, 2, 2, 0.2);
}





void _loc_txt(type_person person, type_property property){
    _report_person_txt_(person);
    _report_property_lease_txt_(property);
}

void _loc_svg(type_person person, type_property property){
    int number = get_property_house_number(property);
    char color[8];
    sprintf(color, "black%c", '\0');
    insert_line_in_svg(QPL_SVGFILE, QPL_x1 + number, QPL_y1 + number, QPL_x1 + number, QPL_VIEWBOX[1] - QPL_height/2, color, 1);

    char* person_cpf = get_person_cpf(person);
    char* person_fullname = get_person_full_name(person);
    char* property_cep = get_property_cep(property);
    char* lease_id = get_property_lease_id(property);
    
    char *string = malloc(sizeof(char) * (strlen(person_cpf) + strlen(person_fullname) + strlen(property_cep) + strlen(lease_id) + 15));
    
    sprintf(string, "%s %s %s %d %s%c", person_cpf, person_fullname, property_cep, number, lease_id, '\0');
    insert_text_in_svg(QPL_SVGFILE, QPL_x1+number, QPL_VIEWBOX[1] - QPL_height/2, color, string, 2);
    free(person_fullname);
    free(string);
}

void _loc_action(type_rect rectangle){
    QPL_x1 = get_rect_x(rectangle);
    QPL_y1 = get_rect_y(rectangle);
    QPL_height = get_rect_height(rectangle);
}

// Pessoa identificada por cpf aluga o imóvel cuja oferta é identificada por id. 
// O imóvel deixa de estar disponível para alocação. O indivíduo passa a ser morador do referido imóvel.
// TXT: reportar dados do imóvel, da locação e da pessoa.
// SVG: marcar endereço do imóvel, traçar uma reta vertical do imóvel até a borda superior do desenho e, 
// ao lado, colocar informações sobre morador, imóvel e locação
int loc(type_svg SVGFILE, type_txt TXTFILE, type_hashtable blocks_table, type_hashtable property_leases, type_hashtable people_table, char property_lease_id[], char person_cpf[], double viewbox[4]){
    QPL_SVGFILE = SVGFILE;
    set_txt_file(TXTFILE);

    QPL_VIEWBOX[0] = viewbox[0];
    QPL_VIEWBOX[1] = viewbox[1];
    QPL_VIEWBOX[2] = viewbox[2];
    QPL_VIEWBOX[3] = viewbox[3];

    long formatted_cpf = format_cpf(person_cpf);
    sprintf(QPL_CPF, "%s%c", person_cpf, '\0');
    
    long formatted_property_id = format_cep_from_base36_to_base10(property_lease_id);
    sprintf(QPL_ID, "%s%c", property_lease_id, '\0');

    set_id(person_cpf);
    type_hashitem person = lookup_item_in_hash_table(people_table, formatted_cpf, (void*)get_person_formatted_cpf, (void*)verify_person_found);
    if(person == NULL) return 0;

    set_id(property_lease_id);
    type_hashitem property_lease = lookup_item_in_hash_table(property_leases, formatted_property_id, (void*)get_property_lease_key, (void*)verify_property_leases_by_id);
    if(property_lease == NULL) return 0;

    int successful = add_property_tenant(property_lease, person);
    if(!successful) return 0;

    set_properties_leases_to_person(person, 1);
    add_persons_property_lease(person, property_lease);
    change_property_rent_status(property_lease, 0);

    set_id(get_property_cep(property_lease));
    type_rect block_rect = lookup_item_in_hash_table(blocks_table, get_property_cep_key(property_lease), (void*)get_key_from_block, (void*)verify_block_found);
    if(block_rect == NULL) return 0;
    QPL_x1 = get_rect_x(block_rect);
    QPL_y1 = get_rect_y(block_rect);
    QPL_height = get_rect_height(block_rect);

    _loc_txt(person, property_lease);
    _loc_svg(person, property_lease);

    return successful;
}




void _loc_txt_(type_property property){
    _report_property_lease_txt_(property);
    if(get_property_rent_status(property)){
        _report_person_txt_(get_property_tenant(property));
    }
}

void _loc_svg_(type_property property){
    int house_number = get_property_house_number(property);
    char color[8];
    sprintf(color, "black%c", '\0');
    if(get_property_rent_status(property) == 1){
        insert_text_in_svg(QPL_SVGFILE, QPL_x1+house_number, QPL_y1+house_number, color, "$", FONTSIZE);
    }
    else{
        type_person tenant = get_property_tenant(property);
        if(tenant == NULL) insert_text_in_svg(QPL_SVGFILE, QPL_x1+house_number, QPL_y1+house_number, color, "#", FONTSIZE);
        else insert_text_in_svg(QPL_SVGFILE, QPL_x1+house_number, QPL_y1+house_number, color, "*", FONTSIZE);
    }
}

// Qual a situação da oferta de locação?
// TXT: reportar os dados da moradia, se ela está alocada, se está disponível para locação. Caso esteja locada, reportar os dados pessoais do morador.
// SVG: marcar o local da moradia com ‘*’ se está locada; ‘$’ se está disponível para locação; ‘#’, caso o contrato de locação tenha sido encerrado (dloc).
int loc_(type_svg SVGFILE, type_txt TXTFILE, type_hashtable blocks_table, type_hashtable property_leases, char property_lease_id[]){
    QPL_SVGFILE = SVGFILE;
    set_txt_file(TXTFILE);

    long formatted_property_id = format_cep_from_base36_to_base10(property_lease_id);
    sprintf(QPL_ID, "%s%c", property_lease_id, '\0');

    set_id(property_lease_id);
    type_hashitem property_lease = lookup_item_in_hash_table(property_leases, formatted_property_id, (void*)get_property_lease_key, (void*)verify_property_leases_by_id);
    if(property_lease == NULL) return 0;

    set_id(get_property_cep(property_lease));
    type_hashitem block_rect = lookup_item_in_hash_table(blocks_table, get_property_cep_key(property_lease), (void*)get_key_from_block, (void*)verify_block_found);
    if(block_rect == NULL) return 0;

    QPL_x1 = get_rect_x(block_rect);
    QPL_y1 = get_rect_y(block_rect);

    _loc_txt_(property_lease);
    _loc_svg_(property_lease);
    return 1; //AQUIDE ?
}





void _dloc_txt(type_property property){
    _report_property_lease_txt_(property);
    if(!get_property_rent_status(property)){
        _report_person_txt_(get_property_tenant(property));
    }
}

void _dloc_svg(type_property property){
    char color[9];
    sprintf(color, "purple%c", '\0');
    insert_line_in_svg(QPL_SVGFILE, QPL_x1, QPL_y1, QPL_x1, QPL_VIEWBOX[1] - QPL_height/2, color, 1);
    
    char* property_cep = get_property_cep(property);
    char* lease_id = get_property_lease_id(property);
    int number = get_property_house_number(property);
    char *string;
    if(!get_property_rent_status(property)){
        type_person person = get_property_tenant(property);
        char* person_cpf = get_person_cpf(person);
        char* person_fullname = get_person_full_name(person);

        string = malloc(sizeof(char) * (strlen(person_cpf) + strlen(person_fullname) + strlen(property_cep) + strlen(lease_id) + 15));
        sprintf(string, "%s %s %s %d %s%c", person_cpf, person_fullname, property_cep, number, lease_id, '\0');
        free(person_fullname);
    }
    else{
        string = malloc(sizeof(char) * (strlen(property_cep) + strlen(lease_id) + 25));
        sprintf(string, "Sem morador %s %d %s%c", property_cep, number, lease_id, '\0');
    }
    
    insert_text_in_svg(QPL_SVGFILE, QPL_x1+number, QPL_VIEWBOX[1] - QPL_height/2, color, string, 2);
    free(string);
}

// Locatário encerra contrato de locação. A oferta é removida.
// TXT: reportar dados pessoais e sobre a moradia. 
// SVG: semelhante a loc.
// SVG: marcar endereço do imóvel, traçar uma reta vertical do imóvel até a borda superior do desenho e, 
// ao lado, colocar informações sobre morador, imóvel e locação
int dloc(type_txt TXTFILE, type_hashtable blocks_table, type_hashtable property_leases, char property_lease_id[], double viewbox[4]){
    set_txt_file(TXTFILE);
    
    QPL_VIEWBOX[0] = viewbox[0];
    QPL_VIEWBOX[1] = viewbox[1];
    QPL_VIEWBOX[2] = viewbox[2];
    QPL_VIEWBOX[3] = viewbox[3];

    //locatário encerra contrado de locação
    long formatted_property_id = format_cep_from_base36_to_base10(property_lease_id);
    sprintf(QPL_ID, "%s%c", property_lease_id, '\0');

    set_id(property_lease_id);
    type_hashitem property_deleted = delete_item_in_hash_table(property_leases, formatted_property_id, (void*)get_property_lease_key, (void*)verify_property_leases_by_id);
    if(property_deleted == NULL) return 0;

    set_id(get_property_cep(property_deleted));
    type_hashitem block_rect = lookup_item_in_hash_table(blocks_table, get_property_cep_key(property_deleted), (void*)get_key_from_block, (void*)verify_block_found);
    QPL_x1 = get_rect_x(block_rect);
    QPL_y1 = get_rect_y(block_rect);
    QPL_height = get_rect_height(block_rect);

    _dloc_txt(property_deleted);
    _dloc_svg(property_deleted);

    remove_property(property_deleted);

    return 1;
}
