#include "ThresholdMapCreator.h"

cv::Mat ThresholdMapCreator::getThresholdMap(const cv::Mat& mat, threshold_types type)
{
    auto threshold_map = creators[type]->getThresholdMap(mat);
    return threshold_map;
}
