# retroarch-info-api APPEND start

include_core_stella_info_api() {
	register_module core "stella_info_api" -ngc -wii
}
libretro_stella_info_api_name="Stella"
libretro_stella_info_api_git_url="https://github.com/stella-emu/stella.git"
libretro_stella_info_api_build_subdir="src/libretro"
libretro_stella_info_api_build_makefile="Makefile"

# retroarch-info-api APPEND end