#include <windows.h>
#include "stdafx.h"
#include <string>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sstream> 
#include <math.h> 
#include <gl\gl.h>
#include <gl\glu.h>
#include "GL\freeglut.h"
#pragma comment(lib, "OpenGL32.lib")
#include "Ball.h"
#include "Player.h"
#include "irrKlang\irrKlang.h" //sound
#pragma comment(lib, "irrKlang.lib")
#include <vector>
#define VK_W 0x57 //w
#define VK_S 0x53 //s
#define VK_P 0x50 //p
#define VK_R 0x52 //r
#define VK_T 0x54 //t
#define VK_U 0x55 //u
Player player_1; //left
Player player_2; //right
bool paused = false;
bool end_game = false;
bool start_game = true;
//using namespace irrklang; //sound
//using namespace std;

irrklang::ISoundEngine *SoundEngine = irrklang::createIrrKlangDevice(); //sound
int width = 800;
int height = 400;
int max_score = 10;
std::vector<Ball> balls;
int player_2_score;// = player_2.score - 1;
int player_1_score;// = player_1.score - 1;
void drawText(float x, float y, std::string text) {
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}
void draw_start() {
	// clear opengl
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	drawText(width / 2 - 110, height / 2, "First one to 25 wins\nPress (P) at any time to pause\nPress (U) to start!");


	glutSwapBuffers();
}
void draw_end() {
	// clear opengl
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//const int player_2_score = player_2.score-1;
	//const int player_1_score = player_1.score-1;
	for (Ball &ball : balls) {
		ball.speed = 0;
	}
	if (player_1_score > player_2_score) {
		drawText(width / 2 - 110, height - 20, "Player 1 has won the game! ->" + std::to_string(player_1_score));
	}
	else {
		drawText(width / 2 - 110, height - 20, "Player 2 has won the game! -> " + std::to_string(player_2_score));
	}
	//SoundEngine->play2D("win.wav", GL_FALSE); //doesn't play sound correctly
	drawText(width / 2 - 110, height - 20, "\nPress (R) to reset");

	
	glutSwapBuffers();
}
void drawRect(float x, float y, float width, float height, float r, float g, float b) {

	glBegin(GL_QUADS);
	glColor3d(r, g, b);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glColor3d(1.0, 1.0, 1.0);
	glEnd();
}

