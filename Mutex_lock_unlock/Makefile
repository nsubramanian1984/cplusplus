REBUILDABLES = lock_unlock

PROG_NAME= lock_unlock.cpp

$(REBUILDABLES): $(PROG_NAME)
  g++ -o $@ $^ -lpthread

clean:
  rm -f $(REBUILDABLES)
