#include <opencv2/opencv.hpp>
#include "ThresholdMapCreator.h"
#include "GraphGUI.h"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Format:\n main image.jpg\n";
		exit(-1);
	}
	cv::Mat img = cv::imread(argv[1]);
	if (img.empty())
	{
		return -1;
	}
	std::cout << "Hello! This is a text scanning application!\n Below you can see some instructions:\n";
	std::cout << "Press 'q' to exit\nPress 'Enter' to show the result\nPress 's' to save the result" << std::endl;
	GraphGUI gui(img);
	gui.imageProcessing();
	return 0;
}