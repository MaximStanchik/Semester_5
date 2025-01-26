#pragma once
#pragma comment(lib, "WS2_32.lib") 
#pragma warning(disable: 4996)

#include <algorithm>
#include <iostream>
#include <string>

#include "Winsock2.h"

using namespace std;

string GetErrorMsgText(int errorCode);
string SetErrorMsgText(string msgText, int code);