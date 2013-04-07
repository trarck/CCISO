#include "CCISOObject.h"


NS_CC_BEGIN

CCISOObject::CCISOObject()
:m_uGid(0)
{
    m_pProperties=new CCDictionary();
}


CCISOObject::~CCISOObject()
{
    CCLOG("CCISOObject destroy");
    CC_SAFE_RELEASE(m_pProperties);
}

void CCISOObject::setType(const char * pType)
{
    m_sType = pType;
}

std::string& CCISOObject::getType()
{
    return m_sType;
}

void CCISOObject::setPosition(CCPoint tPosition)
{
    m_tPosition = tPosition;
}

CCPoint CCISOObject::getPosition()
{
    return m_tPosition;
}

void CCISOObject::setSize(CCSize tSize)
{
    m_tSize = tSize;
}

CCSize CCISOObject::getSize()
{
    return m_tSize;
}

void CCISOObject::setGid(unsigned int uGid)
{
    m_uGid = uGid;
}

unsigned int CCISOObject::getGid()
{
    return m_uGid;
}

void CCISOObject::setVisible(bool bVisible)
{
    m_bVisible = bVisible;
}

bool CCISOObject::getVisible()
{
    return m_bVisible;
}

void CCISOObject::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties=pProperties;
    
}

CCDictionary* CCISOObject::getProperties()
{
    return m_pProperties;
}

NS_CC_END
