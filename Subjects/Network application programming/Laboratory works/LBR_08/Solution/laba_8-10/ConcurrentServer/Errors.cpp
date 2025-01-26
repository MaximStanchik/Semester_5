#include "stdafx.h"
#include "Errors.h"

string  GetErrorMsgText(int code)
{
	string msgText;
	switch (code)
	{
	case WSAEINTR:               msgText = "WSAEINTR";				 break;
	case WSAEACCES:              msgText = "WSAEACCES";				 break;						    
	case WSAEFAULT:              msgText = "WSAEFAULT";				 break;
	case WSAEINVAL:              msgText = "WSAEINVAL";				 break;
	case WSAEMFILE:              msgText = "WSAEMFILE";              break;
	case WSAEWOULDBLOCK:         msgText = "WSAEWOULDBLOCK";         break;
	case WSAEINPROGRESS:         msgText = "WSAEINPROGRESS";         break;
	case WSAEALREADY:            msgText = "WSAEALREADY";            break;
	case WSAENOTSOCK:            msgText = "WSAENOTSOCK";            break;
	case WSAEDESTADDRREQ:        msgText = "WSAEDESTADDRREQ";        break;
	case WSAEMSGSIZE:            msgText = "WSAEMSGSIZE";            break;
	case WSAEPROTOTYPE:          msgText = "WSAEPROTOTYPE";          break;
	case WSAENOPROTOOPT:         msgText = "WSAENOPROTOOPT";         break;
	case WSAEPROTONOSUPPORT:     msgText = "WSAEPROTONOSUPPORT";     break;
	case WSAESOCKTNOSUPPORT:     msgText = "WSAESOCKTNOSUPPORT";     break;
	case WSAEOPNOTSUPP:          msgText = "WSAEOPNOTSUPP";          break;
	case WSAEPFNOSUPPORT:        msgText = "WSAEPFNOSUPPORT";        break;
	case WSAEAFNOSUPPORT:        msgText = "WSAEAFNOSUPPORT";        break;
	case WSAEADDRINUSE:          msgText = "WSAEADDRINUSE";          break;
	case WSAEADDRNOTAVAIL:       msgText = "WSAEADDRNOTAVAIL";       break;
	case WSAENETDOWN:            msgText = "WSAENETDOWN";            break;
	case WSAENETUNREACH:         msgText = "WSAENETUNREACH";         break;
	case WSAENETRESET:           msgText = "WSAENETRESET";           break;
	case WSAECONNABORTED:        msgText = "WSAECONNABORTED";        break;
	case WSAECONNRESET:          msgText = "WSAECONNRESET";          break;
	case WSAENOBUFS:             msgText = "WSAENOBUFS";             break;
	case WSAEISCONN:             msgText = "WSAEISCONN";             break;
	case WSAENOTCONN:            msgText = "WSAENOTCONN";            break;
	case WSAESHUTDOWN:           msgText = "WSAESHUTDOWN";           break;
	case WSAETIMEDOUT:           msgText = "WSAETIMEDOUT";           break;
	case WSAECONNREFUSED:        msgText = "WSAECONNREFUSED";        break;
	case WSAEHOSTDOWN:           msgText = "WSAEHOSTDOWN";           break;
	case WSAEHOSTUNREACH:        msgText = "WSAEHOSTUNREACH";        break;
	case WSAEPROCLIM:            msgText = "WSAEPROCLIM";            break;
	case WSASYSNOTREADY:         msgText = "WSASYSNOTREADY";         break;
	case WSAVERNOTSUPPORTED:     msgText = "WSAVERNOTSUPPORTED";     break;
	case WSANOTINITIALISED:      msgText = "WSANOTINITIALISED";      break;
	case WSAEDISCON:             msgText = "WSAEDISCON";             break;
	case WSATYPE_NOT_FOUND:      msgText = "WSATYPE_NOT_FOUND";      break;
	case WSAHOST_NOT_FOUND:      msgText = "WSAHOST_NOT_FOUND";      break;
	case WSATRY_AGAIN:           msgText = "WSATRY_AGAIN";           break;
	case WSANO_RECOVERY:         msgText = "WSANO_RECOVERY";         break;
	case WSANO_DATA:             msgText = "WSANO_DATA";             break;
	case WSA_INVALID_HANDLE:     msgText = "WSA_INVALID_HANDLE";     break;
	case WSA_INVALID_PARAMETER:  msgText = "WSA_INVALID_PARAMETER";  break;
	case WSA_IO_INCOMPLETE:      msgText = "WSA_IO_INCOMPLETE";      break;
	case WSA_IO_PENDING:         msgText = "WSA_IO_PENDING";         break;
	case WSA_NOT_ENOUGH_MEMORY:  msgText = "WSA_NOT_ENOUGH_MEMORY";  break;
	case WSA_OPERATION_ABORTED:  msgText = "WSA_OPERATION_ABORTED";  break;
	case WSAEINVALIDPROCTABLE:   msgText = "WSAEINVALIDPROCTABLE";   break;
	case WSAEINVALIDPROVIDER:    msgText = "WSAEINVALIDPROVIDER";    break;
	case WSAEPROVIDERFAILEDINIT: msgText = "WSAEPROVIDERFAILEDINIT"; break;

	case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE"; break;
	default:                msgText = "***ERROR***";      break;
	};
	return msgText;
};

