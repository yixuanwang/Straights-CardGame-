/*
 * Test harness provided for the Account abstract base class and its derived classes.
 *
 *  Created by Caroline Kierstead on 2017-03-24.
 *  Last updated: 2018-05-08
 *  Copyright 2017 UW. All rights reserved.
 *
 */

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

// ****************** Forward Declarations *************************

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

// Outputs the given account and stores it in the associated vector.
void storeAndOutput( vector<const Account*> & v, const Account * account );

// Read in the JSON data contained in the file that was specified as a command argument and use it to 
// create a {Reddit,Instagram,Twitter,YouTube}Account if the data is valid. Any error results in a 
// nullptr being returned. Note that the number of friends/followers is ignored since it will be 
// determined by the number of friends/followers actually added to the account.
Account * readInRedditAccount();
Account * readInInstagramAccount();
Account * readInYouTubeAccount();
Account * readInTwitterAccount();

// Create a {Reddit,Instagram,Twitter,YouTube}Account from the given JSON data. Any error results in a 
// nullptr being returned. Note that the number of friends/followers is ignored since it will be 
// determined by the number of friends/followers actually added to the account.
Account * createRedditAccount( const Json::Value & root );
Account * createInstagramAccount( const Json::Value & root );
Account * createYouTubeAccount( const Json::Value & root );
Account * createTwitterAccount( const Json::Value & root );

// Read in a set of accounts from a file and creates the appropriate derived account objects. Each object
// is stored in the specified vector, so long as it isn't a nullptr. Relies upon the static 
// {Reddit,Instagram,YouTube,Twitter}Account::validateJSON to determine what account to create.
void createAccounts( vector<const Account*> & v );

// Searches the vector for an Account whose id() matches the one passed. Returns the appropriate iterator
// if successful; otherwise returns v.end().
vector<const Account*>::iterator findAccount( string id, vector<const Account*> & v );

// Reads in the id associated with the account to find and output (assumes uniquely specified ids,
// otherwise uses first one found). If the attempt to read fails, or cannot successfully find the
// account, prints an error message and does nothing. Returns the pointer to the account, or nullptr.
Account* findAccount( vector<const Account*> & v );

// Read in the ids associated with the add a follower command, and then attempts to 1) add the first 
// account as a follower of the second account (assumes uniquely specified ids, otherwise uses first
// one found), and 2) add the second account as a friend of the first account. If one (or both) of the 
// accounts cannot be found, or the ids are not distinct from each other, prints an error message and 
// does nothing.
void addFollower( vector<const Account*> & v );

// Read in the ids associated with the remove a follower command, and then attempts to 1) remove the first 
// account as a follower of the second account (assumes uniquely specified ids, otherwise uses first
// one found), and 2) remove the second account as a friend of the first account. If one (or both) of the 
// accounts cannot be found, or the ids are not distinct from each other, prints an error message and 
// does nothing.
void removeFollower( vector<const Account*> & v );

int main() {
    vector<const Account*> accounts;
    Account * currentAccount = nullptr;

    for ( ;; ) {
	char command;
	string fileName;

	cerr << " Enter command: ";
	cin >> command;
	if ( cin.fail() ) break;

	switch( command ) {
	  case 'R':
	      currentAccount = readInRedditAccount();
	      if ( currentAccount != nullptr ) { 
		  storeAndOutput( accounts, currentAccount );
	      } else {
		  cerr << "Failed to create RedditAccount." << endl;
	      } // if
	      break;
	  case 'Y':
	      currentAccount = readInYouTubeAccount();
	      if ( currentAccount != nullptr ) {
		  storeAndOutput( accounts, currentAccount );
	      } else {
		  cerr << "Failed to create YouTubeAccount." << endl;
	      } // if
	      break;
	  case 'T':
	      currentAccount = readInTwitterAccount();
	      if ( currentAccount != nullptr ) {
		  storeAndOutput( accounts, currentAccount );
	      } else {
		  cerr << "Failed to create TwitterAccount." << endl;
	      } // if
	      break;
	  case 'I':
	      currentAccount = readInInstagramAccount();
	      if ( currentAccount != nullptr ) {
		  storeAndOutput( accounts, currentAccount );
	      } else {
		  cerr << "Failed to create InstagramAccount." << endl;
	      } // if
	      break;
	  case 'a':
	      createAccounts( accounts );
	      break;
	  case 'P':
	      for ( auto it : accounts ) output( it );
	      break;
	  case '+':
	      addFollower( accounts );
	      break;
	  case '-':
	      removeFollower( accounts );
	      break;
	  case 'f':
	      currentAccount = findAccount( accounts );
	      break;
	  case 'p':
	      if ( currentAccount != nullptr ) {
		  output( currentAccount ); 
	      } else {
		  cerr << "Current account is set to a nullptr." << endl;
	      } // if
	      break;
	  case 'u':
	      if ( currentAccount != nullptr ) {
		  cout << "User name of current account is: " << currentAccount->username() << endl;
	      } else {
		  cerr << "Current account is set to a nullptr." << endl;
	      } // if
	      break;
	  case 's':
	      if ( currentAccount != nullptr ) {
		  cout << "Is current account suspended? " << boolalpha << currentAccount->suspended() << endl;
	      } else {
		  cerr << "Current account is set to a nullptr." << endl;
	      } // if
	      break;
	  case 'm':
	      if ( currentAccount != nullptr ) {
		  cout << "Is current account a moderator? " << boolalpha << currentAccount->moderator() << endl;
	      } else {
		  cerr << "Current account is set to a nullptr." << endl;
	      } // if
	      break;
	  case 'n':
	      if ( currentAccount != nullptr ) {
		  cout << "Current account has " << currentAccount->numAssociatedMedia() << " media associated." << endl;
	      } else {
		  cerr << "Current account is set to a nullptr." << endl;
	      } // if
	      break;
	} // switch
    } // for

    for ( auto it : accounts ) delete it;
    accounts.clear();

    return 0;
} // main

