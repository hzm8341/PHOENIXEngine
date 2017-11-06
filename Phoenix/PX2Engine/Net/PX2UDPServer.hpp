// PX2UDPServer.hpp

#ifndef PX2UDPSERVER_HPP
#define PX2UDPSERVER_HPP

#include "PX2Runnable.hpp"
#include "PX2SocketAddress.hpp"
#include "PX2DatagramSocket.hpp"
#include "PX2Thread.hpp"
#include "PX2Eventt.hpp"
#include "PX2Mutex.hpp"
#include "PX2Object.hpp"

namespace PX2
{

	typedef void(*UDPServerRecvCallback) (SocketAddress &address,
		const std::string &buf);

	class PX2_ENGINE_ITEM UDPServer : public Object, public Runnable
	{
	public:
		UDPServer();
		UDPServer(const SocketAddress& sa);
		~UDPServer();

		void Start();
		void Stop();

		DatagramSocket &GetSocket();
		int GetPort() const;
		SocketAddress GetAddress() const;
		void Update(float elapsedSeconds);

		virtual void Run();

		bool IsHasRecvCallback(UDPServerRecvCallback callback);
		void AddRecvCallback(UDPServerRecvCallback callback);
		void OnRecv(SocketAddress &address, const std::string &buf);

		bool IsHasOnRecvCallback(const std::string &callback) const;
		bool AddOnRecvCallback(const std::string &callback);
		bool RemoveOnRecvCallback(const std::string &callback);

	private:
		DatagramSocket mSocket;
		Thread mThread;
		Eventt mReadEvent;
		bool mIsStop;

		Mutex mMutex;
		std::vector<std::pair<SocketAddress, std::string> > mRecvBufs;
		std::vector<UDPServerRecvCallback> mUDPServerRecvCallbacks;

		std::vector<std::string> mOnRecvCallbacks;
	};
	typedef Pointer0<UDPServer> UDPServerPtr;

}

#endif