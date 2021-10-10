//
//  hash_table.c
//  
//
//  Created by Denise F. de Rezende on 01/09/21.
//


#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

#define TABLE_SIZE 1001

unsigned long hashing_function(long key){
    unsigned long hash_value = key % TABLE_SIZE;
    return hash_value;
}

void initialize_hash_table_aux(type_hashtable hash_table){
    type_hashitem* hashtable = hash_table;
    for(int i = 0; i < TABLE_SIZE; i++){
        hashtable[i] = NULL;
    }
}

type_hashtable create_hash_table(){
    type_hashitem* hash_table = malloc(sizeof(type_hashitem*) * TABLE_SIZE + 1);  
    initialize_hash_table_aux(hash_table);
    return hash_table;
}

void print_hash_table(type_hashtable hash_table, type_hashtptrf_oneitem print_item){
    type_hashitem *hashtable = hash_table;
    type_list vertical_list;
    type_list horizontal_list;

    printf("Start\n");
    for(int i = 0; i < TABLE_SIZE; i=i+1){
        printf("%d", i);
        if(hashtable[i] == NULL){
            printf("\t---");
        }
        else{
            vertical_list = hashtable[i];
            set_current_to_first_item_in_list(vertical_list);
            int done;
            do{
                done = is_current_last_item_in_list(vertical_list);
                horizontal_list = get_current_item_in_list(vertical_list);
                int _done;
                type_hashitem item;
                
                // getting the items in the vertical list aka horizontal list
                set_current_to_first_item_in_list(horizontal_list);
                do{
                    _done = is_current_last_item_in_list(horizontal_list);
                    item = get_current_item_in_list(horizontal_list);
                    printf("\t");
                    print_item(item);
                    move_current_forward_in_list(horizontal_list);
                }while(!_done);
                
                move_current_forward_in_list(vertical_list);

            }while(!done);
        }
        printf("\n");
    }
    printf("End\n");
}

unsigned int collision_in_hash_table_aux(type_hashtable hash_table, int index, type_hashitem collision_item, long collision_item_key, type_lptrf_oneitem get_item_key){
    type_hashitem * hashtable = hash_table;
    type_list vertical_list = hashtable[index];
    type_list horizontal_list;
    type_hashitem current_item;
    int done;
    int successful_operation = 0;

    set_current_to_first_item_in_list(vertical_list);
    do{
        // traversing the vertical list
        done = is_current_last_item_in_list(vertical_list);
        horizontal_list = get_current_item_in_list(vertical_list);

        // getting the items in the vertical list aka horizontal list
        set_current_to_first_item_in_list(horizontal_list);
        current_item = get_current_item_in_list(horizontal_list);
        long current_item_key = (long)get_item_key(current_item);
        // checking if the item in the horizontal list has the same key as the one to be inserted
        if(collision_item_key == current_item_key){
            // If so add the item to this horizontal list
            insert_item_at_the_end_of_list(horizontal_list, collision_item);
            successful_operation = 1;
            break;
        }
        // Else continue looking for the maching key
        move_current_forward_in_list(vertical_list);

    }while(!done);

    // If the key of the item to be inserted was never found, create new horizontal list
    // and add the item to that new list
    if(!successful_operation){
        type_list new_horizontal_list = create_list();
        insert_item_at_the_end_of_list(new_horizontal_list, collision_item);
        insert_item_at_the_end_of_list(vertical_list, new_horizontal_list);
        successful_operation = 1;
    }

    return successful_operation;
}

// item cannot equal null
int insert_item_in_hash_table(type_hashtable hash_table, type_hashitem item, long key, type_lptrf_oneitem get_item_key){
    type_hashitem *hashtable = hash_table;
    int index = hashing_function(key);
    // Collision
    if(hashtable[index] != NULL){
        // To deal with collision, we will create a double linked list
        return collision_in_hash_table_aux(hashtable, index, item, key, get_item_key);
    }
    // If there isn't a item in the index position, we will add two linked lists to add the item.
    // One vertical pointed by the position indicated by index and another horizontal 
    // pointed by the first element in the vertical list.
    type_list vertical_list = create_list();
    type_list horizontal_list = create_list();

    insert_item_at_the_end_of_list(horizontal_list, item);
    insert_item_at_the_end_of_list(vertical_list, horizontal_list);
    hashtable[index] = vertical_list;

    return 1;
} 


