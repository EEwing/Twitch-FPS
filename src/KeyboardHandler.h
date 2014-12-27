#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include "Player.h"

class Player;

class KeyboardHandler {
  private:
	void 	CalcModifiers();
  public:
	Player *player; 
			KeyboardHandler(Player *);
	bool 	keys[256];
	bool 	arrows[4];
	void 	onSpecialKeyDown(int, int, int);
	void 	onSpecialKeyUp(int, int, int);
	void 	onNormalKeyDown(unsigned char, int, int);
	void 	onNormalKeyUp(unsigned char, int, int);
};

#endif