IDIR := .
ODIR := build
LIBS :=

CC := gcc
CFLAGS := -I$(IDIR)

_FILES := token shell

_DEPS := $(patsubst %,%.h,$(_FILES))
_OBJ := main.o $(patsubst %,%.o,$(_FILES))

DEPS := $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ := $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean run

# Some symbols ->>
# $@: left side of :
# $<: first dependency (what does that mean? the first arg of $(DEPS)?)
# $^: right side of :

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: clean shell

clean:
	if [ -r $(ODIR) ]; then rm -r $(ODIR); fi
	mkdir $(ODIR)

shell: $(OBJ)
	$(CC) -o $(ODIR)/$@ $^ $(CFLAGS) $(LIBS)

run: all
	$(ODIR)/shell

# TODO: shell is incomplete and wrong
