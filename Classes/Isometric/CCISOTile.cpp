#include "CCISOCoordinate.h"
#include "CCISOTile.h"


NS_CC_BEGIN

CCISOTile::CCISOTile()
:m_nId(0)
,m_pSprite(NULL)
{

}

CCISOTile::~CCISOTile()
{
    CCLOG("CCISOTile destroy");
    CC_SAFE_RELEASE(m_pSprite);
    CC_SAFE_RELEASE(m_pProperties);
}

bool CCISOTile::init()
{
    m_pProperties=new CCDictionary();
    return true;
}

bool CCISOTile::init(int id,CCISOTileset* tileset)
{
    if(init()){
        m_nId=id;
        setTileset(tileset);
        return true;
    }
    return false;
}


bool CCISOTile::init(int id,CCISOTileset* tileset,CCSprite* sprite)
{
    if(init(id,tileset)){
        setSprite(sprite);
        return true;
    }
    return false;
}




void CCISOTile::setId(int nId)
{
    m_nId = nId;
}

int CCISOTile::getId()
{
    return m_nId;
}

void CCISOTile::setTileset(CCISOTileset* pTileset)
{
    m_pTileset = pTileset;
}

CCISOTileset* CCISOTile::getTileset()
{
    return m_pTileset;
}

void CCISOTile::setSprite(CCSprite* pSprite)
{
    CC_SAFE_RETAIN(pSprite);
    CC_SAFE_RELEASE(m_pSprite);
    m_pSprite = pSprite;
}

CCSprite* CCISOTile::getSprite()
{
    return m_pSprite;
}

void CCISOTile::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* CCISOTile::getProperties()
{
    return m_pProperties;
}

NS_CC_END
