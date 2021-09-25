#include <vector>

#include "SystemUser.hpp"

using namespace std;

ifstream* SystemUser::readingFile;
ofstream* SystemUser::writingFile;

void SystemUser::setWallparerPath()
{
	if( SystemUser::executeShellCommand( SET_WALLPARERER_COMMAND ) )
	{
		throw Exception("GSettings error: set path operation failed");
	}
}

void SystemUser::writeListOfFilesInFile()
{
	if( SystemUser::executeShellCommand( GET_FILE_NAMES_IN_THE_DIR_COMMAND ) )
	{
		throw Exception("System error: can't get file names");
	}
}

void SystemUser::openFileForWriting( string path, ios_base::openmode mode)
{
	SystemUser::writingFile = new ofstream( path, mode );

	if( !SystemUser::writingFile->is_open() )
	{
		throw Exception("Error on openning " + path + " for writing");
	}
}

void SystemUser::openFileForReading( string path, ios_base::openmode mode )
{
	SystemUser::readingFile = new ifstream( path, mode );

	if( !SystemUser::readingFile->is_open() )
	{
		throw Exception("Error on openning " + path + " for reading");
	}
}

string SystemUser::readFromFile()
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

void SystemUser::closeReadingFile()
{
	if(SystemUser::readingFile && SystemUser::readingFile->is_open())
	{
		SystemUser::readingFile->close();

		delete SystemUser::readingFile;

		SystemUser::readingFile = NULL;
	}
}

void SystemUser::closeWritingFile()
{
	if(SystemUser::writingFile && SystemUser::writingFile->is_open())
	{
		SystemUser::writingFile->close();

		delete SystemUser::writingFile;

		SystemUser::writingFile = NULL;
	}
}

string SystemUser::replaceSpecialCharacters( string str )
{
	int index = 0;

	while( (index = str.find( " ", index )) != std::string::npos )
	{
		str.insert( index, "\\");
		index += 2;
	}

	return str;
}

vector<string>* SystemUser::getListOfFilesInTheFolder( string path )
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

string SystemUser::getUserHomeDir()
{
	SystemUser::executeShellCommand( "echo ~/ > /tmp/homedir" );

	SystemUser::openFileForReading( "/tmp/homedir" );
	
	string str = SystemUser::readFromFile();

	SystemUser::closeReadingFile();

	return str;
}

int SystemUser::executeShellCommand(string command) {
    return system(command.c_str());
}
