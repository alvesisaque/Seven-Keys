#Makefile
CC = g++

CFLAGS = -W -Wall -pedantic -std=c++11 -MMD -g3 
INCLUDES = -Iinclude `sdl2-config --cflags` -I/usr/local/include/ijengine
LDLIBS = -lcppunit -lijengine `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

SRC_TEST = tests
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIB_DIR = lib
BIN_DIR = bin

GAME = $(BIN_DIR)/$(NAME)

SRC = ${wildcard $(SRC_DIR)/*.cpp}
OBJ = ${addprefix $(OBJ_DIR)/, ${notdir ${SRC:.cpp=.o}}} 



.PHONY: clean depend

all:
	
	@mkdir -p $(OBJ_DIR) $(LIB_DIR) 
	$(MAKE) $(GAME)

$(OBJ_DIR)/%.o: $(SRC_TEST)/%.cpp
	@echo Building Tests $@ ...
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	@echo Cleaning Tests...
	@find . -name *.o -exec rm {} \;
	@find . -name *.d -exec rm {} \;

-include $(OBJ:.o=.d)
