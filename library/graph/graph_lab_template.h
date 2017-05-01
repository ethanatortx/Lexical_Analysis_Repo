#ifndef GRAPH_H
#define GRAPH_H

#include <sstream>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class graph
{
public:

	struct node;

	struct edge
	{
		node* end;
		double cost;
	};

	graph();
	~graph();

	bool empty() const;
	void clear();

	void erase(string name);
	void insert(string name);

	vector<edge> get_adjacent(string name);
	void set_adjacent(string name, vector<edge> adjacent);

	bool is_edge(string first, string last);
	void insert_edge(string first, string last);
	void erase_edge(string first, string last);

	vector<edge> get_path(string first, string last);

private:
	map<string, vector<edge> > nmap;
};

graph::graph()
{

}
bool graph::empty() const
{

}
void graph::clear()
{

}
void graph::erase(string name)
{

}
void graph::insert(string name)
{

}
vector<typename graph::edge> graph::get_adjacent(string name)
{

}
void graph::set_adjacent(string name, vector<edge> adjacent)
{

}
bool graph::is_edge(string first, string last)
{

}
void graph::insert_edge(string first, string last)
{

}
void graph::erase_edge(string first, string last)
{

}
vector<typename graph::edge> get_path(string first, string last)
{

}

#endif