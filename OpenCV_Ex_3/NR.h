#pragma once
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class NR
{

public:
	Mat averageFiltering();
	Mat MidFiltering();
	Mat KNNFiltering();
	NR(Mat srcimage);
	~NR();
private:
	Mat srcImage;
	int	avgcore(int, int, Mat inputMat);
	int midOf9(int,int,Mat inputMat);
	int KNN(int K,int ,int,Mat inputMat);
};

