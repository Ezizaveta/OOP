#include "PyramidalCreator.h"

cv::Mat PyramidalCreator::getThresholdMap(const cv::Mat& mat)
{
	auto source = mat.clone();
	if (mat.channels() != 1) {
		source = channels::getYchannel(mat);
	}

	MinPolicy<uchar> min_policy;
	MaxPolicy<uchar> max_policy;
	AveragePolicy<uchar> average_policy;
	auto mins_async = std::async(std::launch::async, std::mem_fn(&(AbstractDecompositor::decompose)),
		decompositor, std::ref(source), std::ref(min_policy));
	auto maxs_async = std::async(std::launch::async, std::mem_fn(&(AbstractDecompositor::decompose)),
		decompositor, std::ref(source), std::ref(max_policy));
	auto avers_async = std::async(std::launch::async, std::mem_fn(&(AbstractDecompositor::decompose)),
		decompositor, std::ref(source), std::ref(average_policy));

	mins_async.wait();
	maxs_async.wait();
	avers_async.wait();

	auto mins_pyramid = mins_async.get();
	auto maxs_pyramid = maxs_async.get();
	auto avers_pyramid = avers_async.get();

	cv::Mat threshold_map = avers_pyramid.back().getMat().clone();
	const int lvl = avers_pyramid.back().getLevel() - 1;
	int rough_lvl = 3; 	
	for (int i = lvl; i >= rough_lvl; i--) {
		auto& min = mins_pyramid[i].getMat();
		auto& max = maxs_pyramid[i].getMat();
		auto& average = avers_pyramid[i].getMat();
		cv::resize(threshold_map, threshold_map, min.size(), 0, 0, 1);
		for (int y = 0; y < threshold_map.rows; y++) {
			for (int x = 0; x < threshold_map.cols; x++) {
				if ((max.at<uchar>(y, x) - min.at<uchar>(y, x)) >= 10) {
					threshold_map.at<uchar>(y, x) = average.at<uchar>(y, x);
						// + max.at<uchar>(y, x) + min.at<uchar>(y, x)) / 3;
				}
			}
		}
	}
	cv::resize(threshold_map, threshold_map, source.size(), 0, 0, 1);
	return threshold_map;
}
