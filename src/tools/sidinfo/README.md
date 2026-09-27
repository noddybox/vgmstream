# nfstracks

A small utility to get info from a SID file.

# License

`sidinfo` is released under version 3 of GNU General Public License.

# Building

Building should work fine on any POSIX system with the libsidplayfp library
available and a C++ compiler.  Simply `make`.

# Usage

`sidinfo` takes a path to the HVSC song database MD5 file, then a number of
files and outputs the info extracted from the files e.g.

```
$ sidinfo /path/to/HVSC-song-database.md5 /path/file.sid
```

Alternatively, like `nfstracks` it can output in a form suitable for the
playlist, trimming subtunes which are below a `max_msec` milliseconds in length:

```
$ sidinfo [-p max_msec] /path/to/HVSC-song-database.md5 /path/file.sid
```
