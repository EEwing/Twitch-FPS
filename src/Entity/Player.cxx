#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cmath>

#include "Event/PlayerMoveEvent.h"
#include "globals.h"
#include "Player.h"
#include "RenderUtils.h"

Player::Player() :  keyHandler(new KeyboardHandler(this)), 
                    mouseHandler(new MouseHandler(this)),
                    guiHandler(new GuiHandler(this)){
    height = 2.0;
    location = Vector(0, height, -10);
    xRot = yRot = 0;
    isShifted = false;
    sensitivity = 1.0;
    inGui = false;
    curGui = NULL;
    world = new World();
}

Player::~Player(){
    delete keyHandler;
    delete mouseHandler;
    delete guiHandler;
}

Vector Player::GetLocation() { return location; }

void Player::Teleport(Vector toLoc) {
    location = toLoc;
}

void Player::CalculateMovement() {
    Vector toLocation(location);
    if(!inGui) {
        int diffX = mouseHandler->x - (SCREEN_WIDTH/2) ;
        int diffY = (SCREEN_HEIGHT/2) - mouseHandler->y;
        xRot += diffX*sensitivity/10;
        yRot += diffY*sensitivity/10;
        if(xRot >= 360) xRot -= 360;
        if(yRot > 90) yRot = 90;
        if(xRot < 0) xRot += 360;
        if(yRot < -90) yRot = -90;
            direction = Vector(sin(-xRot*M_PI/180), sin(yRot*M_PI/180), cos(-xRot*M_PI/180));
        if(keyHandler->keys[27]) {
            //glutLeaveMainLoop();
            return;
        }
        if(keyHandler->arrows[0] || keyHandler->keys['a']) {
            Vector v = Vector(0, 1, 0).cross(direction);
            toLocation = toLocation+Vector(v.x/10., 0, v.z/10.);
        }
        if(keyHandler->arrows[1] || keyHandler->keys['d']) {
            Vector v = Vector(0, 1, 0).cross(direction);
            toLocation = toLocation+Vector(-v.x/10., 0, -v.z/10.);
        }
        if(keyHandler->arrows[2] || keyHandler->keys['w']) {
            toLocation = toLocation+Vector(direction.x/10., 0, direction.z/10.);
        }
        if(keyHandler->arrows[3] || keyHandler->keys['s']) {
            toLocation = toLocation+Vector(-direction.x/10., 0, -direction.z/10.);
        }

        if(location != toLocation) {
            PlayerMoveEvent e(this, toLocation);
            e.CallEvent();
        }
    
                glutWarpPointer(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    }
}

void Player::RenderWorld() {
    //fprintf(stderr, "Location: %s\n", location.toString());
    //fprintf(stderr, "Direction: %s\n", direction.toString());
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();
      gluLookAt(location.x, location.y, location.z,
        location.x+direction.x, location.y+direction.y, location.z+direction.z,
        0, 1, 0);       

      GLfloat light_position[] = {0., 5., 5., 1.};
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);

      world->LoadArea(*this);

      world->Render();
      /*
      GLfloat mat_spec[]    = {1., 1., 1., 1.0};
      GLfloat mat_shine[]       = { 50 };
      GLfloat mat_noshine[]     = { 1 };

      // Begin Floor
      glColor3f(1., 0., 1.);
      glNormal3f(0, 1, 0);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_noshine);
      for(int i=-10; i<10; i++) {
          for(int j=-10; j<10; j++) {
          glBegin(GL_TRIANGLE_FAN);
            glVertex3f(i+.5, 0, j+.5);
            glVertex3f(i, 0, j);
                glVertex3f(i+1, 0, j);
            glVertex3f(i+1, 0, j+1);
                glVertex3f(i, 0, j+1);
            glVertex3f(i, 0, j);
              glEnd();
          }
      }
      // End Floor

      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shine);
      glColor3f(0, 1, 1);
      glTranslatef(0, 1, 0);
      glutSolidSphere(2, 50, 50);
    glPopMatrix();
    */
}

void Player::RenderHUD() {
    glPushAttrib(GL_LIGHTING_BIT | GL_DEPTH_BUFFER_BIT | GL_TEXTURE_BIT);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, 1, 0, 1);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glDisable(GL_LIGHTING);
      glDisable(GL_DEPTH_TEST);
      glPushMatrix();
        glBegin(GL_QUADS);
          glColor4f(0., 0., 0., 1.);
          glVertex2d(0.25, 0.);
          glVertex2d(0.75, 0.);
          glVertex2d(0.75, 0.1);
          glVertex2d(0.25, 0.1);
        glEnd();

      glPopMatrix();
    glPopAttrib();  
}
    
void Player::RenderGui() {
    if(curGui != NULL) {    
        glPushAttrib(GL_LIGHTING_BIT | GL_DEPTH_BUFFER_BIT | GL_TEXTURE_BIT);
          glMatrixMode(GL_PROJECTION);
          glLoadIdentity();
          gluOrtho2D(0, 1, 0, 1);
          glMatrixMode(GL_MODELVIEW);
          glLoadIdentity();
          glDisable(GL_LIGHTING);
          glDisable(GL_DEPTH_TEST);
          glPushMatrix();
            glBegin(GL_QUADS);
              glColor4f(0., 0., 0., 0.5);
              glVertex2d(0, 0);
              glVertex2d(1, 0);
              glVertex2d(1, 1);
              glVertex2d(0, 1);
            glEnd();
        
            curGui->Render();
          glPopMatrix();
        glPopAttrib();  
    }
}

void Player::OpenGui(Gui *toOpen) {
    fprintf(stderr, "Opening Graphical User Interface @ %p\n", toOpen);
    curGui = toOpen;
    if(curGui != NULL) {
        inGui = true;
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    } else {
        CloseGui();
    }
}

void Player::CloseGui() {
    if(curGui != NULL) {
        fprintf(stderr, "Closing GUI @ %p\n", curGui);
        curGui->Close();
    }
    fprintf(stderr, "Gui is now %p\n", curGui);
    if(curGui == NULL) {
        inGui =false;
        glutWarpPointer(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
        glutSetCursor(GLUT_CURSOR_NONE);
    }
}
