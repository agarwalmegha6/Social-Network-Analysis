/**************************************************************************************************/

/*
 * File: Users.cpp
 * Author: Megha Agarwal
 * NetID: meghaagarwal
 * Date: December 8, 2015
 *
 * Description: This file implements the getter and setter methods for all the private member variables of the Users class.
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
#include "Users.h"
#include "Graph.h"

/**************************************************************************************************/

//The Users class has two vectors of type Users* and a string variable which are used by the Graph class to create the directed Graph.

//Default constructor.
Users::Users()
{
    this->name = "";
}

//Parameterized constructor which initializes the string.
Users::Users(string name)
{
    this->name = name;
}

//Setter method which sets the name of the user.
void Users::setName(string name)
{
    this->name = name;
}

//Getter method which gets the name of the user.
string Users::getName()
{
    return this->name;
}

//Setter method which adds the followers to the follower vector.
void Users::addFollower(Users* u)
{
    followers.push_back(u);
}

//Getter method which gets the followers from the follower vector.
vector<Users*> Users::getFollowers()
{
    return followers;
}

//Setter method which adds the following to the following vector.
void Users::addFollowing(Users* u)
{
    following.push_back(u);

}

//Getter method which gets the following from the following vector.
vector<Users*> Users::getFollowing()
{
    return following;
}
/**************************************************************************************************/
