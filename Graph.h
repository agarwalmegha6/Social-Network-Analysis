#ifndef GRAPH_H
#define GRAPH_H

/*************/
/*
 * File: Graph.h
 * Author: Megha Agarwal
 * NetID: meghaagarwal
 * Date: December 8, 2015
 *
 * Description: This file contains the implementation of the Graph class which implements the social network analysis.
 */

#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include<fstream>
#include<vector>

using namespace std;

#include "Users.h"

//The Graph class reads data from the input file, creates a directed graph, finds the root user and suggestions for the user to follow.
class Graph{
    
private:
    
    //vector users to store the vertices of the graph.
    vector<Users*> users;
    
public:
    
    // Default constructor for Graph.
    Graph();
    
    //Destructor to delete the users vector.
    ~Graph();
    
    //This method reads input from the input file and checks if the usernames are valid or not.
    bool ReadInputFile(string filename);
    
    //This method writes output to the output file by sorting the result vector in descending order and breaking a tie.
    bool WriteOutputFile(string filename);
    
    //Search method to check if the user is already present in the graph.
    Users* search(string name);
    
    //Breadth-first search algorithm to search for users to follow within a depth of 2.
    vector<Users*> BFS(Users* source);
    
};

#endif // GRAPH_H
