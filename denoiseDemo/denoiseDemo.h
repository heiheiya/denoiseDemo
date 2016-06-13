#ifndef _DENOISE_DEMO_H_
#define _DENOISE_DEMO_H_

#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;

class DenoiseDemo
{
public:
	DenoiseDemo();
	~DenoiseDemo();

public:
	bool denoise(Mat& input, Mat& guide, Mat& output,int mode);

private:

};

#endif//_DENOISE_DEMO_H_