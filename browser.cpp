#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>
#include "sha.h"
#include "database.h"

using namespace std;

void randSleep();
void sleepFor(int seconds);
void browse(User user);
void browse(Guest guest);
int userSelectionProcess();
User createUser();
User login();

int main(int argc, char* argv[]) {
    /**
     * Terminal interface below. A GUI using a C++ library will 
     * hopefully come soon
     */
    srand(time(NULL));
    string screenReset('\n', 20);

    //Asking user to either browse as guest or create a user account;
    cout << "Loading..." << endl;
    randSleep();
    cout << "Hello! Welcome to the terminal browser! You can look at 'websites', create User accounts, and have bookmarks stored for said accounts." << endl;
    sleepFor(5);
    cout << "This project was created after breifly discussed topics in class piqued my interest. These topics are Page Rank and one-way hash functions, \nalthough there are more that I'd like to explore in the future." << endl;
    sleepFor(9);
    cout << "The functionalities and presentation here are only meant for a proof of concept and for a learning experience,\nnot exactly as a functional, presentable web app." << endl;
    sleepFor(7);
    cout << "Feel free to use this program and explore it! If you have any questions, comments, or concerns, reach out to me at carlosr5@usc.edu" << endl;
    cout << endl;
    // Can have functions like intro, userSelection, etc.
    sleepFor(7);
    cout << endl;
    switch(userSelectionProcess()) {
        cout << screenReset << endl;
        case 1: {
            Guest guest("guest", "12345");
            browse(guest);
            break;
        }
        case 2: { 
            User newUser = createUser();
            browse(newUser);
            break;
        }
        case 3: {
            User existingUser = login();
            browse(existingUser);
            break;
        }
    }

    cout << "Thank you for using this program! Have a good day!" << endl;

    return 0;
}

/**
 * Sleeps the program between 0 and 3 seconds, chosen at random.
 * Meant to simulate slow computers hehe
 **/
void randSleep() {
    int randNum = (rand() % 4)*1000;
    this_thread::sleep_for(chrono::milliseconds(randNum));
}

void sleepFor(int seconds) {
    int millisecs = seconds * 1000;
    this_thread::sleep_for(chrono::milliseconds(millisecs));
}

User createUser() {
    cout << "In createUser()" << endl;
}

User login() {
    cout << "In login()" << endl;
}

int userSelectionProcess() {
    string input;
    cout << "Would you like to browse as a user or guest? Please enter either 'user' or 'guest'. ";

    do{
        cin >> input;
        string newStr = "";
        for(char c: input) {
            newStr += tolower(c);
        }
        input = newStr;

        if(input == "user") {
            cout << "Would you like to create a new user or login to an existing user account? Please enter either 'create' or 'login'. ";
            do {
                cin >> input;
                newStr = "";
                for(char c: input) {
                    newStr += tolower(c);
                }
                input = newStr;

                if(input == "create") {
                    return 2;
                }
                else if(input == "login") {
                    return 3;
                }
                else {
                    cout << "Please choose whether you'd like to create a new account or login. Please enter either 'create' or 'login'." << endl;
                }
            } while(input != "create" || input != "login");

        }
        else if(input == "guest") {
            return 1;
        }
        else {
            cout << "Please choose whether you'd like to browse as a user or a guest. Please enter either 'user' or 'guest'." << endl;
        }
    } while(input != "user" || input != "guest");
    return 0;
}

void browse(User user) {

}

void browse(Guest guest) {

}