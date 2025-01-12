#include <iostream>
#include <cstdint>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <sstream>
#include <limits>

struct Edge
{
    uint16_t  start;
    uint16_t  end;
    uint32_t  weight;
    
    friend std::ostream& operator<<(std::ostream& os, const Edge& edge) 
    {
        os << "{ " << edge.start << "->" << edge.end << " @ " << edge.weight << " }"; // Format the output
        return os;
    }
};

struct Node 
{
    uint16_t ID;
    uint32_t shortestPath;
    std::vector<Edge> OutboundEdges;
    bool visited;
    Node() : shortestPath{std::numeric_limits<uint32_t>::max()}, visited{false} {};
};



int main(int argc, char** argv)
{
    // build graph
    std::vector<Edge> allKnownEdges = { {0, 1, 1}, {0, 2, 50},{1, 2, 1},{2, 5, 1},{5, 1, 1},{1, 3, 15},{2, 4, 1},
                                        {4, 3, 1}, {3, 4, 1}, {3, 5, 2}, {4, 5, 6}};
    

    std::list<Node> nodesPriorityList;
    std::map<uint16_t, Node> nodeMap;

    // convert the table of edges into a map, key is nodeID
    for (const auto &edge : allKnownEdges)
    {
        const uint16_t &startNode = edge.start;
        const uint16_t &endNode = edge.end;
        const uint16_t &weight = edge.weight;

        nodeMap[startNode].OutboundEdges.push_back(edge);
        nodeMap[startNode].ID = startNode;
    }

    // print out the nodeMap
    for (const auto &[keys, values] : nodeMap )
    {
        std::ostringstream oss{};
        oss << keys << " ";
        for (const auto &edge : values.OutboundEdges)
        {
           oss << edge << ",";
        } 
        std::cout << oss.str() << std::endl;
    }
    std::cout << " ~~~~~~~~~~~~~~~~~~" << std::endl;

    // set the first location to distance 0 to source, as it is the source
    nodeMap[0].shortestPath = 0;

    // find the node with the shorted route to source, with visited set False
    // then relax the edges that come out of this node and update scores on the 
    // nodes that can be reached from this "closest to source" node    
    
    while(true)
    {
        uint16_t nodeToProcess = std::numeric_limits<uint16_t>::max();    
        auto currentClosestNode = std::numeric_limits<uint32_t>::max();
        std::cout<< "Search for next node " <<std::endl;

        for (const auto &[keys, values] : nodeMap )
        {
            if (values.visited == false)
            {
                if (values.shortestPath < currentClosestNode) 
                {
                    currentClosestNode = values.shortestPath;
                    nodeToProcess = values.ID;                    
                }
            }
        }        

        if (nodeToProcess == std::numeric_limits<uint16_t>::max()){
            break;
        }
        else{
            std::cout<< "lets process " << std::to_string(nodeToProcess) << std::endl;;
        } 

        if (nodeToProcess != std::numeric_limits<uint16_t>::max())
        {
            std::cout << "Processing Node " << std::to_string(nodeToProcess)<< std::endl;
            auto weightThisNode = nodeMap[nodeToProcess].shortestPath;
            
            for (const auto& edge: nodeMap[nodeToProcess].OutboundEdges)
            {
                auto nodeReached = edge.end;
                auto weight = edge.weight;
                auto impliedWeight = weightThisNode + edge.weight;
                
                if (nodeMap[nodeReached].shortestPath > impliedWeight)
                {
                    nodeMap[nodeReached].shortestPath = impliedWeight;
                }
            }
            nodeMap[nodeToProcess].visited = true;
        }
    }


    // show nodes and shortest path in order
    for (const auto &[keys, values] : nodeMap )
    {
        std::ostringstream oss{};
        oss << keys << " " << values.shortestPath;
        std::cout << oss.str() << std::endl;
    }
    std::cout << " ~~~~~~~~~~~~~~~~~~" << std::endl;
    
    std::cout << "hello world" << std::endl;

    return 0;
}