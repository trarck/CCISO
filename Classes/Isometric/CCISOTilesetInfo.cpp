#include "CCISOCoordinate.h"
#include "CCISOTilesetInfo.h"


NS_CC_BEGIN

CCISOTilesetInfo::CCISOTilesetInfo()
:m_uFirstGid(0)
,m_tTileSize(CCSizeZero)
,m_uSpacing(0)
,m_uMargin(0)
,m_tImageSize(CCSizeZero)
{

}

CCISOTilesetInfo::~CCISOTilesetInfo()
{
    CCLOG("CCISOTilesetInfo destroy");
}

CCRect CCTMXTilesetInfo::rectForGID(unsigned int gid)
{
    CCRect rect;
    rect.size = m_tTileSize;
    gid &= kCCFlippedMask;
    gid = gid - m_uFirstGid;
    int max_x = (int)((m_tImageSize.width - m_uMargin*2 + m_uSpacing) / (m_tTileSize.width + m_uSpacing));
    //    int max_y = (imageSize.height - margin*2 + spacing) / (tileSize.height + spacing);
    rect.origin.x = (gid % max_x) * (m_tTileSize.width + m_uSpacing) + m_uMargin;
    rect.origin.y = (gid / max_x) * (m_tTileSize.height + m_uSpacing) + m_uMargin;
    return rect;
}

NS_CC_END
