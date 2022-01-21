#!/usr/bin/env bash

BASEDIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

cd $BASEDIR/modules/libretro-super/

./libretro-stella_info_api/configure
NOCLEAN=1 ./libretro-build.sh stella_info_api

cp ./dist/unix/stella_info_api_libretro.so $BASEDIR/compiled/

# comentar abaixo, só pra teste:
# retroarch -v -L /home/unknown/snap/retroarch/1005/.config/retroarch/cores/bettinastella_libretro.so /home/unknown/Downloads/Atari\ 2600/Enduro.bin