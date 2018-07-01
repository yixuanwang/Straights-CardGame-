/*
 * Test harness provided for the Graph and Collection classes.
 *
 *  Created by Caroline Kierstead on 2017-04-18.
 *  Last updated: 2018-05-08
 *  Copyright 2017 UW. All rights reserved.
 *
 */

#include "Collection.h"
#include "Graph.h"
#include "User.h"
#include "Account.h"
#include "RedditAccount.h"
#include "InstagramAccount.h"
#include "TwitterAccount.h"
#include "YouTubeAccount.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <jsoncpp/json/json.h>

using namespace std;

const unsigned int NUM_GRAPHS = 5;

// ****************** Forward Declarations *************************
// Read in JSON data from the specified file to set up a collection of Users and their 
// associated social network site Accounts. Assumes that email addresses are unique, so
// will not create a user if the email address already exists in the dictionary. Once 
// have a User, add it as a Graph::Node. Every follower that gets added creates a
// Graph::Edge between the Users associated with the accounts.
void initializeUsers( Collection & dictionary, Graph & graph );

// Verify that the current graph is set to one of the graphs, in which case, return
// true; otherwise, return false;
bool verifyGraph( Graph * currentGraph, vector<Graph*> graphs );

// Read in two account ids and the social network type and then add id1 as a follower to id2
// and id2 as a friend of id1. Also adds the appropriate edge between the users in the current
// graph.
//
// Preconditions: 
//     - id1 and id2 must be valid ids and id1 != id2
//     - account type must be one of "T"/"R"/"I"/"Y"
//     - users with associated accounts id1 and id2 must exist in collection 
void addEdge( Collection & dictionary, Graph & graph );

// Read in two account ids and the social network type and then remove id1 as a follower to id2
// and id2 as a friend of id1. Also removes the appropriate edge between the users in the current
// graph.
//
// Preconditions: 
//     - id1 and id2 must be valid ids and id1 != id2
//     - account type must be one of "T"/"R"/"I"/"Y"
//     - users with associated accounts id1 and id2 must exist in collection 
void removeEdge( Collection & dictionary, Graph & graph );

// Read in a graph id (unsigned integer in range 0..NUM_GRAPHS). Returns true if successful, else
// returns false;
bool readGraphId( unsigned int & id );

// Read in a user's id i.e. email address. Relies upon EmailAddress::validateEmailAddress. Returns
// true if successful; otherwise returns false. 
bool readEmailAddress( string & id );

