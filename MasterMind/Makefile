
LINK_TARGET = MasterMind

OBJS = colors.o util.o mastermind.o main.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

clean:
	rm -f $(REBUILDABLES)

all: $(LINK_TARGET)

$(LINK_TARGET) : $(OBJS)
	g++ -std=c++11 -o $@ $^

%.o : %.cpp
	g++ -std=c++11 -o $@ -c $<

main.o : mastermind.h colors.h util.h
mastermind.o: mastermind.h
colors.o : colors.h
util.o : util.h