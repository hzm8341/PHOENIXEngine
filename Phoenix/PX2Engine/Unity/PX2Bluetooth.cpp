// PX2Bluetooth.cpp

#include "PX2Bluetooth.hpp"
#include "PX2StringTokenizer.hpp"

#if defined(__ANDROID__)
#include "AppPlayJNI.hpp"
#endif

using namespace PX2;

PX2_IMPLEMENT_EVENT(BluetoothES);

//----------------------------------------------------------------------------
Bluetooth::Bluetooth()
{
}
//----------------------------------------------------------------------------
Bluetooth::~Bluetooth()
{
}
//----------------------------------------------------------------------------
bool Bluetooth::IsAvailable() const
{
#if defined(__ANDROID__)
	return BluetoothIsAvailable();
#endif

	return false;
}
//----------------------------------------------------------------------------
bool Bluetooth::IsConnected() const
{
#if defined(__ANDROID__)
	return BluetoothIsConnected();
#endif

	return false;
}
//----------------------------------------------------------------------------
std::vector<std::string> Bluetooth::GetPairedDevices()
{
	std::vector<std::string> devices;

	std::string allDeviceStr;

#if defined(__ANDROID__)
	allDeviceStr = BluetoothGetPairedDevices();

	StringTokenizer token(allDeviceStr, ";");
	for (int i = 0; i < token.Count(); i++)
	{
		std::string deviceStr = token[i];
		devices.push_back(deviceStr);
	}

#endif

	return devices;
}
//----------------------------------------------------------------------------
void Bluetooth::DisConnect()
{
#if defined(__ANDROID__)
	BluetoothDisConnect();
#endif
}
//----------------------------------------------------------------------------
void Bluetooth::Connect(const std::string &addr)
{
	PX2_UNUSED(addr);

#if defined(__ANDROID__)
	BluetoothConnect(addr.c_str());
#endif
}
//----------------------------------------------------------------------------
void Bluetooth::Send(const std::string &str, bool isAppendCRLF)
{
	PX2_UNUSED(str);
	PX2_UNUSED(isAppendCRLF);

#if defined(__ANDROID__)
	BluetoothSend(str.c_str(), isAppendCRLF);
#endif
}
//----------------------------------------------------------------------------
void Bluetooth::DoDiscovery()
{
#if defined(__ANDROID__)
	BluetoothDoDiscovery();
#endif
}
//----------------------------------------------------------------------------
void Bluetooth::CancelDiscovery()
{
#if defined(__ANDROID__)
	BluetoothCancelDiscovery();
#endif
}
//----------------------------------------------------------------------------
void Bluetooth::OnConnected()
{
	Event *ent = BluetoothES::CreateEventX(BluetoothES::OnConnected);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Bluetooth::OnConnectFailed()
{
	Event *ent = BluetoothES::CreateEventX(BluetoothES::OnConnectFailed);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Bluetooth::OnDisConnected()
{
	Event *ent = BluetoothES::CreateEventX(BluetoothES::OnDisConnected);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Bluetooth::OnDisocveryNewDevice(const std::string &deviceStr)
{
	Event *ent = BluetoothES::CreateEventX(BluetoothES::OnDisocveryNewDevice);
	ent->SetData<std::string>(deviceStr);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Bluetooth::OnDiscoveryFinished()
{
	Event *ent = BluetoothES::CreateEventX(BluetoothES::OnDiscoveryFinished);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------