#include "CCISOCoordinate.h"
#include "CCISOTileLayerDynamic.h"


NS_CC_BEGIN

const CCSize testSize=CCSizeMake(320,160);

CCISOTileLayerDynamic::CCISOTileLayerDynamic()
{
	
}

CCISOTileLayerDynamic::~CCISOTileLayerDynamic()
{
//	CC_SAFE_RELEASE();
}

bool CCISOTileLayerDynamic::init()
{
	if(CCISOTileLayer::init()){
		m_iComponenTileExtendCount=0;
	}
	return true;
}


void CCISOTileLayerDynamic::setPosition(const CCPoint& newPosition)
{
	m_tPosition=newPosition;
	if(this->beforeUpdateContent()){
		//TODO 不删除所有tile,只修改改变的tile.
		this->removeAllChildrenWithCleanup(true);
		this->doUpdateContent();
	}
}


/**
 * 检查是否需要由于位置的改变而更新显示内容。
 * 并记录新位置对应的地图坐标，为更新使用。
 */
//bool CCISOTileLayerDynamic::beforeUpdateContent()
//{
//
//}
//
//void CCISOTileLayerDynamic::doUpdateContent()
//{
//   
//}

int CCISOTileLayerDynamic::calcComponentTilesCount()
{
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    screenSize=testSize;
    
    
    m_iComponentTileColumn=floor(screenSize.width/m_tTileSize.width)+2;
    m_iComponentTileRow=floor(screenSize.height/m_tTileSize.height)+2;
    
    m_iComponentTileColumn+=m_iComponenTileExtendCount;
    m_iComponentTileRow+=m_iComponenTileExtendCount;
    
}

void CCISOTileLayerDynamic::createComponentTiles()
{
    for(int j=0;j<m_iComponentTileRow;j++){
        for(int i=0;i<m_iComponentTileColumn;i++){
            
        }
    }
}


void CCISOTileLayerDynamic::draw()
{
	
	ccDrawColor4B(255,0,0,255);
    ccDrawRect(m_tPosition,ccp(m_tPosition.x+testSize.width,m_tPosition.y+testSize.height));
}

void CCISOTileLayerDynamic::setComponentTileColumn(int iComponentTileColumn)
{
    m_iComponentTileColumn = iComponentTileColumn;
}

int CCISOTileLayerDynamic::getComponentTileColumn()
{
    return m_iComponentTileColumn;
}

void CCISOTileLayerDynamic::setComponentTileRow(int iComponentTileRow)
{
    m_iComponentTileRow = iComponentTileRow;
}

int CCISOTileLayerDynamic::getComponentTileRow()
{
    return m_iComponentTileRow;
}

void CCISOTileLayerDynamic::setComponenTileExtendCount(int iComponenTileExtendCount)
{
    m_iComponenTileExtendCount = iComponenTileExtendCount;
}

int CCISOTileLayerDynamic::getComponenTileExtendCount()
{
    return m_iComponenTileExtendCount;
}

NS_CC_END
