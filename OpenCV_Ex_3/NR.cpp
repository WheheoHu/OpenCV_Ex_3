#include "NR.h"

#include <vector>

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
				res_img.at<uchar>(Point(col,row)) = avgcore(col, row, res_img);
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
