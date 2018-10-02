// PX2AIAgentGroup.cpp

#include "PX2AIAgentGroup.hpp"
#include "PX2AIAgent.hpp"
using namespace PX2;
 
//----------------------------------------------------------------------------
AIAgentGroup::AIAgentGroup() :
OpenSteer::AVGroup()
{

}
//----------------------------------------------------------------------------
AIAgentGroup::AIAgentGroup(const AIAgentGroup& group):
OpenSteer::AVGroup(group)
{
}
//----------------------------------------------------------------------------
AIAgentGroup::~AIAgentGroup()
{
}
//----------------------------------------------------------------------------
AIAgentGroup& AIAgentGroup::operator=(const AIAgentGroup& group)
{
	clear();

	insert(begin(), group.begin(), group.end());
	return *this;
}
//----------------------------------------------------------------------------
void AIAgentGroup::AddAgent(const AIAgent* agent)
{
	if (!ContainsAgent(agent))
	{
		push_back((OpenSteer::AbstractVehicle*)agent);
	}
}
//----------------------------------------------------------------------------
bool AIAgentGroup::ContainsAgent(const AIAgent* agent) const
{
	std::vector<OpenSteer::AbstractVehicle*>::const_iterator it;

	for (it = begin(); it != end(); ++it)
	{
		if (*it == (OpenSteer::AbstractVehicle*)(agent))
		{
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
bool AIAgentGroup::RemoveAgent(const AIAgent* agent)
{
	auto it = begin();

	for (it = begin(); it != end(); ++it)
	{
		if (*it == (OpenSteer::AbstractVehicle*)agent)
		{
			break;
		}
	}

	if (it != end())
	{
		erase(it);
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void AIAgentGroup::RemoveAgents()
{
	clear();
}
//----------------------------------------------------------------------------
size_t AIAgentGroup::Size() const
{
	return (int)size();
}
//----------------------------------------------------------------------------