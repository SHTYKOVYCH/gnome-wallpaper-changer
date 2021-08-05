#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Exception.hpp"
#include "definitions.hpp"

using namespace std;

class SystemUser
{
public:
	static ifstream* readingFile;
	static ofstream* writingFile;

	static string getUserHomeDir()
	{
		system( "echo ~/ > /tmp/homedir" );

		SystemUser::openFileForReading( "/tmp/homedir" );
		
		string str = SystemUser::readFromFile();

		SystemUser::closeReadingFile();

		return str;
	}

	static void setWallparerPath()
	{
		if( system( SET_WALLPARERER_COMMAND ) )
		{
			throw Exception("GSettings error: set path operation failed");
		}
	}

	static void writeListOfFilesInFile()
	{
		if( system( GET_FILE_NAMES_IN_THE_DIR_COMMAND ) )
		{
			throw Exception("System error: can't get file names");
		}
	}

	static void openFileForWriting( string path, ios_base::openmode mode = ios_base::out)
	{
		writingFile = new ofstream( path, mode );

		if( !writingFile->is_open() )
		{
			throw Exception("Error on openning " + path + " for writing");
		}
	}

	static void openFileForReading( string path, ios_base::openmode mode = ios_base::in )
	{
		readingFile = new ifstream( path, mode );

		if( !readingFile->is_open() )
		{
			throw Exception("Error on openning " + path + " for reading");
		}
	}

	static string readFromFile()
	{
		if (!SystemUser::readingFile)
		{
			throw Exception("Error: file not openned");
		}

		string str;

		std::getline(*SystemUser::readingFile, str);

		if( SystemUser::readingFile->bad() )
		{
			throw Exception("Error on reading from file with filenames");
		}


		return str;
	}

	static void closeReadingFile()
	{
		if(SystemUser::readingFile && SystemUser::readingFile->is_open())
		{
			SystemUser::readingFile->close();

			delete SystemUser::readingFile;

			SystemUser::readingFile = NULL;
		}
	}	

	static void closeWritingFile()
	{
		if(SystemUser::writingFile && SystemUser::writingFile->is_open())
		{
			SystemUser::writingFile->close();

			delete SystemUser::writingFile;

			SystemUser::writingFile = NULL;
		}
	}

	static string replaceSpecialCharacters( string str )
	{
		int index = 0;

		while( (index = str.find( " ", index )) != std::string::npos )
		{
			str.insert( index, "\\");
			index += 2;
		}

		return str;
	}

	static vector<string>* getListOfFilesInTheFolder( string path = "/.wallparers/list" )
	{
		SystemUser::writeListOfFilesInFile();

		SystemUser::openFileForReading( SystemUser::getUserHomeDir() + path );

		vector<string>* list_of_names = new vector<string>;

		for( string filename; (filename = SystemUser::readFromFile()).size();)
		{
			list_of_names->push_back(filename);
		}

		SystemUser::closeReadingFile();

		return list_of_names;
	}
};

