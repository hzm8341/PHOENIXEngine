// PX2BDefine.hpp

#ifndef PX2BDEFINE_HPP
#define PX2BDEFINE_HPP

#include "PX2LogicPre.hpp"
#include "PX2BBlockPre.hpp"
#include "PX2Size.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM BDefine
	{
	public:
		BDefine();
		~BDefine();

		static void Config(float adjust, const std::string &tag);

		static float BlockFunMinWidth;

		static float Adjust;
		static float BlockHeight;
		static float BlockHeightTopTitle;
		static float BlockHeightMiddle;
		static float BlockHeightVer;
		static float ParamHeight;

		static float BlockParamLeft;
		static float BlockTitleParamHor;
		static float BlockTitleParamHorSpace;
		static float BlockParamEditBoxMinWidth;

		static float ParamInOutAdjust;
		static float SquareAdjust;
		static float BlockSpace;
		static Sizef CornorFunLeft;
		static Sizef CornorFunRight;
		static Sizef CornorCtrlLeft;
		static Sizef CornorMiddleLeft;
		static Sizef CornorMiddleRight;
		static Sizef CornorGeneral;
	};

	const int BBlockSystemUDPPortRobot = 9951;

}

#endif