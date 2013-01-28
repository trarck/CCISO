#include "CCISOCoordinate.h"
#include "CCISODynamicComponent.h"


NS_CC_BEGIN

//const CCSize testSize=CCSizeMake(256,160);

CCISODynamicComponent::CCISODynamicComponent()
:m_pComponents(NULL)
,m_iStartX(0)
,m_iStartY(0)
,m_iLastStartX(-999999)
,m_iLastStartY(-999999)
,m_iComponentIndexX(0)
,m_iComponentIndexY(0)
,m_iComponentNodeExtendCount(0)
,m_tMapTileSize(CCSizeMake(64, 32))
,m_pDelegator(NULL)
{
	
}

CCISODynamicComponent::~CCISODynamicComponent()
{
	CC_SAFE_RELEASE(m_pComponents);
}

bool CCISODynamicComponent::init()
{
    m_tScreenSize=CCDirector::sharedDirector()->getWinSize();//CCSizeMake(480,320);CCSizeMake(480,320);//
	return true;
}

/**
 * 检查是否需要由于位置的改变而更新显示内容。
 * 并记录新位置对应的地图坐标，为更新使用。
 */
bool CCISODynamicComponent::beforeUpdateContent()
{
	
	//屏幕的四个点。使用gl坐标系统，地图坐标x正方向右上，y正方向左上。初始点为屏幕左下角。也就是gl坐标的原点
	//CCPoint startMapCoord=isoViewToGame2F(0,0);
	//only for test
	CCPoint startMapCoord=isoViewToGamePoint(m_tOffset);
	m_iStartX=(int)startMapCoord.x;
	m_iStartY=(int)startMapCoord.y;
    //CCLOG("start:%d,%d %f,%f",m_iStartX,m_iStartY,m_tPosition.x,m_tPosition.y);
	return m_iStartX!=m_iLastStartX || m_iStartY!=m_iLastStartY;
}

