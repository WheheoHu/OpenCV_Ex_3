#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include "Noise.h"
#include "NR.h"

using namespace std;
using namespace cv;
int main() {
	Mat img_origin = imread("test.jpg");
	Mat img_gray;
	cvtColor(img_origin, img_gray, COLOR_RGB2GRAY);
	imshow("Origin", img_origin);
	imshow("Gray", img_gray);

	Mat img_SaltNoise = Noise().AddSaltNoise(img_gray, 2000);
	Mat img_GaussianNoise = Noise().AddGaussianNoise(img_gray, 1, 0.5);
	imshow("SaltNoise", img_SaltNoise);
	imshow("GaussianNoise", img_GaussianNoise);

	Mat img_NR_avg = NR(img_SaltNoise).averageFiltering();
	imshow("NR_avg", img_NR_avg);
	waitKey();

}