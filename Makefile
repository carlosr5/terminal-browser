CPP = g++
CPPFLAGS = -g -Wall -fmax-errors=2 -std=c++11
OBJS = browser.o user.o page.o sha.o database.o

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