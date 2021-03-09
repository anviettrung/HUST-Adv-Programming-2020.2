#include <iostream>
#include <fstream>
#include <stdint.h>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

using namespace std;

const char* brightness = " .,-~:;=!*#$@";
const int   brightnessLeng = 12;

struct Pix
{
	uint8_t r, g, b;
	uint8_t grayscale;
};

Pix ReadPixel(uint8_t* rgb_map, int x, int y, int w)
{
	Pix t_pix;

	t_pix.r = rgb_map[3 * (y * w + x)];
	t_pix.g = rgb_map[3 * (y * w + x) + 1];
	t_pix.b = rgb_map[3 * (y * w + x) + 2];
	t_pix.grayscale = (t_pix.r + t_pix.g + t_pix.b) / 3;

	return t_pix;
}

char grayscale_to_ascii(uint8_t value)
{
	float t = (value / 255.0f) * brightnessLeng;
	return brightness[(int)round(t)];
}

void PrintImage(uint8_t* img, int std_w, int std_h, int new_w, int new_h)
{
	Pix pix;
	int x_coord, y_coord;
	float w_ratio = (float)std_w / new_w;
	float h_ratio = (float)std_h / new_h; 

	cout << w_ratio << " " << h_ratio << endl;

	for (int y = 0; y < new_h; y++) {
		for (int x = 0; x < new_w; x++) {
			x_coord = (int)round(x * w_ratio);
			y_coord = (int)round(y * h_ratio);

    		pix = ReadPixel(img, x_coord, y_coord, std_w);
    		cout << grayscale_to_ascii(pix.grayscale);
    	}
    	cout << endl;
	}
}

int main(int argc, char* argv[]) {
    int width, height, bpp;
    int fixed_W, fixed_H;
    uint8_t* rgb_image;
    string fileName;
    ifstream f;

    cout << "Path to file: ";
    cin >> fileName;

    f.open(fileName);

    if (f.is_open()) {
	    rgb_image = stbi_load(fileName.c_str(), &width, &height, &bpp, 3);

	    cout << "Width length = ";
    	cin >> fixed_W;
    	fixed_H = (float)fixed_W / width * height / 2.0f;

	    PrintImage(rgb_image, width, height, fixed_W, fixed_H);

	    stbi_image_free(rgb_image);
	} else {
		cout << "\"" << fileName << "\"" << " doesn't exist!";
	}

    return 0;
}