#include "CCISOCoordinate.h"
#include "CCISOObjectInfo.h"


NS_CC_BEGIN

CCISOObjectInfo::CCISOObjectInfo()
:m_sName("")
,m_sType("")
,m_uGid(0)
,m_tPosition(CCPointZero)
,m_tSize(CCSizeZero)
,m_bVisible(true)
{
    m_pProperties=new CCDictionary();
}

CCISOObjectInfo::~CCISOObjectInfo()
{
    CCLOG("CCISOObjectInfo destroy");
    CC_SAFE_RELEASE(m_pProperties);
}

NS_CC_END
