#pragma once
#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<map>

using namespace std;




vector<string> split(string line, char delimiter = ' ')
{
    vector<string> parts;
    for (int i = 0; i < line.length();)
    {
        string part = "";
        while (line[i] != delimiter && i < line.length()) part += line[i++];
        while (++i < line.length() && line[i] == delimiter);
        parts.push_back(part);
    }
    return parts;
}




class tag
{
public:
    string name;
    map<string, tag*> sub_tags;
    tag* prev;
    map<string, string> attributes;


    tag(string name = "")
    {
        this->name = name;
        prev = NULL;
    }
};



class attribute_parser
{
    tag* root;

public:
    attribute_parser()
    {
        root = new tag("hrml");
    }

    void reset_root();
    void insertion(string, char delimiter = ' ');
    string is_valid_tag(string);
    void solve();
};






void attribute_parser::reset_root()
{
    while (root->name != "hrml") root = root->prev;
}





void attribute_parser::insertion(string line, char delimiter)
{
    if (line[1] == '/')                                                                                // If Closing tag encountered, go upwards
    {
        root = root->prev;
        return;
    }
    line = line.substr(1, line.length() - 2);
    line.erase(remove(line.begin(), line.end(), '='), line.end()); //remove = from string
    line.erase(remove(line.begin(), line.end(), '"'), line.end()); //remove = from string

    vector<string> line_parts = split(line, delimiter);
    tag* subTag = new tag(line_parts[0].substr(0));                          // Tag Name

    for (int i = 1; i < line_parts.size() - 1; i += 2) subTag->attributes[line_parts[i]] = line_parts[i + 1];

    subTag->prev = root;
    root->sub_tags[subTag->name] = subTag;
    root = subTag;
}




string attribute_parser::is_valid_tag(string line)
{
    vector<string> attributes = split(line, '.');
    vector<string> last_2 = split(attributes[attributes.size() - 1], '~');
    attributes[attributes.size() - 1] = last_2[0];

    tag* temp = root;
    for (int i = 0; i < attributes.size(); i++)
    {
        if (temp->sub_tags[attributes[i]] == NULL) return "";
        temp = temp->sub_tags[attributes[i]];
    }

    return temp->attributes[last_2[1]];
}



void attribute_parser::solve()
{
    int n, q; cin >> n >> q;
    string inp;

    for (int i = 0; i < n; i++)
    {
        getline(cin >> ws, inp);
        insertion(inp);
    }
    reset_root();
    for (int i = 0; i < q; i++)
    {
        getline(cin >> ws, inp);
        string returned = is_valid_tag(inp);
        cout << (returned.size() == 0 ? "Not Found!" : returned) << "\n";
    }
}


