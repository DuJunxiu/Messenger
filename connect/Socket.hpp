
#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include <string>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace MyMessenger
{
	const int MAX_LISTEN_SOCKET_COUNT = 5;
	
	class CSocket
	{
	public:
		CSocket()	{}
		~CSocket()	{}

	public:
		// 初始化
		int initialize(void);

		// 创建socket
		int createSocket(void);

		// 绑定地址
		int bindAddress(std::string strIP = "", uint16_t usPort = 0);

		// 监听socket
		void listenSocket(void);

		// 接收消息
		int acceptRequest();

	private:
		int m_iServerSockFD;

	};
}

#endif
