// PX2AILiDar.hpp

#ifndef PX2AILIDAR_HPP
#define PX2AILIDAR_HPP

#include "PX2CorePre.hpp"
#include "PX2Object.hpp"
#include "PX2UIFPicBox.hpp"
#include "PX2Memory.hpp"

namespace everest
{
	namespace hwdrivers
	{
		class C3iroboticsLidar;
		class CDeviceConnection;
	}
}

class SinglePositionSLAM;

namespace PX2
{

	class Rover;

	typedef struct _rslidar_data
	{
		_rslidar_data()
		{
			signal = 0;
			angle = 0.0;
			distance = 0.0;
		}
		uint8_t signal;
		float   angle;
		float   distance;
	}RslidarDataComplete;

	class PX2_ENGINE_ITEM LiDar : public Object
	{
	public:
		LiDar();
		virtual ~LiDar();

		static LiDar *New();

		bool Open(const std::string &port, int baud);
		bool IsOpened() const;
		void Close();

		void Update(float appSeconds, float elapsedSeconds);

		Texture2D *GetTexture();
		UIFPicBox *GetUIFPicBox();

		void SetPosColor(int posWidth, int posHeight, int r, int g, int b);

	protected:
		everest::hwdrivers::C3iroboticsLidar *mLiDar;
		everest::hwdrivers::CDeviceConnection *mDeviceConnectin;

		Texture2DPtr mTexture;
		UIFPicBoxPtr mPicBox;
		UIFPicBoxPtr mCurPosPic;
		std::vector<RslidarDataComplete> mLiDarData;

		Rover *mRover;
		unsigned char *mMapData;
		SinglePositionSLAM *mSlam;
	};

}

#endif