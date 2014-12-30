#ifndef GUI_H
#define GUI_H

#include <vector>

#include <GL/glu.h>

#include "Button.h"
#include "Entity/Player.h"

class Player;

class Gui {
  private:
	GLuint 				texture;
	std::vector<Button> buttons;
	Gui				   *exitGui;
	Player			   *player;
	void				LoadTexture(const char *);
	int					GetWidth();
	int					GetHeight();
  public:
  
	double				locationX, locationY;
	int					texWidth, texHeight, channels;
	double				scale;
	
						Gui(const char *, Player *);
	void 				Render(); // Renders the GUI
	void				ProcessMouseEvent(int, int);
	Gui				   *SetLocation(double, double);
	Gui				   *SetScale(double);
	Gui				   *SetExitGui(Gui *);
	void				Close();
	
	/**********
	 * Sets location values so Gui is centered in the Screen
	 **********/
	void				Center();  
	
	//static Gui			MainMenu;
};

class GuiMainMenu : public Gui {
  public:
	GuiMainMenu(Player *);
};

//extern Gui MainMenuGui;
#endif
