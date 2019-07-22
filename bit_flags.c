/*
 Author: Dylan Bennett
 Date: 2/15/2019
 Effort: 7+ hours
 Purpose: Create an opague object wrapper for the first few daily assignments
 that dealt with bit-wise operators.
 Interface proposal: A function that prints the bits so that you can see
 the changes you are making to your container. (I created the function
 and commented it out below.)
 */

#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"
#include "status.h"

struct flag_holder
{
    int size;
    int capacity;
    int* data;
};
typedef struct flag_holder Flag_holder;



BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
    Flag_holder* pBit_flags;
    unsigned int n;
    unsigned int system_bits;
    
    n = 1;
    system_bits = 0;
    while (n)
    {
        system_bits ++;
        n <<= 1;
    }
    
    pBit_flags = (Flag_holder*)malloc(sizeof(Flag_holder));
    if (pBit_flags != NULL)
    {
        pBit_flags->size = 0;
        pBit_flags->capacity = (number_of_bits + (system_bits - number_of_bits % system_bits)) / system_bits;
        pBit_flags->data = (int*)malloc(sizeof(int)*pBit_flags->capacity/**system_bits*/);
        if (pBit_flags->data == NULL)
        {
            free(pBit_flags);
            return NULL;
        }
    }
    
    return (BIT_FLAGS)pBit_flags;
}


Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    Flag_holder* pBit_flags = (Flag_holder*)hBit_flags;
    int index;
    int* pTemp;
    int i;
    unsigned int hold;
    unsigned int n;
    unsigned int system_bits;
    int precapacity = pBit_flags->capacity;
    
    
    
    
    //Get size of system bits
    n = 1;
    system_bits = 0;
    while (n)
    {
        system_bits ++;
        n <<= 1;
    }
    
    //get size
    if(flag_position > pBit_flags->size)
    {
        pBit_flags->size = flag_position+1;
    }
    
    
    //Get index that flag_position is in
    index = flag_position / system_bits;
    
    //Resize data if index is greater than capacity
    if (index >= pBit_flags->capacity)
    {
        pBit_flags->capacity = (flag_position + (system_bits - flag_position % system_bits)) / system_bits;
        pTemp = (int*)malloc(sizeof(int)*pBit_flags->capacity/**system_bits*/);
        if (pTemp == NULL)
        {
            printf("Failed to allocate memory for pTemp.\n");
            exit(1);
        }
        
        //copy numbers in data to pTemp; pTemp has the added capacity
        for(i = 0; i < pBit_flags->capacity /* * system_bits */; i ++)
        {
            if(i < precapacity)
            {
                pTemp[i] = pBit_flags->data[i];
            }
            else
            {
                pTemp[i] = 0;
            }
        }
        //Rewrite Data
        free(pBit_flags->data);
        pBit_flags->data = pTemp;
    }
    
    //get flag_position in bitwise format and add to data
    hold = 1;
    hold <<= flag_position % system_bits;
    pBit_flags->data[index] |= hold;
    
    
    return SUCCESS;
}


Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    Flag_holder* pBit_flags = (Flag_holder*)hBit_flags;
    int index;
    int* pTemp;
    int i;
    unsigned int hold;
    unsigned int n;
    unsigned int system_bits;
    int size = 0;
    int precapacity = pBit_flags->capacity;

    
    //Get bumber of bits the system can hold
    n = 1;
    system_bits = 0;
    while (n)
    {
        system_bits ++;
        n <<= 1;
    }
    
    
    //get index of flag_postion
    index = flag_position / system_bits;
    
    
    //Resize data if index is greater than capacity
    if (index >= pBit_flags->capacity)
    {
        pBit_flags->capacity = (flag_position + (system_bits - flag_position % system_bits)) / system_bits;
        pTemp = (int*)malloc(sizeof(int)*pBit_flags->capacity/* * system_bits*/);
        if (pTemp == NULL)
        {
            printf("Failed to allocate memory for pTemp.\n");
            exit(1);
        }
        
        //rewrite data with increased capacity
        for(i = 0; i < pBit_flags->capacity/* * system_bits*/; i ++)
        {
            if(i < precapacity)
            {
                pTemp[i] = pBit_flags->data[i];
            }
            else
            {
                pTemp[i] = 0;
            }
        }
        free(pBit_flags->data);
        pBit_flags->data = pTemp;
    }
    
    
    
    
    //Get flag_position in bitwise format and remove from data[index]
    hold = 1;
    hold <<= flag_position % system_bits;
    pBit_flags->data[index] &= ~hold;
    
    
    //get size
    if(flag_position + 1 == pBit_flags->size)
    {
        while (size == 0 || flag_position >= 0)
        {
            size = bit_flags_check_flag(hBit_flags, flag_position);
            if(size == 1)
            {
                pBit_flags->size = flag_position + 1;
            }
            flag_position --;
        }
        if(size == -1)
        {
            pBit_flags->size = 0;
        }
    }
    
    return SUCCESS;
}


int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    Flag_holder* pBit_flags = (Flag_holder*)hBit_flags;
    int index;
    unsigned int hold;
    unsigned int n;
    unsigned int system_bits;
    
    n = 1;
    system_bits = 0;
    while (n)
    {
        system_bits ++;
        n <<= 1;
    }
    
    // Condition: Out of bounds
    index = flag_position / system_bits;
    if (index > pBit_flags->capacity)
    {
        return -1;
    }
    
    //Condition: In bounds
    hold = 1;
    hold <<= flag_position;
    if(pBit_flags->data[index] & hold)
    {
        return 1;
    }
    return 0;
}


int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
    Flag_holder* pBit_flags = (Flag_holder*)hBit_flags;
    return pBit_flags->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
    Flag_holder* pBit_flags = (Flag_holder*)hBit_flags;
    unsigned int n;
    unsigned int system_bits;
    
    n = 1;
    system_bits = 0;
    while (n)
    {
        system_bits ++;
        n <<= 1;
    }
    return pBit_flags->capacity*system_bits;
}


void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
    Flag_holder* pBit_flags = (Flag_holder*)*phBit_flags;
    free(pBit_flags->data);
    free(pBit_flags);
    *phBit_flags = NULL;
    
}




void bit_flags_display_flags(BIT_FLAGS hBit_flags)
{
    Flag_holder* pBit_flags = (Flag_holder*)hBit_flags;
    int i;
    unsigned int n;
    unsigned int system_bits;
    
    n = 1;
    system_bits = 0;
    while (n)
    {
        system_bits ++;
        n <<= 1;
    }
    
    for(i = 0; i < (pBit_flags->capacity)*system_bits; i ++)
    {
        printf("%d", bit_flags_check_flag(hBit_flags, i));
        if((i+1)%4==0)
        {
            printf(" ");
        }
        if ((i+1)%system_bits==0)
        {
            printf("\n");
        }
    }
}
