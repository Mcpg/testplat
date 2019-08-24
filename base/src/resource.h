#ifndef _RESOURCE_H
#define _RESOURCE_H

#define NODE_SPRITE 0x00

#include <stdint.h>

/* See data/README.md for a little documentation of the format */

struct data_node
{
    uint8_t type;
    uint8_t name_length;
    char name[1];
};
typedef struct data_node data_node_t;

struct sprite
{
    uint16_t width;
    uint16_t height;
    uint8_t data[1];
};
typedef struct sprite sprite_t;

/* An array of pointers to loaded data nodes */
extern data_node_t __far** data_nodes;

/* Raw buffer of data nodes */
extern uint8_t __far* data_nodes_raw;
extern uint16_t data_nodes_size;
extern uint16_t data_node_amount;

/* Returns NULL if the data node is not a sprite node */
extern sprite_t* node_get_sprite(data_node_t* node);
extern void load_data();

#endif
