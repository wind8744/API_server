#include <WinSock2.h>
#include <iostream>
#include <process.h>
#include <list>

#pragma comment(lib,"ws2_32.lib")

enum class NetworkProtocol
{
	Chat
};

std::list<SOCKET> g_UserList;

// ������ ����
unsigned int __stdcall RecvThread(void* Arg)
{
	SOCKET Sock = (SOCKET)Arg;
	
	while (true)
	{
		char Packet[1024] = {};
		int Length = recv(Sock, Packet, 1024, 0);

		std::cout << "Recv Length : " << Length << std::endl;

		if (Length == -1)
			break;

		auto iter = g_UserList.begin();
		auto iterEnd = g_UserList.end();

		for (; iter != iterEnd; ++iter)
		{
			if (*iter == Sock)
				continue;

			send(*iter, Packet, Length, 0);
		}

	}

	closesocket(Sock);

	return 0;
}

int main()
{
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);

	// 1. Server Socket ����
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN Addr = {};
	Addr.sin_family = PF_INET;
	Addr.sin_addr.s_addr = htonl(INADDR_ANY);
	Addr.sin_port = htons(6000);

	// 2. bind
	bind(ListenSocket, (SOCKADDR*)&Addr, sizeof(Addr));

	// 3. listen
	listen(ListenSocket, 10);

	while (true)
	{
		SOCKADDR_IN ClientAddr = {};
		int Size = sizeof(ClientAddr);

		// 4. accept (Ŭ���̾�Ʈ�� ���� ��û�� accept �� �Ǿ�� ����)
		SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientAddr, &Size);

		std::cout << ClientSocket << "Client connnect " << std::endl;

		g_UserList.push_back(ClientSocket); // * ������ ��� �߰��Ұ�

		// 5. recv ������ ȣ��
		HANDLE Thread = (HANDLE)_beginthreadex(0, 0, RecvThread, (void*)ClientSocket, 0, 0);
	}

	// 6. close
	closesocket(ListenSocket);

	// ������ ���� ��� ����
	WSACleanup();

	return 0;
}