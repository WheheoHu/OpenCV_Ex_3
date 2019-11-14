#pragma once
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class NR
{

public:
	Mat averageFiltering();
	NR(Mat srcimage);
	~NR();
private:
	Mat srcImage;
	int	avgcore(int, int, Mat inputMat);
};

