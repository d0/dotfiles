CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -lboost_system -lssl -lcrypto -lpthread
	
SRC = ../src
PROGS = server client
OBJ = ssl_conn.o

all: $(PROGS)
	
# $@ bedeutet Name des Targets
%: $(OBJ) %.o
	$(CPP) $(CPPFLAGS) $(OBJ) $@.o -o $@ $(LDFLAGS)

%.o: $(SRC)/%.cc
	$(CPP) $(CPPFLAGS) -g -c $<

clean:
	rm -rf *.o
