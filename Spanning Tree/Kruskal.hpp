#pragma once
#include "Graph.hpp"
#include "DisjointSet.hpp"

std::vector<std::pair<double, edge>> Kruskal(const Graph & graph);
size_t indexer(std::vector<size_t>& idxr, size_t id);