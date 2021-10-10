// 
//  qry_del_m_dm_mud.h
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef qry_del_m_dm_mud_h
#define qry_del_m_dm_mud_h
#include "hash_table.h"
#include "rectangle.h" 
#include "block.h"
#include "property.h"
#include "person.h"
#include "_auxiliary_functions.h"
#include "SVG.h"
#include "TXT.h"


void del(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable blocks_table, type_hashtable properties_table, type_hashtable people_table, type_hashtable property_leases, char block_cep[]);
void m_(type_txt TXTFILE, type_hashtable blocks_table, type_hashtable properties_table, char block_cep[]);
void dm_(type_svg SVGFILE, type_txt TXTFILE, type_hashtable blocks_table, type_hashtable people_table, char person_cpf[]);
void mud(type_svg SVGFILE, type_txt TXTFILE, type_hashtable blocks_table, type_hashtable people_table, type_hashtable properties_table, char person_cpf[], char property_cep[], char cardinal_direction, int house_number, char addicional_data[]);

#endif /* qry_del_m_dm_mud_h */