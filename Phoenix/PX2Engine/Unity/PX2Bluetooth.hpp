// PX2Bluetooth.hpp

#ifndef PX2BLUETOOTH_HPP
#define PX2BLUETOOTH_HPP

#include "PX2UnityPre.hpp"
#include "PX2Singleton_NeedNew.hpp"
#include "PX2EventSystem.hpp"

namespace PX2
{

	PX2_DECLARE_EVENT_BEGIN(PX2_ENGINE_ITEM BluetoothES)
	PX2_EVENT(OnConnected)
	PX2_EVENT(OnDisConnected)
	PX2_EVENT(OnConnectFailed)
	PX2_EVENT(OnDisocveryNewDevice)
	PX2_EVENT(OnDiscoveryFinished)
	PX2_DECLARE_EVENT_END(BluetoothES)

	class PX2_ENGINE_ITEM Bluetooth : public Singleton<Bluetooth>
	{
	public:
		Bluetooth();
		~Bluetooth();

		bool IsAvailable() const;
		bool IsConnected() const;

		std::vector<std::string> GetPairedDevices();

		int GetNumPairedDevices() const;
		const std::string &GetPairedDevice(int i) const;

		void DisConnect();
		void Connect(const std::string &addr);
		void Send(const std::string &str, bool isAppendCRLF);
		
		void DoDiscovery();
		void CancelDiscovery();
		void OnDisocveryNewDevice(const std::string &deviceStr);
		void OnDiscoveryFinished();
		void OnConnected();
		void OnConnectFailed();
		void OnDisConnected();
		void OnReceive(const std::string &recvBuffer);

	protected:
		std::vector<std::string> mPairedDevices;
	};

#define PX2_BLUETOOTH Bluetooth::GetSingleton()

}

#endif