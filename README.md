# vgmstream

Written as I couldn't get an transcoding stream for SID files to work, then
thought it would be nice to support other video game formats, of the older
variety.  Hence I decided to see if I could write a streamer that transcoded    
video game music files to MP3 to be consumed by icecast.                        

# Thanks        

`vgmstream` couldn't have been written without these libraries:

* LAME, an MP3 encoder: https://lame.sourceforge.io/index.php
* libsidplayfp, a library for decoding Commodore 64 SID files:
https://github.com/libsidplayfp/libsidplayfp
* libgme, a library for decoding a variety of old 8-bit music formats (yes,
the SNES is 8-bit): https://github.com/libgme/game-music-emu
* libshout, a library for streaming to an Icecast server:
https://gitlab.xiph.org/xiph/icecast-libshout
