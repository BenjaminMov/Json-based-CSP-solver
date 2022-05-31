#pragma once

bool isConsistent(Node& node);
string getNext(Node* node);
void printNode(Node& node);
void printOrdering();
void DFS();
void init(int argc, char* argv[], bool customOrdering);
int main(int argc, char *argv[]);