#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "sha.h"
#include "database.h"

using namespace std;

Database::Database() {

}

Database::~Database() {

}

/**
 * Adds a user to the database. Has a separate db file to check if the user
 * exists. O(n) time and space, so not the most optimal solution atm. Rn
 * it's the best that I can think of 
 **/
int Database::addUser(string username, string password) {
    db.open("mydatabase.txt"); 

    User user(username, password);

    string line;

    //Checks if user exists in actual database file (w/o append as feature)
    while(getline(db, line)) {
        stringstream ss;
        ss << line;

        string info;
        for(int i=0; i<2; i++) {
            ss >> info;

            if(info == user._uuid) {
                db.close();
                return -1;
            }
        }
    }
    db.close();
    
    db.open("mydatabase.txt", fstream::app);
    //Add user to database
    db << user._password << " " << user._uuid << "\n";
    this->addedUsers[user._uuid] = totalUsers++;

    db.close();
    
    return 0;
}

/*
Removes a user from the database and an internal helper map. Case sensitive.
Checks if password is correct before deleting user. 
Bug: Multiple users in database, calling remove on one user multiple times.
Functionality works, but can clutter the database. May be other bugs present.
*/
int Database::removeUser(string username, string password) {
    db.open("mydatabase.txt");

    string line, _line;
    bool userDeleted = false;
    ofstream temp("temp.txt");
    //while there are items in the database
    while(getline(db, _line)) {
        User user(username, password);
        stringstream ss;
        
        ss << _line;
        
        //if user exists and equal, delete that line and exit out of the program
        while (ss >> line) {
            if(addedUsers.count(user._uuid) == 1 && !userDeleted) {
                if(line == user._password) {
                    addedUsers.erase(user._uuid);

                    //Remove user from db
                    string deleteline = line;
                    line.replace(line.find(deleteline),deleteline.length(),"");
                    temp << '\n';

                    ss >> line;
                    deleteline = line;
                    line.replace(line.find(deleteline),deleteline.length(),"");

                    totalUsers--;
                    userDeleted = true;
                }  
            }
            //Else if a different user, add them back into the original file once
            else {
                temp << _line << '\n';
            }
        } 
    }

    db.close();
    temp.close();

    remove("mydatabase.txt");
    rename("temp.txt", "mydatabase.txt");
    
    return 0;
}