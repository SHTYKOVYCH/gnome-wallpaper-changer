#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Exception.hpp"
#include "definitions.hpp"

using namespace std;

class SystemUser
{
public:
	static ifstream* readingFile;
	static ofstream* writingFile;

	static string getUserHomeDir();

	static void setWallparerPath();

	static void writeListOfFilesInFile();

	static void openFileForWriting( string path, ios_base::openmode mode = ios_base::out);

	static void openFileForReading( string path, ios_base::openmode mode = ios_base::in );

	static string readFromFile();

	static void closeReadingFile();

	static void closeWritingFile();

	static string replaceSpecialCharacters( string str );

	static vector<string>* getListOfFilesInTheFolder( string path = "/.wallparers/list" );
};

