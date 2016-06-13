#include <sstream>
#include <iomanip>
#include <direct.h>
#include <stdio.h>
#include "denoiseDemo.h"

using namespace std;

const int BUFLEN = 50;
const int FILENUMBER = 1;
const int MODE = 7;
const int LENGTH = 150;
const int FOLDER = 13;

void mkDir(char *path)
{
	int ipathLength = strlen(path);
	int ileaveLength = 0;
	int iCreatedLength = 0;
	char szPathTemp[LENGTH] = { 0 };
	for (int i = 0; (NULL != strchr(path + iCreatedLength, '\\')); i++)
	{
		ileaveLength = strlen(strchr(path + iCreatedLength, '\\')) - 1;
		iCreatedLength = ipathLength - ileaveLength;
		strncpy_s(szPathTemp, path, iCreatedLength);
		_mkdir(szPathTemp);
	}
	if (iCreatedLength < ipathLength)
	{
		_mkdir(path);
	}
}

int main(int argc, char* argv[])
{
	char rgbPath[BUFLEN];
	char guidePath[BUFLEN];
	for (int imageIndex = 1; imageIndex <= FILENUMBER; imageIndex++)
	{
		sprintf_s(rgbPath, BUFLEN, "image/bsp_2016_03_15/pair%d/rcv_fushion.jpg", imageIndex);
		sprintf_s(guidePath, BUFLEN, "image/bsp_2016_03_15/pair%d/rcv_rgb_cop.jpg", imageIndex);
		Mat im1 = imread(rgbPath, -1);
		Mat im2 = imread(guidePath, -1);
		//Mat im1 = imread(argv[1]);
		//Mat im2 = imread(argv[2]);
		//int mode = atoi(argv[3]);
		if (im1.empty() || im2.empty())
		{
			cout << "could not open one of the images..." << endl;
			cout << "the cmd parameters have next current value: " << endl;
			return 1;
		}

		for (int mode = 7; mode <= MODE; mode++)
		{
			char savePath[BUFLEN];

			Mat out;
			float duration0 = static_cast<float>(getTickCount());
			DenoiseDemo test;
			test.denoise(im1, im2, out, mode);
			duration0 = static_cast<float>(getTickCount()) - duration0;
			duration0 /= getTickFrequency();
			cout << "denoise " << mode <<":" << duration0 << " s" << endl;
			//imshow("fusion", out);
			sprintf_s(savePath, BUFLEN, "image/bsp_2016_03_15/pair%d/denoise_%d.jpg", imageIndex, mode);
			imwrite(savePath, out);
			//waitKey(0);

		}
	}
	system("pause");
	return 0;
}