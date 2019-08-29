# Game files
The game's assets are separated into multiple files. Currently implemented file
types are:
 * SPRITES.DAT,
 * ANIM.DAT,
 * TILESET.DAT,
 * PALETTE.DAT

## SPRITES.DAT format
SPRITES.DAT is a file containing every sprite used in the game. Its data is
stored in one separate segment, enforcing a max size of 64k.

First byte of the file is the amount of defined sprites. The rest is the raw
sprite data, where each sprite is stored in the following format:
 * 1 byte for width
 * 1 byte for height
 * 8 bytes for ASCII name
 * [width * height bytes representing sprite's raw data. Legal color values are
   0-15, with values > 15 treated as transparent. The data is stored row by
   row]

## ANIM.DAT format
ANIM.DAT stores animation data. Similairly to SPRITE.DAT, first byte specifies
the amount of animations stored within the file. After that, there is the
animation data, each one stored in the format:
 * 1 byte for animation's frames per second
 * 1 byte for amount of frames
 * 8 bytes for ASCII name
 * [8 bytes per frame with each frame being defined by a sprite name]

## TILESET.DAT format
TILESET.DAT stores... the game's tileset. First byte defines amount of tiles
defined. Every tile is stored in this format:
 * 1 byte for type
   * bit 0 (LSB) is the type of the tile. 0 means normal tile, 1 means animated
     tile
   * unused bits are reserved
 * 8 bytes for ASCII name
 * 8 bytes for animation or sprite name (depending on bit 0 of type)

## PALETTE.DAT format
PALETTE.DAT is a simple file. It's only 16 bytes long and contains values of
every palette value used in EGA graphic mode.