void CCISODynamicComponent::doUpdateComponents()
{
    
    int totalRow=2*m_iComponentTileRow;
    int totalColumn=2*m_iComponentTileColumn;
    
    int dx=m_iStartX-m_iLastStartX;
    int dy=m_iStartY-m_iLastStartY;
    
    int dirX=dx>0?1:dx<0?-1:0;
    int dirY=dy>0?1:dy<0?-1:0;
    
    int loopX=abs(dx);
    int loopY=abs(dy);
    
	CCLOG("updateCompoents:%d,%d loops:%d,%d",dx,dy,loopX,loopY);
    int moveComponentIndexX=0,moveComponentIndexY=0;
    int index,row,col;
    
//    float mx=0,my=0;
//    CCISOComponentNode* node=NULL;
    
    //注意正向，反向node移动的序列位置
    if(dx!=0){
        for(int k=0;k<loopX;k++){
            //横向移动 移动列
            if(dirX>0){
                moveComponentIndexX=m_iComponentIndexX;
                m_iComponentIndexX=(m_iComponentIndexX+dirX)%totalColumn;
            }else if(dirX<0){
                m_iComponentIndexX=(m_iComponentIndexX+dirX+totalColumn)%totalColumn;
                moveComponentIndexX=m_iComponentIndexX;
            }
            
            for(int j=0;j<m_iComponentTileRow;j++){
                //如果行列的奇偶性一至，则从当前位置开始。如果互为奇奇偶，则要把行加1，变为奇或偶。
                row=(j*2+m_iComponentIndexY+((m_iComponentIndexY&1)^(moveComponentIndexX&1)))%totalRow;
                index=row*m_iComponentTileColumn+moveComponentIndexX/2;
                //CCLOG("updateComponents x:%d,%d,%d",index,moveComponentIndexX,row);
                this->updateMapCoordinate(index, dirX*m_iComponentTileColumn, -dirX*m_iComponentTileColumn);

//                node=(CCISOComponentNode*) m_pComponents->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx+dirX*m_iComponentTileColumn, my-dirX*m_iComponentTileColumn);
            }
                    
            //纵向移动 移动行
            if(dirX>0){
                moveComponentIndexY=m_iComponentIndexY;
                m_iComponentIndexY=(m_iComponentIndexY+dirX)%totalRow;
                
            }else if(dirX<0){
                m_iComponentIndexY=(m_iComponentIndexY+dirX+totalRow)%totalRow;
                moveComponentIndexY=m_iComponentIndexY;
            }
            
            for(int i=0;i<m_iComponentTileColumn;i++){
                //如果行列的奇偶性一至，则从当前位置开始。如果互为奇奇偶，则要把行加1，变为奇或偶。
                col=(i*2+m_iComponentIndexX+((m_iComponentIndexX & 1)^(moveComponentIndexY & 1)))%totalColumn;
                index=moveComponentIndexY*m_iComponentTileColumn+col/2;
//                CCLOG("updateComponents y:%d,%d,%d",index,col,moveComponentIndexY);
                this->updateMapCoordinate(index, dirX*m_iComponentTileRow, dirX*m_iComponentTileRow);
//                node=(CCISOComponentNode*) m_pComponents->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx+dirX*m_iComponentTileRow, my+dirX*m_iComponentTileRow);
            }
        }
    }
    
	if(dy!=0){
        for(int k=0;k<loopY;k++){
            //横向移动
            if(dirY>0){
                m_iComponentIndexX=(m_iComponentIndexX-1+totalColumn)%totalColumn;
                moveComponentIndexX=m_iComponentIndexX;
            }else if(dirY<0){
                moveComponentIndexX=m_iComponentIndexX;
                m_iComponentIndexX=(m_iComponentIndexX+1)%totalColumn;
            }

            
            for(int j=0;j<m_iComponentTileRow;j++){
                row=(j*2+m_iComponentIndexY+((m_iComponentIndexY&1)^(moveComponentIndexX&1)))%totalRow;
                index=row*m_iComponentTileColumn+moveComponentIndexX/2;
//                CCLOG("updateComponents x:%d,%d,%d",index,moveComponentIndexX,row);
                this->updateMapCoordinate(index, -dirY*m_iComponentTileColumn, dirY*m_iComponentTileColumn);
//                node=(CCISOComponentNode*) m_pComponents->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx-dirY*m_iComponentTileColumn, my+dirY*m_iComponentTileColumn);
            }
            
            if(dirY>0){
                moveComponentIndexY=m_iComponentIndexY;
                m_iComponentIndexY=(m_iComponentIndexY+1)%totalRow;
            }else if(dirY<0){
                m_iComponentIndexY=(m_iComponentIndexY-1+totalRow)%totalRow;
                moveComponentIndexY=m_iComponentIndexY;
            }
            //纵向移动
            
            for(int i=0;i<m_iComponentTileColumn;i++){
                col=(i*2+m_iComponentIndexX+((m_iComponentIndexX & 1)^(moveComponentIndexY & 1)))%totalColumn;
                index=moveComponentIndexY*m_iComponentTileColumn+col/2;
//                CCLOG("updateComponents y:%d,%d,%d",index,col,moveComponentIndexY);
                this->updateMapCoordinate(index,dirY*m_iComponentTileRow, dirY*m_iComponentTileRow);
//                node=(CCISOComponentNode*) m_pComponents->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx+dirY*m_iComponentTileRow, my+dirY*m_iComponentTileRow);
            }
        }
    }
    
    m_iLastStartX=m_iStartX;
    m_iLastStartY=m_iStartY;
}

void CCISODynamicComponent::calcComponentsCount()
{
    m_iComponentTileColumn=floor(m_tScreenSize.width/m_tMapTileSize.width)+2;
    m_iComponentTileRow=floor(m_tScreenSize.height/m_tMapTileSize.height)+2;
    
    m_iComponentTileColumn+=m_iComponentNodeExtendCount;
    m_iComponentTileRow+=m_iComponentNodeExtendCount;
    m_iComponentTileTotalColumn=2*m_iComponentTileColumn;
    m_iComponentTileTotalRow=2*m_iComponentTileRow;
	CCLOG("calcComponentsCount:%d,%d",m_iComponentTileColumn,m_iComponentTileRow);
}

void CCISODynamicComponent::createComponents()
{
	int totalColumn=2*m_iComponentTileColumn;
	int totalRow=2*m_iComponentTileRow;
	m_pComponents=new CCArray(totalColumn*totalRow);

	CCISOComponentNode* node;
    for(int j=0;j<totalRow;j++){
		for(int i=0;i<m_iComponentTileColumn;i++){
			node=new CCISOComponentNode();
			node->setColumn(i*2+(j&1));
			node->setRow(j);
			m_pComponents->addObject(node);
			node->release();
		}
		//if(j&1){
		//	//奇
		//	for(int i=0;i<m_iComponentTileColumn;i++){
		//		node=new CCISOComponentNode();
		//		node->setColumn(i*2+1);
		//		node->setRow(j);
		//		m_pComponents->addObject(node);
		//		node->release();
		//	}
		//}else{
		//	//偶
		//	for(int i=0;i<m_iComponentTileColumn;i++){
		//		node=new CCISOComponentNode();
		//		node->setColumn(i*2);
		//		node->setRow(j);
		//		m_pComponents->addObject(node);
		//		node->release();
		//	}
		//}
    }
}

