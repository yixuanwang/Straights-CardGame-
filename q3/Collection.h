/*
 * Collection used to hold a set of Users, keyed by unique email addresses.
 *
 *  Created by Caroline Kierstead on 2017-04-18.
 *  Last updated: 2018-05-08
 *  Copyright 2017 UW. All rights reserved.
 *
 */
#ifndef COLLECTION_H_
#define COLLECTION_H_
#include <string>
#include <map>
#include <iostream>
#include "Graph.h"
class User;
class Account;

class Collection {
    friend std::ostream & operator<<( std::ostream &, const Collection & );
  public:
    Collection();
    virtual ~Collection();

    // Precondition: user != nullptr
    // Postcondition: user is in the dictionary
    void add( User * user );

    // Precondition: user != nullptr
    // Postcondition: user is not in the dictionary
    void remove( User * user );

    // Precondition: unique email address
    // Postcondition: returns either associated User, or nullptr
    User * findUser( std::string email_address ) const;

    // Postcondition: returns the Account that matches the id and accountType, or nullptr
    // if no match is found.
    const Account * findAccount( std::string id, Graph::Connector accountType ) const;
};

#endif
