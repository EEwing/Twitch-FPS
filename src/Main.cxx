#include <fstream>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <sstream>
#include <stdio.h>

#include "Entity/Player.h"
#include "Event/Event.h"
#include "Event/PlayerMoveEvent.h"
#include "globals.h"
#include "Gui/Gui.h"
#include "RenderUtils.h"

Player *player;

int SCREEN_WIDTH  = 800;
int SCREEN_HEIGHT = 600;

void renderShadow() {
    glPushAttrib(GL_LIGHTING_BIT | GL_DEPTH_BUFFER_BIT | GL_TEXTURE_BIT);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, 1, 0, 1);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glDisable(GL_LIGHTING);
//      glDisable(GL_DEPTH_TEST);
      glColor4f(1., 1., 1., 1.);
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, shadowTexture);

      glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glTexCoord2f(1, 0); glVertex2f(1, 0);
        glTexCoord2f(1, 1); glVertex2f(1, 1);
        glTexCoord2f(0, 1); glVertex2f(0, 1);
      glEnd();
    glPopAttrib();	
}

void renderScene() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)SCREEN_WIDTH/SCREEN_HEIGHT, 0.1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    player->CalculateMovement();

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, shadowFramebuffer);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    player->RenderWorld();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    renderShadow();
    player->RenderHUD();
    player->RenderGui();
	
    glutSwapBuffers();
}


void initLighting() {
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
	
    GLfloat mat_ambient[] = {0.03, .03, .03, 1.0};
    GLfloat mat_diffuse[] = {.8, 0.8, .8, 1.0};
    GLfloat mat_spec[]    = {.5, .5, .5, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, mat_ambient);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
    glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, mat_spec);

}

std::string ReadFileAsString(const char * filename) {
    std::ifstream file;
    file.open(filename);
    if(!file.good()) fprintf(stderr, "Could not open shader file: %s\n", filename);
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

void initShaders() {
	std::string vs_shader_str = ReadFileAsString("src/Shaders/vs.glsl");
	std::string fs_shader_str = ReadFileAsString("src/Shaders/fs.glsl");
	
	const char * vs_shader_src = vs_shader_str.c_str();
	const char * fs_shader_src = fs_shader_str.c_str();
	
	int vs_shader_len = strlen(vs_shader_src);
	int fs_shader_len = strlen(fs_shader_src);
	
	GLuint vertexShader, fragShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(vertexShader, 1, &vs_shader_src, &vs_shader_len);
	glShaderSource(fragShader, 1, &fs_shader_src, &fs_shader_len);
	
	glCompileShader(vertexShader);
	glCompileShader(fragShader);
	
	GLint vs_compiled, fs_compiled;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vs_compiled);
	if(vs_compiled) {
		fprintf(stderr, "Vertex Shader loaded properly\n");
	} else {
		fprintf(stderr, "ERROR: Vertex Shader failed to load\n");
		GLint blen = 0;
		GLsizei slen = 0;
		
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &blen);
		if(blen > 1) {
			GLchar vs_log[blen];
			glGetShaderInfoLog(vertexShader, blen, &slen, &vs_log[0]);
			fprintf(stderr, "Vertex Shader log:\n%s\n", &vs_log);
		}
	}
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fs_compiled);
	if(fs_compiled) {
		fprintf(stderr, "Fragment Shader loaded properly\n");
	} else {
		fprintf(stderr, "ERROR: Fragment Shader failed to load\n");
		GLint blen = 0;
		GLsizei slen = 0;
		
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &blen);
		if(blen > 1) {
			GLchar compiler_log[blen];
			glGetShaderInfoLog(fragShader, blen, &slen, &compiler_log[0]);
			fprintf(stderr, "Fragment Shader log:\n%s\n", &compiler_log);
		}
	}
	
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);
	
	glLinkProgram(program);
	
	GLint linkSuccess = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int *)&linkSuccess);
	if(linkSuccess != GL_FALSE) {
		fprintf(stderr, "Shaders linked properly\n");
	} else {
		fprintf(stderr, "ERROR: GLSL Linker did not link properly.\n");
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		
		GLchar * linker_log = new GLchar[maxLength];
		glGetProgramInfoLog(program, maxLength, &maxLength, linker_log);
		fprintf(stderr, "GLSL Linker Log:\n%s\n", linker_log);
		delete linker_log;
	}
}

void init() {
	glLoadIdentity();
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	gluPerspective(45, (float)SCREEN_WIDTH/SCREEN_HEIGHT, 0.1, 100);
    Cell::init();
	initLighting();
	initShadows();
	initShaders();


	glClearColor(0.6, 0.6, 0.6, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	player = new Player();
}
/*****
* Keyboard function pointers
******/
void normKeyUp(unsigned char key, int x, int y) {
	player->keyHandler->onNormalKeyUp(key, x, y);
}

void normKeyDown(unsigned char key, int x, int y) {
	player->keyHandler->onNormalKeyDown(key, x, y);
}

void specKeyUp(int key, int x, int y) {
	player->keyHandler->onSpecialKeyUp(key, x, y);
}

void specKeyDown(int key, int x, int y) {
	player->keyHandler->onSpecialKeyDown(key, x, y);
}

void mouseFunc(int button, int state, int x, int y) {
	player->mouseHandler->onMouse(button, state, x, y);
}

void wheelFunc(int wheel, int direction, int x, int y) {
	player->mouseHandler->onWheel(wheel, direction, x, y);
}

void mouseMoveFunc(int x, int y) {
	player->mouseHandler->onMove(x, y);
}

void resize(int x, int y) {
	SCREEN_WIDTH = x;
	SCREEN_HEIGHT = y;
	glViewport(0, 0, x, y);
}

int main(int argc, char **argv) {


	fprintf(stderr, "Initializing GLUT variables\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(1920, 0);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Twitch FPS Game");
	
	GLenum glewStatus = glewInit();
	if(glewStatus != GLEW_OK) {
		fprintf(stderr, "ERROR: GLEW was not initialized successfully\n%s\n", glewGetErrorString(glewStatus));
		exit(EXIT_FAILURE);
	}
		
	init();
	
	fprintf(stderr, "Registering Callback Functions\n");

	/*****
	* Register Callback Functions
	******/	
	//TODO register main loop timer
	glutIdleFunc(renderScene);
	glutSpecialFunc(specKeyDown);
	glutKeyboardFunc(normKeyDown);
	glutSpecialUpFunc(specKeyUp);
	glutKeyboardUpFunc(normKeyUp);
	glutMouseFunc(mouseFunc);
	glutMouseWheelFunc(wheelFunc);
	glutMotionFunc(mouseMoveFunc);
	glutPassiveMotionFunc(mouseMoveFunc);
	glutReshapeFunc(resize);
	glutDisplayFunc(renderScene);
	
	fprintf(stderr, "Starting Main Loop\n");
	
	glutMainLoop();
    // Terminate Program
}
