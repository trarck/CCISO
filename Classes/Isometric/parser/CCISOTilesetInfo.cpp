#include "CCISOCoordinate.h"
#include "CCISOTilesetInfo.h"


NS_CC_BEGIN

CCISOTilesetInfo::CCISOTilesetInfo()
:m_sName("")
,m_uFirstGid(0)
,m_sSourceFile("")
,m_tTileSize(CCSizeZero)
,m_uSpacing(0)
,m_uMargin(0)
,m_tTileOffset(CCPointZero)
,m_sImageSource("")
,m_tImageSize(CCSizeZero)
//,m_pProperties(NULL)
//,m_pTiles(NULL)
//,m_pTileProperties(NULL)
{
    m_pProperties=new CCDictionary();
    m_pTiles=new CCArray();
    m_pTileProperties=new CCDictionary();
}

CCISOTilesetInfo::~CCISOTilesetInfo()
{
    CCLOG("CCISOTilesetInfo destroy");
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pTiles);
    CC_SAFE_RELEASE(m_pTileProperties);
}

NS_CC_END
