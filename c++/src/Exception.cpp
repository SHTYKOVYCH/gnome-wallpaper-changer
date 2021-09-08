#include <string>

#include "Exception.hpp"

using namespace std;

Exception::Exception( string msg )
{
	this->msg = msg;
}

string Exception::getMessage()
{
	return this->msg;
}
