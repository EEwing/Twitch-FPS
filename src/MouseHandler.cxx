#include "MouseHandler.h"

#include <stdio.h>

#include <GL/freeglut.h>

#include "globals.h"

MouseHandler::MouseHandler(Player *p) {
	player = p;
}

void MouseHandler::onMouse(int button, int state, int x, int y) {
}

void MouseHandler::onWheel(int wheel, int direction, int x, int y) {
}

void MouseHandler::onMove(int x, int y) {
	this->x = x;
	this->y = y;
	if(player->inGui) {
		player->curGui->ProcessMouseEvent(x, y);
	}
}