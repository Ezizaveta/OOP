#pragma once
#include <future>
#include "AbstractCreator.h"
#include "PyramidalDecompositor.h"
#include "Utils.h"


class PyramidalCreator final : public AbstractCreator
{
	std::shared_ptr<AbstractDecompositor> decompositor;

public:
	PyramidalCreator(std::shared_ptr<AbstractDecompositor> decomp =
		std::shared_ptr<AbstractDecompositor>(new PyramidalDecompositor())) : decompositor(decomp) {};
	cv::Mat getThresholdMap(const cv::Mat& mat) override;
};