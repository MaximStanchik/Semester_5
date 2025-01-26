#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <algorithm>

#include "Winsock2.h"

#pragma comment(lib, "WS2_32.lib") 
#pragma warning(disable: 4996)

using namespace std;

string GetErrorMsgText(int errorCode);
string SetErrorMsgText(string msgText, int code);