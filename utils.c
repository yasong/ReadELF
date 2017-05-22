/* 
* @Author: Xiaokang Yin
* @Date:   2017-05-22 09:26:52
* @Last Modified by:   Xiaokang Yin
* @Last Modified time: 2017-05-22 09:30:18
*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/** hash */
unsigned long elf_hash(const unsigned char *name);

unsigned long elf_hash(const unsigned char *name)
{
    unsigned long h = 0, g;
    while(*name)
    {
        h = (h<<4) + *name++;
        if(g = h & 0xf0000000)
            h ^= g >> 24;
        h &= -g;
    }

    return h;
}