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
    CCLOG("doVisit#########");
	CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    screenSize=testSize;
	
	int startX=m_iStartX,startY=m_iStartY;

	m_tLastStartPoint.x=startX;
	m_tLastStartPoint.y=startY;
	//移动的格子数.为了确保显示的完全，每个角相应移动一个格子。左右在一起就加2，同样上下在一起也要加2
	int columnCount=floor(screenSize.width/m_tTileSize.width)+2;
	//会有一行浪费掉的。所以要减去1.
	int rowCount=(floor(screenSize.height/m_tTileSize.height)+2)*2-1;
	int oggColumnCount=columnCount+1;
	//后移一步.由于是在左下角，则只需移动x轴
	startX-=1;
    
	int mx=0,my=0;
	for(int j=0;j<rowCount;j++){
		//if(j>0){
		//	if(j&1){
		//		columnCount++;
		//		startY++;
		//	}else{
		//		columnCount--;
		//		startX++;
		//	}
		//}
		for(int i=0;i<columnCount;i++){
			mx=startX+i;
			my=startY-i;
			//CCLOG("visit:%f,%f",mx,my);
			//有了map坐标就可以显示内容。
			addTileAt(mx,my);
		}
		//if((j+1)&1){
		//	columnCount++;
		//	startY++;
		//}else{
		//	columnCount--;
		//	startX++;
		//}
		//这里可以使j+1，再调换true和false的body,就是正常逻辑
		if(j&1){
			//下个循环为偶
			columnCount--;
			startX++;
		}else{
			//下个循环为奇
			columnCount++;
			startY++;
		}
	}
}

int CCISOTileLayerDynamic::calcComponentTilesCount()
{
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    screenSize=testSize;
    
    
    m_iComponentTileColumn=floor(screenSize.width/m_tTileSize.width)+2;
    m_iComponentTileRow=floor(screenSize.height/m_tTileSize.height)+2;
    
    
}

void CCISOTileLayerDynamic::createComponentTiles()
{
    
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
