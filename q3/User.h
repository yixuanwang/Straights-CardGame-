/*
 * User contains a name, an EmailAddress, which acts as a key for various social network site Accounts, 
 * and a possibly empty set of social network site accounts.
 *
 *  Created by Caroline Kierstead on 2017-04-17.
 *  Last updated: 2018-05-08
 *  Copyright 2017 UW. All rights reserved.
 *
 */
#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <iostream>
#include "util.h"
#include "EmailAddress.h"
class Account;

class User {
    const std::string _name; // all accounts have a unique identifier
    const EmailAddress _email_address; 
    std::vector<const Account*> accounts; 

  public:
    User( const std::string & name, const std::string & email_address );
    virtual ~User();

    // Each type of account has a way to return its JSON representation for output.
    Json::Value * createJSON() const;
 
    // Returns true if the specifed JSON object contains the information necessary to properly initialize
    // the account with an id and email address; otherwise, returns false.
    static bool validateJSON( const Json::Value & value );

    // Returns email address as unique user identity.
    std::string id() const;

    // Returns user name.
    std::string name() const;

    // Returns number of social network site accounts associated with this user.
    unsigned int numAccounts();

    // Precondition: 0 <= index < User::numAccounts
    // Postcondition: returns associated (const Account*)
    const Account * get( unsigned int index );

    // Associate specified social network site account with this user.
    void add( const Account * account );

    // Remove specified social network site account. Returns true if successful; otherwise, returns false.
    bool remove( const Account * account );

    // Returns true if specified account is in set; otherwise, returns false.
    bool has( const Account * account ) const;
    bool has( const std::string & accountID ) const;
};

std::ostream & operator<<( std::ostream &, const User & );
#endif
