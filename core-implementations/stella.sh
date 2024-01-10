#!/usr/bin/env bash

BASEDIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
CORE="$( cd -- "$BASEDIR/../modules/libretro-super/libretro-stella_info_api/src"; pwd -P)"
DATE=$(date)

#### open file: ./modules/libretro-super/libretro-stella_info_api/src/libretro/libretro.cxx
FILE="$CORE/os/libretro/libretro.cxx"
# add timestamp to the beginning of file
# this forces ./compile.sh to always compile the core
sed -i "1s;^;// $DATE\n;" $FILE

# add:
# ```
# #include "./info/InfoLIBRETRO.cxx"
# static InfoLIBRETRO infoLIBRETRO;
# ```
# between: `#include "Version.hxx"` and: `static StellaLIBRETRO stella;`

find='#include "Version.hxx"'
replace='\n#include "./info/InfoLIBRETRO.cxx"\nstatic InfoLIBRETRO infoLIBRETRO;'
sed -i "s|$find|$find\n$replace|" $FILE

# ------------------------------------------------

# add:
# ```
# infoLIBRETRO.setOSystem(stella.osystem());
# ```
# inside function `static bool reset_system()` but right before `return true;`

find='if(!stella.create(log_cb ? true : false)) return false;'
replace='infoLIBRETRO.setOSystem(stella.osystem());'
sed -i "s|$find|$find\n\n\t$replace|" $FILE

# ------------------------------------------------

# add:
# ```
# infoLIBRETRO.retroRun();
# ```
# inside the function: `void retro_run()` but as the latest statement.

find='stella.runFrame();'
replace='infoLIBRETRO.retroRun();'
sed -i "s|$find|$find\n\n\t$replace|" $FILE

# ------------------------------------------------
echo "$FILE changed."
# ------------------------------------------------
# #########################
# #########################
# #########################

#### open file: ./modules/libretro-super/libretro-stella_info_api/src/common/HighScoresManager.cxx
FILE="$CORE/common/HighScoresManager.cxx"
# find
# ```
# #include "Launcher.hxx"
# ```
# and replace by:
# ```
# #ifdef GUI_SUPPORT
# #include "Launcher.hxx"
# #endif
# ```

find='#include "Launcher.hxx"'
replace="#ifdef GUI_SUPPORT\n\t$find\n#endif"
sed -i "s|$find|$replace|" $FILE

# ------------------------------------------------

# find
# ```
#     const string& md5 = myOSystem.launcher().selectedRomMD5();
#     myOSystem.propSet().getMD5(md5, props);
# ```
# and replace by:
# ```
#     #ifdef GUI_SUPPORT
#       const string& md5 = myOSystem.launcher().selectedRomMD5();
#       myOSystem.propSet().getMD5(md5, props);
#     #endif
# ```

find='const string\& md5 = myOSystem.launcher().selectedRomMD5();'
sed -i "s|$find||" $FILE
find2='myOSystem.propSet().getMD5(md5, props);'
replace="#ifdef GUI_SUPPORT\n\t\t\t$find\n\t\t\t$find2\n\t\t#endif"
sed -i "s|$find2|$replace|" $FILE

# ------------------------------------------------
echo "$FILE changed."
# ------------------------------------------------
# #########################
# #########################
# #########################