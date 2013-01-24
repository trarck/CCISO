
#include "CCISOTileMap.h"

NS_CC_BEGIN

CCISOTileMap::CCISOTileMap()
{
	
}

CCISOTileMap::~CCISOTileMap()
{

}

bool CCISOTileMap::init()
{

	
	return true;
}

void CCISOTileMap::setMapSize(CCSize tMapSize)
{
    m_tMapSize = tMapSize;
}

CCSize CCISOTileMap::getMapSize()
{
    return m_tMapSize;
}

void CCISOTileMap::setName(const char* pName)
{
    //CC_SAFE_RETAIN(pName);
    //CC_SAFE_RELEASE(m_pName);
    m_pName = pName;
}

const char* CCISOTileMap::getName()
{
    return m_pName;
}


NS_CC_END
