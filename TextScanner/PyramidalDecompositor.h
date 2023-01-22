#pragma once
#include "AbstractDecompositor.h"

class PyramidalDecompositor final : public AbstractDecompositor
{
private:
	cv::Mat compress(const cv::Mat& mat, const AbstractPolicy<uchar>& policy);

public:
	std::vector<SubMat> decompose(const cv::Mat& mat, const AbstractPolicy<uchar>& policy) override;
	~PyramidalDecompositor() = default;
};