/**************************************************************************************************/

/*
 * File: Graph.cpp
 * Author: Megha Agarwal
 * NetID: meghaagarwal
 * Date: December 8, 2015
 *
 * Description: This file implements the Graph class which reads data, creates graph, does analysis on it and then writes data to the output file.
 *
 */

/**************************************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include<fstream>
#include<vector>
#include <queue>
#include<iomanip>

using namespace std;

// Includes header files for clarity.
#include "Graph.h"
#include "Users.h"


/**************************************************************************************************/
//The Graph class reads data from the input file, creates a directed graph, finds the root user and suggestions for the user to follow.

//Default constructor.
Graph::Graph()
{
    
}

//Destructor to delete the users vector.
Graph::~Graph()
{
    //Deletes all the elements of the users vector.
    for(unsigned int i=0;i<users.size();i++)
    {
        delete users.at(i);
    }
}

//This method reads input from the input file and checks if the usernames are valid or not.
bool Graph::ReadInputFile( std::string filename)
{
    //The two strings store the two usernames.
    string user1_name;
    string user2_name;
    
    //The two User pointers stores the user information to be added to the users vector.
    Users* user1;
    Users* user2;
    
    bool result = false;
    
    // Input file stream.
    ifstream file;
    
    // Open file.
    file.open(filename.c_str( ));
    
    //Checks if file can't be opened.
    if (!file.is_open())
    {
        // Prints error message accordingly.
        std::cerr << "Error! Unable to read from file " << filename << ". Aborting." << std::endl;
        
        result = false;
        return result;
    }
    
    // Reads data from file.
    while (!file.eof()) {
        
        // Stores data in temporary variables.
        file>>user1_name;
        file>>user2_name;
        
        //Checks for the validity of the usernames.
        if (user1_name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") == std::string::npos && user2_name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") == std::string::npos && user1_name.length() <=15 && user2_name.length() <=15)
        {
         
        if(!file.fail())
        {
            //Checks if the users are already present in the graph or not.
            user1 = this->search(user1_name);
            user2 = this->search(user2_name);
            
            //If the users are unique, then they are added to the graph and the following and followers vectors are incremented accordingly.
            if(user1 == NULL)
            {
                user1 = new Users(user1_name);
                this->users.push_back(user1);
            }
            if(user2 == NULL)
            {
                user2 = new Users(user2_name);
                this->users.push_back(user2);
            }
            
            user1->addFollower(user2);
            user2->addFollowing(user1);
        }
    }
    }
    
    //Checks for empty file.
    if(users.size()==0)
    {
        std::cerr << "Error! Unable to read from file " << filename << ". Aborting." << std::endl;
        
        result = false;
        return result;
    }
    
    // Closes the file.
    file.close();
    return true;
    
}

