#include "CCISOCoordinate.h"
#include "CCISOComponentNode.h"


NS_CC_BEGIN

CCISOComponentNode::CCISOComponentNode()
:m_iColumn(0)
,m_iRow(0)
,m_iMapCellX(0)
,m_iMapCellY(0)
,m_pTile(NULL)
{

}

CCISOComponentNode::~CCISOComponentNode()
{
    CCLOG("CCISOComponentNode destroy");
    CC_SAFE_RELEASE(m_pTile);
}

void CCISOComponentNode::updateMapCoordinate(float mapX,float mapY)
{
    m_fMapX=mapX;
    m_fMapY=mapY;
//    CCPoint pos=isoGameToView2F(mapX, mapY);
//    CCLOG("updateMapCoordinate:%f,%f:%f,%f",mapX,mapY,pos.x,pos.y);
    m_pTile->setPosition(isoGameToView2F(mapX, mapY));
}

NS_CC_END
