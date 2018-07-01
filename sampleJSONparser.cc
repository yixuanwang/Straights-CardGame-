// C++ file handling from command-line taken from https://www.student.cs.uwaterloo.ca/~cs246/current/codeExamples/IO.cc
// Command syntax:
//   $ ./a.out [ input-file [ output-file ] ] 
// all parameters are optional. Defaults: input=>cin, output=>cout
//
#include <iostream>
#include <fstream>
#include <string>
#include <jsoncpp/json/json.h>

using namespace std;

int main( int argc, char * argv[] ) {
	istream *infile = &cin;	  // default value
	ostream *outfile = &cout; // default value

	switch ( argc ) {
		case 3:
		try {
			outfile = new ofstream( argv[2] );	// open output file
			outfile->exceptions( ios_base::failbit ); // set exceptions
		} catch( ios_base::failure ) {
			throw ios_base::failure( "could not open output file" );
		} // try
		// FALL THROUGH so can set up input stream.
		case 2:
		try {
			infile = new ifstream( argv[1] );	// open input file
			infile->exceptions( ios_base::failbit ); // set exceptions
		} catch( ios_base::failure ) {
			throw ios_base::failure( "could not open input file" );
		} // try
		break;
	} // switch

	Json::Value root; // 'root' contains the root value after parsing.
	Json::CharReaderBuilder rbuilder; // Use the builder to create the parser.
	string errors;
	bool parsedOk = Json::parseFromStream( rbuilder, *infile, &root, &errors );
	
	if ( not parsedOk ) {
		cerr << "error in parsing JSON: " << errors << endl;
		return 1;
	} // if

	// Output the JSON object to the stream in a human-friendly manner.
	// First set up the JSON writer object.
	Json::StreamWriterBuilder wbuilder;
	Json::StreamWriter * writer = wbuilder.newStreamWriter();

	if ( root.isMember( "email_address" ) ) {
		root[ "email_address"] = root.get( "email_address", "default" ).asString() + "_xxx";
		writer->write( root, outfile );
		*outfile << endl;
	} // if

	if ( root.isMember( "users" ) && root[ "users" ].isArray() ) {
		for ( Json::ValueConstIterator it = root[ "users" ].begin(); it != root[ "users" ].end(); ++it ) {
			writer->write( *it, outfile );
			*outfile << endl; // add line feed and flush output
		} // for
	} // if

	if ( infile != &cin ) delete infile;		// Close file, do not delete cin!
    if ( outfile != &cout ) delete outfile;		// Close file, do not delete cout!
	return 0;
} // main
