all: build clean

build:
	+$(MAKE) -C Items
	+$(MAKE) -C Environment
	+$(MAKE) -C Inventory
	+$(MAKE) -C IO
	+$(MAKE) -C GameScene
	+$(MAKE) -C Vector2D
	+$(MAKE) -C Player
	+$(MAKE) -C CSVRow
	+$(MAKE) -C DynamicArray
	g++ -g DynamicArray/DynamicArray.o CSVRow/CSVRow.o IO/IoClass.o Environment/Environment.o GameScene/GameScene.o Inventory/Inventory.o Items/Item/Item.o Items/Coconut/Coconut.o Items/Leafs/Leafs.o Items/Lighter/Lighter.o Items/Rock/Rock.o Items/WoodStick/WoodStick.o Items/Axe/Axe.o Items/Hut/Hut.o Items/OpenCoconut/OpenCoconut.o Items/LightedTorch/LightedTorch.o Vector2D/Vector2D.o Player/Player.o main.cpp -lncurses -lmenu -o adventureGame


clean:	
	rm */*.o
	rm -f ./appData.dat
 
	
