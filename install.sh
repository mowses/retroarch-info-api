#!/usr/bin/env bash

BASEDIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

append_content () {
    local src="$1"
    local dst="$2"
    local src_dir=$(echo "$src" | sed 's/\//\\\//g')
    local dst_dir=$(echo "$dst" | sed 's/\//\\\//g')
    
    shopt -s nullglob dotglob

    for pathname in "$src"/*; do
        dst_file=$(echo "$pathname" | sed "s/$src_dir/$dst_dir/");
        if [ -d "$pathname" ]; then
            append_content "$pathname" "$dst_file"
        else
            status="?????"
            if grep "# retroarch-info-api APPEND start" -F -q "$dst_file"; then
                status="SKIPPED"
            else
                cat $pathname >> $dst_file;
                status="APPENDED"
            fi
            printf '[%s] %s >> %s\n' "$status" "$pathname" "$dst_file"
        fi
    done
}

src_dir="$BASEDIR/libretro-info-api/append"
dst_dir="$BASEDIR/modules/libretro-super"
echo ""
echo "Recursively append the content of files from $src_dir into $dst_dir:"
append_content "$src_dir" "$dst_dir"


echo ""
echo "Fetching cores that retroarch-info-api supports:"
cd $dst_dir && ./libretro-fetch.sh stella_info_api
# replace the target_name from stella to stella_info_api
# replacing this string make the compile process succeed in the `cp` step.
sed -i 's/TARGET_NAME = stella$/TARGET_NAME = stella_info_api/' $dst_dir/libretro-stella_info_api/src/libretro/Makefile


echo ""
echo "Creating symlinks..."
ln -s $BASEDIR/libretro-info-api/libretro-stella/src/libretro/info $dst_dir/libretro-stella_info_api/src/libretro/info

