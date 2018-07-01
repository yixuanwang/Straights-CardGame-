/*
 * EmailAddress ensures email addresses are formatted to specification.
 *
 *  Created by Caroline Kierstead on 2017-04-17.
 *  Last updated: 2018-05-08
 *  Copyright 2017 UW. All rights reserved.
 *
 */
#ifndef EMAIL_ADDRESS_H_
#define EMAIL_ADDRESS_H_
#include <string>

class EmailAddress {
    const std::string _email_address; 
    static const std::string ALL_VALID;
    static const std::string ALPHANUM;

public:
    // Precondition: validateEmailAddress on email_address returns true
    EmailAddress( const std::string & email_address );
    static bool validateEmailAddress( const std::string & email_address );
    std::string id() const;
};

#endif
