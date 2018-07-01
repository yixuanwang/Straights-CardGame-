/*
 * Some general utilities useful for the question.
 *
 *  Created by Caroline Kierstead on 2017-03-23.
 *  Last updated: 2018-05-08
 *  Copyright 2017 UW. All rights reserved.
 *
 */
#ifndef UTIL_H
#define UTIL_H

#include <jsoncpp/json/json.h>
#include <boost/date_time/gregorian/gregorian.hpp>

using Date = boost::gregorian::date; // short-form to reduce typing

// Returns true if the specified JSON object correctly specifies a date; otherwise, returns false.
bool validateJSONDate( const Json::Value & date ); 

// Creates the JSON equivalent of a null date i.e. '{ "date " : "NULL" }'
Json::Value * createNullDateJSON(); 

// Given a Date, returns the corresponding JSON object.
Json::Value * createDateJSON( const Date & d = boost::gregorian::day_clock::universal_day() );

// Given a correctly formed JSON date object, returns the date; otherwise, returns a nullptr.
Date * createDateFromJSON( const Json::Value & root );

#endif
