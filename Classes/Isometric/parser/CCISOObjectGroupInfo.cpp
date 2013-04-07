#include "CCISOCoordinate.h"
#include "CCISOObjectGroupInfo.h"


NS_CC_BEGIN

CCISOObjectGroupInfo::CCISOObjectGroupInfo()
:m_sName("")
,m_tColor(ccWHITE)
{
    m_pProperties=new CCDictionary();
    m_pObjects=new CCArray();
}

CCISOObjectGroupInfo::~CCISOObjectGroupInfo()
{
    CCLOG("CCISOObjectGroupInfo destroy");
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pObjects);
}

NS_CC_END
