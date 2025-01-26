#include "stdafx.h"

string GetErrorMsgText(int code)
{
	string msgText;
	switch (code)
	{
	case WSAEINTR: msgText = "The function has been interrupted"; break;
	case WSAEACCES: msgText = "Permission denied"; break;
	case WSAEFAULT: msgText = "Error address"; break;
	case WSAEINVAL: msgText = "Error in argument"; break;
	case WSAEMFILE: msgText = "Too many files open"; break;
	case WSAEWOULDBLOCK: msgText = "Resource is temporarily unavailable"; break;
	case WSAEINPROGRESS: msgText = "Operation in progress"; break;
	case WSAEALREADY: msgText = "Operation is already in progress"; break;
	case WSAENOTSOCK: msgText = "Socket set incorrectly"; break;
	case WSAEDESTADDRREQ: msgText = "Location address required"; break;
	case WSAEMSGSIZE: msgText = "Message is too long"; break;
	case WSAEPROTOTYPE: msgText = "Incorrect protocol type for socket"; break;
	case WSAENOPROTOOPT: msgText = "Error in protocol option"; break;
	case WSAEPROTONOSUPPORT: msgText = "Protocol not supported"; break;
	case WSAESOCKTNOSUPPORT: msgText = "Socket type not supported"; break;
	case WSAEOPNOTSUPP: msgText = "Operation not supported"; break;
	case WSAEPFNOSUPPORT: msgText = "Protocol type not supported"; break;
	case WSAEAFNOSUPPORT: msgText = "Address type is not supported by protocol"; break;
	case WSAEADDRNOTAVAIL: msgText = "The requested address cannot be used"; break;
	case WSAENETDOWN: msgText = "Network is down"; break;
	case WSAENETUNREACH: msgText = "Network not reachable"; break;
	case WSAENETRESET: msgText = "Network disconnected"; break;
	case WSAECONNABORTED: msgText = "Programmatic communication failure"; break;
	case WSAECONNRESET: msgText = "Connection not restored"; break;
	case WSAENOBUFS: msgText = "Not enough memory for buffers"; break;
	case WSAEISCONN: msgText = "Socket is already connected"; break;
	case WSAENOTCONN: msgText = "Socket is not connected"; break;
	case WSAESHUTDOWN: msgText = "Cannot send : socket terminated"; break;
	case WSAETIMEDOUT: msgText = "Timeout expired"; break;
	case WSAECONNREFUSED: msgText = "Connection rejected"; break;
	case WSAEHOSTDOWN: msgText = "Host is down"; break;
	case WSAEPROCLIM: msgText = "Too many processes"; break;
	case WSASYSNOTREADY: msgText = "Network is not available"; break;
	case WSAVERNOTSUPPORTED: msgText = "This version is not available"; break;
	case WSANOTINITIALISED: msgText = "WS2_32.dll not initialized"; break;
	case WSAEDISCON: msgText = "Shutdown in progress"; break;
	case WSATYPE_NOT_FOUND: msgText = "Class not found"; break;
	case WSAHOST_NOT_FOUND: msgText = "Host not found"; break;
	case WSATRY_AGAIN: msgText = "Unauthorized host not found"; break;
	case WSANO_RECOVERY: msgText = "Unspecified error"; break;
	case WSANO_DATA: msgText = "No record of requested type"; break;
	case WSA_INVALID_HANDLE: msgText = "Specified event descriptor with error"; break;
	case WSA_INVALID_PARAMETER: msgText = "One or more parameters in error"; break;
	case WSA_IO_INCOMPLETE: msgText = "I / O object not in signaling state"; break;
	case WSA_IO_PENDING: msgText = "Operation will complete later"; break;
	case WSA_NOT_ENOUGH_MEMORY: msgText = "Not enough memory"; break;
	case WSA_OPERATION_ABORTED: msgText = "Operation rejected"; break;
	case WSASYSCALLFAILURE: msgText = "System call aborted"; break;
	default: break;
	}
	return msgText;
};

string SetErrorMsgText(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
};