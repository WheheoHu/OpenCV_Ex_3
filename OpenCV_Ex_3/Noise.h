#pragma once
#include <opencv2/opencv.hpp>
#include <stdlib.h>
using namespace cv;
using namespace std;
class Noise
{
public:
	Mat AddSaltNoise(Mat inputimg, int n);
	Mat AddGaussianNoise(Mat inputimg, double mu, double sigma);
	Noise();
	~Noise();
};

