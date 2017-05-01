#ifndef GRAPH_H
#define GRAPH_H

#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <utility>

using std::string;
using std::vector;
using std::map;

class graph
{
public:

	struct node;

	struct edge
	{
		string end;
		double cost;
	};

	graph();
	~graph();

	bool empty() const;
	void clear();

	void erase(string name);
	void insert(string name);
	void insert(string name, vector<edge> evec);

	vector<edge> get_adjacent(string name);
	void set_adjacent(string name, vector<edge> adjacent);

	std::pair<vector<edge>::iterator&, bool> is_edge(string first, string last);
	void add_edge(string first, string last, double cost = 0.0);
	void erase_edge(string first, string last);

	string to_string() const;

	vector<edge> get_path(string first, string last);

private:
	map<string, vector<edge> > nmap;
};

graph::graph()
{

}
inline bool graph::empty() const
{ return nmap.empty(); }
inline void graph::clear()
{ nmap.clear(); }
inline void graph::erase(string name)
{ nmap.erase(name); }
inline void graph::insert(string name, vector<edge> evec)
{ nmap.emplace(name, evec); }
inline void graph::insert(string name)
{
	vector<edge> evec;
	insert(name, evec);
}
inline vector<typename graph::edge> graph::get_adjacent(string name)
{ return nmap[name]; }
inline void graph::set_adjacent(string name, vector<edge> adjacent)
{ nmap[name] = adjacent; }
std::pair<vector<typename graph::edge>::iterator&, bool> graph::is_edge(string first, string last)
{
	vector<edge>::iterator it = (nmap[first]).begin();
	for(; it != (nmap[first]).end(); ++it)
	{
		if(it->end == last) return std::pair<vector<typename graph::edge>::iterator&, bool>(it, true); 
	}

	return std::pair<vector<typename graph::edge>::iterator&, bool>(it, false);
}
inline void graph::add_edge(string first, string last, double cost)
{
	graph::edge e;
	e.end = last;
	e.cost = cost;
	nmap[first].push_back(e);
}
void graph::erase_edge(string first, string last)
{
	for(vector<edge>::iterator it = (nmap[first]).begin(); it != (nmap[first]).end(); ++it)
	{
		if(it->end == last)
		{
			nmap[first].erase(it);
			break;
		}
	}
}
string graph::to_string() const
{
	std::stringstream ss;
	for(map<string, vector<edge> >::const_iterator m_it = nmap.begin(); m_it != nmap.end(); ++m_it)
	{
		ss << m_it->first << '\n';

		for(vector<edge>::const_iterator v_it = (m_it->second).begin(); v_it != (m_it->second).end(); ++v_it)
		{
			ss << v_it->end << " : " << v_it->cost << '\n';
		}
	}

	return (ss.str());
}
vector<typename graph::edge> graph::get_path(string first, string last)
{

}

graph::~graph() {}

#endif