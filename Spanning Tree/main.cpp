#include "Graph.hpp"
#include "Writer.hpp"
#include "Kruskal.hpp"

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cout << "Can't create MST: not enough args\n";
		exit(-1);
	}
	std::ifstream ifs(argv[1]);

	if (!ifs)
		return 2;
	Graph graph;
	Parser fileParser(ifs);
	graph.fillGraph(fileParser); //fill graph with points from the file
	ifs.close();

	std::ofstream ofs(argv[2]);	//output file
	Writer mstWriter(ofs);		//writer to the output file
	graph.createEdges();		//create all edges in our graph
	mstWriter.writeMSTVector(Kruskal(graph));	//make Kruskal alg and save result to the output file Writer
	
	ofs.close();
	std::cout << "MST is in mst.txt file " << std::endl;

	return 0;
}
