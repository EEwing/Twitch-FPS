#include "GuiHandler.h"

#include <stdio.h>

GuiHandler::GuiHandler(Player *player) {
	mainMenu = new GuiMainMenu(player);
	//mainMenu = new Gui("Main.png", player);
	mainMenu->SetLocation(0.05, 0.05)->SetScale(0.9);
}