type_hashitem lookup_item_in_hash_table(type_hashtable hash_table, long key, type_lptrf_oneitem get_item_key, type_lptrf_oneitem this_item){
    type_hashitem * hashtable = hash_table;
    int index = hashing_function(key);
    int done;
    int successful_operation = 0;
    if(hashtable[index] == NULL) return NULL;

    type_list vertical_list = hashtable[index];
    type_list horizontal_list;
    type_hashitem item;

    // lookup the item
    set_current_to_first_item_in_list(vertical_list);
    do{
        // traversing the vertical list
        done = is_current_last_item_in_list(vertical_list);
        horizontal_list = get_current_item_in_list(vertical_list);

        // getting the items in the vertical list aka horizontal list
        set_current_to_first_item_in_list(horizontal_list);
        item = get_current_item_in_list(horizontal_list);
        long item_key = (long)get_item_key(item);

        // checking if the item in the horizontal list has the same key as the one we are looking for
        if(key == item_key){
            // If this is the list containing the item we want to find
            int done_;
            type_hashitem item_;
            
            do{
                done_ = is_current_last_item_in_list(horizontal_list);
                item_ = get_current_item_in_list(horizontal_list);
                if((long)this_item(item_)){
                    return(item_);
                    break;
                }

                move_current_forward_in_list(horizontal_list);
            }while(!done_);
            
            break;
        }
        // Else continue looking for the maching key
        move_current_forward_in_list(vertical_list);

    }while(!done);

    return NULL;
}

/*type_hashitem delete_item_in_hash_table(type_hashtable hash_table, long key, type_lptrf_oneitem get_item_key, type_lptrf_oneitem delete_this_item){
    type_hashitem *hashtable = hash_table;
    int index = hashing_function(key);
    int done;
    int successful_operation = 0;
    if(hashtable[index] == NULL) return NULL;

    type_list vertical_list = hashtable[index];
    type_list horizontal_list;
    type_hashitem item;

    // lookup the item
    set_current_to_first_item_in_list(vertical_list);
    do{
        // traversing the vertical list
        done = is_current_last_item_in_list(vertical_list);
        horizontal_list = get_current_item_in_list(vertical_list);

        // getting the items in the vertical list aka horizontal list
        set_current_to_first_item_in_list(horizontal_list);
        item = get_current_item_in_list(horizontal_list);
        long item_key = (long)get_item_key(item);

        // checking if the item in the horizontal list has the same key as the one to be deleted
        if(key == item_key){
            // If this is the list containing the item to be deleted
            int done_;
            type_hashitem item_;
            
            do{
                done_ = is_current_last_item_in_list(horizontal_list);
                item_ = get_current_item_in_list(horizontal_list);
                if((long)delete_this_item(item_)){
                    delete_current_item_in_list(horizontal_list);
                    break;
                }

                move_current_forward_in_list(horizontal_list);
            }while(!done_);
            
            // If horizontal list became empty then remove item from vertical list as well
            if(empty_list(horizontal_list)){
                delete_current_item_in_list(vertical_list);
                destroi_list(horizontal_list);
                if(empty_list(vertical_list)){
                    destroi_list(vertical_list);
                    hashtable[index] = NULL;
                }
            }
            break;
        }
        // Else continue looking for the maching key
        move_current_forward_in_list(vertical_list);

    }while(!done);

    return NULL;
}  
*/

type_hashitem delete_item_in_hash_table(type_hashtable hash_table, long key, type_lptrf_oneitem get_item_key, type_lptrf_oneitem delete_this_item){
    type_hashitem *hashtable = hash_table;
    int index = hashing_function(key);
    int done;
    int successful_operation = 0;
    if(hashtable[index] == NULL) return NULL;

    type_list vertical_list = hashtable[index];
    type_list horizontal_list;
    type_hashitem item;

    // lookup the item
    set_current_to_first_item_in_list(vertical_list);
    do{
        // traversing the vertical list
        done = is_current_last_item_in_list(vertical_list);
        horizontal_list = get_current_item_in_list(vertical_list);

        // getting the items in the vertical list aka horizontal list
        set_current_to_first_item_in_list(horizontal_list);
        item = get_current_item_in_list(horizontal_list);
        long item_key = (long)get_item_key(item);

        // checking if the item in the horizontal list has the same key as the one to be deleted
        if(key == item_key){
            // If this is the list containing the item to be deleted
            int done_;
            type_hashitem item_;
            
            do{
                done_ = is_current_last_item_in_list(horizontal_list);
                item_ = get_current_item_in_list(horizontal_list);
                if((long)delete_this_item(item_)){
                    delete_current_item_in_list(horizontal_list);
                    successful_operation = 1;
                    break;
                }

                move_current_forward_in_list(horizontal_list);
            }while(!done_);
            
            // If horizontal list became empty then remove item from vertical list as well
            if(empty_list(horizontal_list)){
                delete_current_item_in_list(vertical_list);
                destroi_list(horizontal_list);
                if(empty_list(vertical_list)){
                    destroi_list(vertical_list);
                    hashtable[index] = NULL;
                }
            }

            if(successful_operation){
                return item_;
            }
        }
        // Else continue looking for the maching key
        move_current_forward_in_list(vertical_list);

    }while(!done);

    return NULL;
}  

