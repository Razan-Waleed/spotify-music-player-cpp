#include <iostream>
#include <string>
#include "global.h"  

using namespace std;

// Convert a string to lowercase
string strtolower(string str) {
	
	for (int i = 0; i < str.size(); i++) {
		// Convert current character to lowercase
		str[i] = tolower(str[i]);
	}
	
	return str;
}
