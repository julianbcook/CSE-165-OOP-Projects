#include "Paddle.h"
class Player {
public:
	int score = 0;
	int win_streak = 0;
	bool power_down = false;
	Paddle paddle;

	void reset() {
		win_streak = 0;
		score = 0;
		paddle.reset();
	}
};