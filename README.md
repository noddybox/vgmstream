# vgmstream

Written as I couldn't get an transcoding stream for SID files to work, then
thought it would be nice to support other video game formats, of the older
variety.  Hence I decided to see if I could write a streamer that transcoded
video game music files to MP3 to be consumed by Icecast 2.

# Thanks        

`vgmstream` couldn't have been written without these libraries:

* LAME, an MP3 encoder: https://lame.sourceforge.io/index.php
* libsidplayfp, a library for decoding Commodore 64 SID files:
https://github.com/libsidplayfp/libsidplayfp
* libgme, a library for decoding a variety of old 8-bit music formats (yes,
the SNES is 8-bit): https://github.com/libgme/game-music-emu
* libshout, a library for streaming to an Icecast server:
https://gitlab.xiph.org/xiph/icecast-libshout

# License

`vgmstream` is released under version 3 of GNU General Public License.

# Usage

`vgmstream` can be controlled with these command line switches.  Most
configuration is done via the configuration file detailed below.

|**Switch**|**Description**|
|-|-|
|`-c file`|Configuration file to read.  Defaults to `/etc/vgmstreamrc`.|
|`-d`|Make the process a daemon.  Defaults to a normal foreground process.|

If `vgmstream` is run in the foreground it logs to stdout.  If the `-d` switch
is given logs are sent to `syslog()`.

# Configuration file

`vgmstream` reads its configuration from a text file.  Settings are simply
pair of white space separated words.  Any white space in the setting can be
left as is - only the first white space separator is used to differentiate
the setting with its value.  Blank lines and lines starting with a `#`
character are ignored.

|**Setting**|**Optional**|**Description**|
|-|-|-|
|`icecast.url`|N|The URL of the endpoint on Icecast to connect to.|
|`icecast.password`|N|The password to connect as a **source**  in Icecast.|
