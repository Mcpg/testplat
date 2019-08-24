#include "resource.h"
#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE_PATH "DATA.DAT"
#define DATA_READ_BUF ((uint16_t) 256)

data_node_t __far** data_nodes;
uint8_t __far* data_nodes_raw;
uint16_t data_nodes_size;
uint16_t data_node_amount;

extern void __far* near_to_far(void*);
#pragma aux near_to_far = \
        "nop"             \
        parm [ax]         \
        value [ds ax];

sprite_t* node_get_sprite(data_node_t __far* node)
{
    if (node->type != NODE_SPRITE)
        return NULL;
    
    return (sprite_t*) (
        (uintptr_t) node + sizeof(data_node_t) + node->name_length
    );
}

void load_data()
{
    uint16_t i;
    uint8_t buffer[DATA_READ_BUF];
    uint8_t __far* buf_faddr = near_to_far(buffer);
    FILE* f;
    uint32_t file_size;
    uint16_t offset;
    uint16_t read_amount;
    
    f = fopen(DATA_FILE_PATH, "r");
    if (f == NULL)
    {
        printf("ERROR: Could not open DATA.DAT!\n");
        exit(1);
        return;
    }
    
    /* Get the file size */
    fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    if (file_size >= 0x10000)
    {
        printf("ERROR: DATA.DAT is too big! Max allowed size is 64k\n");
        fclose(f);
        exit(1);
        return;
    }
    
    if (fread(&data_node_amount, sizeof(data_node_amount), 1, f) != 1)
    {
        printf("ERROR: DATA.DAT read error (incorrect format?)\n");
        fclose(f);
        exit(1);
        return;
    }
    
    if (data_node_amount == 0)
    {
        printf("ERROR: 0 data nodes?\n");
        fclose(f);
        exit(1);
    }

    /* Directly allocate a separate segment for data */
    data_nodes_raw = (uint8_t __far*) _fmalloc((size_t) file_size & 0xFFFF - 2);
    if (data_nodes_raw == NULL)
    {
        printf("ERROR: Could not allocate enough memory for game data!\n");
        exit(1);
        return;
    }

    /* Read the file in 256 byte chunks, since there isn't anything like
       _fread, unfortuantely.
       
       TODO: Rewrite this part of file reading in Assembly? */
    for (i = file_size & 0xFFFF; i > 0; i -= DATA_READ_BUF)
    {
        read_amount = i < DATA_READ_BUF ? i : DATA_READ_BUF;
        fread(&buffer, read_amount, 1, f);
        _fmemcpy(data_nodes_raw + read_amount, buf_faddr, read_amount);
        
        offset += read_amount;
        if (i < DATA_READ_BUF)
            break;
    }
    
    fclose(f);
}
