CC = g++

# External Libraries
GL3W_INCLUDE_PATH = ../GL3W/include
GL3W_LIBRARY_PATH = ../GL3W/lib
SOIL_INCLUDE_PATH = ../SOIL/src
SOIL_LIBRARY_PATH = ../SOIL/lib
GLM_INCLUDE_PATH = ../GLM/glm

# Game
SRC_PATH = Peon/Source
BIN_PATH = Peon/Binaries
BUILD_PATH := $(BIN_PATH)
RES_PATH = Peon/Resources
OSX_FRAMEWORK_PATH = -F/Library/Frameworks/SDL2
INCLUDE_PATH = -I$(SRC_PATH) -I$(GL3W_INCLUDE_PATH) -I$(SOIL_INCLUDE_PATH) -I$(GLM_INCLUDE_PATH)
LIBRARY_PATH = -L$(GL3W_LIBRARY_PATH) -L$(SOIL_LIBARY_PATH)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LIBRARIES = $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_mixer SDL2_image) -ldl -lpthread -lGL -lX11 -lgl3w -lSOIL
	override CFLAGS += $($shell pkg-config --cflags sdl2 SDL2_ttf SDL2_mixer SDL2_image)
else
	LIBRARIES = -framework SDL2 -framework SDL2_ttf -framework SDL2_mixer -framework SDL2_image -framework OpenGL
endif


BIN_NAME = peon
BUILD_NAME = "Peon"
C_FLAGS = -Wall -std=c++14 -IPeon/Source -O0
VPATH = Peon/Source/Game Peon/Source Peon/Source/Engine Peon/Source/Game/Entity Peon/Source/Game/Entity/Action Peon/Source/Game/Item Peon/Source/Game/World Peon/Source/Game/Terrain

DIRS = Peon/Source Peon/Source/Engine Peon/Source/Game Peon/Source/Game/Entity Peon/Source/Game/Entity/Action Peon/Source/Game/Item Peon/Source/Game/World Peon/Source/Game/Terrain
SEARCH_CPP := $(addsuffix /*.cpp ,$(DIRS))
SRC_FILES := $(wildcard $(SEARCH_CPP))
OBJ_FILES := $(SRC_FILES:$(SRC_PATH)%.cpp=$(BIN_PATH)%.o)

vpath %.cpp $(DIRS)

# Build the project in either debug or release
all: debug

# Build the project and package it into an app bundle
release: build clean_app package_app
	@echo "*** Release build complete ***"

# Build the project and run it through the terminal
debug: build
	@echo "*** Debug build complete ***"
	#@./$(BIN_PATH)/$(BIN_NAME)

# Link all the .o files in the bin/ directory to create the executable
build: $(OBJ_FILES)
	@echo "*** Linking ***"
	@$(CC) $(OBJ_FILES) -o $(BIN_PATH)/$(BIN_NAME) $(INCLUDE_PATH) $(OSX_FRAMEWORK_PATH) $(LIBRARY_PATH) $(LIBRARIES)

# Compile all the .cpp files in the src/ directory to the bin/ directory
$(BIN_PATH)/%.o: %.cpp
	@echo "*** Compiling" $< "***"
	@mkdir -p $(dir $@)
	@$(CC) $(INCLUDE_PATH) $(OSX_FRAMEWORK_PATH) -c $< -o $@ $(C_FLAGS)

# Clean up all the raw binaries
clean:
	@echo "*** Cleaning Binaries ***"
	@rm -f $(BIN_PATH)/$(BIN_NAME) $(OBJ_FILES)

# Clean up the OSX app bundle
clean_app:
	@rm -f -r $(BUILD_PATH)/$(BUILD_NAME).app

# Package up the OSX app bundle
package_app:
	@echo "*** Packaging ***"
	@mkdir -p $(BUILD_PATH)/$(BUILD_NAME).app/Contents/MacOS
	@mkdir -p $(BUILD_PATH)/$(BUILD_NAME).app/Contents/Resources
	@cp info.plist $(BUILD_PATH)/$(BUILD_NAME).app/Contents
	@cp -R $(RES_PATH) $(BUILD_PATH)/$(BUILD_NAME).app/Contents/Resources
	@cp -R $(FRAMEWORK_PATH)/ $(BUILD_PATH)/$(BUILD_NAME).app/Contents/Frameworks
	@cp $(BIN_PATH)/$(BIN_NAME) $(BUILD_PATH)/$(BUILD_NAME).app/Contents/MacOS
	@install_name_tool -add_rpath @loader_path/../Frameworks $(BUILD_PATH)/$(BUILD_NAME).app/Contents/MacOS/$(BIN_NAME)

help:
	@echo $(SRC_FILES)
	@echo $(OBJ_FILES)
