#pragma once
#include <opencv2/core/mat.hpp>
#include <iostream>

#include "ThresholdMapCreator.h"

class GraphData final
{
	cv::Mat source_img;
	cv::Mat resized_img;
	cv::Mat thresholded_img;
	std::shared_ptr<ThresholdMapCreator> map_creator;

	int contrast = 6;
	int alpha = 50;
	int beta = 50;

	int max_alpha = 100;
	int max_beta = 100;
	double max_size = 100;


public:
	GraphData(const cv::Mat& img) : source_img(img), resized_img(img), thresholded_img(img),
		map_creator(new ThresholdMapCreator()) {};

	const cv::Mat& getSourceImage() const { return source_img; }
	const cv::Mat& getResizedImage() const { return resized_img; }
	const cv::Mat& getThresholdedImage() const { return thresholded_img; };

	void resizeImg(double current_size);
	void setContrast(int new_contrast);
	void setAlpha(int new_alpha);
	void setBeta(int new_beta);

	void improveContrast();
	~GraphData() = default;
};