int main() {
    vector<Graph*> graphs;
    Graph *currentGraph = nullptr;
    Collection dictionary;

    for ( unsigned int i = 0; i < NUM_GRAPHS; ++i ) graphs.emplace_back( new Graph );

    for ( ;; ) {
	unsigned int currentGraphId, graphId1, graphId2;
	char command;
	string id;

	cerr << " Enter command: ";
	cin >> command;
	if ( cin.fail() ) break;

	switch( command ) {
	  case 'p':
	      if ( verifyGraph( currentGraph, graphs ) )
		  cout << "Graph " << currentGraphId << "\n" << *currentGraph;
	      break;
	  case 'i':
	      if ( verifyGraph( currentGraph, graphs ) )
		  initializeUsers( dictionary, *currentGraph );
	      break;
	  case '+':
	      if ( verifyGraph( currentGraph, graphs ) )
		  addEdge( dictionary, *currentGraph );
	      break;
	  case '-':
	      if ( verifyGraph( currentGraph, graphs ) )
		  removeEdge( dictionary, *currentGraph );
	      break;
	  case 'g':
	      if ( readGraphId( currentGraphId ) )
		  currentGraph = graphs.at( currentGraphId );
	      break;
	  case 'f':
	      if ( verifyGraph( currentGraph, graphs ) && readEmailAddress( id ) ) {
		  const User * user = currentGraph->findUser( id );
		  if ( user == nullptr ) cerr << "Unable to find user with id " << id << endl;
		  else cout << *user << endl;
	      } // if
	      break;
	  case 'd':
	      if ( verifyGraph( currentGraph, graphs ) && readEmailAddress( id ) )
		  currentGraph->removeNode( id );
	      break;
	  case 'a':
	      if ( verifyGraph( currentGraph, graphs) && readEmailAddress( id ) && dictionary.findUser( id ) != nullptr )
		  currentGraph->addNode( dictionary.findUser( id ) );
	      break;
	  case 'k':
	      if ( verifyGraph( currentGraph, graphs ) && readEmailAddress( id ) ) {
		  for ( auto it : graphs ) it->removeNode( id );
		  dictionary.remove( dictionary.findUser( id ) );
	      } // if
	      break;
	  case 'c':
	      if ( readGraphId( graphId1 ) && readGraphId( graphId2 ) ) {
		  delete graphs.at( graphId1 );
		  graphs.at( graphId1 ) = new Graph( *(graphs.at( graphId2 ) ) );
		  cout << "Graph " << graphId1 << endl << *( graphs.at( graphId1 ) );
	      } // if
	      break;
	  case 'C':
	      if ( readGraphId( graphId1 ) && readGraphId( graphId2 ) ) {
		  delete graphs.at( graphId1 );
		  graphs.at( graphId1 ) = new Graph( std::move( *(graphs.at( graphId2 ) ) ) );
		  cout << *( graphs.at( graphId1 ) );
	      } // if
	      break;
	  case '=':
	      if ( readGraphId( graphId1 ) && readGraphId( graphId2 ) ) {
		  *(graphs.at( graphId1 )) = *(graphs.at( graphId2 ) );
		  cout << "Graph " << graphId1 << endl << *(graphs.at( graphId1 ) );
	      } // if
	      break;
	  case '<':
	      if ( readGraphId( graphId1 ) && readGraphId( graphId2 ) ) {
		  *(graphs.at( graphId1 )) = std::move( *(graphs.at( graphId2 ) ) );
	      } // if
	      break;
	  case 'e':
	      if ( readGraphId( graphId1 ) && readGraphId( graphId2 ) ) {
		  cout << "Graphs " << graphId1 << " and " << graphId2 << " are ";
		  if ( *(graphs.at( graphId1 )) == *(graphs.at( graphId2 )) )
		      cout << "equal." << endl;
		  else
		      cout << "NOT equal." << endl;
	      } // if
	      break;
	  case '?':
	      if ( verifyGraph( currentGraph, graphs ) ) {
		  string id1, id2;
		  if ( readEmailAddress( id1 ) && readEmailAddress( id2 ) ) {
		      string _printAll;
		      bool printAll = false;
		      cin >> _printAll;
		      if ( ! cin.fail() ) {
			  if ( _printAll[0] == 'T' || _printAll[0] == 't' ) printAll = true;
			  cout << "Paths from " << id1 << " to " << id2 << " are:" << endl;
			  currentGraph->printPaths( id1, id2, printAll );
		      } // if
		  } // if
	      } // if
	      break;
	} // switch
    } // for

    for ( unsigned int i = 0; i < NUM_GRAPHS; ++i ) delete graphs.at( i );
    graphs.clear();
    return 0;
} // main

// Create a User account from the given JSON data. 
// Precondition: User::validateJSON( root ) == true
User * createUserAccount( const Json::Value & root );

// Given the Account and the JSON object of followers associated with it, add the followers to the account.
void addFollowers( Account * account, const Json::Value & root, Collection & dictionary, Graph & graph, 
		   Graph::Connector & accountType );

// Read in a Json::Value object from the file whose name was specified as a command argument 
// read from standard input. Any error results in nullptr being returned.
Json::Value * readInJSON();

// Given JSON code of the form '{ "date": { "year" : NNNN, "month": N, "day": N }}', create a Date object
// from the information. If date is of the form '{ "date" : "NULL"}', return nullptr. Return nullptr in all
// other cases.
Date * createDateFromJSON( const Json::Value & root );

// Outputs the given JSON object.
void output( const Json::Value * root, ostream &out = cout );

// Outputs the account's data in JSON form.
void output( const Account * account );

// Read in two distinct social network site ids from standard input as well as the type of social network site 
// account to search for. Returns true if successful; otherwise, returns false.
bool read2Ids( string & id1, string & id2, Graph::Connector & accountType );

// Given the dictionary, the type of social network account to search for, and two social network site ids in id[12], 
// sets a[12] to the addresses of the Accounts associated with each of the ids or nullptr if not in the dictionary. 
// Returns true if successfully found both accounts, otherwise returns false. 
bool get2Accounts( const Collection & dictionary, const string & id1, const string & id2, 
		   Graph::Connector accountType, Account ** a1, Account ** a2 );

// Create a {Reddit,Instagram,Twitter,YouTube}Account from the given JSON data. 
void createRedditAccount( const Json::Value & root, const Collection & dictionary );
void createInstagramAccount( const Json::Value & root, const Collection & dictionary );
void createYouTubeAccount( const Json::Value & root, const Collection & dictionary );
void createTwitterAccount( const Json::Value & root, const Collection & dictionary );

