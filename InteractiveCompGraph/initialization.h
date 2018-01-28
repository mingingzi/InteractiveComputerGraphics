#ifndef INITIALIZATION_H
#define INITIALIZATION_H

struct Color
{
	float r, g, b;
};

Color makeColor(float r, float g, float b)
{
	Color c = { r, g, b };
	return c;
}

Color lerp(Color a, Color b, float t)
{
	Color c;
	c.r = (1 - t)*a.r + t*b.r;
	c.g = (1 - t)*a.g + t*b.g;
	c.b = (1 - t)*a.b + t*b.b;

	return c;
}

int myrandom(int m) {

	return rand() % m;

}
#endif