void createAccounts( vector<const Account*> & v ) {
    Json::Value * root = readInJSON();
    if ( root == nullptr ) return;
    if ( not root->isObject() ) { delete root; return; }
    if ( not root->isMember( "users" ) ) { delete root; return; }
    if ( not (*root)[ "users" ].isArray() ) { delete root; return; }
    
    for ( Json::ValueConstIterator it = (*root)[ "users" ].begin(); it != (*root)[ "users" ].end(); ++it ) {
	Account * account = nullptr;

	// Check for type of account and then create it.
	if ( RedditAccount::validateJSON( *it ) ) account = createRedditAccount( *it );
	else if ( TwitterAccount::validateJSON( *it ) ) account = createTwitterAccount( *it );
	else if ( InstagramAccount::validateJSON( *it ) ) account = createInstagramAccount( *it );
	else if ( YouTubeAccount::validateJSON( *it ) ) account = createYouTubeAccount( *it );
	else {
	    cerr << "Unrecognized type of account." << std::endl;
	    output( &(*it), cerr );
	} // if
	if ( account != nullptr ) v.emplace_back( static_cast<const Account*>( account ) );
    } // for
    delete root;
} // createAccounts

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

void storeAndOutput( vector<const Account*> & v, const Account * account ) {
    if ( account == nullptr ) {
	cerr << "Account is a nullptr, not stored." << endl;
	return;
    } // if
    v.emplace_back( account );
    output( account );
} // storeAndOutput

Account * createRedditAccount( const Json::Value & root ) {
    if ( not RedditAccount::validateJSON( root ) ) return nullptr;

    // Create temporary constants since compiler doesn't like passing rvalues as constants.
    const Date * creationDate = createDateFromJSON( root[ "created" ] );
    Date * expirationDate = createDateFromJSON( root[ "suspension_expiration" ] );
    const string id = root["id"].asString(); // otherwise complains about passing an rvalue as a constant
    const string email_address = root[ "email_address" ].asString();
    const string name = root[ "name" ].asString();

    return new RedditAccount( id, email_address, name,  root[ "is_mod" ].asBool(), root[ "is_employee" ].asBool(), 
			      root[ "over_18" ].asBool(), root[ "has_verified_email" ].asBool(), root[ "is_gold" ].asBool(), 
			      root[ "gold_creddits"].asUInt(), root[ "link_karma" ].asUInt(), root[ "comment_karma" ].asUInt(),
			      root[ "inbox_count" ].asUInt(), expirationDate, creationDate );
} // createRedditAccount

Account * createTwitterAccount( const Json::Value & root ) {
    if ( not TwitterAccount::validateJSON( root ) ) return nullptr;

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

    return new TwitterAccount( id, email_address, name, screen_name, location,
			       description, url, language, profile_image_url, createdAt, root[ "favourites_count" ].asUInt(),
			       root[ "statuses_count" ].asUInt(), root[ "verified" ].asBool()  );
} // createTwitterAccount

