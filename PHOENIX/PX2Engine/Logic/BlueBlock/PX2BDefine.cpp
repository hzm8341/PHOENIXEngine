// PX2BDefine.cpp

#include "PX2BDefine.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
float BDefine::Adjust = 2.0f;

float BDefine::BlockFunMinWidth = 120.0f * Adjust;
float BDefine::BlockHeight = 22.0f * Adjust;
float BDefine::BlockHeightTopTitle = 16.0f * Adjust;
float BDefine::BlockHeightMiddle = 26.0f * Adjust;
float BDefine::BlockHeightVer = 20.0f * Adjust;
float BDefine::ParamHeight = 20.0f * Adjust;

float BDefine::BlockParamLeft = 4.0f;
float BDefine::BlockTitleParamHor = 5.0f * Adjust;
float BDefine::BlockTitleParamHorSpace = 4.0f * Adjust;

float BDefine::BlockParamEditBoxMinWidth = 40.0f * Adjust;

float BDefine::ParamInOutAdjust = 4.0f;
float BDefine::SquareAdjust = 30.0f;
float BDefine::BlockSpace = 2.0f;
Sizef BDefine::CornorFunLeft;
Sizef BDefine::CornorFunRight;
Sizef BDefine::CornorCtrlLeft;
Sizef BDefine::CornorGeneral;
Sizef BDefine::CornorMiddleLeft;
Sizef BDefine::CornorMiddleRight;
//----------------------------------------------------------------------------
BDefine::BDefine()
{
}
//----------------------------------------------------------------------------
BDefine::~BDefine()
{
}
//----------------------------------------------------------------------------
void BDefine::Config(float adjust, const std::string &tag)
{
	Adjust = adjust;

	BlockFunMinWidth = 180.0f * Adjust;
	BlockHeight = 52.0f * Adjust;
	ParamHeight = 45.0f * Adjust;
	BlockHeightTopTitle = 30.0f * Adjust;
	BlockHeightMiddle = 20.0f * Adjust;
	BlockHeightVer = 39.0f * Adjust;

	BlockTitleParamHor = BlockHeightVer * Adjust;
	BlockTitleParamHorSpace = 6.0f * Adjust;

	BlockParamEditBoxMinWidth = 40.0f * Adjust;

	ParamInOutAdjust = 10.0f;

	SquareAdjust = 16.0f;
	BlockSpace = 0.0f;

	CornorFunLeft = Sizef(125.0f, 32.0f);
	CornorFunRight = Sizef(6.0, 6.0);

	CornorCtrlLeft = Sizef(220.0f, 32.0f);

	CornorGeneral = Sizef(16.0f, 16.0f);

	CornorMiddleLeft = Sizef(68.0f, 18.0f);
	CornorMiddleRight = Sizef(4.0f, 18.0f);

	if ("flat" == tag)
	{
		BlockHeight = 40.0f * Adjust;
		ParamHeight = 33.0f * Adjust;
		SquareAdjust = 0.0f;
		BlockSpace = 1.0f;
		ParamInOutAdjust = 0.0f;
		BlockHeightVer = 25.0f * Adjust;

		CornorMiddleLeft = Sizef(1.0f, 1.0f);
		CornorMiddleRight = Sizef(1.0f, 1.0f);
	}
}
//----------------------------------------------------------------------------