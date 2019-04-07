// PX2RobotDatas.cpp

#include "PX2RobotDatas.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Slam3DPoint::Slam3DPoint():
Key(0),
IsBad(false)
{
}
//----------------------------------------------------------------------------
Slam3DPoint::~Slam3DPoint()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
RobotMapDataStruct::RobotMapDataStruct()
{
	MapSize = 256;
	MapResolution = 0.1f;
	IndexX = 0;
	IndexY = 0;
	CurAngle = 0.0f;
}
//----------------------------------------------------------------------------
RobotMapDataStruct::~RobotMapDataStruct()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
PX2_IMPLEMENT_RTTI(PX2, Object, RobotMapData);
PX2_IMPLEMENT_STREAM(RobotMapData);
PX2_IMPLEMENT_FACTORY(RobotMapData);
PX2_IMPLEMENT_DEFAULT_NAMES(Object, RobotMapData);
//----------------------------------------------------------------------------
RobotMapData::RobotMapData()
{

}
//----------------------------------------------------------------------------
RobotMapData::~RobotMapData()
{
}
//----------------------------------------------------------------------------
void RobotMapData::CopyDataFrom(RobotMapData *data)
{
	//int MapSize;
	//float MapResolution;
	//std::vector<unsigned char> Map2D;
	//int IndexX;
	//int IndexY;
	//APoint CurPos;
	//float CurAngle;

	MapStruct.MapSize = data->MapStruct.MapSize;
	MapStruct.MapResolution = data->MapStruct.MapResolution;
	MapStruct.IndexX = data->MapStruct.IndexX;
	MapStruct.IndexY = data->MapStruct.IndexY;
	MapStruct.CurPos = data->MapStruct.CurPos;
	MapStruct.CurAngle = data->MapStruct.CurAngle;
	Map2D = data->Map2D;
	SelfDrawMapData2D = data->SelfDrawMapData2D;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ³Ö¾Ã»¯
//----------------------------------------------------------------------------
RobotMapData::RobotMapData(LoadConstructor value) :
Object(value)
{
}
//----------------------------------------------------------------------------
void RobotMapData::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);
	PX2_VERSION_LOAD(source);

	source.Read(MapStruct.MapSize);
	source.Read(MapStruct.MapResolution);
	source.Read(MapStruct.IndexX);
	source.Read(MapStruct.IndexY);
	source.ReadAggregate(MapStruct.CurPos);
	source.Read(MapStruct.CurAngle);

	int numDatas = 0;
	source.Read(numDatas);

	Map2D.resize(numDatas);
	for (int i = 0; i < numDatas; i++)
	{
		source.Read<uint8_t>(Map2D[i]);
	}

	SelfDrawMapData2D.resize(numDatas);
	for (int i = 0; i < numDatas; i++)
	{
		source.Read<uint8_t>(SelfDrawMapData2D[i]);
	}

	LineDrawMapData2D.resize(numDatas);
	for (int i = 0; i < numDatas; i++)
	{
		source.Read<uint8_t>(LineDrawMapData2D[i]);
	}
	memset(&LineDrawMapData2D[0], 0, numDatas);

	PX2_END_DEBUG_STREAM_LOAD(RobotMapData, source);
}
//----------------------------------------------------------------------------
void RobotMapData::Link(InStream& source)
{
	Object::Link(source);
}
//----------------------------------------------------------------------------
void RobotMapData::PostLink()
{
	Object::PostLink();
}
//----------------------------------------------------------------------------
bool RobotMapData::Register(OutStream& target) const
{
	if (Object::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void RobotMapData::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);
	PX2_VERSION_SAVE(target);

	target.Write(MapStruct.MapSize);
	target.Write(MapStruct.MapResolution);
	target.Write(MapStruct.IndexX);
	target.Write(MapStruct.IndexY);
	target.WriteAggregate(MapStruct.CurPos);
	target.Write(MapStruct.CurAngle);

	int numDatas = (int)Map2D.size();
	target.Write(numDatas);
	for (int i = 0; i < numDatas; i++)
	{
		target.Write<uint8_t>(Map2D[i]);
	}
	for (int i = 0; i < numDatas; i++)
	{
		target.Write<uint8_t>(SelfDrawMapData2D[i]);
	}
	for (int i = 0; i < numDatas; i++)
	{
		target.Write<uint8_t>(LineDrawMapData2D[i]);
	}

	PX2_END_DEBUG_STREAM_SAVE(RobotMapData, target);
}
//----------------------------------------------------------------------------
int RobotMapData::GetStreamingSize(Stream &stream) const
{
	int size = Object::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += sizeof(MapStruct.MapSize);
	size += sizeof(MapStruct.MapResolution);
	size += sizeof(MapStruct.IndexX);
	size += sizeof(MapStruct.IndexY);
	size += sizeof(MapStruct.CurPos);
	size += sizeof(MapStruct.CurAngle);

	int numDatas = (int)Map2D.size();
	size += sizeof(numDatas);
	size += numDatas * sizeof(uint8_t);
	size += numDatas * sizeof(uint8_t);
	size += numDatas * sizeof(uint8_t);

	return size;
}
//----------------------------------------------------------------------------