Account * createYouTubeAccount( const Json::Value & root ) {
    if ( not YouTubeAccount::validateJSON( root ) ) return nullptr;

    // Create temporary constants since compiler doesn't like passing rvalues as constants.
    const string id = root["id"].asString();
    const string email_address = root[ "email_address" ].asString();
    const string title = root[ "snippet" ][ "title" ].asString();
    const string description = root[ "snippet" ][ "description" ].asString();
    Date * publishedAt = createDateFromJSON( root[ "snippet" ][ "publishedAt" ] );

    return new YouTubeAccount( id, email_address, title, description, publishedAt, 
			       root[ "statistics" ][ "viewCount" ].asUInt(), 
			       root[ "statistics" ][ "commentCount" ].asUInt(), 
			       root[ "statistics" ][ "videoCount" ].asUInt() );
} // createInstagramAccount

Account * createInstagramAccount( const Json::Value & root ) {
    if ( not InstagramAccount::validateJSON( root ) ) return nullptr;

    // Create temporary constants since compiler doesn't like passing rvalues as constants.
    const string id = root["id"].asString();
    const string email_address = root[ "email_address" ].asString();
    const string username = root[ "username" ].asString();
    const string full_name = root[ "full_name" ].asString();
    const string profile_picture = root[ "profile_picture" ].asString();
    const string bio = root[ "bio" ].asString();
    const string website = root[ "website" ].asString();

    return new InstagramAccount( id, email_address, username, full_name, profile_picture,
				 bio, website, root[ "counts" ][ "media" ].asUInt()  );;
} // createYouTubeAccount

Account * readInRedditAccount() {
    Json::Value * root = readInJSON();
    if ( root == nullptr ) return nullptr;
    Account * account = createRedditAccount( *root );
    delete root;
    return account;
} // readInRedditAccount

Account * readInInstagramAccount() {
    Json::Value * root = readInJSON();
    if ( root == nullptr ) return nullptr;
    Account * account = createInstagramAccount( *root );
    delete root;
    return account;
} // readInInstagramAccount

Account * readInYouTubeAccount() {
    Json::Value * root = readInJSON();
    if ( root == nullptr ) return nullptr;
    Account * account = createYouTubeAccount( *root );
    delete root;
    return account;
} // readInYouTubeAccount

Account * readInTwitterAccount() {
    Json::Value * root = readInJSON();
    if ( root == nullptr ) return nullptr;
    Account * account = createTwitterAccount( *root );
    delete root;
    return account;
} // readInTwitterAccount

vector<const Account*>::iterator findAccount( string id, vector<const Account*> & v ) {
    auto it = find_if( v.begin(), v.end(), [ id ]( const Account * account ){ return account->id() == id; } );
    if ( it == v.end() ) {
	cerr << "Unable to find Account with id '" << id << "'." << endl;
	return v.end();
    } // if
    return it;
} // findAccount

void addFollower( vector<const Account*> & v ) {
    string id1, id2;
    cin >> id1 >> id2;
    if ( cin.fail() ) {
	cerr << "Failed to read in two ids." << endl;
	return;
    } // if
    if ( id1 == id2 ) {
	cerr << "Add follower command requires both ids to be distinct from each other." << endl;
	return;
    } // if
    auto it1 = findAccount( id1, v );
    auto it2 = findAccount( id2, v );
    if ( it1 == v.end() || it2 == v.end() ) return;

    // Cast away "const"ness so can modify account (due to -Wall).
    const_cast<Account*>( *it2 )->addFollower( *it1 );
    const_cast<Account*>( *it1 )->addFriend( *it2 );
} // addFollower

void removeFollower( vector<const Account*> & v ) {
    string id1, id2;
    cin >> id1 >> id2;
    if ( cin.fail() ) {
	cerr << "Failed to read in two ids." << endl;
	return;
    } // if
    if ( id1 == id2 ) {
	cerr << "Remove follower command requires both ids to be distinct from each other." << endl;
	return;
    } // if
    auto it1 = findAccount( id1, v );
    auto it2 = findAccount( id2, v );
    if ( it1 == v.end() || it2 == v.end() ) return;

    // Cast away "const"ness so can modify account (due to -Wall).
    const_cast<Account*>( *it2 )->removeFollower( *it1 );
    const_cast<Account*>( *it1 )->removeFriend( *it2 );
} // removeFollower

Account * findAccount( vector<const Account*> & v ) {
    string id;
    cin >> id;
    if ( cin.fail() ) {
	cerr << "Failed to read in an id." << endl;
	return nullptr;
    } // if
    auto it = findAccount( id, v );
    if ( it == v.end() ) return nullptr;
    output( *it );
    return const_cast<Account*>( *it );
} // findAccount