void drawMedian()
{
	//draw median
	glLineStipple(20, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glColor3d(1.0, 1.0, 0);
	glVertex2f(width/2, -10);
	glVertex2f(width/2, height-20);
	glColor3d(1.0, 1.0, 1.0);
	glEnd();

}

void draw() {
	// clear opengl
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//draw median
	drawMedian();
	// draw ball
	for (Ball &ball : balls) {
		drawRect(ball.x - ball.size / 2, ball.y - ball.size / 2, ball.size, ball.size, 0.0, 1.0, 0.0);
	}

	// draw player paddles
	drawRect(player_1.paddle.x, player_1.paddle.y, player_1.paddle.width, player_1.paddle.height, 0.7, 0.0, 0.0);
	
	drawRect(player_2.paddle.x, player_2.paddle.y, player_2.paddle.width, player_2.paddle.height, 0.0, 0.0, 0.7);

	// draw player score
	drawText(width / 2 - 84, height - 20,
		"Speed: " + std::to_string(player_1.paddle.speed) + " " + std::to_string(player_1.score) + ":" + std::to_string(player_2.score) +
		" Speed: " + std::to_string(player_2.paddle.speed) + " " + "\n" + "Size: " + std::to_string(player_1.paddle.height) +
		"     Size: " + std::to_string(player_2.paddle.height) + "\n" + "Streak: " + std::to_string(player_1.win_streak) +
		"    Streak: " + std::to_string(player_2.win_streak));



	//swap
	glutSwapBuffers();
}
void keyboard() {
	//handle pause
	if (GetAsyncKeyState(VK_ESCAPE)) {
		exit(0);
	}
	if (GetAsyncKeyState(VK_P)){
		paused = !paused;
		Sleep(100); //so that the key doesnt get pressed again
	}
	if (GetAsyncKeyState(VK_R)&& end_game) {
		std::cout << "R" << std::endl;
		player_1.reset();
		player_2.reset();
		balls.clear();
		balls.push_back(Ball(width / 2, height / 2));
		glutDisplayFunc(draw);
		Sleep(100);
		//glutDisplayFunc(draw);

	}
	if (GetAsyncKeyState(VK_U) && start_game) {
		player_1.paddle.x = 2.0f;
		player_1.paddle.y = 200 - player_1.paddle.height / 2;
		//right paddle pos
		player_2.paddle.x = width - player_2.paddle.width - 10;
		player_2.paddle.y = 200 - player_2.paddle.height / 2;
		player_1.reset();
		player_2.reset();
		balls.clear();
		balls.push_back(Ball(width / 2, height / 2));
		start_game = false;
		Sleep(500);
		glutDisplayFunc(draw);
		
		//glutDisplayFunc(draw);

	}
	
	// left racket
	//prevent from going off screen
	if (!paused) { //dont let the players move when paused
		if (GetAsyncKeyState(VK_W) && (player_1.paddle.y + player_1.paddle.speed) + player_1.paddle.height-5 < height) {
			player_1.paddle.y += player_1.paddle.speed;
		}
		if (GetAsyncKeyState(VK_S) && (player_1.paddle.y - player_1.paddle.speed) > 0) {
			player_1.paddle.y -= player_1.paddle.speed;
		}

		// right racket
		//prevent from going off screen
		if (GetAsyncKeyState(VK_UP) && (player_2.paddle.y + player_2.paddle.speed) + player_2.paddle.height-5 < height) {
			player_2.paddle.y += player_2.paddle.speed;
		}
		if (GetAsyncKeyState(VK_DOWN) && (player_2.paddle.y - player_2.paddle.speed) > 0) {
			player_2.paddle.y -= player_2.paddle.speed;
		}
	}
}





void updateBall() {
	if ((player_1.win_streak == 0 && player_2.win_streak == 1)|| (player_1.win_streak == 1 && player_2.win_streak == 0) && balls.size() > 1) {
		while (balls.size() > 1) {
			balls.pop_back();
		}
	}
	for (int i = 0; i < balls.size(); i++) {
		bool remove = false;
		bool player_is_bad = false;
		// start
		balls[i].x += balls[i].dir_x * balls[i].speed;
		balls[i].y += balls[i].dir_y * balls[i].speed;


		// hit by left racket?
		if (balls[i].x <= player_1.paddle.x + player_1.paddle.width &&
			balls[i].x > player_1.paddle.x &&
			balls[i].y < player_1.paddle.y + player_1.paddle.height &&
			balls[i].y > player_1.paddle.y) {
			//calculates if balls[i] hit paddle at bottom or top or center
			float t = ((balls[i].y - player_1.paddle.y) / player_1.paddle.height) - 0.5f;
			balls[i].dir_x = fabs(balls[i].dir_x); // hit left racket so send it back with positive direction
			balls[i].dir_y = t; //send it back the that way
			SoundEngine->play2D("solid.wav", GL_FALSE); //play that sound
			//add speed up till 10 so gets harder
			if (balls[i].speed < 10)
				balls[i].speed += 0.5;
		}

		// hit by right racket?
		if (balls[i].x > player_2.paddle.x &&
			balls[i].x <= player_2.paddle.x + player_2.paddle.width &&
			balls[i].y < player_2.paddle.y + player_2.paddle.height &&
			balls[i].y > player_2.paddle.y) {
			float t = ((balls[i].y - player_2.paddle.y) / player_2.paddle.height) - 0.5f;
			balls[i].dir_x = -fabs(balls[i].dir_x); // hit right racket so send it back with negative direction
			balls[i].dir_y = t;
			SoundEngine->play2D("solid.wav", GL_FALSE); //play that sound
			if (balls[i].speed < 10)
				balls[i].speed += 0.5;
		}

		// hit left wall?
		if (balls[i].x < 0) {
			//balls[i]s.erase(balls[i]);
			
			++player_2.score;
			++player_2.win_streak;
			if (player_2.score >= max_score) {
				SoundEngine->play2D("win.wav", GL_FALSE);
				end_game = true;
				player_2_score = max_score;
				glutDisplayFunc(draw_end);
			}
			else {
				SoundEngine->play2D("goal.wav", GL_FALSE);
				player_1.reset();
				if (player_2.win_streak >= 2) {
					if (player_2.win_streak >= 6) {
						if (player_2.win_streak >= 7) {
							if (player_2.win_streak >= 8) {
								player_1.paddle.height = 250;
								balls.push_back(Ball(width / 3, height / 2));
								player_2.paddle.speed = 5;
								player_is_bad = true;
							}
							else
								player_2.paddle.speed = 2;
						}
						else {
							player_2.paddle.height = 40;
						}
					}
					else {
						int power_up = rand() % 2;
						if (power_up == 0)
							player_2.paddle.speed += 3;
						else if (power_up == 1)
							player_2.paddle.height += 15;
					}
				}
				if (balls.size() > 1 && !player_is_bad) {
					remove = true;
				}
				else {
					balls[i].x = width / 2;
					balls[i].y = height / 2;
					balls[i].dir_x = fabs(balls[i].dir_x); // force it to be positive
					balls[i].dir_y = 0.4f;
					balls[i].speed = 4;
				}
			}
		}

		// hit right wall?
		if (balls[i].x > width) {
			++player_1.win_streak;
			++player_1.score;
			if (player_1.score >= max_score) {
				SoundEngine->play2D("win.wav", GL_FALSE);
				end_game = true;
				player_1_score = max_score;
				glutDisplayFunc(draw_end);
				
			}
			else {
				SoundEngine->play2D("goal.wav", GL_FALSE);
				
				player_2.reset();
				if (player_1.win_streak >= 2) {
					if (player_1.win_streak >= 6) {
						if (player_1.win_streak >= 7) {
							if (player_1.win_streak >= 8) {
								player_2.paddle.height = 250;
								balls.push_back(Ball(width / 3, height / 2));
								player_1.paddle.speed = 5;
								player_is_bad = true;
							}
							else
								player_1.paddle.speed = 4;
						}
						else {
							player_1.paddle.height = 40;
						}
					}
					else {
						int power_up = rand() % 2;
						if (power_up == 0)
							player_1.paddle.speed += 3;
						else if (power_up == 1)
							player_1.paddle.height += 15;
					}
				}
				if (balls.size() > 1 && !player_is_bad) {
					remove = true;
				}
				else {
					balls[i].x = width / 2;
					balls[i].y = height / 2;
					balls[i].dir_x = -fabs(balls[i].dir_x); // force it to be negative
					balls[i].dir_y = 0.4f;
					balls[i].speed = 4;
				}
			}
		}

		// hit top wall?
		if (balls[i].y > height) {
			SoundEngine->play2D("solid.wav", GL_FALSE);
			balls[i].dir_y = -fabs(balls[i].dir_y); // force it to be negative
		}

		// hit bottom wall?
		if (balls[i].y < 0) {
			SoundEngine->play2D("solid.wav", GL_FALSE);
			balls[i].dir_y = fabs(balls[i].dir_y); // force it to be positive
		}

		// make sure that length of dir stays at 1
		balls[i].vec2_norm(balls[i].dir_x, balls[i].dir_y);
		if (remove) { balls.erase(balls.begin() + i); }
	}
}

void update(int value) {
	keyboard();
	if (!paused) { //meh not the best way but the paddles will be stoped in the keybaord function
		updateBall();
	}

	glutTimerFunc(17, update, 0);
	glutPostRedisplay();
}
void enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int _tmain(int argc, char** argv) {

	//add first ball
	
	//player_2.win_streak = 14;
	// initialize opengl (via glut)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Pong");

	glutDisplayFunc(draw_start);
	glutTimerFunc(17, update, 0);

	enable2D(width, height);
	glColor3f(1.0f, 1.0f, 1.0f);

	// start the whole thing
	//this thing is too loud :(
	//SoundEngine->play2D("background.mp3", GL_TRUE);
	glutMainLoop();
	return 0;
}