string  SetErrorMsgText(string msgText, int code)
{
	return  msgText + GetErrorMsgText(code);
};

string  SetPipeError(string msgText, int code)
{
	return  msgText + GetErrorMsgText(code);
};






//#include "stdafx.h"
//
//string GetErrorMsgText(int code) // c����������� ����� ������
//{
//	string msgText;
//	switch (code)
//	{
//	case WSAEINTR: msgText = "������ ������� ��������"; break;
//	case WSAEACCES:	msgText = "���������� ����������"; break;
//	case WSAEFAULT: msgText = "��������� �����"; break;
//	case WSAEINVAL:	msgText = "������ � ���������";	break;
//	case WSAEMFILE:	msgText = "������� ������� ����� ������"; break;
//	case WSAEWOULDBLOCK: msgText = "������ �������� ����������"; break;
//	case WSAEINPROGRESS: msgText = "�������� � �������� ��������"; break;
//	case WSAEALREADY: msgText = "�������� ��� �����������";	break;
//	case WSAENOTSOCK: msgText = "����� ����� �����������"; break;
//	case WSAEDESTADDRREQ: msgText = "��������� ����� ������������"; break;
//	case WSAEMSGSIZE: msgText = "��������� ������� �������"; break;
//	case WSAEPROTOTYPE: msgText = "������������ ��� ��������� ��� ������"; break;
//	case WSAENOPROTOOPT: msgText = "������ � ����� ���������"; break;
//	case WSAEPROTONOSUPPORT: msgText = "�������� �� ��������������"; break;
//	case WSAESOCKTNOSUPPORT: msgText = "��� ������ �� ��������������"; break;
//	case WSAEOPNOTSUPP: msgText = "�������� �� ��������������"; break;
//	case WSAEPFNOSUPPORT: msgText = "��� ���������� �� ��������������"; break;
//	case WSAEAFNOSUPPORT: msgText = "��� ������� �� �������������� ����������"; break;
//	case WSAEADDRINUSE: msgText = "����� ��� ������������"; break;
//	case WSAEADDRNOTAVAIL: msgText = "����������� ����� �� ����� ���� �����������"; break;
//	case WSAENETDOWN: msgText = "���� ���������"; break;
//	case WSAENETUNREACH: msgText = "���� �� ���������"; break;
//	case WSAENETRESET: msgText = "���� ��������� ����������"; break;
//	case WSAECONNABORTED: msgText = "����������� ����� �����"; break;
//	case WSAECONNRESET: msgText = "����� �� �������������"; break;
//	case WSAENOBUFS: msgText = "�� ������� ������ ��� �������"; break;
//	case WSAEISCONN: msgText = "����� ��� ���������"; break;
//	case WSAENOTCONN: msgText = "����� �� ���������"; break;
//	case WSAESHUTDOWN: msgText = "������ ��������� send: ����� �������� ������"; break;
//	case WSAETIMEDOUT: msgText = "���������� ���������� �������� �������"; break;
//	case WSAECONNREFUSED: msgText = "���������� ���������"; break;
//	case WSAEHOSTDOWN: msgText = "���� � ����������������� ���������"; break;
//	case WSAEHOSTUNREACH: msgText = "��� �������� ��� �����"; break;
//	case WSAEPROCLIM: msgText = "������� ����� ���������"; break;
//	case WSASYSNOTREADY: msgText = "���� �� ��������"; break;
//	case WSAVERNOTSUPPORTED: msgText = "������ ������ ����������"; break;
//	case WSANOTINITIALISED: msgText = "�� ��������� ������������� WS2_32.dll"; break;
//	case WSAEDISCON: msgText = "����������� ����������"; break;
//	case WSATYPE_NOT_FOUND: msgText = "����� �� ������"; break;
//	case WSAHOST_NOT_FOUND: msgText = "���� �� ������"; break;
//	case WSATRY_AGAIN: msgText = "���������������� ���� �� ������"; break;
//	case WSANO_RECOVERY: msgText = "�������������� ������"; break;
//	case WSANO_DATA: msgText = "��� ������ ������������ ����"; break;
//	case WSA_INVALID_HANDLE: msgText = "��������� ���������� ������� � �������"; break;
//	case WSA_INVALID_PARAMETER: msgText = "���� ��� ����� ���������� � �������"; break;
//	case WSA_IO_INCOMPLETE: msgText = "������ �����-������ �� � ���������� ���������"; break;
//	case WSA_IO_PENDING: msgText = "�������� ���������� �����"; break;
//	case WSA_NOT_ENOUGH_MEMORY: msgText = "�� ���������� ������"; break;
//	case WSA_OPERATION_ABORTED: msgText = "�������� ����������"; break;
//	case WSASYSCALLFAILURE: msgText = "��������� ���������� ���������� ������"; break;
//	default: break;
//	}
//	return msgText;
//};
//
//string SetErrorMsgText(string msgText, int code)
//{
//	return msgText + GetErrorMsgText(code);
//};