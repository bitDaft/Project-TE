CC			:= g++
C_FLAGS			:= -std=c++17 -Wall -Wextra

.PHONY			 = all clean run lib env_debug env_release debug release cleanwin cleanlinux
LIBEXEC			:= libte.a


# debug or release
COMPILE_ENV	:= debug
# BIN		:= bin/$(COMPILE_ENV)
# INCLUDE		:= include
# LIB		:= lib/$(COMPILE_ENV)
# SRC		:= src
# SRCS		:= $(wildcard $(SRC)/*.cpp)
# OBJ		:= obj/$(COMPILE_ENV)
# OBJS		:= $(addprefix $(OBJ)/, $(notdir $(SRCS:.cpp=.o)))

ifeq ($(COMPILE_ENV),debug)
LIBRARIES		:= -lsfml-audio-d -lsfml-graphics-d -lsfml-window-d -lsfml-main-d -lsfml-system-d -lteldr
MODE_FLAG		:= -D_DEBUG_=1
C_FLAGS			+= -og -g
else
LIBRARIES		:= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-main -lsfml-system -lteldr
MODE_FLAG		:= -mwindows -D_DEBUG_=0 -DNDEBUG
C_FLAGS			+= -o3
endif


ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
RM		 	= del /Q /S
MODE_FLAG 	+= -Ddebug(x)='do{if(_DEBUG_)std::cerr<<"\n"<<__FILE__<<":"<<__LINE__<<":"<<__func__<<": "<<x<<"\n";}while(false)'
MKDIR_P 		:= -mkdir 
BIN		:= bin\$(COMPILE_ENV)
INCLUDE		:= include
LIB		:= lib\$(COMPILE_ENV)
SRC		:= src
SRCS		:= $(wildcard $(SRC)/*.cpp)
OBJ		:= obj\$(COMPILE_ENV)
OBJS		:= $(addprefix $(OBJ)/, $(notdir $(SRCS:.cpp=.o)))
all: dirwin $(BIN)/$(EXECUTABLE)
clean : cleanwin
run: runwin
else
MKDIR_P 		:= mkdir -p
MODE_FLAG 	+= -Ddebug\(x\)='do{if(_DEBUG_)std::cerr<<"\n"<<__FILE__<<":"<<__LINE__<<":"<<__func__<<": "<<x<<"\n";}while(false)'
LIBRARIES	:= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lteldr
EXECUTABLE	:= main
BIN		:= bin/$(COMPILE_ENV)
INCLUDE		:= include
LIB		:= lib/$(COMPILE_ENV)
SRC		:= src
SRCS		:= $(wildcard $(SRC)/*.cpp)
OBJ		:= obj/$(COMPILE_ENV)
OBJS		:= $(addprefix $(OBJ)/, $(notdir $(SRCS:.cpp=.o)))
all: dirlinux $(BIN)/$(EXECUTABLE)
clean : cleanlinux
run: runlinux
endif

dirlinux:
	${MKDIR_P} ./bin/debug 2>/dev/null
	${MKDIR_P} ./bin/release 2>/dev/null
	${MKDIR_P} ./obj/debug 2>/dev/null
	${MKDIR_P} ./obj/release 2>/dev/null

dirwin:
	if not exist bin\debug\ ${MKDIR_P} bin\debug\ 
	if not exist bin\release\ ${MKDIR_P} bin\release\ 
	if not exist obj\debug\ ${MKDIR_P} obj\debug\ 
	if not exist obj\release\ ${MKDIR_P} obj\release\ 

cleanlinux:
	$(RM) ./$(BIN)/$(EXECUTABLE)
	$(RM) ./$(BIN)/$(LIBEXEC)
	$(RM) ./$(OBJ)/*.o
	$(RM) ./$(INCLUDE)/*.gch

cleanwin:
	$(RM) $(BIN)\$(EXECUTABLE)
	$(RM) $(BIN)\$(LIBEXEC)
	$(RM) $(OBJ)\*.o
	$(RM) $(INCLUDE)\*.gch

runwin: all
	cd $(BIN)  &&  $(EXECUTABLE)

runlinux: all
	cd $(BIN)  &&  ./$(EXECUTABLE)

lib: $(OBJS)
	ar crf $(BIN)/$(LIBEXEC) $^

$(BIN)/$(EXECUTABLE):	$(OBJS)
	$(CC) $^ -o $@ -L$(LIB) $(LIBRARIES)

$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/*
	$(CC) -c $(C_FLAGS) -I$(INCLUDE) $< -o $@ $(MODE_FLAG) 
