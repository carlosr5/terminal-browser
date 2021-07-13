#include <string>
#include <vector>
#include "sha.h"
#include "database.h"

using namespace std;

Guest::Guest(string username, string password) {
    this->_username = username;

    ShaHash hashedPassword(password);
    this->_password = hashedPassword.getHash();

    //Calculate and set UUID
    string uuidBase = username+password;
    ShaHash uuid(uuidBase);
    this->_uuid = uuid.getHash();
}

Guest::~Guest() {

}

vector<Page> Guest::getHistory() {
    return this->history;
}

void Guest::clearHistory() {
    history.clear();
}

void Guest::addPageToHistory(Page page) {
    this->history.push_back(page);
}

User::User(string username, string password): Guest(username, password) {

}

User::~User() {
    
}

void User::setBookmark(Page page) {
    this->bookmarks.push_back(page);
}

vector<Page> User::getBookmarks() {
    return this->bookmarks;
}