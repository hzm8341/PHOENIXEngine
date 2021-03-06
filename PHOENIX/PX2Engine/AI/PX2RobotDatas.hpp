// PX2RobotDatas.hpp

#ifndef PX2ROBOTDATAS_HPP
#define PX2ROBOTDATAS_HPP

#include "PX2CorePre.hpp"
#include "PX2APoint.hpp"
#include "PX2Object.hpp"

namespace PX2
{

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

		void ConvertOriginToUsing(bool isSimple);

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

	struct PX2_ENGINE_ITEM RobotState
	{
		RobotState();
		~RobotState();

		// x坐标，y坐标，机器朝向，速度，角速度
		Vector2f Pos;
		float Orientation;
		float LeftSpeed;
		float RightSpeed;
	};

	struct PX2_ENGINE_ITEM EvaluationPara
	{
		EvaluationPara();
		~EvaluationPara();

		int Index;

		float DiffHeading;
		float Clearance;
		float Leftspped;
		float RightSpeed;
		float Speed;

		float LastValue;
	};

}

#endif