#pragma once
#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

//Indispensable includes for DirectedGraph class
#include <iostream>
#include <vector>
#include <unordered_map>

class DirectedGraph {
private:
	std::unordered_map<int, std::vector<std::pair<int, float>>> adjList_;

	static const int MIN_NODE_VALUE;
	static const int MAX_NODE_VALUE;
	static const float MAX_WEIGHT;
	static const float MIN_WEIGHT;

public:
	DirectedGraph() noexcept;
	~DirectedGraph() noexcept;

	bool isEmpty() const noexcept;
	size_t getSize() const noexcept;
	std::vector<int> getAllNodes() const noexcept;

	bool containsNode(int node) const;
	bool containsArc(int from, int to) const noexcept;

	void addNode(int node) noexcept;
	void removeNode(int node) noexcept;
	bool addArc(int from, int to, float weight) noexcept;
	bool removeArc(int from, int to, float& removedWeight) noexcept;

	bool getOutgoingArcs(int node, std::vector<std::pair<int, float>>& outgoingArcs) const noexcept;
	bool getIncomingArcs(int node, std::vector<std::pair<int, float>>& incomingArcs) const noexcept;
	int getOutDegree(int node) const noexcept;
	int getInDegree(int node) const noexcept;
};

#endif // DIRECTEDGRAPH_H