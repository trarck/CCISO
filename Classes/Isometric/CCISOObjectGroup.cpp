#include "CCISOObjectGroup.h"
#include "ccMacros.h"

NS_CC_BEGIN

//implementation CCISOObjectGroup

CCISOObjectGroup::CCISOObjectGroup()
:m_tOffset(CCPointZero)
,m_sName("")
,m_pObjects(NULL)
,m_pProperties(NULL)
{
    
}

CCISOObjectGroup::~CCISOObjectGroup()
{
    CCLOGINFO( "CCISOObjectGroup: deallocing.");
    CC_SAFE_RELEASE(m_pObjects);
    CC_SAFE_RELEASE(m_pProperties);
}

bool CCISOObjectGroup::init()
{
    m_pObjects = new CCArray();
    m_pObjects->init();
    m_pProperties = new CCDictionary();
    return true;
}

CCDictionary* CCISOObjectGroup::objectNamed(const char *objectName)
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

CCString* CCISOObjectGroup::propertyNamed(const char* propertyName)
{
    return (CCString*)m_pProperties->objectForKey(propertyName);
}

void CCISOObjectGroup::setOffset(const CCPoint& tOffset)
{
    m_tOffset = tOffset;
}

const CCPoint& CCISOObjectGroup::getOffset()
{
    return m_tOffset;
}

void CCISOObjectGroup::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* CCISOObjectGroup::getProperties()
{
    return m_pProperties;
}

void CCISOObjectGroup::setObjects(CCArray* pObjects)
{
    CC_SAFE_RETAIN(pObjects);
    CC_SAFE_RELEASE(m_pObjects);
    m_pObjects = pObjects;
}

CCArray* CCISOObjectGroup::getObjects()
{
    return m_pObjects;
}
NS_CC_END
