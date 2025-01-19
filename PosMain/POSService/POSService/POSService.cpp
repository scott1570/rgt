


#include "json/json.h"

#include "Win32_Service.h"

#pragma warning(disable:4996) 
bool exitflag = false;




class Service : public WindowsService {
	using WindowsService::WindowsService;


	void respond(SOCKET sock)
	{
		const char* response =
			"HTTP/1.1 200 OK\r\n"
			"Connection: close\r\n"
			"Content-Type: text/plain\r\n\r\n"
			"Local time is: ";
		int bytes_sent = send(sock, response, strlen(response), 0);
		printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));

	}

	  void startServerThread() {
		DWORD dwid = 0;
		DWORD dwid2 = 0;
		::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CommandServerThread, this, 0, &dwid);
		::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ProxyServerThread, this, 0, &dwid2);
	}
	int parseJson(char* json) {

		Json::Value root;
		Json::Reader reader;
		bool parse_result = reader.parse(json, root);
		if (!parse_result) {
		
			printf("cannot parse\n");
			return -1;
		}
		printf("name : %s\n", root["name"].asString().c_str());
		printf("name : %s\n", root["number"].asString().c_str());
		printf("name : %s\n", root["table"].asString().c_str());

		return 0;
	}

	int read_exact(SOCKET s, char* pbuff, int size)
	{
		int iResult;
		struct timeval tv;
		fd_set rfds;

		FD_ZERO(&rfds);
		FD_SET(s, &rfds);

		tv.tv_sec = (long)2;
		tv.tv_usec = 0;

		iResult = select(s + 1, &rfds, (fd_set*)0, (fd_set*)0, &tv);
		if (iResult > 0)
		{
			return recv(s, pbuff, size, 0);
		}


		return 0;
	}
protected:
	virtual DWORD WINAPI worker(LPVOID) {
		//  Periodically check if the service has been requested to stop
		while (WaitForSingleObject(stopEvent, 0) != WAIT_OBJECT_0) {



			
			
			// Pause on pauseEvent
			if (WaitForSingleObject(pauseEvent, 0) != WAIT_OBJECT_0) {

				/*
				* Perform main service functionality here
				*/

				//  Simulate work



			}
			else {
				confirm_pause();
				// Wait for continue to be thrown
				WaitForSingleObject(continueEvent, INFINITE);
				confirm_continue();
			}
		}

		return ERROR_SUCCESS;
	}

	// Gets called during startup.
	virtual void on_startup() {
		/*
		 * Perform tasks necessary to start the service here.
		 */
	}

	// Gets called when pause is thrown and pause/continue is enabled.
	virtual void on_pause() {
		/*
		 * Perform tasks necessary to pause the service here.
		 */
	}

	// Gets called when continue is thrown and pause/continue is enabled.
	virtual void on_continue() {
		/*
		 * Perform tasks necessary to continue the service here.
		 */
	}

	// Gets called when the windows service controller tells service to stop, but BEFORE stopEvent is thrown.
	virtual void on_stop() {
		/*
		 * Perform tasks necessary to stop the service loop here.
		 */
	}

	// Gets called all the way at the end of the liecycle.
	virtual void on_exit() {
		/*
		 * Perform tasks necessary for cleanup.
		 */
	}

	// What to do when the service fails to regiser.
	// By default it runs test_startStop();
	virtual void on_failedRegistration() {
		/*
		 * what to do when registration fails...
		 */
		test_startStop();
	}






	static LPVOID CommandServerThread(LPVOID param) {



		Service* pthis = (Service*)param;

		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);




		SOCKADDR_IN sockaddr;
		sockaddr.sin_port = htons(5678);
		sockaddr.sin_family = AF_INET;
		sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

		char option = 1;
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

		if (bind(sock, (SOCKADDR*)&sockaddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
			return 0;
		}

		if (listen(sock, 5) == SOCKET_ERROR) {
			return 0;
		}



		char buf[1024] = { 0 };
		while (true) {

			SOCKET asock = accept(sock, NULL, 0);

			if (exitflag)
				break;

			if (asock == INVALID_SOCKET)
				break;
			int recved = pthis->read_exact(asock, buf, sizeof(buf));

			printf("buff: %s\n", buf);



			char* pJsonBody = strstr(buf, "{");
			if (recved == 0)
				closesocket(asock);


			printf("json body : %s\n", pJsonBody);
			printf("recved : %d\n", recved);
			pthis->parseJson(pJsonBody);
			pthis->respond(asock);

			closesocket(asock);
		}


		return NULL;

	}
	static LPVOID ProxyServerThread(LPVOID param) {

		while (true)
		{

			if (exitflag)
				break;

		}

		return NULL;

	}

};


	



int main(int, TCHAR) {



	WSADATA wsa; // Windows 소켓 구현에 대한 구조체 생성

	// WSAStartup을 통해 wsadata 초기화
	// MAKEWORD(2,2) 매개 변수는 시스템에서 Winsock 버전 2.2를 요청
	// WSAStartup은 성공시 0, 실패시 SOCKET_ERROR를 리턴하므로
	// 리턴값이 0인지 검사하여 에러 여부 확인
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {

		return 0;
	}



	Service test("POSService", true);
	//test.SvcInstall("POSService");
	test.run();
	

	WSACleanup();
	return 0;
}
