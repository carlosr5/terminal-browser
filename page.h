#include <string>
#include <vector>

class Page {
public:
	//View contents on page
	Page(std::vector<std::string> initContents, std::vector<int> initOutgoingLinks, int link);
	~Page();
	std::vector<std::string> viewPage();
	int getLink();
	std::vector<int> getOutgoingLinks();

private:
	//Actual content?
	std::vector<std::string> pageContents;
	//Page "link" (an ID?)
	int _link;
	std::vector<int> outgoingLinks;
};