# test platformer
This repository contains sources of my yet unnamed platformer game for 286
MS-DOS computers.

## Hardware requirements
They're not yet guaranteed, they might be too high or too low to match the game,
since it's still in development.
 * Free RAM for the game: around 100 kB (probably way less)
 * CPU: 80286+
 * Graphics: EGA+ or compatible
 * MS-DOS 2.x+
 
## Building
You need:
 * GNU make,
 * Open Watcom,
 * Netwide Assembler (nasm),
 * *nix or Windows shell
 * Python 3:
   * Pillow Python library

On Linux you can use `./build.sh [module]`, `./buildall.sh` and `./clean.sh`.
On Windows you can use `build.bat [module]`, `buildall.bat` and `clean.bat`.

## License
See [LICENSE](LICENSE).