bool readGraphId( unsigned int & id ) {
    unsigned int graphId;
    cin >> graphId;
    if ( cin.fail() || graphId < 0 || graphId > NUM_GRAPHS ) {
	cerr << "Failed to read in valid graph id." << endl;
	return false;
    } // if
    id = graphId;
    return true;
} // readGraphId


void initializeUsers( Collection & dictionary, Graph & graph ) {
    Json::Value * root = readInJSON();
    if ( root == nullptr ) return;
    if ( not root->isObject() ) { delete root; return; }

    // Set up the users and their social network site accounts.
    if ( not root->isMember( "users" ) ) { delete root; return; }
    if ( not (*root)[ "users" ].isArray() ) { delete root; return; }
	
    for ( Json::ValueConstIterator it = (*root)[ "users" ].begin(); it != (*root)[ "users" ].end(); ++it ) {
	User * user = nullptr;

	// Check for type of account and then create it.
	if ( User::validateJSON( *it ) ) {
	    user = createUserAccount( *it );

	    if ( dictionary.findUser( user->id() ) != nullptr ) {
		cerr << "User with email address '" << user->id() << "' already exists in dictionary." << endl;
		delete user;
		user = nullptr;
		continue;
	    } // if

	    dictionary.add( user );
	    //graph.addNode( user ); 

	} else {
	    if ( RedditAccount::validateJSON( *it ) ) createRedditAccount( *it, dictionary );
	    else if ( TwitterAccount::validateJSON( *it ) ) createTwitterAccount( *it, dictionary );
	    else if ( InstagramAccount::validateJSON( *it ) ) createInstagramAccount( *it, dictionary );
	    else if ( YouTubeAccount::validateJSON( *it ) ) createYouTubeAccount( *it, dictionary );
	    else {
		cerr << "Unrecognized type of account." << std::endl;
		output( &(*it), cerr );
	    } // if
	} // if
    } // for

    // Check if have follower information to parse and add to graph.
    if ( not root->isMember( "followers" ) || not (*root)[ "followers" ].isArray() ) { delete root; return; }

    // Set up friends and followers.
    for ( Json::ValueConstIterator it = (*root)[ "followers" ].begin(); it != (*root)[ "followers" ].end(); ++it ) {
	// Validate JSON for follower.
	if ( not it->isObject() || not it->isMember( "account_type" ) || not it->isMember( "id" ) || not it->isMember( "followers" ) ||
	     not (*it)[ "account_type" ].isString() || not (*it)[ "id" ].isString() || not (*it)[ "followers" ].isArray() ) continue;

	// Find the Account with the appropriate id and type.
	const string account_type = (*it)[ "account_type" ].asString();
	const string id = (*it)[ "id" ].asString();
	Graph::Connector accountType = Graph::convert( account_type );
	Account * account = const_cast<Account*>( dictionary.findAccount( id, accountType ) );
		
	if ( account != nullptr ) {
	    // Check if user for this account is already in the graph or not and add if not.
	    const User * user = account->user();
	    if ( graph.findUser( user->id() ) == nullptr ) graph.addNode( user );
	    addFollowers( account, (*it)[ "followers" ], dictionary, graph, accountType );
	} // if
    } // for
    delete root;
} // initializeUsers

Json::Value * readInJSON() {
    string fileName;
    cin >> fileName;
    if ( cin.fail() ) return nullptr;

    ifstream infile( fileName );
    if ( not infile.is_open() ) { // Ensure file successfully opened
	cerr << "Failed to open file \"" << fileName << "\"." << endl;
	return nullptr; 
    } // if

    // 'root' contains the root value after parsing. Start with it set to a "null value" object by default.
    Json::Value * root = new Json::Value; 
    Json::CharReaderBuilder rbuilder; // Use the builder to create the parser.
    string errors; // Contains error messages from the parsing.
    bool parsedOk = Json::parseFromStream( rbuilder, infile, root, &errors );
	
    if ( not parsedOk ) {
	cerr << "Error in parsing JSON: " << errors << endl;
	delete root;
	return nullptr;
    } // if

    return root;
} // readInJSON

void output( const Json::Value * root, ostream &out ) {
    Json::StreamWriterBuilder wbuilder;
    Json::StreamWriter * writer = wbuilder.newStreamWriter();
    writer->write( *root, &out );
    out << endl; // add line feed and flush output
} // output

void output( const Account * account ) {
    Json::Value * root = account->createJSON();
    output( root );
    delete root;
} // output