void traverse_hash_table_with_conditional_action_optimal(type_hashtable hash_table, long key, type_lptrf_oneitem get_item_key, type_hashtptrf_oneitem condition, type_hashtptrf_oneitem action){
    type_hashitem * hashtable = hash_table;
    int index = hashing_function(key);
    int done;
    int successful_operation = 0;
    if(hashtable[index] == NULL) return;

    type_list vertical_list = hashtable[index];
    type_list horizontal_list;
    type_hashitem item;

    // lookup the item
    set_current_to_first_item_in_list(vertical_list);
    do{
        // traversing the vertical list
        done = is_current_last_item_in_list(vertical_list);
        horizontal_list = get_current_item_in_list(vertical_list);

        traverse_full_list_with_conditional_action(horizontal_list, condition, action);
                
        // If horizontal list became empty then remove item from vertical list as well
        if(empty_list(horizontal_list)){
            delete_current_item_in_list(vertical_list);
            destroi_list(horizontal_list);
            if(empty_list(vertical_list)){
                destroi_list(vertical_list);
                hashtable[index] = NULL;
                break;
            }
        } 

        // // getting the items in the vertical list aka horizontal list
        // set_current_to_first_item_in_list(horizontal_list);
        // item = get_current_item_in_list(horizontal_list);
        // long item_key = (long)get_item_key(item);

        // // checking if the item in the horizontal list has the same key as the one we are looking for
        // if(key == item_key){
        //     // If this is the list containing the item we want to find
        //     int done_;
        //     type_hashitem item_;
            
        //     do{
        //         done_ = is_current_last_item_in_list(horizontal_list);
        //         item_ = get_current_item_in_list(horizontal_list);
        //         if((long)condition(item_)){
        //             action(item_);
        //         }

        //         move_current_forward_in_list(horizontal_list);
        //     }while(!done_);
            
        //     break;
        // }
        // Else continue looking for the maching key

        move_current_forward_in_list(vertical_list);

    }while(!done);

    return;
}


// del?
/*
void traverse_full_hash_table_with_action(type_hashtable hash_table, type_hashtptrf_oneitem action){
    type_hashitem *hashtable = hash_table;
    type_list vertical_list;
    type_list horizontal_list;

    for(int i = 0; i < TABLE_SIZE; i=i+1){
        if(hashtable[i] != NULL){
            vertical_list = hashtable[i];
            set_current_to_first_item_in_list(vertical_list);
            int done;
            do{
                done = is_current_last_item_in_list(vertical_list);
                horizontal_list = get_current_item_in_list(vertical_list);
                int _done;
                type_hashitem item;

                // getting the items in the vertical list aka horizontal list
                set_current_to_first_item_in_list(horizontal_list);
                do{
                    _done = is_current_last_item_in_list(horizontal_list);
                    item = get_current_item_in_list(horizontal_list);
                    action(item);
                    move_current_forward_in_list(horizontal_list);
                }while(!_done);

                move_current_forward_in_list(vertical_list);

            }while(!done);
        }
    }
}
*/

void traverse_full_hash_table_with_conditional_action(type_hashtable hash_table, type_hashtptrf_oneitem condition, type_hashtptrf_oneitem action){
    type_hashitem *hashtable = hash_table;
    type_list vertical_list;
    type_list horizontal_list;

    for(int i = 0; i < TABLE_SIZE; i=i+1){
        if(hashtable[i] != NULL){
            vertical_list = hashtable[i];
            set_current_to_first_item_in_list(vertical_list);
            int done;
            do{
                done = is_current_last_item_in_list(vertical_list);
                horizontal_list = get_current_item_in_list(vertical_list);
                int _done;
                type_hashitem item;
                traverse_full_list_with_conditional_action(horizontal_list, condition, action);
                
                // If horizontal list became empty then remove item from vertical list as well
                if(empty_list(horizontal_list)){
                    delete_current_item_in_list(vertical_list);
                    destroi_list(horizontal_list);
                    if(empty_list(vertical_list)){
                        destroi_list(vertical_list);
                        hashtable[i] = NULL;
                    }
                }   

                // // getting the items in the vertical list aka horizontal list
                // set_current_to_first_item_in_list(horizontal_list);
                // do{
                //     _done = is_current_last_item_in_list(horizontal_list);
                //     item = get_current_item_in_list(horizontal_list);
                //     if((long)condition(item)){
                //         if(action(item);
                //     }
                //     move_current_forward_in_list(horizontal_list);
                // }while(!_done);

                move_current_forward_in_list(vertical_list);

            }while(!done);
        }
    }
}