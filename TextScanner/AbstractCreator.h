#pragma once
#include <memory>
#include <opencv2/core/mat.hpp>


class AbstractCreator
{
public:
	virtual cv::Mat getThresholdMap(const cv::Mat& mat) = 0;
	virtual ~AbstractCreator() = default;
};

