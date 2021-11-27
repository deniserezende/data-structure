#include <stdio.h>
#include "qry_o_.h"

// Armazena no registrador r a posição geográfica
// do endereço cep/face/num
// SVG: linha vertical com identificação do
// registrador.
type_property o_(type_svg SVGFILE, char cep[], char cardinal_direction, int house_number){
    // AQUIDE fazer algo no svg


    type_property property = new_property(cep, cardinal_direction, house_number, "");
    return property;
}