User * createUserAccount( const Json::Value & root ) {
    const string email_address = root[ "email_address" ].asString();
    const string name = root[ "name" ].asString();
    if ( ! EmailAddress::validateEmailAddress( email_address ) ) return nullptr;
    return new User( name, email_address );
} // createUserAccount


void addFollowers( Account * account, const Json::Value & root, Collection & dictionary, Graph & graph, Graph::Connector & accountType ) {
    for ( Json::ValueConstIterator it = root.begin(); it != root.end(); ++it ) {
	if ( not it->isMember( "id" ) ) continue;
	if ( not (*it)[ "id"].isString() ) continue;
	const string id = (*it)["id"].asString();

	// Add id as follower to account and account as friend to id.
	Account* followerAccount = const_cast<Account*>( dictionary.findAccount( id, accountType ) );
	if ( followerAccount == nullptr ) continue; // didn't find it, so skip past
	account->addFollower( followerAccount );
	followerAccount->addFriend( account );

	// Add connection to Graph. First find associated users.
	const User * u1 = account->user();
	const User * u2 = followerAccount->user();
	if ( u1 == nullptr || u2 == nullptr ) continue;

	// If u2 isn't in graph, add it.
	if ( graph.findUser( u2->id() ) == nullptr ) graph.addNode( u2 );
	graph.addEdge( u1, u2, accountType );
    } // for
} // addFollowers

bool readEmailAddress( string & id ) {
    cin >> id;
    if ( cin.fail() ) return false;
    return EmailAddress::validateEmailAddress( id );
} // readEmailAddress


bool read2Ids( string & id1, string & id2, Graph::Connector & accountType ) {
    string account_type;
    cin >> id1 >> id2 >> account_type;
    if ( cin.fail() ) {
	cerr << "Failed to successfully read in two ids and an account type." << endl;
	return false;
    } // if
    if ( id1 == id2 ) {
	cerr << "id1 == id2 and shouldn't." << endl;
	return false;
    } // if
    accountType = Graph::convert( account_type );
    if ( accountType == Graph::Connector::BAD_CONNECTOR ) {
	cerr << "Invalid connector type." << endl;
	return false;
    } // if
    return true;
} // read2Ids

bool get2Accounts( const Collection & dictionary, const string & id1, const string & id2, Graph::Connector accountType, 
		   Account ** a1, Account ** a2 ) 
{
    *a1 = *a2 = nullptr;
    const Account * _a1 = dictionary.findAccount( id1, accountType );
    const Account * _a2 = dictionary.findAccount( id2, accountType );
    if ( _a1 == nullptr ) {
	cerr << "Unable to find account with id " << id1 << endl;
	return false;
    } // if
    if ( _a2 == nullptr ) {
	cerr << "Unable to find account with id " << id2 << endl;
	return false;
    } // if
    *a1 = const_cast<Account*>( _a1 );
    *a2 = const_cast<Account*>( _a2 );
    return true;
} // get2Accounts


void addEdge( Collection & dictionary, Graph & graph ) {
    string id1, id2;
    Graph::Connector accountType;
    Account * a1, * a2;
    if ( read2Ids( id1, id2, accountType ) ) {
	if ( get2Accounts( dictionary, id1, id2, accountType, &a1, &a2 ) ) {
	    a2->addFollower( a1 );
	    a1->addFriend( a2 );
	    const User * u1 = a1->user();
	    const User * u2 = a2->user();
	    if ( u1 == nullptr || u2 == nullptr ) return;
	    graph.addEdge( u1, u2, accountType );
	} // if
    } // if
} // addEdge


void removeEdge( Collection & dictionary, Graph & graph ) {
    string id1, id2;
    Graph::Connector accountType;
    Account * a1, * a2;
    if ( read2Ids( id1, id2, accountType ) ) {
	if ( get2Accounts( dictionary, id1, id2, accountType, &a1, &a2 ) ) {
	    a2->removeFollower( a1 );
	    a1->removeFriend( a2 );
	    const User * u1 = a1->user();
	    const User * u2 = a2->user();
	    if ( u1 == nullptr || u2 == nullptr ) return;
	    graph.removeEdge( u1, u2, accountType );
	} // if
    } // if
} // removeEdge


bool verifyGraph( Graph * currentGraph, vector<Graph*> graphs ) {
    for ( unsigned int i = 0; i < NUM_GRAPHS; ++i ) if ( currentGraph == graphs.at( i ) ) return true;
    cerr << "Need to set current graph before this command can be completed." << endl;
    return false;
} // verifyGraph


