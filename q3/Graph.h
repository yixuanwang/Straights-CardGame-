/*
 * Graph is an class that describes the connections between Users.
 *
 *  Created by Joanne Atlee on 2015-04-27.
 *  Modified by Caroline Kierstead on 2017-04-17.
 *  Last updated: 2018-05-08
 *  Copyright 2017 UW. All rights reserved.
 *
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>

class User; // forward declaration

class Graph {
  public:
    enum Connector { BAD_CONNECTOR, Twitter, Reddit, Instagram, YouTube };

  public:
    Graph(); // Sets graph to be "empty".
    Graph( const Graph & ); // Copy constructor.
    Graph( Graph && ); // Move constructor.
    virtual ~Graph();

    // Precondition: None
    // Postcondition: Converts string to matchingConnector type; returns BAD_CONNECTOR
    //    if no valid match found.
    static Graph::Connector convert( const std::string & );

    // Precondition: Graph doesn't already contain a node for this user.
    // Postcondition: Graph contains a node for this user.
    void addNode( const User * );

    // Precondition: None
    // Postcondition: Removes node whose user's id matches string or does nothing if
    //    node not found.
    void removeNode( const std::string & );

    // Precondition: None
    // Postcondition: Finds node whose user's email address matches the given string;
    //     returns nullptr if no match found.
    const User * findUser( const std::string & ) const;

    // Precondition: None
    // Postcondition: Graph contains an edge for the specified connector type between the two
    //     nodes if they exist; otherwise, the graph is left unchanged.
    void addEdge( const User*, const User *, Graph::Connector );

    // Precondition: None
    // Postcondition: If Graph had an edge of the appropriate connector type between the two
    //     users, it is now gone; otherwise, the graph is left unchanged.
    void removeEdge( const User*, const User *, Graph::Connector );

    // Precondition: None
    // Postcondition: Prints path (if it exists) between two users whose email addresses
    //     match the given strings.
    void printPaths( const std::string &, const std::string &, const bool = false ) const;

    // Precondition: None
    // Postcondition: Erases the contents of the graph.
    void deleteGraph(); 

    Graph& operator=( const Graph & ); // Copy assignment operator.
    Graph& operator=( Graph && ); // Move assignment operator.

    // Precondition: None
    // Postcondition: Returns true if the two graphs have the same sets of nodes and edges;
    //    otherwise, returns false.
    bool operator==( const Graph & ) const; 

    friend std::ostream& operator<<( std::ostream &, const Graph & );
};

#endif
