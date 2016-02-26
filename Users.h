#ifndef USERS_H
#define USERS_H

/*************/
/*
 * File: Users.h
 * Author: Megha Agarwal
 * NetID: meghaagarwal
 * Date: December 8, 2015
 *
 * Description: This file contains the implementation of the Users class which is used by the Graph class to store the users and their followers and following.
 */

#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include<fstream>
#include<vector>

using namespace std;

//The Users class has two vectors of type Users* and a string variable which are used by the Graph class to create the directed Graph.
class Users{
    
private:
    
    //Three private variables to store name, followers and following of each user.
    string name;
    
    vector<Users*> followers;
    
    vector<Users*> following;
    
public:
    
    //Default constructor.
    Users();
    
    //Parameterized constructor which initializes the string.
    Users(string name);
    
    //Setter method which sets the name of the user.
    void setName(string name);
    
    //Getter method which gets the name of the user.
    string getName();
    
    //Setter method which adds the followers to the follower vector.
    void addFollower(Users* u);
    
    //Getter method which gets the followers from the follower vector.
    vector<Users*> getFollowers();
    
    //Setter method which adds the following to the following vector.
    void addFollowing(Users* u);
    
    //Getter method which gets the following from the following vector.
    vector<Users*> getFollowing();
    
    
};

#endif // USERS_H