void CCISODynamicComponent::initComponents()
{
    int totalRow=2*m_iComponentTileRow;
    
    
    int startX=m_iStartX-m_iComponentNodeExtendCount-1;
    int startY=m_iStartY;
    CCLOG("initComponents start:%d,%d",startX,startY);
	CCISOComponentNode* node;
    int row=0,col=0,index=0;
    int mx=0,my=0;
    for(int j=0;j<totalRow;j++){
		for(int i=0;i<m_iComponentTileColumn;i++){
            col=(i*2+(j&1));
            row=j;
            index=j*m_iComponentTileColumn+col/2;
            
			node=(CCISOComponentNode*)m_pComponents->objectAtIndex(j*m_iComponentTileColumn+col/2);
            mx=startX+i;
            my=startY-i;
            node->updateMapCoordinate(mx,my);
            //CCLOG("index:%d,%d,%d:%d,%d",index,i,j,mx,my);
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

void CCISODynamicComponent::updateMapCoordinate(unsigned int index,float deltaMapX,float deltaMapY)
{
    m_pDelegator->updateComponentMapCoordinate(index, deltaMapX, deltaMapY);
    
    CCISOComponentNode* node=(CCISOComponentNode*) m_pComponents->objectAtIndex(index);
    float mx=node->getMapX();
    float my=node->getMapY();
    float newMx=mx+deltaMapX;
    float newMy=my+deltaMapY;
    
    CCLOG("CCISODynamicComponent::updateMapCoordinate from:%f,%f to:%f,%f",mx,my,newMx,newMy);
    
    node->updateMapCoordinate(newMx, newMy);
    
}

void CCISODynamicComponent::setupComponents(int iComponentNodeExtendCount)
{
	this->setComponentTileExtendCount(iComponentNodeExtendCount);
    this->calcComponentsCount();
    this->createComponents();
    this->initComponents();
}

void CCISODynamicComponent::setupComponents(int iComponentNodeExtendCount,const CCPoint& position)
{
	this->setComponentTileExtendCount(iComponentNodeExtendCount);
    this->calcComponentsCount();
    this->createComponents();
	//this->setOffset(position);
	this->initOffset(position);
    this->initComponents();	
}

CCArray* CCISODynamicComponent::getComponents(){
    return m_pComponents;
}

void CCISODynamicComponent::setComponentTileColumn(int iComponentTileColumn)
{
    m_iComponentTileColumn = iComponentTileColumn;
}

int CCISODynamicComponent::getComponentTileColumn()
{
    return m_iComponentTileColumn;
}

void CCISODynamicComponent::setComponentTileRow(int iComponentTileRow)
{
    m_iComponentTileRow = iComponentTileRow;
}

int CCISODynamicComponent::getComponentTileRow()
{
    return m_iComponentTileRow;
}

void CCISODynamicComponent::setComponentTileExtendCount(int iComponentNodeExtendCount)
{
    m_iComponentNodeExtendCount = iComponentNodeExtendCount;
}

int CCISODynamicComponent::getComponentTileExtendCount()
{
    return m_iComponentNodeExtendCount;
}

void CCISODynamicComponent::initOffset(const CCPoint& tOffset)
{
    this->setOffset(tOffset);
	CCPoint startMapCoord=isoViewToGamePoint(tOffset);
	m_iStartX=(int)startMapCoord.x;
	m_iStartY=(int)startMapCoord.y;
	m_iLastStartX=m_iStartX;
	m_iLastStartY=m_iStartY;
}

void CCISODynamicComponent::initOffset(float x,float y)
{
	this->initOffset(ccp(x,y));
}

void CCISODynamicComponent::scroll(const CCPoint& tOffset)
{
    this->setOffset(tOffset);
	if(this->beforeUpdateContent()){
		m_iLastStartX=m_iStartX;
		m_iLastStartY=m_iStartY;
		//TODO 不删除所有tile,只修改改变的tile.
		//this->removeAllChildrenWithCleanup(true);
		//this->doUpdateContent();
		this->doUpdateComponents();

	}
}

void CCISODynamicComponent::scroll(float x,float y)
{
    this->scroll(ccp(x,y));
}



void CCISODynamicComponent::setOffset(const CCPoint& tOffset)
{
    m_tOffset = tOffset;
}

void CCISODynamicComponent::setOffset(float x,float y)
{
    m_tOffset.x=x;
	m_tOffset.y=y;
}

CCPoint CCISODynamicComponent::getOffset()
{
    return m_tOffset;
}

void CCISODynamicComponent::setDelegator(CCISODynamicComponentUpdateDelegator* pDelegator)
{
    m_pDelegator=pDelegator;
}

NS_CC_END
