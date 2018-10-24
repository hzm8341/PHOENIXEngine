// PX2WRLiDar.hpp

#ifndef PX2WRLIDAR_HPP
#define PX2WRLIDAR_HPP

#include "PX2CorePre.hpp"
#include "PX2UDPServer.hpp"
#include "PX2AILidarData.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM WRLidar
	{
	public:
		WRLidar();
		~WRLidar();

		void Start(const std::string &ip, int port);
		void Stop();
		void Update(float appSeconds, float elapsedSeconds);
		
		bool Set_scanning_parameters(int iFirstStepIndex, int iLastStepIndex);
		bool Start_measurement();

		std::vector<RslidarDataComplete> RDCS;

	private:
		UDPServerPtr mUPDServer;
		std::string mIP;
		int mPort;
		SocketAddress mSocketAddress;
		bool is_actived;
	};
	typedef Pointer0<WRLidar> WRLidarPtr;

}

#endif