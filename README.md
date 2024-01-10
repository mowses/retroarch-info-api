## ABOUT

This library makes RetroArch instances capable of listen for predefined commands
and returns the result as JSON to the caller process. Works like a realtime API.

The communication is done via UNIX sockets between processes in the same machine.

[Click here to view the implemented cores and functions](./docs/implementations.md)


## INSTALLATION

This process will clone our repo which includes the [official libretro-super](https://github.com/libretro/libretro-super) submodule.
`install.sh` will append some contents to the libretro-super files so we can compile our project.

```bash
git clone --recurse-submodules -j8 https://github.com/mowses/retroarch-info-api.git
cd retroarch-info-api/
./install.sh
```

To know how to manual implement our lib to your favorite core please read the following docs: **(You dont need to follow these steps if you have ran `./install.sh`)**
- [Atari 2600 (Stella)](./docs/stella.md)


## COMPILE

In the root folder where you have cloned this repo:
```bash
./compile.sh
```
This will compile the cores for you. After you have run this command, you may find the compiled core at `./compiled/*_libretro.so`.

## USAGE

Now you can run the compiled version of the cores. Let's start RetroArch using a core:
```bash
cd /path/to/cloned/repo
INFO_API_UNIX_FILE=~/retroarch-info-api.sock retroarch -v -L ./compiled/stella_info_api_libretro.so /path/to/your/rom
```
Watch for RetroArch `[WARN] --libretro argument "./compiled/stella_info_api_libretro.so" is neither a file nor directory. Ignoring.` This means that you need to make sure the file exists, and can be read by the user running RetroArch. You may need to copy the core to the same folder where other cores are. For example, I installed my RetroArch using snap:
```bash
cp ./compiled/stella_info_api_libretro.so ~/snap/retroarch/1005/.config/retroarch/cores/
```
The destination folder may vary depending on the version installed.

Once RetroArch game is running, pay attention to the message: `[INFO-API] INFO API is available to be connected at: ~/retroarch-info-api.sock`. Make sure to set env `INFO_API_UNIX_FILE` to a valid file name and to a writable folder. I had trouble setting it to `/tmp/retroarch-info-api.sock`.

To request infos, open the terminal and type:
```bash
nc -v -U ~/retroarch-info-api.sock
```
After conected to the socket you may type: `current_score`[Enter]. You will receive a JSON response directly from RetroArch process.

Here is how you may request infos using:
- [Javascript](./docs/usage-javascript.md)


## IMPLEMENTATIONS

[Click here to view the implemented cores and functions](./docs/implementations.md)

## SOURCE

https://docs.libretro.com/development/retroarch/compilation/linux-and-bsd/