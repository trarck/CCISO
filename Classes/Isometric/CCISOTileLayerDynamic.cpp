#include "CCISOCoordinate.h"
#include "CCISOTileLayerDynamic.h"


NS_CC_BEGIN

const CCSize testSize=CCSizeMake(320,160);

CCISOComponentNode::CCISOComponentNode()
:m_iColumn(0)
,m_iRow(0)
,m_iMapCellX(0)
,m_iMapCellY(0)
{
    
}


CCISOTileLayerDynamic::CCISOTileLayerDynamic()
:m_pComponents(NULL)
{
	
}

CCISOTileLayerDynamic::~CCISOTileLayerDynamic()
{
	CC_SAFE_RELEASE(m_pComponents);
}

bool CCISOTileLayerDynamic::init()
{
	if(CCISOTileLayer::init()){
		m_iComponentTileExtendCount=0;
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
bool CCISOTileLayerDynamic::beforeUpdateContent()
{
	CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    screenSize=testSize;
	
	//屏幕的四个点。使用gl坐标系统，地图坐标x正方向右上，y正方向左上。初始点为屏幕左下角。也就是gl坐标的原点
	//CCPoint startMapCoord=isoViewToGame2F(0,0);
	//only for test
	CCPoint startMapCoord=isoViewToGamePoint(m_tPosition);
	m_iStartX=(int)startMapCoord.x,m_iStartY=(int)startMapCoord.y;
	return m_iStartX!=(int)m_tLastStartPoint.x || m_iStartY!=(int)m_tLastStartPoint.y;
}

void CCISOTileLayerDynamic::doUpdateContent()
{
   
}

void CCISOTileLayerDynamic::calcComponentsCount()
{
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    screenSize=testSize;
    
    
    m_iComponentTileColumn=floor(screenSize.width/m_tTileSize.width)+2;
    m_iComponentTileRow=floor(screenSize.height/m_tTileSize.height)+2;
    
    m_iComponentTileColumn+=m_iComponentTileExtendCount;
    m_iComponentTileRow+=m_iComponentTileExtendCount;
	
}

void CCISOTileLayerDynamic::createComponents()
{
	int totalColumn=2*m_iComponentTileColumn;
	int totalRow=2*m_iComponentTileRow;
	m_pComponents=new CCArray(totalColumn*totalRow);

	CCISOComponentNode* tile;
    for(int j=0;j<totalRow;j++){
		for(int i=0;i<m_iComponentTileColumn;i++){
			tile=new CCISOComponentNode();
			tile->setColumn(i*2+(j&1));
			tile->setRow(j);
			m_pComponents->addObject(tile);
			tile->release();
		}
		//if(j&1){
		//	//奇
		//	for(int i=0;i<m_iComponentTileColumn;i++){
		//		tile=new CCISOComponentNode();
		//		tile->setColumn(i*2+1);
		//		tile->setRow(j);
		//		m_pComponents->addObject(tile);
		//		tile->release();
		//	}
		//}else{
		//	//偶
		//	for(int i=0;i<m_iComponentTileColumn;i++){
		//		tile=new CCISOComponentNode();
		//		tile->setColumn(i*2);
		//		tile->setRow(j);
		//		m_pComponents->addObject(tile);
		//		tile->release();
		//	}
		//}
    }
}

void CCISOTileLayerDynamic::setupComponents()
{
	int totalColumn=2*m_iComponentTileColumn;
	int totalRow=2*m_iComponentTileRow;
	m_pComponents=new CCArray(totalColumn*totalRow);
    
	CCISOComponentNode* tile;
    int row=0,col=0;
    for(int j=0;j<totalRow;j++){
		for(int i=0;i<m_iComponentTileColumn;i++){
            col=(i*2+(j&1));
            row=j;
			tile=(CCISOComponentNode*)m_pComponents->objectAtIndex(j*m_iComponentTileColumn+col/2);
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

void CCISOTileLayerDynamic::setComponentTileExtendCount(int iComponentTileExtendCount)
{
    m_iComponentTileExtendCount = iComponentTileExtendCount;
}

int CCISOTileLayerDynamic::getComponentTileExtendCount()
{
    return m_iComponentTileExtendCount;
}

NS_CC_END
