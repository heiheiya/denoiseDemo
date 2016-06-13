#include "filter/opencv2/ximgproc.hpp"
#include "denoiseDemo.h"

DenoiseDemo::DenoiseDemo()
{

}

DenoiseDemo::~DenoiseDemo()
{

}

bool DenoiseDemo::denoise(Mat& input, Mat& guide, Mat& output, int mode /*= 1*/)
{
	if (input.empty())
	{
		return false;
	}

	Mat temp = Mat(input.size(), CV_8UC3);;
	output = Mat(input.size(), CV_8UC3);
	switch (mode)
	{
	case 1:
		boxFilter(input, output, -1, Size(7, 7));
		break;
	case 2:
		GaussianBlur(input, output, Size(7, 7), 1.5);
		break;
	case 3:
		medianBlur(input, output, 7);
		break;
	case 4:
		bilateralFilter(input, output, 7, 75, 75);
		break;
	case 5:
		ximgproc::weightedMedianFilter(guide, input, output, 7, 1.5);
		break;
	case 6:
		ximgproc::jointBilateralFilter(guide, input, output, 7, 0.1, 3);
		break;
	case 7:
		ximgproc::dtFilter(guide, input, output, 10, 5, ximgproc::DTF_NC, 3);
		break;
	case 8:
		//ximgproc::amFilter(guide, input, output, 24,0.2);

		//ximgproc::guidedFilter(guide, input, output, 9, 0.1);
		break;
	default:
		boxFilter(input, output, -1, Size(11, 11));
		break;
	}

	//Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	//cv::filter2D(temp, output, temp.depth(), kernel);

	return true;
}
