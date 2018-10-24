// PX2WRLidar.hpp

#include "PX2WRLidar.hpp"
#include "PX2WRConstant.hpp"
#include "PX2AILidarData.hpp"
using namespace PX2;

struct DataSaveSt
{
	unsigned int   iTotalFrameIndex;
	unsigned char  subPkgNum;
	unsigned char  subPkgIndex;
	unsigned int   iRawDataLens;
	unsigned char  sens_data[CMD_FRAME_MAX_LEN];
};
int first_step_index;
int last_step_index;
unsigned int iFrameTotalIndex = 0;
int rawDatalen = 0;
unsigned char subPkgNum;
unsigned char subPkgIndex;
unsigned char checkSum = 0;
DataSaveSt mDataSaveSt[CMD_FRAME_MAX_SUB_PKG_NUM];
int iCurFrameNumber;
std::vector<int> iDistance;
std::vector<int> iIntensity;
#define angleResolution 1.0/3.0
//----------------------------------------------------------------------------
void _Lidar_UDPServerRecvCallback (UDPServer *server, SocketAddress &address,
	const std::string &buf, int length)
{
	const char *recvBuf = buf.c_str();

	rawDatalen = ((*(recvBuf + CMD_FRAME_HEADER_LENGTH_H) << 8) | (*(recvBuf + CMD_FRAME_HEADER_LENGTH_L))) - (CMD_FRAME_DATA_START - CMD_FRAME_HEADER_CHECK_SUM);
	iFrameTotalIndex = (*(recvBuf + CMD_FRAME_HEADER_TOTAL_INDEX_H) << 8) | (*(recvBuf + CMD_FRAME_HEADER_TOTAL_INDEX_L));
	subPkgNum = *(recvBuf + CMD_FRAME_HEADER_SUB_PKG_NUM);
	subPkgIndex = *(recvBuf + CMD_FRAME_HEADER_SUB_INDEX);
	checkSum = 0;
	for (int i = 0; i < rawDatalen + (CMD_FRAME_DATA_START - CMD_FRAME_HEADER_TYPE); i++)
	{
		checkSum += recvBuf[CMD_FRAME_HEADER_TYPE + i];
	}
	if (checkSum != recvBuf[CMD_FRAME_HEADER_CHECK_SUM])
	{
		return;
	}
	mDataSaveSt[subPkgIndex].iTotalFrameIndex = iFrameTotalIndex;
	mDataSaveSt[subPkgIndex].iRawDataLens = rawDatalen;
	mDataSaveSt[subPkgIndex].subPkgNum = subPkgNum;
	mDataSaveSt[subPkgIndex].subPkgIndex = subPkgIndex;
	memcpy(mDataSaveSt[subPkgIndex].sens_data, recvBuf + CMD_FRAME_DATA_START, rawDatalen);
	bool checkResult = true;
	for (int i = 0; i < subPkgNum - 1; i++)
	{
		if (mDataSaveSt[i].iTotalFrameIndex != mDataSaveSt[i + 1].iTotalFrameIndex || mDataSaveSt[i].subPkgIndex != mDataSaveSt[i + 1].subPkgIndex - 1)
		{
			checkResult = false;
			return;
		}
	}
	if (!checkResult)
	{
		return;
	}

	///////校验通过情况,获取距离信息
	std::vector<int> vcDistance;
	std::vector<int> vcIntensity;
	int iCurDataNumber = mDataSaveSt[0].iRawDataLens / 2;
	for (int i = 0; i < iCurDataNumber; i++)
	{
		vcDistance.push_back(mDataSaveSt[0].sens_data[2 * i] * 256 + mDataSaveSt[0].sens_data[2 * i + 1]);
		vcIntensity.push_back(mDataSaveSt[2].sens_data[2 * i] * 256 + mDataSaveSt[2].sens_data[2 * i + 1]);
	}
	iCurDataNumber = mDataSaveSt[1].iRawDataLens / 2;
	for (int i = 0; i < iCurDataNumber; i++)
	{
		vcDistance.push_back(mDataSaveSt[1].sens_data[2 * i] * 256 + mDataSaveSt[1].sens_data[2 * i + 1]);
		vcIntensity.push_back(mDataSaveSt[3].sens_data[2 * i] * 256 + mDataSaveSt[3].sens_data[2 * i + 1]);
	}
	for (int i = first_step_index; i <= last_step_index; i++)
	{
		iDistance.push_back(vcDistance[i]);
		iIntensity.push_back(vcIntensity[i] > 5000 ? (vcIntensity[i] > 55000 ? 600 : 200 + (vcIntensity[i] - 5000) / 1200) : vcIntensity[i] / 25);
	}
	iCurFrameNumber = mDataSaveSt[0].iTotalFrameIndex;

	std::vector<RslidarDataComplete> lidarDataThread;
	lidarDataThread.resize(vcDistance.size());

	RslidarDataComplete rdc;
	for (int i = 0; i < (int)vcDistance.size(); i++)
	{
		rdc.signal = vcIntensity[i];
		rdc.distance = vcDistance[i] * 0.001f;
		rdc.angle = (i*angleResolution - 45);

		lidarDataThread[i] = rdc;
	}

	WRLidar *lidar = (WRLidar*)server->GetUserDataPointer("Parent");
	lidar->RDCS = lidarDataThread;
}
//----------------------------------------------------------------------------
WRLidar::WRLidar()
{
	mUPDServer = new0 UDPServer();
	mUPDServer->Bind(2112);
	mUPDServer->AddRecvCallback(_Lidar_UDPServerRecvCallback);

	mUPDServer->SetUserDataPointer("Parent", this);
}
//----------------------------------------------------------------------------
WRLidar::~WRLidar()
{
}
//----------------------------------------------------------------------------
void WRLidar::Start(const std::string &ip, int port)
{
	mIP = ip;
	mPort = port;

	mSocketAddress = SocketAddress(mIP, (int16_t)mPort);

	mUPDServer->Start();

	Start_measurement();
}
//----------------------------------------------------------------------------
void WRLidar::Stop()
{
	mUPDServer->Stop();
}
//----------------------------------------------------------------------------
void WRLidar::Update(float appSeconds, float elapsedSeconds)
{
	if (mUPDServer)
	{
		mUPDServer->Update(elapsedSeconds);
	}
}
//----------------------------------------------------------------------------
bool WRLidar::Set_scanning_parameters(int iFirstStepIndex, int iLastStepIndex)
{
	if (iFirstStepIndex < 0 || iLastStepIndex>810 || iFirstStepIndex > iLastStepIndex)
		return false;
	else
	{
		first_step_index = iFirstStepIndex;
		last_step_index = iLastStepIndex;
		return true;
	}
}
//----------------------------------------------------------------------------
bool WRLidar::Start_measurement()
{
	int iSendNumber;
	int sendVal = mUPDServer->GetSocket().SendTo(CMD_START_SCAN, SIZE_OF_CMD, 
		mSocketAddress);
	
	if (sendVal != SIZE_OF_CMD)
	{
		is_actived = false;
		return false;
	}

	is_actived = true;
	
	return true;
}
//----------------------------------------------------------------------------