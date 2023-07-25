/**
 * @file GraphTraversal.cpp
 * @brief This program represents a graph and provides functionality for traversal.
 * @author Stanislav Romanov
 * @date 2008-04-07
 */

#include<iostream>
#include<string>
#include<memory>
using namespace std;

class Graph;
struct Node;

struct Node{
    unique_ptr<Node> next;
    Graph *graph;
    Node() : next(nullptr), graph(nullptr) {}
    Node(Graph *g) : next(nullptr), graph(g) {}

    int countElements(){
        Node *tempNode;
        int i=0;
        tempNode=this;
        while (tempNode->next!=nullptr){
            tempNode=tempNode->next.get();
            i++;
        }
        return i;
    }

    void clear(){
        Node *tempNode;
        while (this->next!=nullptr){
            tempNode=this;
            while(tempNode->next->next!=nullptr)
                tempNode=tempNode->next.get();
            tempNode->next.reset();
        }
    }

    void addNode(Graph *g){
        Node *tempNode;
        tempNode=this;
        while (tempNode->next!=nullptr){
            if (g==tempNode->graph)
                return;
            tempNode=tempNode->next.get();
        }
        if (g==tempNode->graph)
            return;
        tempNode->next.reset(new Node(g));
    }
};

Node nodeList, s2;

class Graph{
    Node connections;
    string vertexName;
    bool n;
    Node associatedNodes;
public:
    friend struct Node;

    Graph(){
        cout<<"Enter vertex name:\n";
        cin>>vertexName;
        n=false;
        connections.next=nullptr;
        connections.graph=this;
    }

    Graph(string vertex){
        vertexName=vertex;
        n=false;
        connections.next=nullptr;
        connections.graph=this;
        associatedNodes.graph=nullptr;
        associatedNodes.next=nullptr;
    }

    void addVertex(){
        Node *tempNode;
        tempNode=&connections;
        string vertex;
        cout<<"Enter vertex name\n";
        cin>>vertex;
        while(tempNode->next!=nullptr){
            if (tempNode->graph->vertexName!=vertex)
                tempNode=tempNode->next.get();
            else
                break;
        }
        if (tempNode->graph->vertexName!=vertex){
            tempNode->next.reset(new Node());
            tempNode=tempNode->next.get();
            tempNode->next=nullptr;
            tempNode->graph=new Graph(vertex);
        }
        else {
            cout<<"Vertex already exists\n";
        }
    }

    void addConnections(Node *nodeList){
        string s;
        cout<<"\nEnter vertices\n";
        cin>>s;
        Node *tempNode;
        Node *z,*p;
        tempNode=&connections;
        while(tempNode!=nullptr){
            if(tempNode->graph->vertexName==s)
                break;
            tempNode=tempNode->next.get();
        }
        if (tempNode==nullptr) {
            cout<<"Vertex not found";
            return;
        }
        nodeList->addNode(tempNode->graph);
        z=nodeList->next.get();
        while(z!=nullptr){
            p=&(z->graph->associatedNodes);
            while(p!=nullptr){
                if(p->graph!=nullptr)
                    nodeList->addNode(p->graph);
                p=p->next.get();
            }
            z=z->next.get();
        }
    }

    void addConnections(Node *nodeList,string s){
        Node *tempNode;
        Node *z,*p;
        tempNode=&connections;
        while(tempNode!=nullptr){
            if(tempNode->graph->vertexName==s)
                break;
            tempNode=tempNode->next.get();
        }
        if (tempNode==nullptr) {
            cout<<"Vertex not found";
            return;
        }
        nodeList->addNode(tempNode->graph);
        z=nodeList->next.get();
        while(z!=nullptr){
            p=&(z->graph->associatedNodes);
            while(p!=nullptr){
                if(p->graph!=nullptr)
                    nodeList->addNode(p->graph);
                p=p->next.get();
            }
            z=z->next.get();
        }
    }

    void printConnections(){
        Node *p;
        p=&connections;
        while(p!=nullptr){
            s2.clear();
            p->graph->addConnections(&s2,p->graph->vertexName);
            if ((this->connections.countElements())!=(s2.countElements()-1)){
                cout<<"Graph is not connected\n";
                return;
            }
            p=p->next.get();
        }
        Node *q;
        q=&nodeList;
        while(q!=nullptr){
            if (q->graph!=nullptr)
                cout<<q->graph->vertexName<<"   ";
            q=q->next.get();
        }
    }

    void connectVertices(){
        string vertex1;
        string vertex2="";
        Node *tempNode1,*tempNode2;
        tempNode1=&connections;
        cout<<"Which vertices to connect?\n";
        cin>>vertex1;
        while (tempNode1!=nullptr){
            if (tempNode1->graph->vertexName==vertex1)
                break;
            else {
                tempNode1=tempNode1->next.get();
            }
        }
        if (tempNode1==nullptr){
            cout<<"Element not found\n";
            return;
        }
        if(tempNode1->graph->vertexName!=vertex1){
            cout<<"\nElement not found\n";
            return;
        }
        while (vertex2!="0"){
            cout<<"\nWhat to connect with? Press '0' to exit\n";
            cin>>vertex2;
            if(vertex2=="0")
                return;
            tempNode2=&connections;
            while(tempNode2!=nullptr){
                if (tempNode2->graph->vertexName==vertex2)
                    break;
                tempNode2=tempNode2->next.get();
            }
            if(tempNode2==nullptr) {
                cout<<"\nElement not found\n";
                continue;
            }
            if (tempNode2->graph->vertexName!=vertex2){
                cout<<"\nElement not found\n";
                continue;
            }
            Node *tempNode3;
            tempNode3=&(tempNode1->graph->associatedNodes);
            if (tempNode3->graph==nullptr){
                tempNode3->graph=tempNode2->graph;
                cout<<"\nConnecting\n\n";
                continue;
            }
            tempNode3=&(tempNode1->graph->associatedNodes);
            while (true){
                if (tempNode3->graph->vertexName==vertex2){
                    cout<<"\nConnection already exists\n";
                    break;
                }
                else {
                    if (tempNode3->next!=nullptr)
                        tempNode3=tempNode3->next.get();
                    else{
                        tempNode3->next.reset(new Node());
                        cout<<"\nConnecting\n";
                        tempNode3=tempNode3->next.get();
                        tempNode3->graph=tempNode2->graph;
                        tempNode3->next=nullptr;
                        break;
                    }
                }
            }
        }
    }
};

int main () {
    int choice;
    cout<<"Enter the first vertex\n";
    Graph b;
    cout<<"Choose an action\n1-Add Vertex\n2-Connect Vertices\n3-Traversal\n4-Repeat Commands\n0-Exit\n";
    cin>>choice;
    while (choice!=0){
        switch(choice){
            case (1):{
                b.addVertex();
                cout<<"\nChoose an action\n";
                cin>>choice;
                break;
            }
            case (2):{
                b.connectVertices();
                cout<<"\nChoose an action\n";
                cin>>choice;
                break;
            }
            case (3):{
                nodeList.clear();
                b.addConnections(&nodeList);
                b.printConnections();
                cout<<"\nChoose an action\n";
                cin>>choice;
                break;
            }
            case (4):{
                cout<<"\n1-Add Vertex\n2-Connect Vertices\n3-Traversal\n4-Repeat Commands\n0-Exit\n";
                cout<<"\nChoose an action\n";
                cin>>choice;
                break;
            }
            case (0):{
                return 0;
            }
            default:{
                cout<<"\nPlease repeat!\n";
                cin>>choice;
                break;
            }
        }
    }
    return 0;
}
