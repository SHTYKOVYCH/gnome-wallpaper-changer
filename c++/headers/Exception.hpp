#pragma once

#include <iostream>
#include <string>

using namespace std;

class Exception
{
private:
	string msg;
public:
	explicit Exception( string );

	string getMessage();
};
