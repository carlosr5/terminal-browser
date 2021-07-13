#include <fstream>
#include <string>
#include <map>
#include "user.h"

class Database {
public:
    Database();
    ~Database();
    int addUser(std::string username, std::string password);
    int removeUser(std::string username, std::string password);
private:
    std::fstream db;
    std::map<std::string, int> addedUsers;
    int totalUsers = 0;
};