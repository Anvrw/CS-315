#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>

using namespace std;
struct AdjNode {
    string cityDes;
    int distance;
};


struct NodeProperties {
    string color;
    int dis;
    string predecessor;
};


void addAdjEdge(map<string, vector<AdjNode>> &, string const &, string const &, string const &);

void BFS(map<string, NodeProperties> &, map<string, vector<AdjNode>> &, const string &);

void printPath(map<string, NodeProperties> &, const string &, const string &);

void Dijkstra(map<string, vector<AdjNode>> &, map<string, NodeProperties> &, string const &) ;

int main() {
    int const GRAPHSIZE = 20;
    string data;
    vector<string> romaniaVertices;
    vector<vector<string>> romaniaEdges;
    string line;
    ifstream myFile("RomaniaVertices.txt");
    while (getline(myFile, data)) {
        romaniaVertices.push_back(data);
    }
    ifstream myFile2("RomaniaEdges.txt");
    while (std::getline(myFile2, line)) {
        //string manipulation
        stringstream s_stream(line);
        vector<string> result;
        while (s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ',');
            result.push_back(substr);
        }
        romaniaEdges.push_back(result);
    }
    map<string, vector<AdjNode>> graph;
    for (int i = 0; i < GRAPHSIZE; i++) {
        vector<AdjNode> addedVector;
        graph.try_emplace(romaniaVertices[i], addedVector);
    }
    for (int i = 0; i < romaniaVertices.size(); i++) {
        addAdjEdge(graph, romaniaEdges[i][0], romaniaEdges[i][1], romaniaEdges[i][2]);
        addAdjEdge(graph, romaniaEdges[i][1], romaniaEdges[i][0], romaniaEdges[i][2]);
    }
    map<string, NodeProperties> graphProperties;
    for (auto const &romaniaVertice: romaniaVertices) {
        NodeProperties addedProperties;
        addedProperties.color = "white";
        addedProperties.dis = 10000;
        addedProperties.predecessor = "";

        graphProperties.try_emplace(romaniaVertice, addedProperties);
    }
//    for (int i = 0; i < 20; i++) {
//        cout << romaniaVertices[i] << ": ";
//        for (auto itr = graph[romaniaVertices[i]].begin(); itr != graph[romaniaVertices[i]].end(); ++itr)
//            cout << itr->cityDes << " ";
//        cout << "\n";
//    }
//    BFS(graphProperties, graph, "Arad");
    Dijkstra(graph, graphProperties, "Arad");
    printPath(graphProperties, "Arad", "Dobreta");

    return 0;

}

void addAdjEdge(map<string, vector<AdjNode>> &graph, string const &srcName, string const &desName, string const &dis) {

    AdjNode addedNode;
    addedNode.cityDes = desName;
    addedNode.distance = stoi(dis);
    graph[srcName].push_back(addedNode);
}

void BFS(map<string, NodeProperties> &graphProperties, map<string, vector<AdjNode>> &graph, const string &start) {
    queue<string> nodeQueue;
    graphProperties[start].color = "gray";
    graphProperties[start].dis = 0;
    graphProperties[start].predecessor = "";
    nodeQueue.push(start);
    while (!nodeQueue.empty()) {
        string top = nodeQueue.front();
        nodeQueue.pop();
        for (auto itr = graph[top].begin(); itr != graph[top].end(); ++itr) {
            if (graphProperties[itr->cityDes].color == "white") {
                graphProperties[itr->cityDes].color = "gray";
                graphProperties[itr->cityDes].dis = graphProperties[top].dis + 1;
                graphProperties[itr->cityDes].predecessor = top;
                nodeQueue.push(itr->cityDes);
            }
        }

    }
}

void printPath(map<string, NodeProperties> &graphProperties, const string &start, const string &end) {
    if (start == end)
        cout << end;
    else if (graphProperties[end].predecessor == "")
        cout << "no path";
    else {
        printPath(graphProperties, start, graphProperties[end].predecessor);
        cout << end << " ";
    }

}

void Dijkstra(map<string, vector<AdjNode>> &graph, map<string, NodeProperties> &graphProperties, string const &start) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    map<string, bool> isProcessed;
    map<string, int> weight;
    string current;
    for (auto itr = graph.begin(); itr != graph.end(); ++itr) {
        pq.push(make_pair(100000, itr->first));
        isProcessed.try_emplace(itr->first, false);
        graphProperties[itr->first].predecessor="";
        weight.try_emplace(itr->first, 100000);
    }
    weight[start]=0;
    pq.push(make_pair(0, start));
    while (!pq.empty()) {
        current = pq.top().second;
        pq.pop();
        string adjNode;
        if (!isProcessed[current]){
            for (auto itr = graph[current].begin(); itr != graph[current].end(); ++itr) {
                adjNode=itr->cityDes;
                int currentToAdj=weight[current]+itr->distance;
                if(weight[adjNode] > currentToAdj){
                    weight[adjNode]= currentToAdj;
                    graphProperties[adjNode].predecessor=current;
                }
                pq.push(make_pair(currentToAdj,adjNode));
            }
            isProcessed[current]=true;
        }
    }
}
//void relax(map<string, vector<AdjNode>> &graph, string current, )

//void maxHeapify(vector<NodeDijkstra>& heap, int current, int size) {
//    int left = current * 2 + 1;
//    int right = current * 2 + 2;
//    int smallest = current;
//    if ((left < size) && (heap[left].dis < heap[current].dis))
//        smallest = left;
//    if ((right < size) && (heap[right].dis < heap[smallest].dis))
//        smallest = right;
//    if (smallest != current) {
//        std::swap(heap[smallest], heap[current]);
//        maxHeapify(heap, smallest, size);
//    }
//}
//
//void buildPriorityQueue(vector<NodeDijkstra>& heap, int size) {
//    for (int i = ((size - 2) / 2); i > -1; i--) {
//        maxHeapify(heap, i, size);
//    }
//}
//NodeDijkstra extractMin(vector<NodeDijkstra>& queue){
//    NodeDijkstra returnValue = queue[0];
//    int size = queue.size();
//    std::swap(queue[0], queue[size-1]);
//    size--;
//    maxHeapify(queue, 0, size);
//}