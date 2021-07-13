#include <string>
#include <vector>
#include "page.h"

class Guest {
public:
	//Should be able to browse pages
	Guest(std::string username, std::string password);
	~Guest();
	//Remember that you gotta clear a Guest's history everytime they log off
	std::vector<Page> getHistory();
	void clearHistory();
	void addPageToHistory(Page page);
private:
	std::vector<Page> history;
    std::string _username;
    std::string _password;
	//Hashed username to create uuid. Not smart in practice. Just for
	//proof of concept
    std::string _uuid;

	friend class Database;
};

class User : public Guest {
public:
	User(std::string username, std::string password);
	~User();
	void setBookmark(Page page);
	std::vector<Page> getBookmarks();

private:
	std::vector<Page> bookmarks;

	friend class Database;
};