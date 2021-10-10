

#include <stdio.h>
#include <string.h>
#include "qry_property_lease.h"
#include <stdlib.h>

#define FONTSIZE 20
double QPL_x1, QPL_x2;
double QPL_y1, QPL_y2;
double QPL_height, QPL_width;
type_hashtable QPL_property_leases;
char QPL_cep[40];
char QPL_CPF[40];
char QPL_ID[40];
type_svg QPL_SVGFILE;
type_txt QPL_TXTFILE;


void _QPL_report_property_txt_(type_property property){
    char cardinal_direction = get_property_cardinal_direction(property);
    insert_string_in_txt(QPL_TXTFILE, get_property_cep(property));
    insert_string_in_txt(QPL_TXTFILE, &cardinal_direction);
    char *number = malloc(sizeof(char) * 7);
    sprintf(number, "%d%c", get_property_house_number(property), '\0');
    insert_string_in_txt(QPL_TXTFILE, number);
    insert_string_in_txt(QPL_TXTFILE, get_property_additional_address_data(property));

    free(number);
}

void _QPL_report_property_lease_txt_(type_property property){
    insert_string_in_txt(QPL_TXTFILE, get_property_lease_id(property));
    _QPL_report_property_txt_(property);
    
    char *area = malloc(sizeof(char) * 7);
    sprintf(area, "%lf%c", get_property_area(property), '\0');
    insert_string_in_txt(QPL_TXTFILE, area);

    char *monthly_rent = malloc(sizeof(char) * 7);
    sprintf(monthly_rent, "%lf%c", get_property_monthly_rent(property), '\0');
    insert_string_in_txt(QPL_TXTFILE, monthly_rent);

    free(area);
    free(monthly_rent);
}

void _QPL_report_person_txt_(type_person person){
    char gender = get_person_gender(person);
    char *name = get_person_full_name(person);
    insert_string_in_txt(QPL_TXTFILE, get_person_cpf(person));
    insert_string_in_txt(QPL_TXTFILE, name);
    insert_string_in_txt(QPL_TXTFILE, &gender);
    insert_string_in_txt(QPL_TXTFILE, get_person_birthday(person));
    free(name);
}




// Oferta de locação. 
// Imóvel do endereço especificado, de área ar m2 é ofertado para locação por R$ v mensais.
void oloc(type_hashtable property_leases, char property_lease_id[], char cep[], char cardinal_direction, int house_number, char addicional_data[], double property_area, double monthly_rent){
    type_property new_lease = new_property(cep, cardinal_direction, house_number, addicional_data);
    add_property_area(new_lease, property_area);
    add_property_monthly_rent(new_lease, monthly_rent);
    change_property_rent_status(new_lease, 1);

    long(*get_key_ptr)(type_property);
    get_key_ptr = get_property_lease_key;

    insert_item_in_hash_table(property_leases, new_lease, get_property_lease_key(new_lease), (void*)get_key_ptr);
    printf("terminei o oloc\n");
}





void _oloc_txt(type_property property){
    _QPL_report_property_lease_txt_(property);
}

void _oloc_svg(type_property property){
    char color[8];
    sprintf(color, "black%c", '\0');
    insert_text_in_svg(QPL_SVGFILE, QPL_x1, QPL_y1, color, "*", FONTSIZE);
}

void action_property_oloc_(type_hashitem property){
    _oloc_txt(property);
    _oloc_svg(property);
}

long action_oloc_(type_mMlavlitems item){
    type_block block = get_rect_data(item);
    long cep = get_block_formatted_cep(block);
    sprintf(QPL_cep, "%s%c", get_block_cep(block), '\0');

    void(*action_property_ptr)(type_property);
    action_property_ptr = action_property_oloc_;

    traverse_hash_table_with_conditional_action_optimal(QPL_property_leases, cep, (void*)get_property_cep_key, (void*)verify_property_found, (void*)action_property_ptr);
    return 0;
}

// Quais são os imóveis disponíveis para locação na região especificada.
// TXT: relatar dados do imóvel e da locação 
// SVG: marcar no svg a região (um retângulo com bordas tracejadas) e os imóveis disponíveis (com ‘*’)
void oloc_(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks, type_hashtable property_leases, double x, double y, double w, double h){
    // Setting up global variables
    QPL_SVGFILE = SVGFILE;
    QPL_TXTFILE = TXTFILE;
    QPL_x1 = x;
    QPL_x2 = x+w;
    QPL_y1 = y;
    QPL_y2 = y+h;
    QPL_property_leases = property_leases;

    long(*action_ptr)(type_property);
    action_ptr = action_oloc_;

    traverse_mMlavltree_with_conditional_action(blocks, (void*)traverse_side_rect_in_rect_, (void*)condition_rect_in_rect_, (void*)action_ptr);
    
    // Inserting dashy rectangle 
    char color[8];
    sprintf(color, "black%c", '\0');
    insert_dasharray_rect_in_svg(QPL_SVGFILE, x, y, w, h, color, color, 2, 2);
}





void _loc_txt(type_person person, type_property property){
    _QPL_report_person_txt_(person);
    _QPL_report_property_lease_txt_(property);
}