void createRedditAccount( const Json::Value & root, const Collection & dictionary ) {
    if ( not RedditAccount::validateJSON( root ) ) return;

    // Create temporary constants since compiler doesn't like passing rvalues as constants.
    const Date * creationDate = createDateFromJSON( root[ "created" ] );
    Date * expirationDate = createDateFromJSON( root[ "suspension_expiration" ] );
    const string id = root["id"].asString(); // otherwise complains about passing an rvalue as a constant
    const string email_address = root[ "email_address" ].asString();
    const string name = root[ "name" ].asString();

    User * user = dictionary.findUser( email_address );
    if ( user == nullptr ) {
	cerr << "Did not find User with email address '" << email_address << "'" << endl;
	return;
    } // if

    const Account * account = new RedditAccount( id, user, name,  root[ "is_mod" ].asBool(), root[ "is_employee" ].asBool(), 
						 root[ "over_18" ].asBool(), root[ "has_verified_email" ].asBool(), root[ "is_gold" ].asBool(), 
						 root[ "gold_creddits"].asUInt(), root[ "link_karma" ].asUInt(), root[ "comment_karma" ].asUInt(),
						 root[ "inbox_count" ].asUInt(), expirationDate, creationDate );
    user->add( account );
} // createRedditAccount

void createTwitterAccount( const Json::Value & root, const Collection & dictionary ) {
    if ( not TwitterAccount::validateJSON( root ) ) return;

    // Create temporary constants since compiler doesn't like passing rvalues as constants.
    const string id = root["id"].asString();
    const string email_address = root[ "email_address" ].asString();
    const string name = root[ "name" ].asString();
    const string screen_name = root[ "screen_name" ].asString();
    const string location = root[ "location" ].asString();
    const string description = root[ "description" ].asString();
    const string url = root[ "url" ].asString();
    const string language = root[ "lang" ].asString();
    const string profile_image_url = root[ "profile_image_url" ].asString();
    Date * createdAt = createDateFromJSON( root[ "created_at" ] );

    User * user = dictionary.findUser( email_address );
    if ( user == nullptr ) {
	cerr << "Did not find User with email address '" << email_address << "'" << endl;
	return;
    } // if

    const Account * account = new TwitterAccount( id, user, name, screen_name, location,
						  description, url, language, profile_image_url, createdAt, root[ "favourites_count" ].asUInt(),
						  root[ "statuses_count" ].asUInt(), root[ "verified" ].asBool() );
    user->add( account );
} // createTwitterAccount

void createYouTubeAccount( const Json::Value & root, const Collection & dictionary ) {
    if ( not YouTubeAccount::validateJSON( root ) ) return;

    // Create temporary constants since compiler doesn't like passing rvalues as constants.
    const string id = root["id"].asString();
    const string email_address = root[ "email_address" ].asString();
    const string title = root[ "snippet" ][ "title" ].asString();
    const string description = root[ "snippet" ][ "description" ].asString();
    Date * publishedAt = createDateFromJSON( root[ "snippet" ][ "publishedAt" ] );

    User * user = dictionary.findUser( email_address );
    if ( user == nullptr ) {
	cerr << "Did not find User with email address '" << email_address << "'" << endl;
	return;
    } // if

    const Account * account = new YouTubeAccount( id, user, title, description, publishedAt, 
						  root[ "statistics" ][ "viewCount" ].asUInt(), 
						  root[ "statistics" ][ "commentCount" ].asUInt(), 
						  root[ "statistics" ][ "videoCount" ].asUInt() );
    user->add( account );
} // createInstagramAccount

void createInstagramAccount( const Json::Value & root, const Collection & dictionary ) {
    if ( not InstagramAccount::validateJSON( root ) ) return;

    // Create temporary constants since compiler doesn't like passing rvalues as constants.
    const string id = root["id"].asString();
    const string email_address = root[ "email_address" ].asString();
    const string username = root[ "username" ].asString();
    const string full_name = root[ "full_name" ].asString();
    const string profile_picture = root[ "profile_picture" ].asString();
    const string bio = root[ "bio" ].asString();
    const string website = root[ "website" ].asString();

    User * user = dictionary.findUser( email_address );
    if ( user == nullptr ) {
	cerr << "Did not find User with email address '" << email_address << "'" << endl;
	return;
    } // if

    const Account * account = new InstagramAccount( id, user, username, full_name, profile_picture,
						    bio, website, root[ "counts" ][ "media" ].asUInt() );
    user->add( account );
} // createYouTubeAccount
