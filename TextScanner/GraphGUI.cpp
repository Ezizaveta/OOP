#include "GraphGUI.h"

void GraphGUI::imageProcessing()
{
	bool repeat = true;
	while (repeat) {
		const int key = cv::waitKey();
		switch (key)
		{
			case 113: // 'q'
				repeat = false;
				break;
			case 13: // enter
				showImage();
				break;
			case 115: // 's'
				std::string result_name;
				std::cout << "Enter the file name with format:\n";
				std::cin >> result_name;
				cv::imwrite(result_name, model->getThresholdedImage());
				std::cout << "result is saved!" << std::endl;
				break;
		}
	}
}

void GraphGUI::showImage()
{
	model->improveContrast();
	cv::Mat double_img;
	cv::hconcat(model->getResizedImage(), model->getThresholdedImage(), double_img);
	cv::imshow(result_win, double_img);
}
