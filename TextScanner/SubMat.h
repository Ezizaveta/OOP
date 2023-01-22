#pragma once
#include <vector>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

class SubMat final
{
private:
	cv::Mat mat;
	int lvl = 0;
public:
	SubMat(cv::Mat _mat, int _lvl) : mat(_mat), lvl(_lvl) {}
	const cv::Mat& getMat() const { return mat; };
	int getLevel() const {	return lvl; };
};