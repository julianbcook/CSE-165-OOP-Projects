#include <math.h> 
//#include "Paddle.h"
class Ball {
public:
	float x;
	float y;
	float dir_x = -1.0f;
	float dir_y = 0.4f;
	int size = 10;
	int speed = 4;

	Ball(float mx, float my) {
		x = mx;
		y = my;
	}
	void vec2_norm(float& x, float &y) {
		// sets a vectors length to 1 (which means that x + y == 1)
		float length = sqrt((x * x) + (y * y));
		if (length != 0.0f) {
			length = 1.0f / length;
			x *= length;
			y *= length;
		}
	}
};