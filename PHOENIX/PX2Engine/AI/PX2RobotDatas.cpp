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
std::vector<unsigned char> RobotMapData::_ExtendLarger(
	std::vector<unsigned char> &mapping, bool usSelfDraw)
{
	std::vector<unsigned char> retMapping = mapping;

	int x = 0;
	int y = 0;
	int sx = 0;
	int sy = 0;
	int mapVal = 200;
	int selfMapVal = 200;
	int index = 0;
	for (int i = 0; i < MapStruct.MapSize; i++)
	{
		for (int j = 0; j < MapStruct.MapSize; j++)
		{
			index = i * MapStruct.MapSize + j;

			x = j;
			y = i;

			mapVal = mapping[index];

			bool isHasObst = false;
			if (0 == mapVal)
			{
				isHasObst = true;
			}

			if (usSelfDraw)
			{
				selfMapVal = SelfDrawMapData2D[index];
				if (0 == selfMapVal)
				{
					isHasObst = true;
				}
				else if (200 == selfMapVal)
				{

				}
				else if (201 == selfMapVal)
				{
					isHasObst = false;
				}
			}

			if (isHasObst)
			{
				_SetMapUsingData(retMapping, x, y, 0);

				int left = x - 1;
				if (left < 0)
					left = 0;
				_SetMapUsingData(retMapping, left, y, 0);

				int right = x + 1;
				if (right >= MapStruct.MapSize)
					right = MapStruct.MapSize - 1;
				_SetMapUsingData(retMapping, right, y, 0);

				int down = y - 1;
				if (down < 0)
					down = 0;
				_SetMapUsingData(retMapping, x, down, 0);

				int up = y + 1;
				if (up >= MapStruct.MapSize)
					up = MapStruct.MapSize - 1;
				_SetMapUsingData(retMapping, x, up, 0);
			}
		}
	}

	return retMapping;
}
//----------------------------------------------------------------------------
void RobotMapData::ConvertOriginToUsing()
{
	std::vector<unsigned char> mapping = _ExtendLarger(Map2DOrigin, true);
	std::vector<unsigned char> mapping1 = _ExtendLarger(mapping, false);
	std::vector<unsigned char> mapping2 = _ExtendLarger(mapping1, false);
	std::vector<unsigned char> mapping3 = _ExtendLarger(mapping2, false);
	std::vector<unsigned char> mapping4 = _ExtendLarger(mapping3, false);
	std::vector<unsigned char> mapping5 = _ExtendLarger(mapping4, false);
	std::vector<unsigned char> mapping6 = _ExtendLarger(mapping5, false);
	std::vector<unsigned char> mapping7 = _ExtendLarger(mapping6, false);
	std::vector<unsigned char> mapping8 = _ExtendLarger(mapping7, false);

	Map2DUsing = mapping8;
}
//----------------------------------------------------------------------------
void RobotMapData::_SetMapUsingData(std::vector<unsigned char> &maping, 
	int x, int y, int val)
{
	int index = y*MapStruct.MapSize + x;
	maping[index] = val;
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

	Map2DOrigin.resize(numDatas);
	for (int i = 0; i < numDatas; i++)
	{
		source.Read<uint8_t>(Map2DOrigin[i]);
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

	ConvertOriginToUsing();
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

	int numDatas = (int)Map2DOrigin.size();
	target.Write(numDatas);
	for (int i = 0; i < numDatas; i++)
	{
		target.Write<uint8_t>(Map2DOrigin[i]);
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

	int numDatas = (int)Map2DOrigin.size();
	size += sizeof(numDatas);
	size += numDatas * sizeof(uint8_t);
	size += numDatas * sizeof(uint8_t);
	size += numDatas * sizeof(uint8_t);

	return size;
}
//----------------------------------------------------------------------------
