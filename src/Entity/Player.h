#ifndef PLAYER_H
#define PLAYER_H

#include "Entity/Entity.h"
#include "Gui/Gui.h"
#include "Gui/GuiHandler.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "Vector.h"
#include "World.h"

class KeyboardHandler;
class MouseHandler;

class Gui;
class GuiHandler;
class World;

class Player : public Entity {
  private:
	double 				xRot, yRot; // in degrees
	double				height;
	Vector 				location, direction;
    World              *world;
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
	void 				RenderWorld();
	void 				RenderHUD();
	void 				RenderGui();
	void				Teleport(Vector);
	Vector 				GetLocation();
	void				OpenGui(Gui *);
	void				CloseGui();
};

#endif