void _loc_svg(type_person person, type_property property){
    char color[8];
    sprintf(color, "black%c", '\0');
    insert_line_in_svg(QPL_SVGFILE, QPL_x1, QPL_y1, QPL_x1, QPL_height*2, color, 2);
    insert_text_in_svg(QPL_SVGFILE, QPL_x1, QPL_height*2, color, get_person_full_name(person), FONTSIZE);
    insert_text_in_svg(QPL_SVGFILE, QPL_x1, QPL_height*2-10, color, get_person_cpf(person), FONTSIZE);
    insert_text_in_svg(QPL_SVGFILE, QPL_x1, QPL_height*2-15, color, get_property_cep(property), FONTSIZE);
    insert_text_in_svg(QPL_SVGFILE, QPL_x1, QPL_height*2-20, color, get_property_lease_id(property), FONTSIZE);
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
int loc(type_svg SVGFILE, type_txt TXTFILE, type_hashtable blocks_table, type_hashtable property_leases, type_hashtable people_table, char property_lease_id[], char person_cpf[]){
    QPL_SVGFILE = SVGFILE;
    QPL_TXTFILE = TXTFILE;

    long formatted_cpf = format_cpf(person_cpf);
    sprintf(QPL_CPF, "%s%c", person_cpf, '\0');
    
    long formatted_property_id = format_cep_from_base36_to_base10(property_lease_id);
    sprintf(QPL_ID, "%s%c", property_lease_id, '\0');

    type_hashitem person = lookup_item_in_hash_table(people_table, formatted_cpf, (void*)get_person_formatted_cpf, (void*)verify_person_found);
    if(person == NULL) return 0;
    printf("found the person\n");

    type_hashitem property_lease = lookup_item_in_hash_table(property_leases, formatted_property_id, (void*)get_property_lease_key, (void*)verify_property_found);
    if(property_lease == NULL) return 0;
    printf("found the property lease\n");

    int successful = add_property_tenant(property_lease, person);
    if(!successful) return 0;

    set_properties_leases_to_person(person, 1);
    add_persons_property_lease(person, property_lease);
    change_property_rent_status(property_lease, 0);


    void(*action_ptr)(type_property);
    action_ptr = _loc_action;
    
    printf("começar o traverse dos blocos\n");
    traverse_hash_table_with_conditional_action_optimal(blocks_table, get_property_cep_key(property_lease), (void*)get_key_from_block, (void*)verify_block_found, (void*)action_ptr);
    printf("finalizar o traverse dos blocos\n");

    _loc_txt(person, property_lease);
    _loc_svg(person, property_lease);

    return successful;
}




void _loc_txt_(type_property property){
    _QPL_report_property_lease_txt_(property);
    if(get_property_rent_status(property)){
        _QPL_report_person_txt_(get_property_tenant(property));
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
    QPL_TXTFILE = TXTFILE;

    long formatted_property_id = format_cep_from_base36_to_base10(property_lease_id);
    sprintf(QPL_ID, "%s%c", property_lease_id, '\0');

    long(*verify_property_ptr)(type_person);
    verify_property_ptr = verify_property_found;

    type_hashitem property_lease = lookup_item_in_hash_table(property_leases, formatted_property_id, (void*)get_property_lease_key, (void*)verify_property_ptr);
    if(property_lease == NULL) return 0;

    type_hashitem block_rect = lookup_item_in_hash_table(blocks_table, get_property_cep_key(property_lease), (void*)get_key_from_block, (void*)verify_block_found);
    if(block_rect == NULL) return 0;

    QPL_x1 = get_rect_x(block_rect);
    QPL_y1 = get_rect_y(block_rect);

    _loc_txt_(property_lease);
    _loc_svg_(property_lease);
    return 1; //AQUIDE ?
}





void _dloc_txt(type_property property){
    _QPL_report_property_lease_txt_(property);
    if(get_property_rent_status(property)){
        _QPL_report_person_txt_(get_property_tenant(property));
    }
}

void _dloc_svg(type_property property){
    char color[8];
    sprintf(color, "black%c", '\0');
    insert_line_in_svg(QPL_SVGFILE, QPL_x1, QPL_y1, QPL_x1, QPL_height*2, color, 2);
    insert_text_in_svg(QPL_SVGFILE, QPL_x1, QPL_height*2-15, color, get_property_cep(property), FONTSIZE);
    insert_text_in_svg(QPL_SVGFILE, QPL_x1, QPL_height*2-20, color, get_property_lease_id(property), FONTSIZE);
}

// Locatário encerra contrato de locação. A oferta é removida.
// TXT: reportar dados pessoais e sobre a moradia. 
// SVG: semelhante a loc.
// SVG: marcar endereço do imóvel, traçar uma reta vertical do imóvel até a borda superior do desenho e, 
// ao lado, colocar informações sobre morador, imóvel e locação
int dloc(type_txt TXTFILE, type_hashtable blocks_table, type_hashtable property_leases, char property_lease_id[]){
    //locatário encerra contrado de locação
    long formatted_property_id = format_cep_from_base36_to_base10(property_lease_id);
    sprintf(QPL_ID, "%s%c", property_lease_id, '\0');

    long(*verify_property_ptr)(type_person);
    verify_property_ptr = verify_property_found;

    // type_hashitem property_lease = lookup_item_in_hash_table(property_leases, formatted_property_id, (void*)get_property_lease_key, (void*)verify_property_ptr);
    // if(property_lease == NULL) return 0; 
    type_hashitem property_deleted = delete_item_in_hash_table(property_leases, formatted_property_id, (void*)get_property_lease_key, (void*)verify_property_ptr);
    if(property_deleted == NULL) return 0;

    type_hashitem block_rect = lookup_item_in_hash_table(blocks_table, get_property_cep_key(property_deleted), (void*)get_key_from_block, (void*)verify_block_found);
    QPL_x1 = get_rect_x(block_rect);
    QPL_y1 = get_rect_y(block_rect);
    QPL_height = get_rect_height(block_rect);

    _dloc_txt(property_deleted);
    _dloc_svg(property_deleted);

    remove_property(property_deleted);
    property_deleted = delete_item_in_hash_table(property_leases, formatted_property_id, (void*)get_property_lease_key, (void*)verify_property_ptr);
    return 1;
}
