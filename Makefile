CPP = g++
CPPFLAGS = -g -Wall -ferror-limit=2 -std=c++11 
OBJS = browser.o user.o page.o sha.o database.o
# -fmax-error for g++, -ferror-limit for clang

all: browser

browser: ${OBJS}
	${CPP} ${CPPFLAGS} -o $@ ${OBJS}

browser.o: browser.cpp user.h page.h sha.h database.h
	${CPP} ${CPPFLAGS} -o $@ -c browser.cpp

user.o: user.cpp user.h page.h sha.h database.h
	${CPP} ${CPPFLAGS} -o $@ -c user.cpp

page.o: page.cpp page.h
	${CPP} ${CPPFLAGS} -o $@ -c page.cpp

sha.o: sha.cpp sha.h
	${CPP} ${CPPFLAGS} -o $@ -c sha.cpp

database.o: database.cpp database.h sha.h
	${CPP} ${CPPFLAGS} -o $@ -c database.cpp

clean:
	rm -f *.o browser