#include "CCISOTileLayer.h"
#include "CCISOCoordinate.h"

NS_CC_BEGIN

const CCSize testSize=CCSizeMake(320,160);

CCISOTileLayer::CCISOTileLayer()
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
	m_tLastStartPoint=ccp(-9999,-9999);
	return true;
}

void CCISOTileLayer::addTileAt(float x,float y)
{
    CCSprite* testGrid=CCSprite::create("grid1.png");
    testGrid->setPosition(isoGameToView2F(x,y));
    testGrid->setAnchorPoint(ccp(0.5,0));
    testGrid->setOpacity(40);
    this->addChild(testGrid);
}

void CCISOTileLayer::setPosition(const CCPoint& newPosition)
{
	m_tPosition=newPosition;
	if(this->beforeUpdateContent()){
		//TODO 不删除所有tile,只修改改变的tile.
		this->removeAllChildrenWithCleanup(true);
		this->doUpdateContent();
	}
}

void CCISOTileLayer::setPosition(float x,float y)
{
	this->setPosition(ccp(x,y));
}

/**
 * 检查是否需要由于位置的改变而更新显示内容。
 * 并记录新位置对应的地图坐标，为更新使用。
 */
bool CCISOTileLayer::beforeUpdateContent()
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

void CCISOTileLayer::doUpdateContent()
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

bool CCISOTileLayer::isCellChange()
{
	CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    screenSize=testSize;
	
	//屏幕的四个点。使用gl坐标系统，地图坐标x正方向右上，y正方向左上。初始点为屏幕左下角。也就是gl坐标的原点
	//CCPoint startMapCoord=isoViewToGame2F(0,0);
	//only for test
	CCPoint startMapCoord=isoViewToGamePoint(m_tOffset);
	int startX=(int)startMapCoord.x,startY=(int)startMapCoord.y;
	//CCLOG("checkMoveable:%d,%d:%d,%d  %f,%f:%f,%f",startX,startY,(int)m_tLastStartPoint.x,(int)m_tLastStartPoint.y,startMapCoord.x,startMapCoord.y,m_tLastStartPoint.x,m_tLastStartPoint.y);
	return startX!=(int)m_tLastStartPoint.x || startY!=(int)m_tLastStartPoint.y;
}

void CCISOTileLayer::visitTileShowable()
{
    CCLOG("in visit#########");
	CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    screenSize=testSize;
	
	//屏幕的四个点。使用gl坐标系统，地图坐标x正方向右上，y正方向左上。初始点为屏幕左下角。也就是gl坐标的原点
	//CCPoint startMapCoord=isoViewToGame2F(0,0);
	//only for test
	CCPoint startMapCoord=isoViewToGamePoint(m_tOffset);
	int startX=(int)startMapCoord.x,startY=(int)startMapCoord.y;
	if(startX!=(int)m_tLastStartPoint.x || startY!=(int)m_tLastStartPoint.y){
		m_tLastStartPoint.x=startX;
		m_tLastStartPoint.y=startY;
		//移动的格子数.为了确保显示的完全，每个角相应移动一个格子。左右在一起就加2，同样上下在一起也要加2
		int columnCount=floor(screenSize.width/m_tTileSize.width)+2;
		//会有一行浪费掉的。所以要减去1.
		int rowCount=(floor(screenSize.height/m_tTileSize.height)+2)*2-1;
		int oggColumnCount=columnCount+1;
		//后移一步.由于是在左下角，则只需移动x轴
		startX-=1;
    
		CCLOG("state:column=%d,rowCount=%d,start=%f,%f:%f,%f",columnCount,rowCount,startMapCoord.x,startMapCoord.y,this->getPosition().x,this->getPosition().y);

		
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
}

//ios game book 上的方法
void CCISOTileLayer::visitTileShowable2()
{
	CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
	//屏幕的四个点。目前按原点在左上角，需要转成gl坐标系。
	CCPoint screenLeftTop=isoViewToGame2F(0,0);
	CCPoint screenRightTop=isoViewToGame2F(screenSize.width,0);
	CCPoint screenLeftBottom=isoViewToGame2F(0,screenSize.height);
	CCPoint screenRightBottom=isoViewToGame2F(screenSize.width,screenSize.height);

	screenLeftTop.x-=1;
	screenRightBottom.x+=1;
	screenRightTop.y-=1;
	screenLeftBottom.y+=1;

	
	CCPoint rowStart=screenLeftTop;
	CCPoint rowEnd=screenRightTop;

	//由于是按对角移动，只需要x移轴
	
	int mx=0,my=0;
	float x=rowStart.x,y=rowStart.y;
	int rowCount=0;
	//在左下角之上
	while(rowStart.x<screenLeftBottom.x||rowStart.y<screenLeftBottom.y){
		while(x!=rowEnd.x && y!=rowEnd.y){
			mx=x;
			my=y;
            x+=1;
            y-=1;
		}
		if(++rowCount&1){
			rowStart.y+=1;
			rowEnd.x+=1;
		}else{
			rowStart.x+=1;
			rowEnd.y+=1;
		}
	}
}




void CCISOTileLayer::draw()
{
	
	ccDrawColor4B(255,0,0,255);
    ccDrawRect(m_tPosition,ccp(m_tPosition.x+testSize.width,m_tPosition.y+testSize.height));
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

void CCISOTileLayer::setName(const char* pName)
{
    m_pName = pName;
}

const char* CCISOTileLayer::getName()
{
    return m_pName;
}

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
