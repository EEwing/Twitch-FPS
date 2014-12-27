#include "Gui.h"

#include <windows.h>

#include <stdio.h>

#include <GL/glu.h>
#include <SOIL.h>

#include "globals.h"

Gui::Gui(const char *filename, Player *p) {
	player = p;
	
	LoadTexture(filename);
	
	scale = 0.9;
	locationX = 0;
	locationY = 0;
	exitGui = NULL;
	fprintf(stderr, "Created GUI successfully\n");
}

void Gui::LoadTexture(const char * filename) {char textureLocation[1024];
	sprintf(textureLocation, "src\\assets\\Textures\\Gui\\%s", filename);
	fprintf(stderr, "Creating GUI @ %s\n", textureLocation);
	channels = 0;
	unsigned char *data = SOIL_load_image (
		textureLocation,
		&texWidth, &texHeight, &channels,
		SOIL_LOAD_AUTO
	);
	fprintf(stderr, "Loaded Data from %s {width:%d,height:%d,channels:%d}\n", textureLocation, texWidth, texHeight, channels);
	texture = SOIL_create_OGL_texture (
		data,
		texWidth, texHeight, channels,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
	);
	if(texture == 0) fprintf(stderr, "Error loading texture: %s\n", textureLocation);
}

int Gui::GetWidth() {
	if((float)texWidth/SCREEN_WIDTH > (float)texHeight/SCREEN_HEIGHT) {
		return scale*SCREEN_WIDTH;
	} else {
		double height, tempScale;
		height = scale*SCREEN_HEIGHT;
		tempScale = height/texHeight;
		return texWidth*tempScale;
	}
	
}

int Gui::GetHeight() {
	if((float)texWidth/SCREEN_WIDTH > (float)texHeight/SCREEN_HEIGHT) {
		double width, tempScale;
		width = scale*SCREEN_WIDTH;
		tempScale = width/texWidth;
		return texHeight*tempScale;
	} else {
		return scale*SCREEN_HEIGHT;
	}
	
}

void Gui::Center() {
	
	locationX = (float)((SCREEN_WIDTH-GetWidth())/2)/SCREEN_WIDTH;
	locationY = (float)((SCREEN_HEIGHT-GetHeight())/2)/SCREEN_HEIGHT;
	//locationY = GetHeight()*SCREEN_HEIGHT;
	//fprintf(stderr, "Setting location to %lf %lf\n", locationX, locationY);
}

void Gui::Render() {
	Center();
	double xOff, yOff;
	xOff = (float)GetWidth()/SCREEN_WIDTH;
	yOff = (float)GetHeight()/SCREEN_HEIGHT;
	fprintf(stderr, "Rendering Gui @ %lf %lf to %lf %lf\n", locationX, locationY, xOff, yOff);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glBindTexture(GL_TEXTURE_2D, shadowTexture);
	glBegin(GL_QUADS);
	  glColor4f(1., 1., 1., 1.);
	  glTexCoord2d(0., 0.);	glVertex2d(locationX,      locationY);
	  glTexCoord2d(1., 0.);	glVertex2d(locationX+xOff, locationY);
	  glTexCoord2d(1., 1.);	glVertex2d(locationX+xOff, locationY+yOff);
	  glTexCoord2d(0., 1.);	glVertex2d(locationX,      locationY+yOff);
	glEnd();
}

void Gui::ProcessMouseEvent(int x, int y) {
	fprintf(stderr, "Reading mouse movement @ %d %d\n", x, y);
	int pixelX = locationX*SCREEN_WIDTH;
	int pixelY = locationY*SCREEN_HEIGHT;
	int pixelWidth = scale*SCREEN_WIDTH;
	int pixelHeight = scale*SCREEN_HEIGHT;
	if(x > pixelX && x < pixelX+pixelWidth && y > pixelY && y < pixelY+pixelHeight) {
		fprintf(stderr, "Mouse is on GUI\n");
	}
}

Gui *Gui::SetLocation(double x, double y) {
	locationX = x;
	locationY = y;
	return this;
}

Gui *Gui::SetScale(double s) {
	scale = s;
	return this;
}

Gui *Gui::SetExitGui(Gui *g) {
	exitGui = g;
	return this;
}

void Gui::Close() {
	player->OpenGui(exitGui);
}

GuiMainMenu::GuiMainMenu(Player *p) : Gui("Main.png", p){}
