#include "CCISOTileLayer.h"
#include "CCISOCoordinate.h"

NS_CC_BEGIN



CCISOTileLayer::CCISOTileLayer()
:m_iStartX(0)
,m_iStartY(0)
{
	
}

CCISOTileLayer::~CCISOTileLayer()
{
//	CC_SAFE_RELEASE();
}

bool CCISOTileLayer::init()
{
    m_tTileSize=CCSizeZero;
	m_tOffset=CCPointZero;
	return true;
}

void CCISOTileLayer::initOffset(const CCPoint& tOffset)
{
	this->setOffset(tOffset);
	CCPoint startMapCoord=isoViewToGamePoint(tOffset);
	m_iStartX=(int)startMapCoord.x;
	m_iStartY=(int)startMapCoord.y;
}

void CCISOTileLayer::initOffset(float x,float y)
{
	this->initOffset(ccp(x,y));
}



void CCISOTileLayer::setLayerSize(const CCSize& tLayerSize)
{
    m_tLayerSize = tLayerSize;
}

CCSize CCISOTileLayer::getLayerSize()
{
    return m_tLayerSize;
}

//void CCISOTileLayer::setContentSize(CCSize tContentSize)
//{
//    m_tContentSize = tContentSize;
//}
//
//CCSize CCISOTileLayer::getContentSize()
//{
//    return m_tContentSize;
//}

void CCISOTileLayer::setTileSize(const CCSize& tileSize)
{
    m_tTileSize=tileSize;
}

void CCISOTileLayer::setTileSize(float width,float height)
{
    m_tTileSize.width=width;
    m_tTileSize.height=height;
}


void CCISOTileLayer::setOffset(const CCPoint& tOffset)
{
    m_tOffset = tOffset;
}

void CCISOTileLayer::setOffset(float x,float y)
{
    m_tOffset.x=x;
	m_tOffset.y=y;
}

CCPoint CCISOTileLayer::getOffset()
{
    return m_tOffset;
}

NS_CC_END
