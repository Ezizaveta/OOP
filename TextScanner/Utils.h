#pragma once
#include <opencv2/imgproc.hpp>

namespace channels
{
	static cv::Mat getYchannel(const cv::Mat& mat)
	{
		cv::Mat yCrCb, channels[3];
		cv::cvtColor(mat, yCrCb, cv::COLOR_BGR2YCrCb);
		cv::split(yCrCb, channels);
		return channels[0].clone();
	}

	static void makeSameChannels(cv::Mat& rhs, cv::Mat& lhs)
	{
		if (rhs.channels() != lhs.channels()) {
			if (rhs.channels() != 1) {
				cv::cvtColor(rhs, rhs, cv::COLOR_BGR2GRAY);
			}
			if (lhs.channels() != 1) {
				cv::cvtColor(lhs, lhs, cv::COLOR_BGR2GRAY);
			}
		}
	}
}
