#include <string>
#include <vector>
#include "page.h"

using namespace std;

Page::Page(vector<string> initContents, vector<int> initOutgoingLinks, int link) {
	this->_link = link;
	this->pageContents = initContents;
	this->outgoingLinks = initOutgoingLinks;
}

Page::~Page() {};

vector<string> Page::viewPage() {
	return this->pageContents;
}

int Page::getLink() {
	return this->_link;
}

vector<int> Page::getOutgoingLinks() {
	return this->outgoingLinks;
}
