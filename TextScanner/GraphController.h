#pragma once
#include <memory>
#include <map>

#include "GraphData.h"
#include "Trackbar.h"


class GraphController final
{
private:
	std::shared_ptr<GraphData> model;
	std::map<std::string, std::shared_ptr<Trackbar<int>>> trackbars;
	
public:
	GraphController(std::shared_ptr<GraphData> _model, std::map<std::string, std::shared_ptr<Trackbar<int>>>& _trackbars) :
		model(_model), trackbars(_trackbars)
	{
		trackbars["size"]->setMotionHandler(model.get(), &resizeTrackbarHandler);
		trackbars["contrast"]->setMotionHandler(model.get(), &contrastTrackbarHandler);
		trackbars["alpha"]->setMotionHandler(model.get(), &alphaTrackbarHandler);
		trackbars["beta"]->setMotionHandler(model.get(), &betaTrackbarHandler);
	}

	static void resizeTrackbarHandler(int pos, void* user);
	static void contrastTrackbarHandler(int pos, void* user);
	static void alphaTrackbarHandler(int pos, void* user);
	static void betaTrackbarHandler(int pos, void* user);

	~GraphController() = default;
};