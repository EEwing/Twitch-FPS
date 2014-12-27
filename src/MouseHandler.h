#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#include "Player.h"

class Player;

class MouseHandler {
  public:
	int 	x, y;
	Player *player;
			MouseHandler(Player *);
	void 	onMouse(int, int, int, int);
	void 	onWheel(int, int, int, int);
	void	onMove(int, int);
};

#endif