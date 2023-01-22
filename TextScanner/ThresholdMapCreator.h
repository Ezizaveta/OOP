#pragma once
#include "AbstractCreator.h"
#include "SubMat.h"
#include "PyramidalCreator.h"
#include <map>

enum threshold_types {
	//expand if necessary
	Pyramidal
};


class ThresholdMapCreator final
{
private:
	std::map<threshold_types, std::shared_ptr<AbstractCreator>> creators
	{
		{Pyramidal, std::shared_ptr<AbstractCreator>(new PyramidalCreator())},
	};
public:
	ThresholdMapCreator() = default;
	cv::Mat getThresholdMap(const cv::Mat& mat, threshold_types type = threshold_types::Pyramidal);
};
