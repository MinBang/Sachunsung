#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

int recvn(SOCKET s, char* buf, int len, int flags);

int IniTCPServerM(int port, int(*Serverproc)(SOCKET c, SOCKADDR_IN* caddr));

int IniTCPServerMEx(int port, int(*proc)(SOCKET c, SOCKADDR_IN* caddr));

int IniTCPClient(char* ip, int port, int(*fn)(SOCKET s));

int IniTCPClientEx(char* ip, int port, int(*fn)(SOCKET s));