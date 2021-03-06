## This is the manual implementation for core Stella (Atari 2600)

This is the same thing that `./core-implementations/stella.sh` do.

**if you ran `install.sh` then you dont need to follow these steps**

------------------------------------------------
#### open file: ./modules/libretro-super/libretro-stella_info_api/src/libretro/libretro.cxx

add:
```c++
#include "./info/InfoLIBRETRO.cxx"
static InfoLIBRETRO infoLIBRETRO;
```
between: `#include "Version.hxx"` and: `static StellaLIBRETRO stella;`

------------------------------------------------

add:
```c++
infoLIBRETRO.setOSystem(stella.osystem());
```
inside function `static bool reset_system()` but right before `return true;`

------------------------------------------------

add:
```c++
infoLIBRETRO.retroRun();
```
inside the function: `void retro_run()` but as the latest statement.



#### open file: ./modules/libretro-super/libretro-stella_info_api/src/common/HighScoresManager.cxx

find
```c++
#include "Launcher.hxx"
```
and replace by:
```c++
#ifdef GUI_SUPPORT
#include "Launcher.hxx"
#endif
```

------------------------------------------------

find
```c++
    const string& md5 = myOSystem.launcher().selectedRomMD5();
    myOSystem.propSet().getMD5(md5, props);
```
and replace by:
```c++
    #ifdef GUI_SUPPORT
      const string& md5 = myOSystem.launcher().selectedRomMD5();
      myOSystem.propSet().getMD5(md5, props);
    #endif
```

------------------------------------------------

That's all. Now head to the [Compile section](../README.md).