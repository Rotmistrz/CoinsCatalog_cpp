#include "dimensions.h"

Dimensions::Dimensions(float x, float y)
: width(x), height(y)
{

}

Dimensions::~Dimensions() {
}

float Dimensions::getWidth() {
	return width;
}

float Dimensions::getHeight() {
	return height;
}