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

To know how to manual implement our lib to your favorite core please read the following docs: **(You dont need to follow these steps if you have ran `./install.sh`)**
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
UNIXFILE=~/retroarch-info-api.sock retroarch -v -L ./modules/libretro-super/dist/unix/stella_info_api_libretro.so [/path/to/your/rom]
```
Watch for RetroArch `[WARN] --libretro argument "./modules/libretro-super/dist/unix/stella_info_api_libretro.so" is neither a file nor directory. Ignoring.` This means that you need to make sure the file exists, and can be read by the user running RetroArch. You may need to copy the core to the same folder where other cores are. For example, I installed my RetroArch using snap:
```
cp ./modules/libretro-super/dist/unix/stella_info_api_libretro.so ~/snap/retroarch/1005/.config/retroarch/cores/
```
The destination folder may vary depending on the version installed.

Once RetroArch game is running, pay attention to the message: `INFO API is available to be connected at: ~/retroarch-info-api.sock`. Make sure to set env `UNIXFILE` to a valid file name and to a writable folder. I had trouble setting it to `/tmp/retroarch-info-api.sock`.

To request infos, open the terminal and type:
```
nc -v -U ~/retroarch-info-api.sock
```
After conected to the socket you may type: `current_score`[Enter]. You will receive a JSON response directly from RetroArch process.


## SOURCE

https://docs.libretro.com/development/retroarch/compilation/linux-and-bsd/