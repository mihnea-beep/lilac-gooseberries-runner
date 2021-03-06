#Compiler
CC= g++

#Simple DirectMedia Layer library
LFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

SRC_FILES=lilacrunner.cpp Scene.cpp Rect.cpp Player.cpp GUI.cpp Message.cpp Bullet.cpp GameScene.cpp SceneHandler.cpp PauseScene.cpp InventoryScene.cpp GameObject.cpp TextScene.cpp MenuScene.cpp OptionsScene.cpp

all:build

build:
	$(CC) $(SRC_FILES) -o lilac_runner $(LFLAGS)

clean:
	rm lilac_runner
