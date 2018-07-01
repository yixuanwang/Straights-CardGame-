/*
 * Account is an abstract base class for social networking accounts.
 *
 *  Created by Caroline Kierstead on 2017-03-23.
 *  Last updated: 2018-05-08
 *  Copyright 2017 UW. All rights reserved.
 *
 */
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <vector>
#include "util.h"

// Account is an abstract base class for the various type of social network accounts.
// A "friend" is an account being followed by "this" account. A "follower" is an account
// following "this" account.
class Account {
  private:
    // *** Fill in any private data and helper methods.
    
  protected:
    // *** Fill in any protected data and helper methods.

  public:
    // *** Note that you may NOT change the interface specified for this class.
    Account( const std::string & id, const std::string & email_address );
    virtual ~Account();

    // Each type of account has a way to return its JSON representation for output.
    virtual Json::Value * createJSON() const = 0;
    // Creates a Json::Value that contains a list of all of the id's of friends/followers for output.
    Json::Value * createFriendsJSON() const;
    Json::Value * createFollowersJSON() const;

    // Returns true if the specifed JSON object contains the information necessary to properly initialize
    // the account with an id and email address; otherwise, returns false.
    static bool validateJSON( const Json::Value & value );

    // Accessors
    std::string id() const;
    unsigned int numFriends() const;
    unsigned int numFollowers() const;

    // Is this account currently suspended? Check expiration date (if applicable) to system date.
    virtual bool suspended() const;

    // Is this account a moderator?
    virtual bool moderator() const;

    // If account doesn't have a specific username (distinct from the id), returns id.
    virtual std::string username() const;

    // How many photos/videos/media/profile pictures are associated with this account?
    virtual unsigned int numAssociatedMedia() const; 

    // Add the specified friend/follower to the list of friends/followers.
    void addFollower( const Account * account );
    void addFriend( const Account * account );

    // Remove specified friend/follower. Returns true if successful; otherwise, returns false.
    bool removeFollower( const Account * account );
    bool removeFriend( const Account * account );

    // Returns true if specified friend/follower is in list; otherwise, returns false.
    bool hasFollower( const Account * account ) const;
    bool hasFollower( const std::string & accountID ) const;
    bool hasFriend( const Account * account ) const;
    bool hasFriend( const std::string & accountID ) const;
};

#endif
