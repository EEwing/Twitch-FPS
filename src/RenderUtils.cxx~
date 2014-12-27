#include "RenderUtils.h"

#include <stdio.h>

#include "globals.h"

GLuint shadowTexture = 0;
GLuint shadowFramebuffer = 0;

void initShadows() {
	fprintf(stderr, "Initializing Shadow Buffers\n");
	glGenFramebuffers(1, &shadowFramebuffer);
	
	glGenTextures(1, &shadowTexture);
	glBindTexture(GL_TEXTURE_2D, shadowTexture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

GLuint RenderToTexture() {	
	fprintf(stderr, "Rendering to Shadow Buffers\n");
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFramebuffer);
	glBindTexture(GL_TEXTURE_2D, shadowTexture);
	 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	  
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowTexture, 0);
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers);
	  
	//glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	  
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		fprintf(stderr, "Framebuffer failed to load\n");
	}
	
	return shadowTexture;
}
