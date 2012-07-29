// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2012
// Glenn P. Downing
// ----------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector
#include <deque>   // deque
#include <algorithm> // find
#include <iostream>   // cout and endl
#include "boost/graph/exception.hpp" // not_a_dag

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;
        typedef int edge_descriptor;

        typedef std::vector<int>::const_iterator vertex_iterator;
        typedef std::vector<int>::const_iterator edge_iterator;
        typedef std::vector<vertex_descriptor>::const_iterator adjacency_iterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor source, vertex_descriptor destination, Graph& g) {
	    std::pair<edge_descriptor, bool> result 
		= g.find_edge(source, destination);
	    if(result.second == true)
		result.second = false;
	    else {
		g.vlist[source].push_back(destination);	
	    	g.elist.push_back(std::make_pair(source, destination));
		g.eindices.push_back(g.eindices.size());
            	result = std::make_pair(g.elist.size() - 1, true); }
	    assert(g.valid());
	    return result;}

        // ----------
        // add_vertex
        // ----------

        /**
         * <your documentation>
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            g.vlist.push_back(std::vector<vertex_descriptor>());
	    g.vindices.push_back(g.vindices.size());
	    assert(g.valid());
            return g.vlist.size() - 1;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * <your documentation>
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, const Graph& g) {
	    adjacency_iterator b = g.vlist[v].begin();
	    adjacency_iterator e = g.vlist[v].end();
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor source, vertex_descriptor destination, const Graph& g) {
            return g.find_edge(source, destination);}

        // -----
        // edges
        // -----

        /**
         * <your documentation>
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {
            return std::make_pair(g.eindices.begin(), g.eindices.end());}

        // ---------
        // num_edges
        // ---------

        /**
         * <your documentation>
         */
        friend edges_size_type num_edges (const Graph& g) {
            return g.elist.size();}

        // ------------
        // num_vertices
        // ------------

        /**
         * <your documentation>
         */
        friend vertices_size_type num_vertices (const Graph& g) {
            return g.vlist.size();}

        // ------
        // source
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor source (edge_descriptor ed, const Graph& g) {
            return g.elist[ed].first;}

        // ------
        // target
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor target (edge_descriptor ed, const Graph& g) {
            return g.elist[ed].second;}

        // ------
        // vertex
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor vertex (vertices_size_type n, const Graph&) {
            return n;}

        // --------
        // vertices
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) {
            return std::make_pair(g.vindices.begin(), g.vindices.end());}

    private:
        // ----
        // data
        // ----

        std::vector< std::vector<vertex_descriptor> > vlist;
	std::vector< std::pair<vertex_descriptor, vertex_descriptor> > elist;

	std::vector<int> vindices;
	std::vector<int> eindices;

	std::pair<edge_descriptor, bool> find_edge(vertex_descriptor source, 
		vertex_descriptor destination) const {
	    for(unsigned int i = 0; i < elist.size(); ++i)
	         if(elist[i].first == source && 
		    elist[i].second == destination)
		 	return std::make_pair(i, true);
	    return std::make_pair(elist.size(), false);}
	
        // -----
        // valid
        // -----


        /**
         * <your documentation>
         */
        bool valid () const {
	    vertices_size_type count_edges = 0;
	    for(unsigned int i = 0; i < vlist.size(); ++i){
		count_edges += vlist[i].size();
		for(unsigned int j = 0; j < vlist[i].size(); ++j) {
		    assert(vlist[i][j] >= 0);		
		    assert((std::size_t)vlist[i][j] < vlist.size());}}
	    assert(count_edges == elist.size());
            for(unsigned int i = 0; i < elist.size(); ++i) {
		assert((std::size_t)elist[i].first < vlist.size());
		assert((std::size_t)elist[i].second < vlist.size());
		adjacency_iterator beg = vlist[elist[i].first].begin();
		adjacency_iterator end = vlist[elist[i].first].end();
		assert(find(beg, end, elist[i].second) != end);}
/*
	    std::cout << "valid method" << std::endl;
	    std::cout << "g contains....";
	    std::cout << " " << vlist.size() << " vertices and ";
	    std::cout << elist.size() << " edges." << std::endl;

	    int edge_num = 0;
	    for(unsigned int i = 0; i < vlist.size(); ++i) {
		std::cout << "Vertex " << i << " has the following edges...." << std::endl;
		for(unsigned int j = 0; j < vlist[i].size(); ++j) {
		    std::cout << "edge " << edge_num << " leads to vertex ";
		    std::cout << vlist[i][j] << std::endl;
		    std::cout << "(actual edge from " << elist[edge_num].first;
		    std::cout << " to " << elist[edge_num++].second << ")" << std::endl << std::endl; }}

*/

            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph () {
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

// ---------
// has_cycle
// ---------
template<typename AIP, typename C, typename G>
bool has_cycle (const AIP& aip, C& v_seen, const G& g) {
    typename G::adjacency_iterator vb = aip.first;
    typename G::adjacency_iterator ve = aip.second;
    while(vb != ve) {
	typename C::iterator sb = v_seen.begin();
	typename C::iterator se = v_seen.end();
	if(std::find(sb, se, *vb) != se)
	    return true;
	v_seen.push_back(*vb);
	if(has_cycle(adjacent_vertices(*vb, g), v_seen, g))
	    return true;
	v_seen.pop_back();
	++vb; }
    
    return false;
}


/**
 * depth-first traversal
 * three colors
 * <your documentation>
 */
template <typename G>
bool has_cycle (const G& g) {
    std::pair<typename G::vertex_iterator, typename G::vertex_iterator> vi = 
	vertices(g);
    typename G::vertex_iterator vb = vi.first;
    typename G::vertex_iterator ve = vi.second;
    
    std::vector<typename G::vertex_descriptor> v_seen;
    while(vb != ve) {
	v_seen.push_back(*vb);
	if(has_cycle(adjacent_vertices(*vb, g), v_seen, g))
	    return true;
	v_seen.pop_back();
	++vb;}
    return false;}

// ----------------
// topological_sort
// ----------------

/**
 * depth-first traversal
 * two colors
 * <your documentation>
 * @throws Boost's not_a_dag exception if has_cycle()
 */
template <typename G, typename OI>
void topological_sort (const G& g, OI x) {
    if(has_cycle(g))
	throw boost::not_a_dag();

    typename G::vertices_size_type num_v = num_vertices(g);
    if(num_v == 0)
	return;

    // initialize target_list
    std::vector<int> target_list(num_v);
    std::deque<typename G::vertex_descriptor> v_zero;
    std::pair<typename G::edge_iterator, typename G::edge_iterator> p = edges(g);
    typename G::edge_iterator eb = p.first; 
    typename G::edge_iterator ee = p.second;
    while(eb != ee) {
	++target_list[target(*eb, g)];
	++eb; }
    
   //algorithm		
    std::vector<typename G::vertex_descriptor> temp_out;
    // add zeroed vertices
    for(unsigned int i = 0; i < target_list.size(); ++i) 
	if(target_list[i] == 0) {
	    --target_list[i];
 	    v_zero.push_back(i);} 
	
    while(!v_zero.empty()) {
	// output next empty
	typename G::vertex_descriptor vd = v_zero.front();
	temp_out.push_back(vd);
	v_zero.pop_front();

	// "cut" edges
	std::pair<typename G::adjacency_iterator, 
		  typename G::adjacency_iterator> ai = adjacent_vertices(vd, g);
	typename G::adjacency_iterator ab = ai.first;
	typename G::adjacency_iterator ae = ai.second;
	while(ab != ae) {
	    --target_list[*ab];
	    // add zeroed edges to v_zero
	    if(target_list[*ab] == 0) {
		--target_list[*ab];
		v_zero.push_back(*ab);}
	    ++ab;}}
	
	while(!temp_out.empty()) {
	    *x = temp_out.back();
	    temp_out.pop_back();
	    ++x; }
}

# endif //Graph_h
