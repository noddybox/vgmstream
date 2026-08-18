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
* libshout, a library for streaming to an Icecast 2 server:
https://gitlab.xiph.org/xiph/icecast-libshout

# License

`vgmstream` is released under version 3 of GNU General Public License.

# Building

Building should work fine on any POSIX system with access to the required
3rd party libraries, `pkgconf` set up to tell the build how to use them and
a C++ compiler.  To build simply `cd src` and then `make`.  If it works this
will generate a `vgmstream` executable, which can be moved anywhere you see fit.

An commented config file can be found in the `docs` directory.  Use this as
a template, and either save the result to `/etc/vgmstreamrc` if you want to
use the default location, or anywhere if you supply it via the `-c` switch.

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

Any flag setting support the following values:

* Enable setting: yes, on, true, 1
* Disable setting: no, off, false, 0

|**Setting**|**Optional**|**Description**|
|-|-|-|
|`icecast.url`|Depends|The URL of the endpoint on Icecast 2 to connect to.  Can be missing if `misc.outputdir` is set.|
|`icecast.password`|Depends|The password to connect as a **source**  in Icecast 2.  Can be missing if `misc.outputdir` is set.|
|`icecast.public`|Y|Flag to say whether to make the stream public.  The default is to not.|
|`playlist.file`|N|The location of the playlist file, with each line being a path to a file # to stream.|
|`playlist.shuffle`|Y|Whether to shuffle the entries in the file or not.  The default is to shuffle.|
|`playlist.repeat`|Y|Whether to repeat the playlist.  It will be reshuffled if `playlist.shuffle` is enabled when the end is reached.  Default is to repeat.|
|`decoder.default_length`|Y|The default number of seconds if the file has no length information.  Defaults to 120 seconds.|
|`decoder.loop`|Y|If the input defines a loop length, the number of times the looped section is played.  Defaults to 2.
|`mp3.bitrate`|Y|The bitrate to encode MP3 as.  Default is `vbr` (variable bit rate).  Either specifiy `vbr` or the kbps value, e.g. `320`.|
|`misc.outputdir`|Y|If set output generated MP3 files to this directory.  Files will be called the same as the source file, with it's extension replaced with .mp3|
|`sid.kernal`|Y|If set defines the path to the C64 kernal ROM.  This improves the SID support.|
|`sid.chargen`|Y|If set defines the path to the C64 chargen ROM.  This improves the SID support.|
|`sid.basic`|Y|If set defines the path to the C64 BASIC ROM.  This improves the SID support.|

# Playlist file

The playlist file is simply a list of filenames to play.  Each entry can have
an optional number, e.g.

`/path/to/file:2`

This means play track 2 in the file.  If the track number is missing it will
play the first track for formats that don't specify a default track, and the
default track if one is specified.
