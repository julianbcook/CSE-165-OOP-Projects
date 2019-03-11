#include "App.h"
#include <iostream>
App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
	rect1.x = 0; rect1.y = .5f; rect1.width = .5f; rect1.height = .8f; rect1.r = 0.0; rect1.g = 1.0f; rect1.b = 1.0f;
	rect2.x = -.5f; rect2.y = -.5f; rect2.width = .4f; rect2.height = .25f; rect2.r = 1.0f; rect2.g = 0; rect2.b = 1.0f;
	
}


void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	

	

    // Set Color
    glColor3d(rect1.r, rect1.g, rect1.b);

    
    // Draw some points
    glBegin(GL_POLYGON);
    
    glVertex2f(rect1.x, rect1.y);
    glVertex2f(rect1.x + rect1.width, rect1.y);
    glVertex2f(rect1.x + rect1.width, rect1.y - rect1.height);
    glVertex2f(rect1.x, rect1.y - rect1.height);
    
    glEnd();
    
    // Draw a yellow cross
    glColor3d(rect2.r, rect2.g, rect2.b);
    
    glBegin(GL_POLYGON);
    
	glVertex2f(rect2.x, rect2.y);
	glVertex2f(rect2.x + rect2.width, rect2.y);
	glVertex2f(rect2.x + rect2.width, rect2.y - rect2.height);
	glVertex2f(rect2.x, rect2.y -rect2.height);
    
    glEnd();
    
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;

	if (rect1.contains(mx, my))
	{
		std::cout << "In" << std::endl;
		rect1.r = 1.0; rect1.g = 0;
	}

	if (rect2.contains(mx, my))
	{
		std::cout << "In" << std::endl;
		rect2.r = 0; rect2.g = 1.0;
	}


	
    
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }
}
