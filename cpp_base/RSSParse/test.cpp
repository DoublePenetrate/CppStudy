#include <iostream>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

void test() {
    XMLDocument doc = new XMLDocument();
    doc.LoadFile("testRSS.xml");
    if (doc.ErrorID()) {
        cerr << "LoadFile error" << endl;
        return ;
    }
    
    XMLElement * itemNode = doc.FirstChildElement("rss")
        ->FirstChildElement("channel")
        ->FirstChildElement("item");

    while (itemNode) {
        string title = itemNode->FirstChildElement("title")->GetText();
        string link = itemNode->FirstChildElement("link")->GetText();
        string description  = itemNode->FirstChildElement("description")->GetText();
        cout << "title : " << title << endl;
        cout << "link : " << link << endl;
        cout << "description : " << description << endl;

        itemNode = itemNode->NextSiblingElement("item");
    }
}

int main()
{
    test();
    return 0;
}

