#pragma once
#include <string>
#include "opencv2/highgui.hpp"
#include "GraphController.h"

class GraphController;

template<typename T = int>
class Trackbar final
{
private:
	const std::string name;
	const std::string win_name;
	T current_pos;
	T upper_bound;

public:
	Trackbar(const std::string& _name, const std::string& _win_name, T pos, T ub) : name(_name),
		win_name(_win_name), current_pos(pos), upper_bound(ub) {}
	void setMotionHandler(void * user, void (* func)(int pos, void*))
	{
		cv::createTrackbar(name, win_name, NULL, upper_bound, func, user);
		cv::setTrackbarPos(name, win_name, current_pos);
	}
	T getCurrentPos() const { return current_pos; }
	T getUpperBound() const { return upper_bound; }
};