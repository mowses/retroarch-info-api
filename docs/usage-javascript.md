## JAVASCRIPT USAGE

Usage examples for javascript:

```js
import { default as LibretroInfoApiClient } from './libretro-info-api/libretro-stella/src/libretro/info/client/client.js';

const libretro_info_api = new LibretroInfoApiClient({
    unixfile: process.env.INFO_API_UNIX_FILE,
});

console.log('The path to the unix file is:', libretro_info_api.getUnixFile());

libretro_info_api
    .request('current_score', function (response) {
        console.log('current_score response:', response);
    })
    .request('retro_api_version', function (response) {
        console.log('retro_api_version response:', response);
    })
    .request('any command that does not exist', function (response) {
        console.log('any command that does not exist response:', response);
    })
    .close();
```

You may copy the file `./libretro-info-api/libretro-stella/src/libretro/info/client/client.js` to your project folder.