// PX2RobotDatas.hpp

#ifndef PX2ROBOTDATAS_HPP
#define PX2ROBOTDATAS_HPP

#include "PX2CorePre.hpp"
#include "PX2APoint.hpp"
#include "PX2Object.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM Slam3DPoint
	{
	public:
		Slam3DPoint();
		~Slam3DPoint();

		int64_t Key;
		APoint Pos;
		bool IsBad;
	};

	class PX2_ENGINE_ITEM RobotMapDataStruct
	{
	public:
		RobotMapDataStruct();
		~RobotMapDataStruct();

		int MapSize;
		float MapResolution;
		int IndexX;
		int IndexY;
		APoint CurPos;
		float CurAngle;
	};

	class PX2_ENGINE_ITEM RobotMapData : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(RobotMapData);

	public:
		RobotMapData();
		virtual ~RobotMapData();

		void ConvertOriginToUsing();

	public:
		std::vector<unsigned char> _ExtendLarger(
			std::vector<unsigned char> &mapping, bool usSelfDraw);
		void _SetMapUsingData(std::vector<unsigned char> &maping, 
			int x, int y, int val);

		RobotMapDataStruct MapStruct;
		std::vector<unsigned char> Map2DOrigin;
		std::vector<unsigned char> SelfDrawMapData2D;
		std::vector<unsigned char> LineDrawMapData2D;

		std::vector<unsigned char> Map2DUsing;
	};

	PX2_REGISTER_STREAM(RobotMapData);
	typedef Pointer0<RobotMapData> RobotMapDataPtr;

}

#endif