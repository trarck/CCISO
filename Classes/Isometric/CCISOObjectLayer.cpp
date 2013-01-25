#include "CCISOObjectLayer.h"
#include "ccMacros.h"

NS_CC_BEGIN

//implementation CCISOObjectLayer

CCISOObjectLayer::CCISOObjectLayer()
:m_tOffset(CCPointZero)
,m_sName("")        
{
    m_pObjects = CCArray::create();
    m_pObjects->retain();
    m_pProperties = new CCDictionary();
}
CCISOObjectLayer::~CCISOObjectLayer()
{
    CCLOGINFO( "CCISOObjectLayer: deallocing.");
    CC_SAFE_RELEASE(m_pObjects);
    CC_SAFE_RELEASE(m_pProperties);
}

CCDictionary* CCISOObjectLayer::objectNamed(const char *objectName)
{
    if (m_pObjects && m_pObjects->count() > 0)
    {
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pObjects, pObj)
        {
            CCDictionary* pDict = (CCDictionary*)pObj;
            CCString *name = (CCString*)pDict->objectForKey("name");
            if (name && name->m_sString == objectName)
            {
                return pDict;
            }
        }
    }
    // object not found
    return NULL;    
}

CCString* CCISOObjectLayer::propertyNamed(const char* propertyName)
{
    return (CCString*)m_pProperties->objectForKey(propertyName);
}

void CCISOObjectLayer::setOffset(const CCPoint& tOffset)
{
    m_tOffset = tOffset;
}

const CCPoint& CCISOObjectLayer::getOffset()
{
    return m_tOffset;
}

void CCISOObjectLayer::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* CCISOObjectLayer::getProperties()
{
    return m_pProperties;
}

void CCISOObjectLayer::setObjects(CCArray* pObjects)
{
    CC_SAFE_RETAIN(pObjects);
    CC_SAFE_RELEASE(m_pObjects);
    m_pObjects = pObjects;
}

CCArray* CCISOObjectLayer::getObjects()
{
    return m_pObjects;
}
NS_CC_END
