#ifndef PLAYER_H
#define PLAYER_H

#include "Vector.h"
#include "Gui/Gui.h"
#include "Gui/GuiHandler.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"

class KeyboardHandler;
class MouseHandler;

class Gui;
class GuiHandler;

class Player {
  private:
	double 				xRot, yRot; // in degrees
	double				height;
	Vector 				location, direction;
	void 				UpdateKeys();
	double				sensitivity;
  public:
	Gui 			   *curGui;
	KeyboardHandler    *keyHandler;
	MouseHandler	   *mouseHandler;
	GuiHandler		   *guiHandler;
	bool 				isShifted;
	bool				inGui;
	
						Player();
					   ~Player();
	void 				CalculateMovement();
	void 				Render();
	void				Teleport(Vector);
	Vector 				GetLocation();
	void				OpenGui(Gui *);
	void				CloseGui();
};

#endif