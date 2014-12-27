#ifndef BUTTON_H
#define BUTTON_H

class Button {
  private:
	int		x, y;
	void  (*execute)(void);
  public:
			Button(void (*)(void));
	void	Execute();
	Button	SetPosition(int, int);
};

#endif