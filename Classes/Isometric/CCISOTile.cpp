#include "CCISOCoordinate.h"
#include "CCISOTile.h"


NS_CC_BEGIN

CCISOTile::CCISOTile()
:m_nId(0)
,m_pTexture(NULL)
,m_tTextureRect(CCRectZero)
{

}

CCISOTile::~CCISOTile()
{
    CCLOG("CCISOTile destroy");
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pTexture);
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

bool CCISOTile::init(int id,CCISOTileset* tileset,CCTexture2D* texture)
{
    if(init(id,tileset)){
        setTexture(texture);
        m_tTextureRect.size=texture->getContentSizeInPixels();
        return true;
    }
    return false;
}

bool CCISOTile::init(int id,CCISOTileset* tileset,CCTexture2D* texture,CCRect& textureRect)
{
    if(init(id,tileset,texture)){
        m_tTextureRect=textureRect;
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
