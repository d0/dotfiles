CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -lboost_system -lboost_thread -lssl -lcrypto -lpthread

OBJ = ssl_conn.o client.o server.o sim.o

all: $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o sim $(LDFLAGS)

%.o: %.cc
	$(CPP) $(CPPFLAGS) -g -c $<

clean:
	rm -rf *.o
