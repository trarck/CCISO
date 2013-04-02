#include "CCISOCoordinate.h"
#include "CCISOTile.h"


NS_CC_BEGIN

CCISOTile::CCISOTile(int id)
:m_nId(id)
{

}


CCISOTile::CCISOTile(int id,CCSprite* sprite,CCISOTileset* tileset)
:m_nId(id)
{
    setTileset(tileset);
    setSprite(sprite);
}


CCISOTile::~CCISOTile()
{
    CCLOG("CCISOTile destroy");
    CC_SAFE_RELEASE(m_pSprite);
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

NS_CC_END
