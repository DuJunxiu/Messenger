
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
		/**
		 * @func desc:	initialize
		 * @param in:
		 * @return:		scucess:0 / otherwise:-1
		 */
		int initialize(void);

		/**
		 * @func desc:	Create Socket
		 * @param in:
		 * @return:		SokcetFD
		 */
		int createSocket(void);

		/**
		 * @func desc:	Bind Socket
		 * @param in:	strIP:IP	usPort:port
		 * @return:		scucess:0 / otherwise:-1
		 */
		int bindAddress(std::string strIP = "", uint16_t usPort = 0);

		/**
		 * @func desc:	Listen Socket
		 * @param in:
		 * @return:		null
		 */
		void listenSocket(void);

		/**
		 * @func desc:	Accept Request
		 * @param in:
		 * @return:		Client SokcetFD
		 */
		int acceptRequest();

	private:
		int m_iServerSockFD;

	};
}

#endif
