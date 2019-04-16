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
		// x坐标，y坐标，机器朝向，速度，角速度
		Vector2f Pos;
		float orientation, velocity, omega;
	};

	struct PX2_ENGINE_ITEM EvaluationPara
	{
		float heading, clearance, velocity, v, w;
	};

#define M_PI 3.1415927
#define MAX_VELOCITY 1.0						//弧形轨迹：最大速度
#define MIN_VELOCITY 0							//弧形轨迹：最小速度
#define MAX_OMEGA 20.0 / 180.0 * M_PI			//弧形轨迹：最大角速度
#define MIN_OMEGA 0								//弧形轨迹：最小角速度
#define MAX_ACCELERATE 0.2						//动态窗口：最大加速度
#define MAX_ACCOMEGA 50.0 / 180.0 * M_PI		//动态窗口：最大角加速度
#define SAMPLING_VELOCITY 0.01					//速度采样间隔
#define SAMPLING_OMEGA 1 / 180.0 * M_PI			//角速度采样间隔
#define DT 0.1									//采样时间间隔
#define PREDICT_TIME 3.0						//预测时间

#define WEIGHT_HEADING 0.05						//HEADING权重
#define WEIGHT_CLEARANCE 0.2					//CLEARANCE权重
#define WEIGHT_VELOCITY 0.1						//VELOCITY权重

#define GOAL_X 10								//目标横坐标
#define GOAL_Y 10								//目标纵坐标
#define ROBOT_RADIUS 0.2						//机器人半径

}

#endif