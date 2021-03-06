#include <iostream>
#include <cstdlib>
#include <string>

#include "WallpaperKeeper.hpp"

using namespace std;

int main( int argc, char* argv[] )
{
	WallpaperKeeper* wallparerer = new WallpaperKeeper();

	if (argc == 1)
	{
		wallparerer->setWallpaper(wallparerer->chooseWallparer());
	} else if (string(argv[1]) == string("menu")){
		wallparerer->talkToUser();
	} else if (string(argv[1]) == string("random")){
		wallparerer->setRandomWallpaper();
	} else {
		cout << "Wrong command! Usage: no command - choose wallpaper, menu - show menu" << endl;
	}

	delete wallparerer;

	return 0;
}
