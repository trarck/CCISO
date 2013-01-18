#include "CCISOCoordinate.h"
#include "CCISOLayerInfo.h"


NS_CC_BEGIN

CCISOLayerInfo::CCISOLayerInfo()
{

}

CCISOLayerInfo::~CCISOLayerInfo()
{
    CCLOG("CCISOLayerInfo destroy");
}

void CCISOLayerInfo::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* CCISOLayerInfo::getProperties()
{
    return m_pProperties;
}

NS_CC_END
