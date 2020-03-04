#include <iostream>
#include <vector>

using namespace std;

template<typename Element = int>
class Node
{
public:
    enum Color { white, gray, black };

    // Properties

    int color;
    Element element;

    // Constructors
    
    Node(int color, Element element) :
        color(color), element(element) {}

    Node(Element element) : Node(Color::white, element) {}
    Node(Color color) : Node(color, Element()) {}
    Node() : Node(Color::white) {}

    // Functions

    void reset()
    {
        color = Color::white;
        element = Element();
    }
};

class Edge
{
public:
    // Properties

    int node0;
    int node1;
    int color;

    // Constructors
    
    Edge(int node0, int node1, int color) : node0(node0), node1(node1), color(color) {}
    Edge(int node0, int node1) : Edge(node0, node1, 0) {}
    Edge() : Edge(-1, -1) {}

    // Functions

    bool exists()
    {
        return node0 >= 0 && node1 >= 0;
    }
};

template<typename Element = int>
class Graph
{
public:
    typedef Node<Element> GraphNode;
    typedef vector<GraphNode> GraphNodes;
    typedef vector<Edge> GraphEdges;
    typedef vector<GraphEdges> GraphMatrix;

    // Properties

    GraphNodes nodes;
    GraphMatrix matrix;
    int numVertices;

    // Constructors
    
    Graph(int numVertices, Element defaultValue) : numVertices(numVertices)
    {
        nodes = GraphNodes(numVertices);
        matrix = GraphMatrix(numVertices);

        for (size_t i = 0; i < numVertices; i++)
            matrix[i] = GraphEdges(numVertices);
    }

    // Functions

    GraphEdges& getEdges(int line)
    {
        return matrix[line];
    }

    Edge& getEdge(int line, int column)
    {
        return getEdges(line)[column];
    }

    void createEdge(int line, int column)
    {
        getEdges(line)[column] = Edge(line, column);
    }

    void resetGraph()
    {
        for (auto &&node : nodes) node.reset();
    }

    void print()
    {
        if (numVertices > 0)
        {
            for (size_t i = 0; i < numVertices; i++)
            {
                cout << getEdge(i, 0).exists() ? "1" : "0";

                for (size_t j = 1; j < numVertices; j++)
                {
                    cout << " " << getEdge(i, j).exists() ? "1" : "0";
                }

                cout << endl;
            }
        }
    }

    int depthFirstSearchR(int initialVertex)
    {
        int maxComponentSize = 0, componentSize;

        for (size_t i = 0; i < numVertices; i++)
        {
            if (nodes[i].color == GraphNode::Color::white)
            {
                //
            }
        }

        return maxComponentSize;
    }

    int depthFirstSearch()
    {
        int maxComponentSize = 0, componentSize;

        for (size_t i = 0; i < numVertices; i++)
        {
            componentSize = depthFirstSearchR(i);
            if (componentSize > maxComponentSize) componentSize = maxComponentSize;
        }

        return maxComponentSize;
    }
};

int main()
{
    int numOfTestCases, numOfCitizens, numOfPairs, citizen0, citizen1;
    cin >> numOfTestCases;

    for (size_t i = 0; i < numOfTestCases; i++)
    {
        cin >> numOfCitizens >> numOfPairs;
        Graph<> graph(numOfCitizens, 0);

        for (size_t i = 0; i < numOfPairs; i++)
        {
            cin >> citizen0 >> citizen1;
            citizen0 -= 1;
            citizen1 -= 1;
            graph.createEdge(citizen0, citizen1);
        }

        graph.print();
        cout << endl;
    }

    return 0;
}
