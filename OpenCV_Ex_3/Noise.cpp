#include "Noise.h"
#include <random>


Mat Noise::AddSaltNoise(Mat inputimg, int n)
{
	Mat res_img = inputimg.clone();
	for (int i = 0; i < n; i++)
	{
		int rand_row = rand() % inputimg.rows;
		int rand_col = rand() % inputimg.cols;
		if (inputimg.channels() == 1)
		{
			res_img.at<uchar>(rand_row, rand_col) = rand() % 90;
		}

	}

	for (int i = 0; i < n; i++)
	{
		int rand_row = rand() % inputimg.rows;
		int rand_col = rand() % inputimg.cols;
		if (inputimg.channels() == 1)
		{
			res_img.at<uchar>(rand_row, rand_col) = rand() % 75 + 180;
		}

	}

	return res_img;
}

Mat Noise::AddGaussianNoise(Mat inputimg, double mu, double sigma)
{
	Mat res_img = inputimg.clone();
	default_random_engine gen;
	normal_distribution<double> GaussianNoise(mu, sigma);
	int img_row = res_img.rows;
	int img_col = res_img.cols;
	for (int row = 0; row < img_row; row++)
	{
		for (int col = 0; col < img_col; col++)
		{
			int val = res_img.at<uchar>(row, col) + GaussianNoise(gen) * 30;
			val = (val < 0) ? 0 : val;
			val = (val > 255) ? 255 : val;
			res_img.at<uchar>(row, col) = val;
		}


	}

	return res_img;
}

Noise::Noise()
{
}


Noise::~Noise()
{
}
