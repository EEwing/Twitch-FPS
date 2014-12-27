#ifndef GLOBALS_H
#define GLOBALS_H

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern GLuint shadowTexture;
extern GLuint shadowFramebuffer;
extern GLuint shadowRenderbuffer;

void initShadows();

#endif
