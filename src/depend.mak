main.o: main.cpp log.h config.h playlist.h decoder.h thread.h decoded.h \
 queue.h util.h sourcefile.h
log.o: log.cpp log.h
config.o: config.cpp config.h log.h
playlist.o: playlist.cpp playlist.h config.h log.h
decoded.o: decoded.cpp decoded.h
thread.o: thread.cpp thread.h util.h
sourcefile.o: sourcefile.cpp sourcefile.h
filetype.o: filetype.cpp filetype.h
decoder.o: decoder.cpp decoder.h thread.h playlist.h decoded.h queue.h \
 util.h gmeapi.h sourcefile.h sidapi.h filetype.h log.h config.h
gmeapi.o: gmeapi.cpp gmeapi.h sourcefile.h decoded.h log.h
sidapi.o: sidapi.cpp sidapi.h sourcefile.h decoded.h log.h
util.o: util.cpp util.h
