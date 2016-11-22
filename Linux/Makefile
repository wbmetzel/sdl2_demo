#OBJS specifies which files to compile as part of the project
OBJS = driver.cpp

#CC specifies which compiler to use
CC = g++

#COMPILER_FLAGS specifies the additional compilation options
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries being linked
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of the executable
OBJ_NAME = demo

#This is the target that compiles the executable
all : $(OBJS) 
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
