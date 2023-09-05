#include"DirectedGraph.h"

const int DirectedGraph::MIN_NODE_VALUE = 0;
const int DirectedGraph::MAX_NODE_VALUE = 1000;
const float DirectedGraph::MAX_WEIGHT = 1.0f;
const float DirectedGraph::MIN_WEIGHT = -1.0f;

// Constructor to form an empty graph
DirectedGraph::DirectedGraph() noexcept {}

// Destructor to destroy the graph
DirectedGraph::~DirectedGraph() noexcept {}

// Check if the graph is empty
bool DirectedGraph::isEmpty() const noexcept {
	return adjList_.empty();
}

size_t DirectedGraph::getSize() const noexcept {
	return adjList_.size();
}

//Retrieve a list of all nodes present in the graph
std::vector<int> DirectedGraph::getAllNodes() const noexcept {
	std::vector<int> nodes{};

	for (const auto& entry : adjList_) {
		nodes.push_back(entry.first);
	}
	return nodes;
}

// Check the presence of a given node in the graph
bool DirectedGraph::containsNode(int node) const {
	// Validity check here, for example:

	if (node < MIN_NODE_VALUE || node > MAX_NODE_VALUE) {
		// Node is out of the valid range
		return false;
	}

	return adjList_.find(node) != adjList_.end();
}

// Check the presence of an arc between specified nodes
bool DirectedGraph::containsArc(int from, int to) const noexcept {
	bool isInvalidInput = (
		containsNode(from) == false ||
		containsNode(to) == false);

	if (isInvalidInput) {
		return false;
	}

	for (const auto& neighbor : adjList_.at(from)) {
		if (neighbor.first == to) {
			return true;
		}
	}
	return false;
}

// Include a new node in the graph
void DirectedGraph::addNode(int node) noexcept {
	bool isInvalidInput = containsNode(node) ||
		node < MIN_NODE_VALUE ||
		node > MAX_NODE_VALUE;

	if (isInvalidInput) {
		return;
	}

	adjList_[node] = std::vector<std::pair<int, float>>();
}

// Exclude a node from the graph
void DirectedGraph::removeNode(int node) noexcept {
	if (!containsNode(node)) {
		return;
	}

	adjList_.erase(node);

	auto isArcToRemove = [node](const std::pair<int, float>& arc) {
		return arc.first == node;
	};

	// Remove all arcs pointing to the removed node
	for (auto& [n, neighbors] : adjList_) {
		neighbors.erase(
			std::remove_if(
				neighbors.begin(), neighbors.end(), isArcToRemove),
			neighbors.end());
	}
}

// Include an arc with a given weight between two nodes
// If the arc exists, update its weight
bool DirectedGraph::addArc(int from, int to, float weight) noexcept {
	bool isInvalidInput = (
		containsNode(from) == false ||
		containsNode(to) == false) ||
		weight< MIN_WEIGHT ||
		weight > MAX_WEIGHT;

	if (isInvalidInput) {
		return false;
	}

	for (auto& neighbor : adjList_[from]) {
		if (neighbor.first == to) {
			// Update weight if the arc already exists
			neighbor.second = weight;
			return true;
		}
	}

	// Add the arc if it doesn't exist
	adjList_[from].emplace_back(to, weight);
	return true;
}

// Exclude an arc between given nodes
//with the output of the weight of the arc
bool DirectedGraph::removeArc(
	int from, int to, float& removedWeight) noexcept {
	// Arc not found
	bool isInvalidInput = (
		containsNode(from) == false ||
		containsNode(to) == false);

	if (isInvalidInput) {
		return false;
	}

	auto& neighbors = adjList_[from];
	for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
		if (it->first == to) {
			removedWeight = it->second;
			neighbors.erase(it);
			return true;
		}
	}
	return false;
}

//Retrieve a list of outgoing arcs from a specific node
bool DirectedGraph::getOutgoingArcs(
	int node, std::vector<std::pair<int, float>>& outgoingArcs)
	const noexcept
{
	outgoingArcs.clear();

	if (!containsNode(node)) {
		return false;
	}

	outgoingArcs = adjList_.at(node);

	return true;
}

//Retrieve a list of incoming arcs to a specific node
bool DirectedGraph::getIncomingArcs(int node,
	std::vector<std::pair<int, float>>& incomingArcs)
	const noexcept
{
	incomingArcs.clear();

	if (!containsNode(node)) {
		return false;
	}

	for (const auto& entry : adjList_) {
		for (const auto& arc : entry.second) {
			if (arc.first == node) {
				incomingArcs.emplace_back(entry.first, arc.second);
			}
		}
	}

	return true;
}

//Calculate the out-degree of a specific node
int DirectedGraph::getOutDegree(int node) const noexcept {
	if (!containsNode(node)) return -1; // Node not found
	return static_cast<int>(adjList_.at(node).size());
}

//Calculate the in-degree of a specific node
int DirectedGraph::getInDegree(int node) const noexcept {
	if (!containsNode(node)) return -1; // Node not found
	int inDegree = 0;
	for (const auto& entry : adjList_) {
		for (const auto& arc : entry.second) {
			if (arc.first == node) {
				inDegree++;
			}
		}
	}
	return inDegree;
}