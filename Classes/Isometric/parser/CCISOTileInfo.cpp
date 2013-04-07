#include "CCISOCoordinate.h"
#include "CCISOTileInfo.h"


NS_CC_BEGIN

CCISOTileInfo::CCISOTileInfo()
:m_uId(0)
,m_sImageSource("")
,m_tImageSize(CCSizeZero)
{
    m_pProperties=new CCDictionary();
}

CCISOTileInfo::~CCISOTileInfo()
{
    CCLOG("CCISOTileInfo destroy");
    CC_SAFE_RELEASE(m_pProperties);
}

NS_CC_END
