# DATA.DAT file format
DATA.DAT is a file containing all of game's graphical and sound data in a simple
format.

*Note: All values in the file are little-endian, unless stated otherwise.*

## Header
The header is very small - just 2 bytes in size. It specifies the amount of
nodes within the file - where every node is a resource - a sprite, a sound, etc.

## Node format
Node's size is dependant on its type and the size of its payload. Every node
starts with a header:
 * 1 byte - type:
   * 0 - sprite,
   * More will be added soon
 * 1 byte - length of the node's name
 * [ASCII characters defining the node's name]

### Sprite
If the node is a sprite, it additionally contains 2 next fields, right after
the nodename's end:
 * 2 bytes - sprite's width
 * 2 bytes - sprite's height
 * [content of the sprite with 1 byte per pixel (a pixel value >= 16 means
   the pixel is transparent. The data is saved row by row]
