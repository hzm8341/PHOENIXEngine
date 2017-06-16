// PX2Bluetooth.cpp

#include "PX2Bluetooth.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2Log.hpp"

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
	mPairedDevices.clear();

	std::string allDeviceStr;

#if defined(__ANDROID__)
	allDeviceStr = BluetoothGetPairedDevices();

	StringTokenizer token(allDeviceStr, ";");
	for (int i = 0; i < token.Count(); i++)
	{
		std::string deviceStr = token[i];
		mPairedDevices.push_back(deviceStr);
	}

#endif

	return mPairedDevices;
}
//----------------------------------------------------------------------------
int Bluetooth::GetNumPairedDevices() const
{
	return (int)mPairedDevices.size();
}
//----------------------------------------------------------------------------
const std::string &Bluetooth::GetPairedDevice(int i) const
{
	if (0 <= i && i < (int)mPairedDevices.size())
		return mPairedDevices[i];

	return 0;
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
	PX2_LOG_INFO("Bluetooth Send %d Str %s", (int)str.length(), str.c_str());

#if defined(__ANDROID__)
	BluetoothSend(str.c_str(), (int)str.length(), isAppendCRLF);
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
	Event *ent = PX2_CREATEEVENTEX(BluetoothES, OnConnected);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Bluetooth::OnConnectFailed()
{
	Event *ent = PX2_CREATEEVENTEX(BluetoothES, OnConnectFailed);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Bluetooth::OnDisConnected()
{
	Event *ent = PX2_CREATEEVENTEX(BluetoothES, OnDisConnected);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Bluetooth::OnDisocveryNewDevice(const std::string &deviceStr)
{
	Event *ent = PX2_CREATEEVENTEX(BluetoothES, OnDisocveryNewDevice);
	ent->SetDataStr0(deviceStr);
	ent->SetData<std::string>(deviceStr);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Bluetooth::OnDiscoveryFinished()
{
	Event *ent = PX2_CREATEEVENTEX(BluetoothES, OnDiscoveryFinished);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Bluetooth::OnReceive(const std::string &recvBuffer)
{
}
//----------------------------------------------------------------------------