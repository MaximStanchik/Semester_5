#include "stdafx.h"

string GetErrorMsgText(int errorCode) {
	string msgText;

	switch (errorCode)
	{
	case WSAEINTR:
		msgText = "Function interrupted";
		break;
	case WSAEACCES:
		msgText = "No authorization";
		break;
	case WSAEFAULT:
		msgText = "Wrong address";
		break;
	case WSAEINVAL:
		msgText = "Error in argument";
		break;
	case WSAEMFILE:
		msgText = "Too many files open";
		break;
	case WSAEWOULDBLOCK:
		msgText = "The resource is temporarily unavailable";
		break;
	case WSAEINPROGRESS:
		msgText = "Operation in development";
		break;
	case WSAEALREADY:
		msgText = "The operation is already in progress";
		break;
	case WSAENOTSOCK:
		msgText = "The socket is not set correctly";
		break;
	case WSAEDESTADDRREQ:
		msgText = "Location address required";
		break;
	case WSAEMSGSIZE:
		msgText = "Message is too long";
		break;
	case WSAEPROTOTYPE:
		msgText = "Incorrect protocol type for socket";
		break;
	case WSAENOPROTOOPT:
		msgText = "Error in protocol option";
		break;
	case WSAEPROTONOSUPPORT:
		msgText = "Protocol not supported";
		break;
	case WSAESOCKTNOSUPPORT:
		msgText = "Socket type not supported";
		break;
	case WSAEOPNOTSUPP:
		msgText = "Operation not supported";
		break;
	case WSAEPFNOSUPPORT:
		msgText = "Protocol type not supported";
		break;
	case WSAEAFNOSUPPORT:
		msgText = "Address type not supported by protocol";
		break;
	case WSAEADDRINUSE:
		msgText = "Address already in use";
		break;
	case WSAEADDRNOTAVAIL:
		msgText = "The requested address cannot be used";
		break;
	case WSAENETDOWN:
		msgText = "The network is down";
		break;
	case WSAENETUNREACH:
		msgText = "Network not reachable";
		break;
	case WSAENETRESET:
		msgText = "The network has dropped the connection";
		break;
	case WSAECONNABORTED:
		msgText = "Programmatic communication failure";
		break;
	case WSAECONNRESET:
		msgText = "Connection restored";
		break;
	case WSAENOBUFS:
		msgText = "Not enough memory for buffers";
		break;
	case WSAEISCONN:
		msgText = "Socket already connected";
		break;
	case WSAENOTCONN:
		msgText = "Socket not connected";
		break;
	case WSAESHUTDOWN:
		msgText = "Cannot send : socket terminated";
		break;
	case WSAETIMEDOUT:
		msgText = "Time interval expired";
		break;
	case WSAECONNREFUSED:
		msgText = "Connection rejected";
		break;
	case WSAEHOSTDOWN:
		msgText = "Host in inoperable state";
		break;
	case WSAEHOSTUNREACH:
		msgText = "No route for host";
		break;
	case WSAEPROCLIM:
		msgText = "Too many processes";
		break;
	case WSASYSNOTREADY:
		msgText = "Network not available";
		break;
	case WSAVERNOTSUPPORTED:
		msgText = "This version is not available";
		break;
	case WSANOTINITIALISED:
		msgText = "WS2_32.DLL not initialized";
		break;
	case WSAEDISCON:
		msgText = "Shutdown in progress";
		break;
	case WSATYPE_NOT_FOUND:
		msgText = "Class not found";
		break;
	case WSAHOST_NOT_FOUND:
		msgText = "Host not found";
		break;
	case WSATRY_AGAIN:
		msgText = "Unauthorized host not found";
		break;
	case WSANO_RECOVERY:
		msgText = "Unspecified error";
		break;
	case WSANO_DATA:
		msgText = "No record of requested type";
		break;
	case WSA_INVALID_HANDLE:
		msgText = "Specified error event descriptor";
		break;
	case WSA_INVALID_PARAMETER:
		msgText = "One or more parameters in error";
		break;
	case WSA_IO_INCOMPLETE:
		msgText = "Input - output object not in signaling state";
		break;
	case WSA_IO_PENDING:
		msgText = "Operation will end later";
		break;
	case WSA_NOT_ENOUGH_MEMORY:
		msgText = "Not enough memory";
		break;
	case WSA_OPERATION_ABORTED:
		msgText = "Operation rejected";
		break;
	case WSASYSCALLFAILURE:
		msgText = "System call emergency termination";
		break;
		//case WSAINVALIDPROCTABLE:
		//	msgText = "Error service";
		//	break;
		//case WSAINVALIDPROVIDER:
		//	msgText = "Service version error";
		//	break;
		//case WSAPROVIDERFAILEDINIT:
		//	msgText = "Unable to initialize service";
		//	break;
	default:
		msgText = "Unknow error";
		break;
	}

	return msgText;
}

string SetErrorMsgText(string msgText, int code)
{
	return  msgText + GetErrorMsgText(code);
};