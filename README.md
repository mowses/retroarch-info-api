## ABOUT

This library makes RetroArch instances capable of listen for predefined commands
and returns the result as JSON to the caller process. Works like a realtime API.

The communication is done via UNIX sockets between processes in the same machine.

These are the implemented cores and functions:
- Stella (Atari 2600)
	- `current_score` returns the current score from player 1;


## INSTALLATION

This process will clone our repo which includes the [official libretro-super](https://github.com/libretro/libretro-super) submodule.
`install.sh` will append some contents to the libretro-super files so we can build and compile our project.

```
git clone --recurse-submodules -j8 https://github.com/mowses/retroarch-info-api.git
cd retroarch-info-api/
./install.sh
```

## USAGE

```
./compile.sh
```

## SOURCE

https://docs.libretro.com/development/retroarch/compilation/linux-and-bsd/