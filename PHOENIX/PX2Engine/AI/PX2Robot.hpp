// PX2Robot.hpp

#ifndef PX2SLAM_HPP
#define PX2SLAM_HPP

#include "PX2CorePre.hpp"
#include "PX2Singleton_NeedNew.hpp"
#include "PX2Camera.hpp"
#include "PX2Canvas.hpp"
#include "PX2Scene.hpp"
#include "PX2UIVlc.hpp"
#include "PX2HMatrix.hpp"
#include "PX2RobotDatas.hpp"
#include "PX2AILiDar.hpp"
#include "PX2Polypoint.hpp"
#include "PX2Serial.hpp"
#include "PX2Timestamp.hpp"
#include "PX2AIPath.hpp"
#include "PX2Arduino.hpp"
#include "PX2Smoother.hpp"
#include "PX2SmartPointer.hpp"
#include "PX2Actor.hpp"
#include "PX2RRTEnviroment.hpp"

namespace PX2
{

	class VoxelSection;

#define PX2_USE_SLAM2D
#if defined PX2_USE_SLAM2D
	class Slam2DPlugin;
#endif

	class AIAgentBase;

	class PX2_ENGINE_ITEM Robot : public Singleton<Robot>
	{
	public:
		Robot();
		virtual ~Robot();

		void Update(float appseconds, float elpasedSeconds);

		UIFrame *GetUIFrame();
		UIVlc *GetUIVlc();

		void SetOffset(const AVector &offset);
		const AVector &GetOffset() const;

		void SetVoxelSection(VoxelSection *vs);
		VoxelSection *GetVoxelSection();

		const APoint &GetPosition() const;
		const AVector &GetDirection() const;
		const AVector &GetUp() const;
		const AVector &GetRight() const;
		const HMatrix &GetMatrix() const;
		
	private:
		UIFramePtr mUIFrame;
		UIVLCPtr mUIVlc;

		AVector mOffset;

		LiDar *mLiDar;
		VoxelSection *mVoxelSection;

		// slam2d
	public:
		enum RoleType
		{
			RT_MASTER,
			RT_CONNECTOR,
			RT_MASTER_ONLY_SENDLIDAR,
			RT_CONNECTOR_CALCULATE,
			RT_MAX_TYPE
		};
		void SetRoleType(RoleType rtType);
		RoleType GetRoleType() const;

		static void InitlizeSlam2D();
		static void TernimateSlam2D();

		void CreateLidar();
		bool LidarOpen(const std::string &portIP, int baudratePort);
		LiDar *GetLidar();
		void SetArduino(Arduino *arduino);
		Arduino *GetArduino();

		bool IsArduinoConnected() const;

		void SetOffsetDegree(float degree);
		float GetOffsetDegree() const;

		float GetYawCrossValue() const;

		void InitSlamMap(int mapSize, float resolution);
		void SetSlam2DMap(std::vector<unsigned char> &map, int mapSize, 
			float resolution);
		int GetMapSize() const;
		float GetResolution() const;

		void SetSlam2DPosition(const APoint &pos, float angle);
		float GetSlam2DDegree() const;

		const AVector &GetMoveDirection() const;
		float GetMoveDirectionDegree() const;

		void SetSlamMapUpdate(bool update);
		bool IsSlamMapUpdate() const;

		void SetCurMapUsingAxisWithOffset(float yDegree);

		Texture2D *GetTextureMap();
		UIFPicBox *GetUIFPicBoxMap();

		bool SaveMap(const std::string &filename);
		bool LoadMap(const std::string &filename, const APoint &initPos = APoint::ORIGIN, float curAngle=0.0f);

		RobotMapData &GetInitMapData();
		void ClearInitMapData();

		RobotMapData *GetCurMapData();
		// 100 robotpos
		// 10 none
		// 200 space can go
		void SetValueAtPos(const APoint &pos, float range = 0.1f, int val=1.0f);
		void UpdateSceneObstacles();

		void SetLineValueAtPos(const APoint &pos, float range = 0.1f, int val = 1.0f);

	private:
		void _RecreateMapTex(int mapSize);
		void _LargerMapObst(Texture2D *tex2D);
		void _SetPixelVal(Texture2D *tex2D, unsigned char *toData, int indexY, int indexX);
		void _UpdateMapObst();
		void _UpdateMapObstDyn(const APoint &pos);
		void _SetGraphValue(int x, int y, float val);

