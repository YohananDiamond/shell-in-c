CC := gcc
LIBS :=

NAME := shell
FILES := main shell token
TARGET := ../target

_SOURCE_FILES := $(patsubst %,%.c,$(FILES))
_OUTPUT_FILES := $(patsubst %,%.o,$(FILES))
_LIB_FLAGS := $(patsubst %,-l%,$(LIBS))
CFLAGS := $(_LIB_FLAGS)

all: compile assemble

compile:
	[ -d $(TARGET) ] || mkdir -p $(TARGET)
	$(CC) -c $(_SOURCE_FILES)
	mv *.o -t $(TARGET)

assemble:
	$(CC) $(CFLAGS) -o $(TARGET)/$(NAME) $(patsubst %,$(TARGET)/%,$(_OUTPUT_FILES))

run: all
	./$(TARGET)/$(NAME)

clean:
	rm $(TARGET)/*.o $(TARGET)/$(NAME)
