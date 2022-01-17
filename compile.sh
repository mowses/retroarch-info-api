#!/usr/bin/env bash

BASEDIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

cd $BASEDIR/libretro-super/
rm /home/unknown/snap/retroarch/1005/.config/retroarch/cores/bettinastella_libretro.so

./libretro-bettinastella/configure
NOCLEAN=1 ./libretro-build.sh bettinastella

# comentar abaixo, só pra teste:
# cp ./dist/unix/bettinastella_libretro.so ~/snap/retroarch/1005/.config/retroarch/cores/
# retroarch -v -L /home/unknown/snap/retroarch/1005/.config/retroarch/cores/bettinastella_libretro.so /home/unknown/Downloads/Atari\ 2600/Enduro.bin