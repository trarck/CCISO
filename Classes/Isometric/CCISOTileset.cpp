#include "CCISOCoordinate.h"
#include "CCISOTileset.h"


NS_CC_BEGIN

CCISOTileset::CCISOTileset()
:m_tName("")
,m_tFileName("")
,m_tImageSource("")
,m_nTileWidth(0)
,m_nTileHeight(0)
,m_nTileSpacing(0)
,m_nMargin(0)
,m_tTileOffset(CCPointZero)
,m_nImageWidth(0)
,m_nImageHeight(0)
,m_nColumnCount(0)
,m_pTiles(NULL)
,m_uFirstGid(0)
,m_uLastGid(0)
{
    
}

CCISOTileset::~CCISOTileset()
{
    CCLOG("CCISOTileset destroy");
}

int CCISOTileset::columnCountForWidth(int width)
{
    CCAssert(m_nTileWidth > 0,"CCISOTileset::columnCountForWidth m_nTileWidth must big then 0");
    return (width - m_nMargin + m_nTileSpacing) / (m_nTileWidth + m_nTileSpacing);
}

int CCISOTileset::rowCountForHeight(int height)
{
    CCAssert(m_nTileHeight > 0,"CCISOTileset::columnRowForHeight m_nTileHeight must big then 0");
    return (height - m_nMargin + m_nTileSpacing) / (m_nTileHeight + m_nTileSpacing);
}

unsigned int CCISOTileset::lastGid()
{
    CCAssert(m_nImageHeight>0 && m_nImageWidth>0, "CCISOTileset::lastGid the image size shuold not 0");
    int column=columnCountForWidth(m_nImageWidth);
    int row=rowCountForHeight(m_nImageHeight);
    CCAssert(column*row>0, "CCISOTileset::lastGid column*row must big then 0");
    return m_uFirstGid+(column*row-1);
}

unsigned int CCISOTileset::getLastGid()
{
    if(this->m_uLastGid==0){
        this->m_uLastGid=this->lastGid();
    }
    return this->m_uLastGid;
}

void CCISOTileset::setLastGid(unsigned int gid)
{
    this->m_uLastGid=gid;
}

bool CCISOTileset::contains(unsigned int gid)
{
    return m_uFirstGid<=gid && m_uLastGid>=gid;
}

void CCISOTileset::setName(const std::string& tName)
{
    m_tName = tName;
}

std::string& CCISOTileset::getName()
{
    return m_tName;
}

void CCISOTileset::setFileName(const std::string& tFileName)
{
    m_tFileName = tFileName;
}

std::string& CCISOTileset::getFileName()
{
    return m_tFileName;
}

void CCISOTileset::setImageSource(const std::string& tImageSource)
{
    m_tImageSource = tImageSource;
}

std::string& CCISOTileset::getImageSource()
{
    return m_tImageSource;
}

void CCISOTileset::setTileWidth(int nTileWidth)
{
    m_nTileWidth = nTileWidth;
}

int CCISOTileset::getTileWidth()
{
    return m_nTileWidth;
}

void CCISOTileset::setTileHeight(int nTileHeight)
{
    m_nTileHeight = nTileHeight;
}

int CCISOTileset::getTileHeight()
{
    return m_nTileHeight;
}

void CCISOTileset::setTileSpacing(int nTileSpacing)
{
    m_nTileSpacing = nTileSpacing;
}

int CCISOTileset::getTileSpacing()
{
    return m_nTileSpacing;
}

void CCISOTileset::setMargin(int nMargin)
{
    m_nMargin = nMargin;
}

int CCISOTileset::getMargin()
{
    return m_nMargin;
}

void CCISOTileset::setTileOffset(CCPoint tTileOffset)
{
    m_tTileOffset = tTileOffset;
}

CCPoint CCISOTileset::getTileOffset()
{
    return m_tTileOffset;
}

void CCISOTileset::setImageWidth(int nImageWidth)
{
    m_nImageWidth = nImageWidth;
}

int CCISOTileset::getImageWidth()
{
    return m_nImageWidth;
}

void CCISOTileset::setImageHeight(int nImageHeight)
{
    m_nImageHeight = nImageHeight;
}

int CCISOTileset::getImageHeight()
{
    return m_nImageHeight;
}

void CCISOTileset::setColumnCount(int nColumnCount)
{
    m_nColumnCount = nColumnCount;
}

int CCISOTileset::getColumnCount()
{
    return m_nColumnCount;
}

void CCISOTileset::setTiles(CCArray* pTiles)
{
    CC_SAFE_RETAIN(pTiles);
    CC_SAFE_RELEASE(m_pTiles);
    m_pTiles = pTiles;
}

CCArray* CCISOTileset::getTiles()
{
    return m_pTiles;
}

void CCISOTileset::setFirstGid(unsigned int uFirstGid)
{
    m_uFirstGid = uFirstGid;
}

unsigned int CCISOTileset::getFirstGid()
{
    return m_uFirstGid;
}

NS_CC_END
