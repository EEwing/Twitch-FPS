#ifndef GUI_HANDLER_H
#define GUI_HANDLER_H

//#include "GuiMainMenu.h"
#include "Gui.h"
#include "Entity/Player.h"

class Gui;
class GuiMainMenu;
class Player;


class GuiHandler {
  public:
			GuiHandler(Player *);
	GuiMainMenu    *mainMenu;
};

#endif
