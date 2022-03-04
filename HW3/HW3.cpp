/*
Homework 3
CS4071 
Authors: Molly V, Mary M, Emily B, Athulya G 
Question 4
*/


#include <iostream>
#include <vector>
#include <set>

using namespace std;


vector<bool> visited; // global variable visited, to be used in DFS and Connected Components function
vector<int> comp; // global variable vector for component function, stores the different components 

struct Node
{// each Node has a value and a pointer to the Next node as in a linked list 
    int value;
    Node* next;
};

class Graph
{
private:

    int numNodes;
    Node** head;
    vector<vector<int>> edge;

    Node* createNode(int value, Node* head) //private function to make creation of new nodes easier
    {
        Node* newN = new Node;
        newN->value = value;
        newN->next = head;
        return newN;
    }

public:

    Graph(vector<vector<int>>edges, int numN) //constructor 
    {
        this->numNodes = numN;
        this->edge = edges;

        head = new Node * [numN]();

        for (int i = 0; i < numN; i++)
        {
            head[i] = nullptr;
        }
        for (int k = 0; k < edge.size(); k++)
        {   
            Node* newNode = createNode(edge[k][1], head[edge[k][0]]);
            head[edge[k][0]] = newNode;
            Node* newNode2 = createNode(edge[k][0], head[edge[k][1]]); //creating all nodes for undirected graph 
            head[edge[k][0]]->next = newNode2; 
        }
        
    }

    ~Graph() //destructor, to delete all arrays 
    {
        for (int i = 0; i < numNodes; i++)
        {
            delete[] head[i];
        }
        delete[] head;
    }
    

    void addEdge(int source, int destination) //function to add an edge to the graph
    {
        for (int i = 0; i < numNodes; i++)
        {
            if (head[i]->value == source)
            {
                Node* temp = head[i];
                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                Node* newN = new Node;
                newN->value = destination;
                newN->next = nullptr;
                temp->next = newN;
            }
        }
    }

    void deleteEdge(int source, int destination) //function to delete a pre-existing edge 
    {
        for (int i = 0; i < numNodes; i++)
        {
            if (head[i]->value == source)
            {
                Node* temp = head[i];
                while (temp->value == destination)
                {
                    temp = temp->next;
                }
                temp->next = temp->next->next;
                delete temp;
            }
        }
    }

    int getNumNodes()
    { // returns total number of nodes from a class 
        return numNodes;
    }

    void printAdjList() //prints the adjacency list 
    {
        for (int i = 0; i < numNodes; i++)
        {
            cout << i << "--->";
            while (head[i] != NULL)
            {
                cout << head[i]->value << "   ";
                head[i] = head[i]->next; 
            }
            cout << endl;
        } 

    }


    vector<vector<int>> createAdjMatrix() //creates an adjacency matrix 
    {

        vector<vector<int>> matrix(numNodes, vector<int>(numNodes, 0));

        for (int k = 0; k < edge.size(); k++)
        {
            matrix[edge[k][0]][edge[k][1]] = 1;
            matrix[edge[k][1]][edge[k][0]] = 1;
        }

        return matrix;
    } 

    void printAdjMatrix() //prints out adjacency matrix 
    {
        vector<vector<int>> matrix = createAdjMatrix(); 
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                cout << matrix[i][j] << "  ";
            }
            cout << endl; 
        }
    } 

};

void DFS(Graph g, int v) //depth first search function 
{
    vector<vector<int>> adj = g.createAdjMatrix();
    cout << v << " "; 
    visited[v] = true;

    for (int i = 0; i < adj[v].size(); i++) {

        if (!visited[i]) {
            DFS(g, i);
        }
        else
        {
            continue;
        }
        
    } 
    return; 
}

void Components(Graph g) // outputs all the individual components in different lines, uses DFS funciton above
{

    for (int i = 0; i < g.getNumNodes(); i++)
    {
        visited.push_back(false); 
    }
    for (int k = 0; k < g.getNumNodes(); k++)
    {
        cout << endl;
        if (visited[k] == false)
        {
            
            cout << "Connected component is: ";
            cout << "{";
            cout << "hi";
            DFS(g, k);
            cout << "No"; 
            cout<< "}"; 
        }
    }
 

}



int main() // main function, focuses on user interface 
{
    cout << "Welcome to solution for Problem 4 on Homework 3!" << endl<<endl;
    cout << "Please enter the number of vertices you would like to see on your graph: ";
    int numV;
    cin >> numV; 
    vector<int> connections = {}; 
    int num=0;
    cout <<endl<< "Enter the values that you want in your graph.\nEnter even number of values.\nStop with -1\nPlease keep the values between 0 and " << numV << "!" << endl;
    while (num != -1)
    {
        cout <<endl<< "Enter new number: ";
        cin >> num;
        if (num == -1)
        {
            continue;
        }
        connections.push_back(num); 
    }
    vector<int> vertices;
    for (int i = 0; i < numV; i++)
    {
        vertices.push_back(i); 
    }
    vector<vector<int>> edges;  //creating a vector of vectors of edges in the graph in the form {..{start,destination},..}
    vector<int> temp; 
    for (int j = 0; j < connections.size(); j = j + 2)
    {
        temp.push_back(connections[j]); 
        temp.push_back(connections[j + 1]);
        edges.push_back(temp);
        temp.clear(); 
    }

    Graph graph(edges, numV);
    cout << endl << "Here is the adjacency matrix of the graph: " << endl<<endl; 
    graph.printAdjMatrix(); 
    cout << endl << endl;
    Components(graph); 
    
}

