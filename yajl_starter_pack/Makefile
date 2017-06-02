PROGRAMS = reader writer

all: $(PROGRAMS)

writer: writer.c
	gcc -o $@ $< -I. -I./include -I./include/yajl -L. -L./lib -lyajl

reader: reader.c
	gcc -o $@ $< -I. -I./include -I./include/yajl -L. -L./lib -lyajl

.PHONY: clean
clean:
	rm -rf *.o reader writer



