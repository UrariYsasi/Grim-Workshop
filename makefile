CC = g++
SRC_PATH = Peon/Source
BIN_PATH = Peon/Binaries
BUILD_PATH := $(BIN_PATH)
RES_PATH = Peon/Resources
FRAMEWORK_PATH = /Library/Frameworks/SDL2
FRAMEWORKS = -framework SDL2 -framework SDL2_ttf -framework SDL2_mixer -framework SDL2_image
BIN_NAME = peon
BUILD_NAME = "Peon"
C_FLAGS = -Wall -std=c++14
VPATH = Peon/Source/Game Peon/Source Peon/Source/Engine Peon/Source/Game/Entity Peon/Source/Game/Entity/Action

DIRS = Peon/Source Peon/Source/Engine Peon/Source/Game Peon/Source/Game/Entity Peon/Source/Game/Entity/Action
SEARCH_CPP := $(addsuffix /*.cpp ,$(DIRS))
SRC_FILES := $(wildcard $(SEARCH_CPP))

vpath %.cpp $(DIRS)

#SRC_FILES := $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES := $(SRC_FILES:$(SRC_PATH)%.cpp=$(BIN_PATH)%.o)

# Build the project in either debug or release
all: debug

# Build the project and package it into an app bundle
release: clean build clean_app package_app
	@echo "*** Release build complete ***"

# Build the project and run it through the terminal
debug: clean build
	@echo "*** Debug build complete ***"
	@./$(BIN_PATH)/$(BIN_NAME)

# Link all the .o files in the bin/ directory to create the executable
build: $(OBJ_FILES)
	@echo "*** Linking ***"
	@$(CC) $(OBJ_FILES) -o $(BIN_PATH)/$(BIN_NAME) -F $(FRAMEWORK_PATH) $(FRAMEWORKS)

# Compile all the .cpp files in the src/ directory to the bin/ directory
$(BIN_PATH)/%.o: %.cpp
	@echo "*** Compiling" $< "***"
	@$(CC) -F $(FRAMEWORK_PATH) -c $< -o $@ $(C_FLAGS)

# Clean up all the raw binaries
clean:
	@echo "*** Cleaning Binaries ***"
	@mkdir -p $(BIN_PATH)/
	@rm -f $(BIN_PATH)/$(BIN_NAME) $(OBJ_FILES)

clean_app:
	@rm -f -r $(BUILD_PATH)/$(BUILD_NAME).app

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
