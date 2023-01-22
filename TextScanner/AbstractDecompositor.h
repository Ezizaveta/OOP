#pragma once
#include <opencv2/core/mat.hpp>

#include "SubMat.h"
#include "Policies.h"

class AbstractDecompositor
{
public:
	virtual std::vector<SubMat> decompose(const cv::Mat& mat, const AbstractPolicy<uchar>& policy) = 0;
	virtual ~AbstractDecompositor() = default;
};