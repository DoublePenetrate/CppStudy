#include <iostream>
#include "tinyxml2.h"
#include <vector>

using namespace std;
using namespace tinyxml2;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    RssReader() {

    };

    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;
 };   

void RssReader::parseRss() {
    XMLDocument doc;
    doc.LoadFile("coolshell.xml");
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
        string description = itemNode->FirstChildElement("description")->GetText();

        string content = itemNode->FirstChildElement("content")->GetText();
        
        cout << "title : " << title << endl;
        cout << "link : " << link << endl;
        cout << "content : " << content << endl;

        itemNode = itemNode->NextSiblingElement("item");
    }
}

int main()
{
    RssReader rss;
    rss.parseRss();
    return 0;
}

