## This is manual installation for core Stella (Atari 2600)

#### open file: ./libretro-super/libretro-stella/src/libretro/libretro.cxx

add:
```
#include "./info/InfoLIBRETRO.cxx"
static InfoLIBRETRO infoLIBRETRO;
```
between: `#include "Version.hxx"` and: `static StellaLIBRETRO stella;`

------------------------------------------------

add:
```
infoLIBRETRO.setOSystem(stella.osystem());
```
inside function `static bool reset_system()` but before `return true;`

------------------------------------------------

add:
```
infoLIBRETRO.retroRun();
```
in the beggining of the function: `void retro_run()`



#### open file: ./libretro-super/libretro-stella/src/common/HighScoresManager.cxx

find
```
#include "Launcher.hxx"
```
and replace by:
```
#ifdef GUI_SUPPORT
#include "Launcher.hxx"
#endif
```

------------------------------------------------

find
```
const string& md5 = myOSystem.launcher().selectedRomMD5();
myOSystem.propSet().getMD5(md5, props);
```
and replace by:
```
#ifdef GUI_SUPPORT
  const string& md5 = myOSystem.launcher().selectedRomMD5();
  myOSystem.propSet().getMD5(md5, props);
#endif
```

------------------------------------------------

That's all.