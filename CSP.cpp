#include <stdio.h>
#include <stack>    
#include <iostream>     
#include <cmath>          
#include <map>  
#include "JsonParser.cpp"

using namespace std;

// Node struct for storage of the values of variables, the order is always as follows:
// A B C D E F G H
// 0 1 2 3 4 5 6 7
struct Node {
    map<std::string, int> vars;
};

std::stack<Node*> myStack;

// array that stores the variable ordering
std::vector<std::string> orderMap;

//Json Parser
JsonParser* parser;

int maxD = 0;
int minD = 0;

// number of pruned branches
int pruned = 0;
// solution count
int solutions = 0;
 
bool lt(int a, int b) {return a < b;}
bool eq(int a, int b) {return a == b;}

map<std::string, bool (*)(int, int)> fn;
 
void initFunction() {
    fn["LessThan"] = &lt;
    fn["Equal"] = &eq;
}  

// check if world(node) is consistent
bool isConsistent(Node& node) {
    bool consistent = true;

    for (int i = 0; i < parser->constraintSize(); i++) {

        string constFirst = parser->ConstraintFirst(i);
        string constSecond = parser->ConstraintSecond(i);

        int varFirst = node.vars[constFirst];
        int varSecond = node.vars[constSecond];
        
        consistent = !varFirst || !varSecond || fn[parser->ConstraintFn(i)](varFirst, varSecond);
        if (!consistent) break;
    }

    return consistent;
}

// returns the index in node.vars that should be explored next
string getNext(Node* node) {
    int retVal = 0;
    while ((node->vars[orderMap[retVal]] != 0) && retVal < parser->varSize()) retVal++;
    return orderMap[retVal];
}

//prints the values of the node
void printNode(Node& node) {
    for (auto& pair: node.vars) {
        std::cout << pair.first << ": " << pair.second << " ";
    }
    std::cout << std::endl;
} 

void printOrdering() {
    cout << "ordering: ";
    for (string elem : orderMap) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Depth first search function using a stack
void DFS() {
    
    if (myStack.empty()) return;
    Node* node = myStack.top();
    myStack.pop();

    if (isConsistent(*node)) {
        bool done = true;
        // check if variable array is full, if yes, then a solution has been found
        for (auto& pair: node->vars) {
            done = (pair.second != 0);
            if (!done) break;
        }
        if (done) {
            std::cout << "solution: ";
            printNode(*node);
            solutions++;
            DFS();
            return;
        }
        
        //std::cout << "failure: ";
        //printNode(*node);

        string nextToAnalyze = getNext(node);
        
        //generate neighbors and add them to the stack
        for (int i = maxD; i >= minD; i--) {
            Node* subNode = new Node();
            map<string, int> subMap(node->vars);
            subNode->vars = subMap;
            subNode->vars[nextToAnalyze] = i;
            myStack.push(subNode);
        }

        //search neighbors
        DFS();

    } else {
        //increment prune count
        pruned++;
        DFS();
    } 
    
}
 
void init(int argc, char* argv[], bool customOrdering) {
    parser = new JsonParser();
    parser->init();

    if (customOrdering && ((argc - 1) != parser->varSize())) throw exception();
 
    //stoi
    maxD = parser->max();
    minD = parser->min();

    if (customOrdering) {
        for (int i = 1; i <= parser->varSize(); i++) {
            orderMap.push_back(parser->getVar(stoi(argv[i])));
        }
    } else {
        for (int i = 0; i < parser->varSize(); i++) {
            orderMap.push_back(parser->getVar(i));
        }
    }

    initFunction(); 
}

int main(int argc, char *argv[]) {
    bool customOrdering = false;
    if (argc > 1) customOrdering = true;

    init(argc, argv, customOrdering);
    printOrdering();
  
    Node* startNode = new Node();

    for (int i = 0; i < parser->varSize(); i++) {
        startNode->vars[parser->getVar(i)] = 0;
    }
    
    myStack.push(startNode);
    DFS();
    std::cout << "solutions " << solutions << std::endl;
    std::cout << "pruned " << pruned << std::endl;   
    return 0;
}