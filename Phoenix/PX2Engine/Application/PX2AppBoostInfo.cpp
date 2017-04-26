// PX2AppBoostInfo.cpp

#include "PX2AppBoostInfo.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
AppBoostInfo::AppBoostInfo()
{
	ThePlayLogicMode = PLM_LOGIC;
	IsShowInfo = false;

	Port = 10180;
	NumMaxConnection = 4000;
}
//----------------------------------------------------------------------------
AppBoostInfo::~AppBoostInfo()
{

}
//----------------------------------------------------------------------------