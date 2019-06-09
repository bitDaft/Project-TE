CC		:= g++
C_FLAGS := -std=c++17 -Wall -Wextra

.PHONY = all clean run

COMPILE_ENV		:= debug
BIN				:= bin/$(COMPILE_ENV)
SRC				:= src
INCLUDE			:= include
OBJ				:= obj
LIB				:= lib/$(COMPILE_ENV)


ifeq ($(COMPILE_ENV),debug)
LIBRARIES	:= -lsfml-audio-d -lsfml-graphics-d -lsfml-window-d -lsfml-main-d -lsfml-system-d
MODE_FLAG 	:= 
else
LIBRARIES	:= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-main -lsfml-system
MODE_FLAG 	:= -mwindows
endif

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
else
EXECUTABLE	:= main
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/* $(INCLUDE)/*.hpp
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES) $(MODE_FLAG)