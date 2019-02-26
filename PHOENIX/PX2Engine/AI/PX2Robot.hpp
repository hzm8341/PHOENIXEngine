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

namespace PX2
{

	class VoxelSection;

#define PX2_USE_SLAM2D
#if defined PX2_USE_SLAM2D
	class Slam2DPlugin;
#endif

	class PX2_ENGINE_ITEM Robot : public Singleton<Robot>
	{
	public:
		Robot();
		virtual ~Robot();

		void StartShareMemory();
		void ShutdownShareMenory();

		void Update(float appseconds, float elpasedSeconds);

		UIFrame *GetUIFrame();
		UIVlc *GetUIVlc();

		void SetOffset(const AVector &offset);
		const AVector &GetOffset() const;

		const APoint &GetPosition() const;
		const AVector &GetDirection() const;
		const AVector &GetUp() const;
		const AVector &GetRight() const;
		const HMatrix &GetMatrix() const;

		// slam 3d
	public:
		void SetCurSlam3DCameraMatrix(HMatrix &mat);
		void SetCurSlam3DTransformLost(bool lost);
		bool IsCurSlam3DTransformLost() const;

		const APoint &GetCameraPosition() const;
		const AVector &GetCameraDirection() const;
		const AVector &GetCameraUp() const;
		const AVector &GetCameraRight() const;
		const HMatrix &GetCameraMatrix() const;

		std::vector<Slam3DPoint> AllPoints;
		std::vector<Slam3DPoint> CurPoints;

		void SetVoxelSection(VoxelSection *vs);
		VoxelSection *GetVoxelSection();

	private:
		void _RefreshVoxelSection(std::vector<Slam3DPoint> &points, int mtlType);
		Float3 _FromString(const std::string &str);
		HMatrix _MatFromString(const std::string &str);
		APoint _PtFromString(const std::string &str, int &key, bool &isBad);

		AVector mOffset;

		APoint mCameraPosition;
		AVector mCameraDirection;
		AVector mCameraUp;
		AVector mCameraRight;
		HMatrix mCameraMatrix;

		bool mIsSlamLost3D;
		
		UIFramePtr mUIFrame;
		UIVLCPtr mUIVlc;

		LiDar *mLiDar;
		VoxelSection *mVoxelSection;

		char *mBufShare;

#if defined _WIN32 || defined WIN32
		void *mHandler;
#endif
		PolypointPtr mPolypoint;

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

		Texture2D *GetTextureMapPathFind();
		UIFPicBox *GetUIFPicBoxMapPathFind();

		bool SaveMap(const std::string &filename);
		bool LoadMap(const std::string &filename, const APoint &initPos = APoint::ORIGIN, float curAngle=0.0f);

		RobotMapData &GetInitMapData();
		void ClearInitMapData();

		RobotMapData *GetCurMapData();
		// 100 robotpos
		// 10 none
		// 200 space can go
		void SetValueAtPos(const APoint &pos, float range = 0.1f, int val=1.0f);

		void SetLineValueAtPos(const APoint &pos, float range = 0.1f, int val = 1.0f);

	private:
		void _RecreateMapTex(int mapSize, int smallMapSize);
		void _RefreshVoxelSection(std::vector<unsigned char> &map,
			float resolution);
		void _LargerMapObst(Texture2D *tex2D);
		void _SetPixelVal(Texture2D *tex2D, unsigned char *toData, int indexY, int indexX);
		void _UpdateMapObst();
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

		UIFPicBoxPtr mRobotTex;
		int mRobotMapX;
		int mRobotMapY;
		float m2DSlameAngle;

		RobotMapData mInitMapData;
#if defined PX2_USE_SLAM2D
		static Slam2DPlugin *mSlam2DPlugin;
#endif

		// common
	public:
		APoint mPosition;
		AVector mDirection;
		AVector mUp;
		AVector mRight;
		HMatrix mMatrix;

		AVector mMoveDirection;

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

		void GoTarget(const APoint &targetPos);

	private:
		bool _IsInRightDirection(const AVector &dir);
		void _UpdateAdjustDirection(const AVector &dir);
		void _CheckPathUpdateing(float appSeconds, float elapsedSeconds);

		PathingGraphPtr mPathGraph;
		PathPlanPtr mCurPathPlan;
		APoint mGoTargetPos;
		APoint mGoingPos;
		float mPathUpdateTiming;
	};

#include "PX2Robot.inl"

#define PX2_ROBOT Robot::GetSingleton()

}

#endif