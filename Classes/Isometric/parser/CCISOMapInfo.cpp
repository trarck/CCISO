#include "CCISOCoordinate.h"
#include "CCISOMapInfo.h"


NS_CC_BEGIN

CCISOMapInfo::CCISOMapInfo()
:m_tMapSize(CCSizeZero)
,m_tTileSize(CCSizeZero)
,m_pLayers(NULL)
,m_pTilesets(NULL)
,m_pObjectGroups(NULL)
,m_pProperties(NULL)
,m_pTileProperties(NULL)
{

}

CCISOMapInfo::~CCISOMapInfo()
{
    CCLOG("CCISOMapInfo destroy");
    CC_SAFE_RELEASE(m_pTilesets);
    CC_SAFE_RELEASE(m_pLayers);
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pTileProperties);
    CC_SAFE_RELEASE(m_pObjectGroups);
}

bool CCISOMapInfo::init()
{
    m_pTilesets = CCArray::create();
    m_pTilesets->retain();
    
    m_pLayers = CCArray::create();
    m_pLayers->retain();

    m_pObjectGroups = CCArray::createWithCapacity(4);
    m_pObjectGroups->retain();
    
    m_pProperties = new CCDictionary();
    m_pTileProperties = new CCDictionary();


    return true;
}

void CCISOMapInfo::setOrientation(int nOrientation)
{
    m_nOrientation = nOrientation;
}

int CCISOMapInfo::getOrientation()
{
    return m_nOrientation;
}

void CCISOMapInfo::setMapSize(const CCSize& tMapSize)
{
    m_tMapSize = tMapSize;
}

const CCSize& CCISOMapInfo::getMapSize()
{
    return m_tMapSize;
}

void CCISOMapInfo::setTileSize(const CCSize& tTileSize)
{
    m_tTileSize = tTileSize;
}

const CCSize& CCISOMapInfo::getTileSize()
{
    return m_tTileSize;
}

void CCISOMapInfo::setLayers(CCArray* pLayers)
{
    CC_SAFE_RETAIN(pLayers);
    CC_SAFE_RELEASE(m_pLayers);
    m_pLayers = pLayers;
}

CCArray* CCISOMapInfo::getLayers()
{
    return m_pLayers;
}

void CCISOMapInfo::setTilesets(CCArray* pTilesets)
{
    CC_SAFE_RETAIN(pTilesets);
    CC_SAFE_RELEASE(m_pTilesets);
    m_pTilesets = pTilesets;
}

CCArray* CCISOMapInfo::getTilesets()
{
    return m_pTilesets;
}

/**
 * keep same for tmx
 */
void CCISOMapInfo::setObjectGroups(CCArray* pObjectGroups)
{
    CC_SAFE_RETAIN(pObjectGroups);
    CC_SAFE_RELEASE(m_pObjectGroups);
    m_pObjectGroups = pObjectGroups;
}

CCArray* CCISOMapInfo::getObjectGroups()
{
    return m_pObjectGroups;
}

void CCISOMapInfo::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* CCISOMapInfo::getProperties()
{
    return m_pProperties;
}

CCDictionary* CCISOMapInfo::getTileProperties()
{
    return m_pTileProperties;
}

void CCISOMapInfo::setTileProperties(CCDictionary* tileProperties)
{
    CC_SAFE_RETAIN(tileProperties);
    CC_SAFE_RELEASE(m_pTileProperties);
    m_pTileProperties = tileProperties;
}

NS_CC_END
