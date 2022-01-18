## ABOUT

This library makes RetroArch instances capable of listen for predefined commands
and returns the result as JSON to the caller process. Works like a realtime API.

The communication is done via UNIX sockets between processes in the same machine.

These are the implemented cores and functions:
- [Stella (Atari 2600)](https://github.com/stella-emu/stella) [commit](https://github.com/stella-emu/stella/commit/4fce2156dfe6d6eeec5f80d0e643781c2d7f9317)
	- `current_score` returns the current score from player 1;


## INSTALLATION

This process will clone our repo which includes the [official libretro-super](https://github.com/libretro/libretro-super) submodule.
`install.sh` will append some contents to the libretro-super files so we can compile our project.

```
git clone --recurse-submodules -j8 https://github.com/mowses/retroarch-info-api.git
cd retroarch-info-api/
./install.sh
```

To be able to compile and run our project with the latest cores versions, please follow our manual installation for cores:
- [Atari 2600 (Stella)](./docs/stella.md)


## COMPILE

In the root folder where you have cloned this repo:
```
./compile.sh
```
This will compile the cores for you.

## USAGE

Now you can run the compiled version of the cores. Let's start RetroArch using a core:
```
cd /path/to/cloned/repo
retroarch -v -L ./modules/libretro-super/dist/unix/stella_info_api_libretro.so [/path/to/your/rom]
```
Once your game is running, open the terminal and type:
```
nc -v -U /home/unknown/Downloads/server.sock
```
After conected to the socket you may type: `current_score`[Enter]. You will receive a JSON response directly from RetroArch process.


## SOURCE

https://docs.libretro.com/development/retroarch/compilation/linux-and-bsd/