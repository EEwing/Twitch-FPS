#include "KeyboardHandler.h"

#include <stdio.h>

#include "GL/freeglut.h"

KeyboardHandler::KeyboardHandler(Player *p) {
	player = p;
	player->keyHandler = this;
	for(int i=0; i<256; i++) {
            keys[i] = false;
	}
}

void KeyboardHandler::CalcModifiers() {
	int modifiers = glutGetModifiers();
	player->isShifted = (modifiers == GLUT_ACTIVE_SHIFT);	
}

void KeyboardHandler::onSpecialKeyDown(int key, int x, int y){
	CalcModifiers();
	switch(key) {
		case GLUT_KEY_LEFT:
			//player->Teleport(player->GetLocation() + Vector(-1, 0, 0));
			arrows[0] = true;
			break;
		case GLUT_KEY_RIGHT:
			//player->Teleport(player->GetLocation() + Vector(1, 0, 0));
			arrows[1] = true;
			break;
		case GLUT_KEY_UP:
			//player->Teleport(player->GetLocation() + Vector(0, 0, 1));
			arrows[2] = true;
			break;
		case GLUT_KEY_DOWN:
			//player->Teleport(player->GetLocation() + Vector(0, 0, -1));
			arrows[3] = true;
			break;
	}
}
void KeyboardHandler::onSpecialKeyUp(int key, int x, int y){
	CalcModifiers();
	switch(key) {
		case GLUT_KEY_LEFT:
			arrows[0] = false;
			break;
		case GLUT_KEY_RIGHT:
			arrows[1] = false;
			break;
		case GLUT_KEY_UP:
			arrows[2] = false;
			break;
		case GLUT_KEY_DOWN:
			arrows[3] = false;
			break;
		
	}
}
void KeyboardHandler::onNormalKeyDown(unsigned char key, int x, int y){
	CalcModifiers();
	keys[key] = true;
	switch(key) {
		case 27: // ESCAPE
			if(player->inGui) {
				player->CloseGui();
			} else {
				player->OpenGui((Gui *)player->guiHandler->mainMenu);
			}
			break;
	}
}
void KeyboardHandler::onNormalKeyUp(unsigned char key, int x, int y){
	CalcModifiers();
	keys[key] = false;
}