		RoleType mRoleType;
		ArduinoPtr mArduino;

		bool mIsInitSlamMap;
		RobotMapDataPtr mRobotMapData;
		bool mIsMapDataChanged;

		float mOffsetDegree;

		float mCurMapUsingAxisWithOffset;

		bool mIsSlamMapUpdate;

		Texture2DPtr mTextureMap;
		UIFPicBoxPtr mPicBoxMap;
		std::vector<unsigned char> mUsingRunningMap2D;

		UIFPicBoxPtr mRobotTex;
		int mRobotMapX;
		int mRobotMapY;
		float m2DSlameAngle;
		NodePtr mObstacleNode;
		std::map< std::pair<int, int>, Pointer0<Actor> > mObstacles;

		RobotMapData mInitMapData;
#if defined PX2_USE_SLAM2D
		static Slam2DPlugin *mSlam2DPlugin;
#endif

		// common
	public:
		APoint mPosition;
		APoint mLastPostion;
		AVector mDirection;
		AVector mUp;
		AVector mRight;
		HMatrix mMatrix;

		AVector mMapSlam2DMoveDirection;

		bool mIsHasEverSettedDirection;
		AVector mFirstMoveDirection;
		float mFirstMoveDirectionAxisY;

		float mMoveDirectionDegreeWithFirst;
		float mCurMoveDirectionAxisY;
		float mDegreeAdjust;

	public_internal:
		AVector &GetAxisDirection();
		HMatrix &GetAxisRotMatrix();
		
	private:
		bool mIsHasAxis;

		AVector mAxisDirection;
		AVector mAxisUp;
		AVector mAxisRight;
		HMatrix mAxisRotMatrix;

		//
	public:
		PathingGraph *GetPathingGraph();

		enum PathType
		{
			PT_A,
			PT_RRT,
			PT_MAX_TYPE
		};
		void GoTarget(const APoint &targetPos, PathType type= PT_A);

		void AdjustToDirection(const AVector &dir);

	public_internal:
		void _SetAIAgent(AIAgent *agent);
		AIAgent *GetAIAgent();

	private:
		bool _IsInRightDirection(const AVector &dir);
		void _UpdateAdjustDirection(const AVector &dir);

		PathingGraphPtr mPathGraph;
		PathPlanPtr mCurPathPlan;
		AIAgentPath mAIAgentPath;
		APoint mGoTargetPos;
		APoint mGoingPos;

		bool mIsAdjustToDirection;
		AVector mAdjustToDirection;

	public:
		void FakeGoForce(const AVector &force);

		float GetSpeed() const;
		AVector GetVelocity() const;

	private:
		AIAgent *mAgent;
		AVector mForce;
		bool mIsUseForce;
		float mSpeed;
		AVector mVelocity;
		float mForceTimer;

		float mLeftSpeed;
		Smoother<float> *mLeftSmoother;
		float mRightSpeed;
		Smoother<float> *mRightSmoother;

	private:
		void _CalSpeed(const Vector2f &dir, float power);
		void _MoveTypeCal(const Vector2f &dir, float strength);
		void _UpdateVirtualRobot(float elaplseSeconds);

		int mDragingLeftMoveType;
		float mDragingLeftMoveSpeed;
		int mDragingRightMoveType;
		float mDragingRightMoveSpeed;

	private:
		RRTRobot *mRRTRobot;
		Enviroment *mEnviroment;
		std::list<RRTobstacles*> mObsts;

	public:
		Vector2f DynamicWindowApproach(RobotState rState, const Vector2f &target,
			std::vector<Vector2f> &obstacle);

		RobotState Motion(RobotState curState, float velocity, float omega);
		std::vector<RobotState> GenerateTraj(RobotState initState, float vel, float ome);
		std::vector<float> CreateDW(RobotState curState);
		float CalcClearance(RobotState rState, std::vector<Vector2f> &obsts);
		float CalcHeading(RobotState rState, const Vector2f &goal);

	private:
		RobotState mRobotState;
	};

#include "PX2Robot.inl"

#define PX2_ROBOT Robot::GetSingleton()

}

#endif