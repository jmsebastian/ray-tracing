#include "Utilitarios.h"
#include "Ray.h"
#include "Point3D.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void savebmp(const char *filename, int w, int h, int dpi, ColorRGB *data)
{
	FILE *f;
	int k = w * h;
	int s = 4 * k;
	int filesize = 54 + s;
	double factor = 39.375;
	int m = static_cast<int>(factor);
	int ppm = dpi * m;

	unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
	unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);

	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s >> 8);
	bmpinfoheader[23] = (unsigned char)(s >> 16);
	bmpinfoheader[24] = (unsigned char)(s >> 24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
	bmpinfoheader[28] = (unsigned char)(ppm >> 24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm >> 8);
	bmpinfoheader[31] = (unsigned char)(ppm >> 16);
	bmpinfoheader[32] = (unsigned char)(ppm >> 24);

	f = fopen(filename, "wb");

	// int res = fopen(&f, filename, "wb");
	// if (res != 0) {
	// 	/* Handle error */
	// }

	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	for (int i = 0; i < k; i++)
	{
		ColorRGB rgb = data[i];
		double red = (data[i].red) * 255;
		double green = (data[i].green) * 255;
		double blue = (data[i].blue) * 255;
		unsigned char color[3] = {(int)floor(blue), (int)floor(green), (int)floor(red)};
		fwrite(color, 1, 3, f);
	}
	fclose(f);
}

ColorRGB getPixelColor(const Ray &ray, vector<GeometricObject *> geometricObjects)
{
	ColorRGB color;
	color.red = 0.0;
	color.green = 0.0;
	color.blue = 0.0;
	double equationRoot;
	double minEquationRoot = 2000000;
	Vector3D normal;
	Point3D q;
	for (int i = 0; i < geometricObjects.size(); i++)
	{
		if (geometricObjects[i]->isImpact(ray, equationRoot, normal, q) && equationRoot < minEquationRoot)
		{
			color.red = geometricObjects[i]->getColor().red;
			color.green = geometricObjects[i]->getColor().green;
			color.blue = geometricObjects[i]->getColor().blue;
			minEquationRoot = equationRoot;
		}
	}
	return color;
}