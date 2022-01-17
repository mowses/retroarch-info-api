## ABOUT

This library makes RetroArch instances capable of listen for predefined commands
and returns the result as JSON to the caller process. Works like a realtime API.

The communication is done via UNIX sockets between processes in the same machine.

These are the implemented cores and functions:
- Stella (atari)
	- `current_score` returns the current score from player 1;


## INSTALLATION AND USAGE

Run `./compile.sh`

## SOURCE

https://docs.libretro.com/development/retroarch/compilation/linux-and-bsd/