//
//  ZIndex.

#include "CCZIndexNode.h"

NS_CC_BEGIN

CCZIndexNode::CCZIndexNode()
:m_pEntity(NULL)
,m_pRect(NULL);
{

}

CCZIndexNode::~CCZIndexNode()
{
    CC_SAFE_RELEASE(m_pRect);
}

void setRect(CCRect* rect)
{
    CC_SAFE_RETAIN(rect);
    CC_SAFE_RELEASE(m_pRect);
    m_pRect=rect;
}

CCRect* getRect()
{
    return m_pRect;
}

void setEntity(CCObject* entity)
{
    m_pEntity=entity;
}

CCObject* getEntity()
{
    return m_pEntity;
}

NS_CC_END