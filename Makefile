CC			:= g++
C_FLAGS			:= -std=c++17 -Wall -Wextra

.PHONY			 = all clean run lib env_debug env_release debug release
LIBEXEC			:= libte.a

MKDIR_P 		:= mkdir -p

# debug or release
COMPILE_ENV	:= debug
BIN		:= bin/$(COMPILE_ENV)
INCLUDE		:= include
LIB		:= lib/$(COMPILE_ENV)
SRC		:= src
SRCS		:= $(wildcard $(SRC)/*.cpp)
OBJ		:= obj/$(COMPILE_ENV)
OBJS		:= $(addprefix $(OBJ)/, $(notdir $(SRCS:.cpp=.o)))

ifeq ($(COMPILE_ENV),debug)
LIBRARIES		:= -lsfml-audio-d -lsfml-graphics-d -lsfml-window-d -lsfml-main-d -lsfml-system-d
MODE_FLAG		:= -D_DEBUG_=1
C_FLAGS			+= -og -g
else
LIBRARIES		:= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-main -lsfml-system
MODE_FLAG		:= -mwindows -D_DEBUG_=0
C_FLAGS			+= -o3
endif

MODE_FLAG 	+= -Ddebug\(x\)='do{if(_DEBUG_)std::cerr<<"\n"<<__FILE__<<":"<<__LINE__<<":"<<__func__<<": "<<x<<"\n";}while(false)'

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
RM		 	= del /Q /S
else
LIBRARIES	:= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE	:= main
endif

all: directories $(BIN)/$(EXECUTABLE)

directories:
	${MKDIR_P} ./bin/debug
	${MKDIR_P} ./bin/release
	${MKDIR_P} ./obj/debug
	${MKDIR_P} ./obj/release

clean:
	$(RM) ./$(BIN)/$(EXECUTABLE)
	$(RM) ./$(BIN)/$(LIBEXEC)
	$(RM) ./$(OBJ)/*.o
	$(RM) ./$(INCLUDE)/*.gch

run: all
	./$(BIN)/$(EXECUTABLE)

lib: $(OBJS)
	ar crf $(BIN)/$(LIBEXEC) $^

$(BIN)/$(EXECUTABLE):	$(OBJS)
	$(CC) $^ -o $@ -L$(LIB) $(LIBRARIES)

$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/*
	$(CC) -c $(C_FLAGS) -I$(INCLUDE) $< -o $@ $(MODE_FLAG) 
