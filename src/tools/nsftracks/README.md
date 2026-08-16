# nfstracks

A small utility to expand an NSF or NSFE file into the path, followed by the
track numbers in the file, to they can be added to the playlist.

# License

`nfstracks` is released under version 3 of GNU General Public License.

# Building

Building should work fine on any ISO C system.  Simply `make`.

# Usage

`nsftracks` takes a number of files and outputs the files followed by the track
numbers, e.g.

```
$ nsftracks /path/megaman1.nsf
/path/megaman1.nsf:0
/path/megaman1.nsf:1
/path/megaman1.nsf:2
/path/megaman1.nsf:3
/path/megaman1.nsf:4
/path/megaman1.nsf:5
/path/megaman1.nsf:6
/path/megaman1.nsf:7
/path/megaman1.nsf:8
/path/megaman1.nsf:9
/path/megaman1.nsf:10
/path/megaman1.nsf:11
/path/megaman1.nsf:12
/path/megaman1.nsf:13
/path/megaman1.nsf:14
/path/megaman1.nsf:15
```
