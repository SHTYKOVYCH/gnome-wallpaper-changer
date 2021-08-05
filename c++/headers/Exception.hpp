#pragma once

#include <iostream>
#include <string>

using namespace std;

class Exception
{
private:
	string msg;
public:
	Exception( string );

	string getMessage();
};
