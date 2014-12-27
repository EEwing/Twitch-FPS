#include "RenderUtils.h"

#include <stdio.h>

#include "globals.h"

GLuint shadowTexture = 0;
GLuint shadowFramebuffer = 0;
GLuint shadowRenderbuffer = 0;

void initShadows() {
	fprintf(stderr, "Initializing Shadow Buffers\n");
	glGenFramebuffers(1, &shadowFramebuffer);
	
	glGenTextures(1, &shadowTexture);
	glBindTexture(GL_TEXTURE_2D, shadowTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, shadowFramebuffer);
	//glClear(GL_COLOR_BUFFER_BIT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowTexture, 0);

	glGenRenderbuffers(1, &shadowRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, shadowRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, shadowRenderbuffer);

	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		fprintf(stderr, "Framebuffer failed to load\n");
	}
}

GLuint RenderToTexture() {	
	fprintf(stderr, "Rendering to Shadow Buffers\n");
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, shadowFramebuffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	//glBindTexture(GL_TEXTURE_2D, shadowTexture);
	 
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	  

	  
	//glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	  
	
	return shadowTexture;
}