//This method writes output to the output file by sorting the result vector in descending order and breaking a tie.
bool Graph::WriteOutputFile(string filename)
{
    // Output file stream.
    ofstream outFS;
        
    // Open file.
    outFS.open(filename.c_str());
    
    //Checks if output file could be opened.
    if (!outFS.is_open()) {
            
        // Prints out the error statement accordingly.
        std::cerr << "Error! Unable to write to file " << filename << ". Aborting." << std::endl;
        return false;
            
    }
    
    //Strings to serve as temporary variables.
    string name1 = "";
    string name2 = "";
    string name3 = "";
    string name4 = "";
    
    //Variable to store maximum centrality.
    unsigned int max = 0;
    
    //Variable to store the position where the centrality is maximum.
    unsigned int pos = 0;
    
    //Code to find out the maximum centrality from the directed graph. It breaks a tie by alphabetical order.
    for(unsigned int i=0;i<users.size();i++)
        {
            //Code to break a tie.
            if(users.at(i)->getFollowers().size()==max)
            {
                name1 = users.at(i)->getName();
                name2 = users.at(pos)->getName();
                for(unsigned int j=0;j<name1.length();j++)
                {
                    name1[j] = tolower(name1[j]);
                }
                for(unsigned int k=0;k<name2.length();k++)
                {
                    name2[k] = tolower(name2[k]);
                }

                if(name1.compare(name2)<0)
                {
                    pos = i;
                }
            }
            else
            {
            //Code to find maximum centrality.
            if(users.at(i)->getFollowers().size()>max)
            {
                max =users.at(i)->getFollowers().size();
                pos = i;
            }
            }
        }
    
    //Vector to store the result vector of unique users for the root user to follow.
    vector<Users*> suggestions;
    suggestions = BFS(users.at(pos));
    
    //Performs bubble sort on the unsorted vector to sort it in descending order of centrality.
    for (unsigned b = 0; b < suggestions.size()-1; b++) {
        for (unsigned c = 0; c < suggestions.size() - b -1; c++) {
            if (suggestions.at(c)->getFollowers().size() < suggestions.at(c+1)->getFollowers().size()) {
                Users* tempObj = suggestions.at(c);
                suggestions.at(c) = suggestions.at(c+1);
                suggestions.at(c+1) = tempObj;
            }
            
            //Checks if two elements have the same size then breaks the tie alphabetically.
            if (suggestions.at(c)->getFollowers().size() == suggestions.at(c+1)->getFollowers().size())
            {
                name3 = suggestions.at(c)->getName();
                name4 = suggestions.at(c+1)->getName();
                for(unsigned int d=0;d<name3.length();d++)
                {
                    name3[d] = tolower(name3[d]);
                }
                for(unsigned int e=0;e<name4.length();e++)
                {
                    name4[e] = tolower(name4[e]);
                }
                
                if(name3.compare(name4)>0)
                {
                    Users* tempObj = suggestions.at(c);
                    suggestions.at(c) = suggestions.at(c+1);
                    suggestions.at(c+1) = tempObj;
                }

            }
        }
    }
    
    //Prints the results into an output file with formatting.
    outFS << "Looking for new accounts for "<<users.at(pos)->getName()<<" ("<<max<<") to follow"<<endl;
    for(unsigned int a = 0;a<suggestions.size();a++)
    {
        outFS <<suggestions.at(a)->getName()<<" ("<<suggestions.at(a)->getFollowers().size()<<")"<<endl;
    }
    
    // Closes the output stream.
    outFS.close();
        
    return true;

}

//Search method to check if the user is already present in the graph.
Users* Graph::search(string name)
{
    //Returns the user if it is present otherwise returns null.
    for(unsigned int i=0;i<this->users.size();i++)
    {
        if(name == users.at(i)->getName())
            return users.at(i);
    }
    return NULL;
}

//Breadth-first search algorithm to search for users to follow within a depth of 2.
vector<Users*> Graph::BFS(Users* root)
{
    //Two vectors - a queue and a vector to store all the suggestions.
    vector<Users*> frontierQueue;
    vector<Users*> discoveredSet;
    
    bool visited = false;
    
    //Stores the current user.
    Users* current;
    
    //Pushes current user to both vectors.
    frontierQueue.push_back(root);
    discoveredSet.push_back(root);
    
    //Runs as long as the queue is not empty.
    while (frontierQueue.size()!=0) {
        
        //Current stores the first element of the queue.
        current = frontierQueue.at(0);
        frontierQueue.erase(frontierQueue.begin());
        
        //Stores all the users who are followed by the people whom the root user is following if they are not already present in the discoveredSet.
        for(unsigned int i = 0;i<current->getFollowing().size();i++)
        {
            for(unsigned int l = 0;l<current->getFollowing().at(i)->getFollowing().size();l++)
            {
            for(unsigned int j=0;j<discoveredSet.size();j++)
            {
                if(discoveredSet.at(j)->getName()==current->getFollowing().at(i)->getFollowing().at(l)->getName())
                {
                    visited = true;
                }
            }
            if(visited == false)
            {
                discoveredSet.push_back(current->getFollowing().at(i)->getFollowing().at(l));
            }
            else
                visited = false;
        }
        }
    }
    
    //Removes the root user from the discoveredSet.
    discoveredSet.erase(discoveredSet.begin());
    
    //Checks if any user in the discoveredSet is already followed by the user and removes them if found.
    for(unsigned int k = 0;k<root->getFollowing().size();k++)
    {
        for(unsigned int j=0;j<discoveredSet.size();j++)
        {
            if(root->getFollowing().at(k)->getName()==discoveredSet.at(j)->getName())
            {
                discoveredSet.erase(discoveredSet.begin()+j);
            }
        }
    }
    
    //Returns the discoveredSet.
    return discoveredSet;
}

/**************************************************************************************************/
