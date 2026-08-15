main.o: main.cpp log.h config.h playlist.h decoder.h thread.h decoded.h \
 queue.h util.h sourcefile.h mp3encoder.h
log.o: log.cpp log.h
config.o: config.cpp config.h util.h log.h
playlist.o: playlist.cpp playlist.h config.h util.h log.h
decoded.o: decoded.cpp decoded.h
thread.o: thread.cpp thread.h util.h
sourcefile.o: sourcefile.cpp sourcefile.h
filetype.o: filetype.cpp filetype.h
decoder.o: decoder.cpp decoder.h thread.h playlist.h decoded.h queue.h \
 util.h gmeapi.h sidapi.h sourcefile.h filetype.h log.h config.h
gmeapi.o: gmeapi.cpp gmeapi.h decoded.h config.h log.h
sidapi.o: sidapi.cpp sidapi.h sourcefile.h decoded.h config.h log.h
mp3encoder.o: mp3encoder.cpp mp3encoder.h thread.h decoded.h queue.h \
 util.h config.h
util.o: util.cpp util.h
