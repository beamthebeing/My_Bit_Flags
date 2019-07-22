/*
 Author: Dylan Bennett
 Date: 2/15/2019
 Effort:
 Purpose:
 Interface proposal: 
 */

#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"
#include "status.h"


int main(int argc, char* argv[])
{

    BIT_FLAGS hBit_flags = NULL;
    int size, capacity;
  
    hBit_flags = bit_flags_init_number_of_bits(4);
    if(hBit_flags == NULL)
    {
        printf("Failed to allocate memory for hBit_flags.\n");
        exit(1);
    }


    bit_flags_set_flag(hBit_flags, 0);
    bit_flags_set_flag(hBit_flags, 1);
    bit_flags_unset_flag(hBit_flags, 1);
    
    bit_flags_set_flag(hBit_flags, 67);
    
    size = bit_flags_get_size(hBit_flags);
    capacity = bit_flags_get_capacity(hBit_flags);
    
    printf("%d/%d\n", size, capacity);
    
    bit_flags_display_flags(hBit_flags);
    
    
    
    bit_flags_destroy(&hBit_flags);
    
    return 0;
}
