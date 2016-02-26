/**************************************************************************************************/

/*
 * File: main.cpp
 * Author: Megha Agarwal
 * NetID: meghaagarwal
 * Date: December 8, 2015
 *
 * Description: This file checks for incorrect number of arguments and creates an object of Graph class and then calls the required methods to implement social network analysis.
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

// Includes all the header files for clarity.
#include "Graph.h"
#include "Users.h"

/**************************************************************************************************/

// main method to check for arguments and create a Graph object.
int main(int argc, char *argv[])
{
    int result=EXIT_SUCCESS;
    
    /* Logic to check arguments */
    if (argc != 3)
    {
        // Prints Usage statement.
        std::cout << std::endl << "Usage: " << argv[0] << " inputFile outputFile"
        << std::endl << std::endl;
        result = EXIT_FAILURE;
        return result;
    }
    
    //Creates an object of Graph class.
    Graph graph;
    
    //Calls a method to read from input file.
    if(!graph.ReadInputFile(argv[1]))
    {
        result = EXIT_FAILURE;
        return result;
    }
    
    //Calls a method to write into the output file.
    if(!graph.WriteOutputFile(argv[2]))
    {
        result = EXIT_FAILURE;
        return result;
    }
    
    return EXIT_SUCCESS;
}

/**************************************************************************************************/
