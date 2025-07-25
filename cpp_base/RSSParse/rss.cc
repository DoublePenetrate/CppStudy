#include <cstdio>
#include <iostream>
#include <fstream>
#include "tinyxml2.h"
#include <vector>
#include <regex>

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
    
    /* FILE * file = fopen("test.txt", "a+"); */
    /* if (!file) { */
    /*     cerr << "open file failed" << endl; */
    /*     return ; */
    /* } */

    XMLElement * itemNode = doc.FirstChildElement("rss")
        ->FirstChildElement("channel")
        ->FirstChildElement("item");

    size_t idx = 0;

    while (itemNode) {
        string title = itemNode->FirstChildElement("title")->GetText();
        string link = itemNode->FirstChildElement("link")->GetText();
        string description = itemNode->FirstChildElement("description")->GetText();
        string content = itemNode->FirstChildElement("content:encoded")->GetText();
        
        regex reg("<[^>]+>");
        description = regex_replace(description, reg, "");
        content = regex_replace(content, reg, "");

        RssItem item;
        item.title = title;
        item.link = link;
        item.description = description;
        item.content = content;

        _rss.push_back(item);
        idx++;

        /* fwrite(title.c_str(), 1, title.size(), file); */
        /* fwrite(link.c_str(), 1, link.size(), file); */
        /* fwrite(description.c_str(), 1, description.size(), file); */
        /* fwrite(content.c_str(), 1, content.size(), file); */
        /* cout << "title : " << title << endl; */
        /* cout << "link : " << link << endl; */
        /* cout << "description : " << description << endl; */
        /* cout << "content : " << content << endl; */

        itemNode = itemNode->NextSiblingElement("item");
    }
    /* fclose(file); */
}


void RssReader::dump(const string & filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "open " << filename << " fail!" << endl;
        return ;
    }

    for (size_t idx = 0; idx != _rss.size(); idx++) {
        ofs << "<doc>\n" 
            << "\t<docid>" << idx + 1 
            << "</docid>\n\t<title>" << _rss[idx].title 
            << "</title>\n\t<link>" << _rss[idx].link
            << "</link>\n\t<description>" << _rss[idx].description
            << "</description>\n\t<content>" << _rss[idx].content
            << "</content>\n</doc>"
            << "\n";
    }
    ofs.close();
}

int main()
{
    RssReader rss;
    rss.parseRss();
    rss.dump("pagelib.dat");
    return 0;
}

