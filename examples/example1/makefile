CC       := gcc
CFLAGS   = -O2 -I$(INCDIR) -L$(LIBDIR) -l$(patsubst lib%.so, %, $(LIBNAME)) -Wl,-rpath=$(LIBDIR)
LDFLAGS  := -lm -pthread

INCDIR   := ../../include
SRCDIR   := .
SRC      := $(wildcard $(SRCDIR)/*.c)
OBJDIR   := obj
OBJ      := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

TARGET   := generateCSV
CSVOUTPUT:= example1.csv

LIBNAME  := libsamt.so
LIBSRCDIR:= ../../src
LIBDIR   := ../../lib
LIBTARGET:= $(LIBDIR)/$(LIBNAME)
LIBOBJ   := $(patsubst $(LIBSRCDIR)/%.c, $(LIBDIR)/%.o, $(wildcard $(LIBSRCDIR)/*.c))

$(TARGET): $(OBJ) $(LIBTARGET)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET) $(CFLAGS)
	rm $(TARGET) $(LIBDIR)/*.o
#may not need ldflags when compiled with library

$(OBJDIR)/%.o: $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.c, $(OBJDIR)/%.o)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(LIBTARGET): $(LIBOBJ)
	$(CC) -shared -o $@ $^ -lm -pthread

$(LIBDIR)/%.o: $(patsubst $(LIBDIR)/%.o, $(LIBSRCDIR)/%.c, $(LIBDIR)/%.o)
	$(CC) -I$(INCDIR) -c -fPIC $< -o $@

.PHONY: run clean fullclean
run: $(TARGET)
	./$(TARGET) $(CSVOUTPUT)

clean:
	rm $(OBJDIR)/*.o $(TARGET)

rmcsv:
	rm $(CSVOUTPUT)

fullclean:
	rm $(OBJDIR)/*.o $(TARGET) $(CSVOUTPUT) $(LIBDIR)/*