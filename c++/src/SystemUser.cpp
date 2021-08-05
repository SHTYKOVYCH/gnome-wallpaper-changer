#include <vector>

#include "SystemUser.hpp"

using namespace std;

ifstream* SystemUser::readingFile;
ofstream* SystemUser::writingFile;


string getUserHomeDir()
{
	system( "echo ~/ > /tmp/homedir" );

	SystemUser::openFileForReading( "/tmp/homedir" );
	
	string str = SystemUser::readFromFile();

	SystemUser::closeReadingFile();

	return str;
}

void setWallparerPath()
{
	if( system( SET_WALLPARERER_COMMAND ) )
	{
		throw Exception("GSettings error: set path operation failed");
	}
}

 void writeListOfFilesInFile()
{
	if( system( GET_FILE_NAMES_IN_THE_DIR_COMMAND ) )
	{
		throw Exception("System error: can't get file names");
	}
}

 void openFileForWriting( string path, ios_base::openmode mode = ios_base::out)
{
	SystemUser::writingFile = new ofstream( path, mode );

	if( !SystemUser::writingFile->is_open() )
	{
		throw Exception("Error on openning " + path + " for writing");
	}
}

 void openFileForReading( string path, ios_base::openmode mode = ios_base::in )
{
	SystemUser::readingFile = new ifstream( path, mode );

	if( !SystemUser::readingFile->is_open() )
	{
		throw Exception("Error on openning " + path + " for reading");
	}
}

string readFromFile()
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

void closeReadingFile()
{
	if(SystemUser::readingFile && SystemUser::readingFile->is_open())
	{
		SystemUser::readingFile->close();

		delete SystemUser::readingFile;

		SystemUser::readingFile = NULL;
	}
}	

void closeWritingFile()
{
	if(SystemUser::writingFile && SystemUser::writingFile->is_open())
	{
		SystemUser::writingFile->close();

		delete SystemUser::writingFile;

		SystemUser::writingFile = NULL;
	}
}

string replaceSpecialCharacters( string str )
{
	int index = 0;

	while( (index = str.find( " ", index )) != std::string::npos )
	{
		str.insert( index, "\\");
		index += 2;
	}

	return str;
}

vector<string>* getListOfFilesInTheFolder( string path = "/.wallparers/list" )
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
