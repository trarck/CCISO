#include "CCISOCoordinate.h"
#include "CCISOLayerInfo.h"


NS_CC_BEGIN

CCISOLayerInfo::CCISOLayerInfo()
:m_sName("")
,m_pTiles(NULL)
,m_tOffset(CCPointZero)
,m_cOpacity(255)
{
    m_pProperties=new CCDictionary();
}

CCISOLayerInfo::~CCISOLayerInfo()
{
    CCLOG("CCISOLayerInfo destroy");
    CC_SAFE_RELEASE(m_pProperties);
    if( m_pTiles )
    {
        delete [] m_pTiles;
        m_pTiles = NULL;
    }
}

NS_CC_END
