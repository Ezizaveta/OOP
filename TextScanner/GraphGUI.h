#pragma once
#include <memory>
#include <opencv2/opencv.hpp>
#include "GraphController.h"


class GraphGUI final
{
private:
	std::shared_ptr<GraphData> model;
	std::shared_ptr<GraphController> controller;
	std::map<std::string, std::shared_ptr<Trackbar<int>>> trackbars;
	const cv::String result_win = "Result";
	const cv::String parameters_win = "Parameters";

	void clearWin(const cv::String& win_name, int property_id)
	{
		if (cv::getWindowProperty(win_name, property_id)) {
			cv::destroyWindow(win_name);
		}
	}

public:
	GraphGUI(const cv::Mat& src_img)
	{
		model = std::shared_ptr<GraphData>(new GraphData(src_img));
		cv::namedWindow(result_win, cv::WINDOW_AUTOSIZE);
		cv::namedWindow(parameters_win, cv::WINDOW_AUTOSIZE);
		trackbars.insert({ "size", std::shared_ptr<Trackbar<int>>
			(new Trackbar<int>("size", parameters_win, 50, 100)) });

		trackbars.insert({ "contrast", std::shared_ptr<Trackbar<int>>
			(new Trackbar<int>("contrast", parameters_win, 10, 100)) });

		trackbars.insert({ "alpha", std::shared_ptr<Trackbar<int>>
			(new Trackbar<int>("alpha", parameters_win, 50, 100)) });

		trackbars.insert({ "beta", std::shared_ptr<Trackbar<int>>
			(new Trackbar<int>("beta", parameters_win, 50, 100)) });

		controller = std::shared_ptr<GraphController>(new GraphController(model, trackbars));
	}
	void imageProcessing();
	~GraphGUI()
	{
		clearWin(result_win, cv::WND_PROP_VISIBLE);
		clearWin(parameters_win, cv::WND_PROP_VISIBLE);
	};
	void showImage();
};