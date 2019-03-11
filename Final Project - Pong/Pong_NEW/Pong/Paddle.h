#include "stdafx.h"

class Paddle {
public:
	
	int width = 10;
	int height = 80;
	int speed = 3;
	float r;
	float g;
	float b;
	// position
	float x;
	float y;
	void reset() {
		width = 10;
		height = 80;
		speed = 3;
	}
};