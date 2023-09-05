//Includes for unit tests only
#include <cstdlib>
#include <ctime>
#include <cassert>

//Include for DirectedGraph class
#include "DirectedGraph.h"

int main() {
	DirectedGraph graph;

	////////////////////////////////////////////
	// Tests for isEmpty, getSize & getAllNodes methods
	assert(graph.isEmpty()); // The graph is initially empty
	assert(graph.getSize() == 0); // The graph has initially no nodes

	auto allNodes = graph.getAllNodes();
	assert(allNodes.size() == 0); // The graph has initially zero nodes

	////////////////////////////////////////////
	// Valid Input Tests for addNode method

	for (int i = 0; i < 10; ++i) {
		graph.addNode(i);
	}
	assert(!graph.isEmpty()); // The graph is not empty
	assert(graph.getSize() == 10); // The graph has 10 nodes now

	allNodes = graph.getAllNodes();
	assert(allNodes.size() == 10); // The graph has 10 nodes now

	//Invalid Input Tests for addNode method
	graph.addNode(-1);
	graph.addNode(2000);

	assert(graph.getSize() == 10); // The graph still has 10 nodes

	////////////////////////////////////////////
	// Valid Input Tests for containsNode method
	assert(graph.containsNode(1)); // Node 1 should exist in the graph
	assert(graph.containsNode(2)); // Node 2 should exist in the graph

	// Invalid Input Tests for containsNode method
	assert(!graph.containsNode(-1)); // Node 0 cannot exist in the graph
	assert(!graph.containsNode(15)); // Node 3 should not exist in the graph

	////////////////////////////////////////////
	// Valid & Invalid Input Tests for removeNode method

	graph.removeNode(0);
	assert(!graph.containsNode(0)); // Node 0 should not exist in the graph
	graph.removeNode(15);
	assert(graph.getSize() == 9); // The graph now has 9 nodes

	////////////////////////////////////////////
	// Valid Input Tests for addArc and containsArc

	// Add a valid arc with a positive weight
	assert(graph.addArc(1, 2, 0.5f));
	assert(graph.containsArc(1, 2));

	// Add an arc with a weight at the maximum allowed limit
	assert(graph.addArc(2, 3, 1.0f));
	assert(graph.containsArc(2, 3));

	// Add an arc with a weight at the minimum allowed limit
	assert(graph.addArc(3, 4, -1.0f));
	assert(graph.containsArc(3, 4));

	// Invalid Input Tests for addArc and containsArc

	// Add an arc from a non-existing node
	assert(!graph.addArc(15, 1, 0.7f));
	assert(!graph.containsArc(15, 1));

	// Add an arc to a non-existing node
	assert(!graph.addArc(1, 16, 0.8f));
	assert(!graph.containsArc(1, 16));

	// Update an arc with a weight exceeding the maximum allowed limit
	assert(!graph.addArc(2, 3, 1.9f));

	////////////////////////////////////////////
	//Valid & Invalid Input Tests for removeArc
	float removedWeight{};

	//removeArc returns through its parameter weight of an removed arc
	assert(graph.removeArc(1, 2, removedWeight));
	assert(removedWeight == 0.5f);

	//removeArc takes into account an ark direction
	assert(!graph.removeArc(3, 2, removedWeight));

	//There is arc from 2 to 3 node, not vice versa
	assert(graph.removeArc(2, 3, removedWeight));
	assert(removedWeight == 1.0f);

	//There is no arc between 4 and 5 nodes
	assert(!graph.removeArc(4, 5, removedWeight));

	//removeArc with an invalid input does not change removedWeight variable
	assert(removedWeight == 1.0f);
	//There is no arc between 2 and 3 nodes anymore
	assert(!graph.removeArc(2, 3, removedWeight));

	////////////////////////////////////////////
	//Valid & Invalid Input Tests for arc direction methods

	//Add a few more arcs for lates tests
	assert(graph.addArc(9, 1, 0.91f));
	assert(graph.addArc(9, 2, 0.9f));
	assert(graph.addArc(9, 3, 0.9f));

	assert(graph.addArc(4, 8, -0.8f));
	assert(graph.addArc(5, 8, -0.8f));
	assert(graph.addArc(6, 8, -0.8f));
	assert(graph.addArc(7, 8, -0.8f));

	//Valid Input
	std::vector<std::pair<int, float>> arcsContainer;
	assert(graph.getOutgoingArcs(3, arcsContainer));
	assert(arcsContainer.size() == 1);
	assert(graph.getOutDegree(3) == 1);

	assert(graph.getOutgoingArcs(9, arcsContainer));
	assert(arcsContainer.size() == 3);
	assert(graph.getOutDegree(9) == 3);

	assert(graph.getIncomingArcs(4, arcsContainer));
	assert(arcsContainer.size() == 1);
	assert(graph.getInDegree(4) == 1);

	assert(graph.getIncomingArcs(8, arcsContainer));
	assert(arcsContainer.size() == 4);
	assert(graph.getInDegree(8) == 4);

	assert(graph.getOutgoingArcs(1, arcsContainer));
	assert(arcsContainer.size() == 0);
	assert(graph.getOutDegree(1) == 0);

	//Invalid Input

	// getOutgoingArcs & getIncomingArcs clean a given arcs container

	assert(!graph.getOutgoingArcs(10, arcsContainer));
	assert(arcsContainer.size() == 0);
	assert(graph.getOutDegree(10) == -1);

	assert(!graph.getOutgoingArcs(10, arcsContainer));
	assert(arcsContainer.size() == 0);
	assert(graph.getOutDegree(10) == -1);

	assert(!graph.getIncomingArcs(10, arcsContainer));
	assert(arcsContainer.size() == 0);
	assert(graph.getInDegree(10) == -1);

	assert(!graph.getIncomingArcs(10, arcsContainer));
	assert(arcsContainer.size() == 0);
	assert(graph.getInDegree(10) == -1);

	return 0;
}