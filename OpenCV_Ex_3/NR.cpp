#include "NR.h"

#include <vector>
#include <unordered_map>
#include <unordered_set>
Mat NR::averageFiltering()
{

	Mat res_img = srcImage.clone();
	if (!res_img.data)
	{
		return res_img;
	}
	auto img_row = res_img.rows;
	auto img_col = res_img.cols;
	for (int col = 0; col < img_col; col++)
	{
		for (int row = 0; row < img_row; row++)
		{
			if (row > 0 && col > 0 && row < img_row - 1 && col < img_col - 1)
			{
				res_img.at<uchar>(Point(col, row)) = avgcore(col, row, res_img);
				//res_img.at<uchar>(Point(row, col)) = res_img.at<uchar>(Point(row, col));

			}
			else
			{
				res_img.at<uchar>(Point(col, row)) = res_img.at<uchar>(Point(col, row));
			}
		}
	}


	return res_img;
}

Mat NR::MidFiltering()
{
	Mat res_img = srcImage.clone();
	if (!res_img.data)
	{
		return res_img;
	}
	auto img_row = res_img.rows;
	auto img_col = res_img.cols;
	for (int col = 0; col < img_col; col++)
	{
		for (int row = 0; row < img_row; row++)
		{
			if (row > 0 && col > 0 && row < img_row - 1 && col < img_col - 1)
			{
				res_img.at<uchar>(col, row) = midOf9(col, row, res_img);
				//res_img.at<uchar>(Point(row, col)) = res_img.at<uchar>(Point(row, col));

			}
			else
			{
				res_img.at<uchar>(Point(col, row)) = res_img.at<uchar>(Point(col, row));
			}
		}
	}

	return res_img;
}

Mat NR::KNNFiltering()
{
	Mat res_img = srcImage.clone();
	if (!res_img.data)
	{
		return res_img;
	}
	auto img_row = res_img.rows;
	auto img_col = res_img.cols;
	for (int col = 0; col < img_col; col++)
	{
		for (int row = 0; row < img_row; row++)
		{
			if (row > 0 && col > 0 && row < img_row - 1 && col < img_col - 1)
			{
				res_img.at<uchar>(col, row) = KNN(5, col, row, res_img);
				//res_img.at<uchar>(Point(row, col)) = res_img.at<uchar>(Point(row, col));

			}
			else
			{
				res_img.at<uchar>(Point(col, row)) = res_img.at<uchar>(Point(col, row));
			}
		}
	}

	return res_img;
}

NR::NR(Mat _srcimage)
{
	srcImage = _srcimage;
}



NR::~NR()
{
}

int NR::avgcore(int col, int row, Mat inputMat)
{
	vector<Point> pointround;
	pointround.push_back(Point(col - 1, row));
	pointround.push_back(Point(col - 1, row - 1));
	pointround.push_back(Point(col - 1, row + 1));
	pointround.push_back(Point(col, row - 1));
	pointround.push_back(Point(col, row + 1));
	pointround.push_back(Point(col + 1, row));
	pointround.push_back(Point(col + 1, row + 1));
	pointround.push_back(Point(col + 1, row - 1));

	int sumval = 0;
	for (auto &it : pointround)
	{
		sumval += inputMat.at<uchar>(it);
	}

	return sumval / 8;
}

int NR::midOf9(int col, int row, Mat inputMat)
{
	vector<int> pixel_data;
	pixel_data.push_back(inputMat.at<uchar>(col, row));
	pixel_data.push_back(inputMat.at<uchar>(col - 1, row + 1));
	pixel_data.push_back(inputMat.at<uchar>(col - 1, row));
	pixel_data.push_back(inputMat.at<uchar>(col - 1, row - 1));
	pixel_data.push_back(inputMat.at<uchar>(col, row + 1));
	pixel_data.push_back(inputMat.at<uchar>(col, row - 1));
	pixel_data.push_back(inputMat.at<uchar>(col + 1, row + 1));
	pixel_data.push_back(inputMat.at<uchar>(col + 1, row));
	pixel_data.push_back(inputMat.at<uchar>(col + 1, row - 1));

	sort(pixel_data.begin(), pixel_data.end());
	return pixel_data.at(4);
}

int NR::KNN(int K, int col, int row, Mat inputMat)
{
	int NN_target = inputMat.at<uchar>(col, row);
	vector<int> pixel_data;
	pixel_data.push_back(inputMat.at<uchar>(col - 1, row + 1));
	pixel_data.push_back(inputMat.at<uchar>(col - 1, row));
	pixel_data.push_back(inputMat.at<uchar>(col - 1, row - 1));
	pixel_data.push_back(inputMat.at<uchar>(col + 1, row + 1));
	pixel_data.push_back(inputMat.at<uchar>(col + 1, row));
	pixel_data.push_back(inputMat.at<uchar>(col + 1, row - 1));
	pixel_data.push_back(inputMat.at<uchar>(col, row + 1));
	pixel_data.push_back(inputMat.at<uchar>(col, row - 1));

	sort(pixel_data.begin(), pixel_data.end(), [&](int a, int b)->bool {
		return (abs(a - NN_target) < abs(b - NN_target));
	});

	int sum = 0;
	for (int i = 0; i < K; i++)
	{
		sum += pixel_data.at(i);
	}


	return sum / 5;
}
