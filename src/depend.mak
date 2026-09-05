main.o: main.cpp log.h config.h playlist.h playlistentry.h filetype.h \
 decoder.h thread.h queuecancel.h util.h mtvar.h decoded.h trackinfo.h \
 queue.h sourcefile.h mp3encoder.h mp3file.h streamer.h shoutapi.h url.h \
 constants.h
log.o: log.cpp log.h
config.o: config.cpp config.h util.h log.h
playlist.o: playlist.cpp playlist.h playlistentry.h filetype.h config.h \
 util.h
playlistentry.o: playlistentry.cpp playlistentry.h filetype.h util.h
decoded.o: decoded.cpp decoded.h playlistentry.h filetype.h trackinfo.h \
 constants.h
thread.o: thread.cpp thread.h queuecancel.h util.h mtvar.h
sourcefile.o: sourcefile.cpp sourcefile.h util.h
filetype.o: filetype.cpp filetype.h
decoder.o: decoder.cpp decoder.h thread.h queuecancel.h util.h mtvar.h \
 playlist.h playlistentry.h filetype.h decoded.h trackinfo.h queue.h \
 gmeapi.h sidapi.h sourcefile.h log.h config.h constants.h
gmeapi.o: gmeapi.cpp gmeapi.h decoded.h playlistentry.h filetype.h \
 trackinfo.h config.h constants.h
sidapi.o: sidapi.cpp sidapi.h sourcefile.h util.h decoded.h \
 playlistentry.h filetype.h trackinfo.h config.h log.h constants.h
mp3encoder.o: mp3encoder.cpp mp3encoder.h thread.h queuecancel.h util.h \
 mtvar.h decoded.h playlistentry.h filetype.h trackinfo.h mp3file.h \
 queue.h lameapi.h log.h config.h constants.h
streamer.o: streamer.cpp streamer.h thread.h queuecancel.h util.h mtvar.h \
 mp3file.h trackinfo.h shoutapi.h url.h queue.h config.h log.h
lameapi.o: lameapi.cpp lameapi.h decoded.h playlistentry.h filetype.h \
 trackinfo.h config.h log.h
mp3file.o: mp3file.cpp mp3file.h trackinfo.h
url.o: url.cpp url.h util.h
shoutapi.o: shoutapi.cpp shoutapi.h url.h
trackinfo.o: trackinfo.cpp trackinfo.h
constants.o: constants.cpp constants.h
util.o: util.cpp util.h
