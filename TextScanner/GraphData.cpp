#include "GraphData.h"

void GraphData::resizeImg(double current_size)
{
	cv::resize(source_img, resized_img, cv::Size(), current_size / max_size + 0.1, current_size / max_size + 0.1);
}

void GraphData::setContrast(int new_contrast)
{
	contrast = new_contrast;
}

void GraphData::setAlpha(int new_alpha)
{
	alpha = new_alpha;
}

void GraphData::setBeta(int new_beta)
{
	beta = new_beta;
}

void GraphData::improveContrast()
{
	thresholded_img = map_creator->getThresholdMap(resized_img);
	channels::makeSameChannels(resized_img, thresholded_img);
	cv::addWeighted(resized_img, -static_cast<double>(alpha) / max_alpha, thresholded_img, static_cast<double>(beta) / max_beta, 0, thresholded_img);
	thresholded_img.convertTo(thresholded_img, -1, static_cast<double>(contrast), 0);
	cv::bitwise_not(thresholded_img, thresholded_img);
}
