#include "GraphController.h"

void GraphController::resizeTrackbarHandler(int pos, void* user)
{
	const auto usr = static_cast<GraphData*>(user);
	usr->resizeImg(static_cast<double>(pos));
}

void GraphController::contrastTrackbarHandler(int pos, void* user)
{
	const auto usr = static_cast<GraphData*>(user);
	usr->setContrast(pos);
}

void GraphController::alphaTrackbarHandler(int pos, void* user)
{
	const auto usr = static_cast<GraphData*>(user);
	usr->setAlpha(pos);
}

void GraphController::betaTrackbarHandler(int pos, void* user)
{
	const auto usr = static_cast<GraphData*>(user);
	usr->setBeta(pos);
}
