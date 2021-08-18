#include <string>

#include "SystemUser.hpp"
#include "WallpaperKeeper.hpp"

string WallpaperKeeper::fixString (string str, int len = 0)
{
	if (!len || str.size() == len)
	{
		return str;
	}

	if (str.size() < len)
	{
		while (str.size() < len)
		{
			str.push_back(' ');
		}

		return str;
	}

	string newString;

	newString = str.substr( 0, len / 3 );

	for (int i = len / 3; i > 0; --i)
	{
		newString += '.';
	}

	if (len % 3 == 1)
	{
		newString += '.';
	} else if (len % 3 == 2)
	{
		newString += "..";
	}

	for (int i = str.length() - len / 3; i < str.length(); i += 1)
	{
		newString += str[i];
	}

	while (newString.size() < len)
	{
		newString.push_back(' ');
	}

	return newString;
}

WallpaperKeeper::WallpaperKeeper()
{
	names = NULL;
	try
	{
		SystemUser::setWallparerPath();

		names = SystemUser::getListOfFilesInTheFolder();
	} catch (Exception e) {
		cout << e.getMessage() << endl;

		SystemUser::closeReadingFile();
	}
}

void WallpaperKeeper::printMenu()
{
	cout << "\t1. Choose wallparerer" << endl;
	cout << "\t0. Exit" << endl;
}

void WallpaperKeeper::printNamesList()
{
	for (int i = 0; i < names->size(); i += 1)
	{
		cout << (i + 1 < 10 ? " " : "") << ( i % 2 == 0 ? "    " : "");
		cout << i + 1 << ". " << fixString((*names)[i], 30) << (i % 2 == 1 ? "\n" : " ");
	}
}

string WallpaperKeeper::chooseWallparer()
{
	string inp;
	do
	{
		system("clear");
		cout << "Choose a wallparerer:" << endl;

		this->printNamesList();

		cout << "\n0 to cancel >>> ";
		
		cin >> inp;
		cin.ignore();
		
		try
		{
			if (stoi(inp) < 0 || stoi(inp) > this->names->size())
			{
				cout << "Oops! Seems there is no such number!\nPress Enter to continue" << endl;
				cin.get();
				continue;
			}
		} catch (std::invalid_argument e)
		{
			cout << "Oops! Seems it's not a number!\nPress Enter to continue";
			cin.get();
			continue;
		}

		break;

	} while (true);

	if (inp == "0")
	{
		cout << endl;
		return "";
	}

	int index = stoi(inp) - 1;

	return SystemUser::replaceSpecialCharacters((*names)[index]);
}

void WallpaperKeeper::setWallpaper()
{
	string path = this->chooseWallparer();

	if (path == "") {
		return;
	}

	system((string(COPY_FILE_COMMAND) + path + string(DESTINATION_STRING)).c_str());
	cout << endl;
}

void WallpaperKeeper::talkToUser()
{
	while (true)
	{
		system("clear");
		cout << "Choose an option:" << endl;
		
		printMenu();

		cout << ">>> ";

		string choice;

		cin >> choice;
		cin.ignore();

		if (choice == "1") 
		{
			setWallpaper();
			continue;
		}
		else if (choice == "0")
		{
			cout << "\nBye!\n" << endl;
			return;
		}
		else
		{
			cout << "Oops! Seems there is no such command!\nPress Enter to continue" << endl;
			cin.get();
		}
	}
}

WallpaperKeeper::~WallpaperKeeper()
{
	if (names)
	{
		delete names;
		names = NULL;
	}
}
