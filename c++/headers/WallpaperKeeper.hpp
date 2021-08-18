#pragma once

#include <iostream>
#include <vector>

#include "Exception.hpp"
#include "SystemUser.hpp"

using namespace std;

class WallpaperKeeper
{
private:
	vector<string>* names = NULL;

	string fixString (string, int);

public:
	WallpaperKeeper();

	~WallpaperKeeper();

	void printMenu();

	void printNamesList();

	string chooseWallparer();

	void setWallpaper();

	void talkToUser();
};
