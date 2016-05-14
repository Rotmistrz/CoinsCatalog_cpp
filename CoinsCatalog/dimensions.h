#pragma once

class Dimensions
{
private:
	float width;
	float height;

public:
	Dimensions(float x, float y);
	~Dimensions();
	float getWidth();
	float getHeight();
};