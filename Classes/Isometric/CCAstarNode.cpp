//
//  AstarNode.m
//  isometric
//
//

#include "CCAstarNode.h"

NS_CC_BEGIN

CCAstarNode::CCAstarNode()
:m_parent(NULL)
{
	
}

CCAstarNode::~CCAstarNode()
{
	CC_SAFE_RELEASE(m_parent);
}

bool CCAstarNode::init()
{

	m_x=0;
	m_y=0;
	m_g=0;
	m_h=0;
	m_f=0;

	return true;
}

bool CCAstarNode::init(int x ,int y ,int g ,int h)
{
	
	m_x=x;
	m_y=y;
	m_g=g;
	m_h=h;
	m_f=g+h;

	return true;
}

bool CCAstarNode::init(int x ,int y)
{
	return init(x,y,0,0);
}

void CCAstarNode::setX(int x)
{
    m_x = x;
}

int CCAstarNode::getX()
{
    return m_x;
}

void CCAstarNode::setY(int y)
{
    m_y = y;
}

int CCAstarNode::getY()
{
    return m_y;
}

void CCAstarNode::setG(int g)
{
    m_g = g;
}

int CCAstarNode::getG()
{
    return m_g;
}

void CCAstarNode::setH(int h)
{
    m_h = h;
}

int CCAstarNode::getH()
{
    return m_h;
}

void CCAstarNode::setF(int f)
{
    m_f = f;
}

int CCAstarNode::getF()
{
    return m_f;
}

void CCAstarNode::setParent(CCAstarNode* parent)
{
    CC_SAFE_RETAIN(parent);
    CC_SAFE_RELEASE(m_parent);
    m_parent = parent;
}

CCAstarNode* CCAstarNode::getParent()
{
    return m_parent;
}

NS_CC_END
