CXX      := g++
CXXFLAGS := -Wall -std=c++17
LDFLAGS  := -Lsrc/vendor/SFML/lib/mac -Lsrc/vendor/SFML/lib/linux -Lsrc/vendor/SFML/lib/win -lsfml-window -lsfml-graphics -lsfml-system
BUILD    := ./build
OBJ_DIR  := $(BUILD)/obj
APP_DIR  := $(BUILD)/bin
TARGET   := program
INCLUDE  := -Isrc/vendor/SFML/include -Isrc/vendor/entt/include -Isrc
SRC      := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJECTS:.o=.d)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)

.PHONY: all build run clean debug release info

run: $(APP_DIR)/$(TARGET)
	$(APP_DIR)/$(TARGET)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O3
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

info:
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"