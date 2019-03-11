#ifndef RECT_H
#define RECT_H
struct Rect{
		//coords
		float x;
		float y;
		float width;
		float height;

		//color
		float r;
		float g;
		float b;

		//constructors

		Rect()
		{}

		Rect(float x, float y, float width, float height, float r, float g, float b)
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->r = r;
			this->g = g;
			this->b = b;
		}

		bool contains(float xc, float yc)
		{
			//boundaries
			float xmin = x; float ymin = y;
			float xmax = x + width; float ymax = y - height;

			if (xc >= xmin && xc <= xmax && yc <= ymin && yc >= ymax)
				return true;
			else
				return false;
		}
	};

	#endif
