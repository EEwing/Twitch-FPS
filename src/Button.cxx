#include "Button.h"

Button::Button(void (*execFunc)(void)) {
	execute = execFunc;
}

void Button::Execute() {
	execute();
}

Button Button::SetPosition(int x, int y) {
	this->x = x;
	this->y = y;
	return *this;
}