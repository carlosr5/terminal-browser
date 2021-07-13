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

/**
 * Sleeps the program between 0 and 3 seconds, chosen at random.
 * Meant to simulate slow computers hehe
 **/
void randSleep() {
    int randNum = (rand() % 4)*1000;
    this_thread::sleep_for(chrono::milliseconds(randNum));
}

void sleepThree() {
    this_thread::sleep_for(chrono::milliseconds(3000));
}

void sleepFive() {
    this_thread::sleep_for(chrono::milliseconds(5000));
}

void sleepFor(int seconds) {
    int millisecs = seconds * 1000;
    this_thread::sleep_for(chrono::milliseconds(millisecs));
}

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
    sleepFive();
    cout << "This project was created after breifly discussed topics in class piqued my interest. These topics are Page Rank and one-way hash functions, \nalthough there are more that I'd like to explore in the future." << endl;
    sleepFor(9);
    cout << "The functionalities and presentation here are only meant for a proof of concept and for a learning experience,\nnot exactly as a functional, presentable web app." << endl;
    sleepFor(7);
    cout << "Feel free to use this program and explore it! If you have any questions, comments, or concerns, reach out to me at carlosr5@usc.edu" << endl;
    cout << endl;

    string input;
    cout << "Would you like to browse as a user or guest?";
    cin >> input;

    do{

    } while(input != "str");

    
    
    return 0;
}