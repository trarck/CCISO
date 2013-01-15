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
,m_iLastStartX(0)
,m_iLastStartY(0)
,m_iComponentIndexX(0)
,m_iComponentIndexY(0)
{
	
}

CCISOTileLayerDynamic::~CCISOTileLayerDynamic()
{
	CC_SAFE_RELEASE(m_pComponents);
}

bool CCISOTileLayerDynamic::init()
{
	if(CCISOTileLayer::init()){
		m_iComponentNodeExtendCount=0;
	}
	return true;
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
	CCPoint startMapCoord=isoViewToGamePoint(m_tOffset);
	m_iStartX=(int)startMapCoord.x,m_iStartY=(int)startMapCoord.y;
    CCLOG("start:%d,%d %f,%f",m_iStartX,m_iStartY,m_tPosition.x,m_tPosition.y);
	return m_iStartX!=(int)m_tLastStartPoint.x || m_iStartY!=(int)m_tLastStartPoint.y;
}

void CCISOTileLayerDynamic::doUpdateContent()
{
    int totalRow=2*m_iComponentTileRow;
    
    
    int startX=m_iStartX-m_iComponentNodeExtendCount-1;
    int startY=m_iStartY;
    CCLOG("start:%d,%d",startX,startY);
	CCISOComponentNode* tile;
    int row=0,col=0,index=0;
    int mx=0,my=0;
    for(int j=0;j<totalRow;j++){
		for(int i=0;i<m_iComponentTileColumn;i++){
            col=(i*2+(j&1));
            row=j;
            index=j*m_iComponentTileColumn+col/2;
            
			tile=(CCISOComponentNode*)m_pComponents->objectAtIndex(j*m_iComponentTileColumn+col/2);
            mx=startX+i;
            my=startY-i;
            this->addTileAt(mx,my);
            CCLOG("index:%d,%d,%d:%d,%d",index,i,j,mx,my);
		}
        if(j&1){
			//下个循环为偶
			startY++;
		}else{
			//下个循环为奇
            startX++;
		}
    }

}

void CCISOTileLayerDynamic::doUpdateComponents()
{
    
    int totalRow=2*m_iComponentTileRow;
    int totalColumn=2*m_iComponentTileColumn;
    
    int dx=m_iStartX-m_iLastStartX;
    int dy=m_iStartY-m_iLastStartY;
    
    int dirX=dx>0?1:-1;
    int dirY=dy>0?1:-1;
    
    int loopX=abs(dx);
    int loopY=abs(dy);
    

    int moveComponentIndex=0;
    int index,row,col;
    if(dx>0){
        //横向移动
        moveComponentIndex=m_iComponentIndexX;
        for(int j=0;j<m_iComponentTileRow;j++){
            row=j*2+moveComponentIndex&1;
            index=j*m_iComponentTileColumn+moveComponentIndex/2;
            CCLOG("updateComponents x:%d,%d,%d",index,moveComponentIndex,j);
        }
        m_iComponentIndexX=(m_iComponentIndexX+1)%totalColumn;
        
        //纵向移动
        moveComponentIndex=m_iComponentIndexY;
        for(int i=0;i<m_iComponentTileColumn;i++){
            col=i*2+moveComponentIndex&1;
            index=moveComponentIndex*m_iComponentTileColumn+col/2;
            CCLOG("updateComponents y:%d,%d,%d",index,col,moveComponentIndex);
        }
        m_iComponentIndexY=(m_iComponentIndexY+1)%totalRow;
        
    }else{
        
        
    }
    
    
    m_iLastStartX=m_iStartX;
    m_iLastStartY=m_iStartY;
}

void CCISOTileLayerDynamic::calcComponentsCount()
{
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    screenSize=testSize;
    
    
    m_iComponentTileColumn=floor(screenSize.width/m_tTileSize.width)+2;
    m_iComponentTileRow=floor(screenSize.height/m_tTileSize.height)+2;
    
    m_iComponentTileColumn+=m_iComponentNodeExtendCount;
    m_iComponentTileRow+=m_iComponentNodeExtendCount;
    m_iComponentTileTotalColumn=2*m_iComponentTileColumn;
    m_iComponentTileTotalRow=2*m_iComponentTileRow;
	CCLOG("calcComponentsCount:%d,%d",m_iComponentTileColumn,m_iComponentTileRow);
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

void CCISOTileLayerDynamic::initComponents()
{
    this->doUpdateContent();
}

void CCISOTileLayerDynamic::setupComponents(int iComponentNodeExtendCount)
{
	this->setComponentTileExtendCount(iComponentNodeExtendCount);
    this->calcComponentsCount();
    this->createComponents();
//    this->initComponents();
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

void CCISOTileLayerDynamic::setComponentTileExtendCount(int iComponentNodeExtendCount)
{
    m_iComponentNodeExtendCount = iComponentNodeExtendCount;
}

int CCISOTileLayerDynamic::getComponentTileExtendCount()
{
    return m_iComponentNodeExtendCount;
}

void CCISOTileLayerDynamic::scroll(const CCPoint& tOffset)
{
    this->setOffset(tOffset);
	if(this->beforeUpdateContent()){
		//TODO 不删除所有tile,只修改改变的tile.
		this->removeAllChildrenWithCleanup(true);
		this->doUpdateContent();
	}
}

void CCISOTileLayerDynamic::scroll(float x,float y)
{
    this->scroll(ccp(x,y));
}

NS_CC_END
