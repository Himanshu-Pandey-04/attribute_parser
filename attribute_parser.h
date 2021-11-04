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
	for (int i = 0; i < line.length(); i++)
	{
		string part = "";
		for (; line[i] != delimiter && i < line.length(); i++) part += line[i];
		parts.push_back(part);
	}
	return parts;
}




class tag
{
public:
	string name;
	vector<tag*> sub_tags;
	tag* prev;
	map<string, string> attributes;


	tag(string name = "")
	{
		this->name = name;
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

	void insertion(string, char delimiter = ' ');
	bool is_valid_tag(string);
	void menu();
};




void attribute_parser::insertion(string line, char delimiter)
{
	if (line[1] == '/')																				// If Closing tag encountered, go upwards
	{
		root = root->prev;
		return;
	}

	vector<string> line_parts = split(line, delimiter);
	tag* subTag = new tag(line_parts[0].substr(1, line_parts[0].length()));  						// Tag Name
	line_parts[line_parts.size() - 1] = line_parts[line_parts.size() - 1].substr(0, line_parts[line_parts.size() - 1].length()-1); // Last element
	
	for (int i = 1; i < line_parts.size(); i += 2) subTag->attributes[line_parts[i]] = line_parts[i + 1];
	subTag->prev = root;
	root->sub_tags.push_back(subTag);
}




bool attribute_parser::is_valid_tag(string line)
{
	
}


void attribute_parser::menu()
{
	int n, q; cin >> n >> q;
	string inp;

	for (int i = 0; i < n; i++)
	{
		getline(cin >> ws, inp);
		insertion(inp);
	}

	for (int i = 0; i < q; i++)
	{
		getline(cin >> ws, inp);
		is_valid_tag(inp);
	}
}




<t1>
	<t2>
		<t3>
		</t3>
		<t4>
		</t4>
	<t5>
	</t5>