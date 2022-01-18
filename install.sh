#!/usr/bin/env bash

BASEDIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

append_content () {
    local src=$1
    local dst=$2

    src_dir=$(echo "$src" | sed 's/\//\\\//g')
    dst_dir=$(echo "$dst" | sed 's/\//\\\//g')
    
    shopt -s nullglob dotglob

    for pathname in "$src"/*; do
        dst_file=$(echo "$pathname" | sed "s/$src_dir/$dst_dir/");
        if [ -d "$pathname" ]; then
            append_content "$pathname" "$dst_file"
        else
            status="?????"
            if grep "# retroarch-info-api APPEND start" -F -q "$dst_file"; then
                status="ALREADY EXISTS"
            else
                cat $pathname >> $dst_file;
                status="APPENDED"
            fi
            printf '[%s] %s > %s\n' "$status" "$pathname" "$dst_file"
        fi
    done
}

src_dir="$BASEDIR/libretro-info-api/append"
echo ""
echo "Recursively append the content of files from $src_dir into the libretro-super:"
dst_dir="$BASEDIR/libretro-super"
append_content "$src_dir" "$dst_dir"


echo ""
echo "Fetching cores that retroarch-info-api supports:"
$BASEDIR/libretro-super/libretro-fetch.sh stella_info_api


echo ""
echo "Creating symlinks..."
ln -s $BASEDIR/libretro-info-api/libretro-stella/src/libretro/info $BASEDIR/libretro-super/libretro-stella/src/libretro/info

