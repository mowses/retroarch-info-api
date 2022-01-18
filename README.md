## ABOUT

This library makes RetroArch instances capable of listen for predefined commands
and returns the result as JSON to the caller process. Works like a realtime API.

The communication is done via UNIX sockets between processes in the same machine.

These are the implemented cores and functions:
- [Stella (Atari 2600)](https://github.com/stella-emu/stella) [commit](https://github.com/stella-emu/stella/commit/4fce2156dfe6d6eeec5f80d0e643781c2d7f9317)
	- `current_score` returns the current score from player 1;


## INSTALLATION

This process will clone our repo which includes the [official libretro-super](https://github.com/libretro/libretro-super) submodule.
`install.sh` will append some contents to the libretro-super files so we can build and compile our project.

```
git clone --recurse-submodules -j8 https://github.com/mowses/retroarch-info-api.git
cd retroarch-info-api/
./install.sh
```

To be able to compile and run our project in the latest cores versions, please follow:

Follow the manual installation for your desired core:
- [Atari 2600 (Stella)](./installation/stella.md)


## COMPILE

```
./compile.sh
```

## USAGE

Run your compiled version of Retroarch normally. Then open your terminal and type:
```
nc -v -U /home/unknown/Downloads/server.sock
```
and type: `current_score`[Enter]. You will receive a JSON response directly from your RetroArch process.


## SOURCE

https://docs.libretro.com/development/retroarch/compilation/linux-and-bsd/