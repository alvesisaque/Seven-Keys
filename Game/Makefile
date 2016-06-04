NAME = 7keys
TEST_NAME = 7keystest

TEST_DIR = test
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIB_DIR = lib
BIN_DIR = bin

CC = g++

CFLAGS = -W -Wall -pedantic -std=c++11 -MMD -g3 
INCLUDES = -Iinclude `sdl2-config --cflags` -I/usr/local/include/ijengine
LIBS = -lijengine `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lcppunit

GAME = $(BIN_DIR)/$(NAME)

TEST = $(BIN_DIR)/$(TEST_NAME)

SRC = ${wildcard $(SRC_DIR)/*.cpp}
OBJ = ${addprefix $(OBJ_DIR)/, ${notdir ${SRC:.cpp=.o}}} 

SRC_TEST = ${wildcard $(TEST_DIR)/*.cpp}
OBJ_TEST = ${addprefix $(OBJ_DIR)/, ${notdir ${SRC_TEST:.cpp=.o}}} 

.PHONY: clean depend

all:
	@mkdir -p $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)
	$(MAKE) $(TEST)
	$(MAKE) $(GAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Building $@ ...
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@echo Building $@ ...
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(TEST): $(OBJ_TEST)
	@echo Builting tests...
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_TEST) -o $@ $(LIBS)
	@echo --- Done

$(GAME): $(OBJ)
	@echo Builting executable...
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $@ $(LIBS)
	@echo --- Done

clean:
	@echo Cleaning...
	@find . -name *.o -exec rm {} \;
	@find . -name *.d -exec rm {} \;
	@rm -rf *~ *.o bin out.txt obj lib/babel.a

dist-clean: clean
	@echo Cleaning engine...
	@find . -name *.a -exec rm {} \;

-include $(OBJ:.o=.d)
-include $(OBJ_TEST:.o=.d)
