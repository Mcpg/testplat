#!/usr/bin/env python3

# DATA.DAT generator

import struct
from palette import *
from datafile import *

from PIL import Image

NODE_TYPE_SPRITE = 0

data_file_target = "../gamedir/DATA.DAT"

# Returns raw sprite data in bytearray
# Returns false on error
def convert_sprite(path):
    result = bytearray()
    
    try:
        im = Image.open(path)
    except IOError:
        print("Couldn't open image ", path, ": IOError")
        quit(1)
    
    with im:
        for y in range(im.height):
            for x in range(im.width):
                pixel_rgba = im.getpixel((x, y))
                
                if pixel_rgba[3] == 0:
                    result.append(255) # Transparent pixel
                    continue
                
                pixel = (pixel_rgba[0], pixel_rgba[1], pixel_rgba[2])
                if not pixel in palette_data:
                    print("Error: image ", path, " does is not palette compliant!")
                    quit(1)
                    return false
                
                result.append(palette_data.index(pixel))
    
    return result

# ################################################

print("Generating DATA.DAT...")

try:
    data_file = open(data_file_target, "wb")
except IOError:
    print("IOError: could not open the file!")
    quit(1)

with data_file:
    
    # Write the node amount
    data_file.write(struct.pack("<h", node_amount))
    
    # Convert sprites
    print("Writing sprite data...")
    for sprite in sprites:
        print(" Writing ", sprite, "...")
        print(" Name Length: ", str(len(sprite)))
        converted = convert_sprite(sprites[sprite])
        
        data_file.write(struct.pack("<b", NODE_TYPE_SPRITE))
        data_file.write(struct.pack("<b", len(sprite)))
        data_file.write(sprite.encode("ascii"))
        data_file.write(converted)
        
    

print("Finished!")
