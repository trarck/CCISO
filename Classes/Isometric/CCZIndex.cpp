//
//  ZIndex.m
//  Dungeons
//
//  Created by trarck trarck on 11-11-3.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "CCZIndex.h"

CCZIndex::CCZIndex()
:m_pStatics(NULL);
,m_pDynamics(NULL);
,m_pSortLayer(NULL);
,m_bIsWorking(true);
,m_bStaticDirty(true);
{
    
}

CCZIndex::~CCZIndex()
{
    CC_SAFE_RELEASE(m_pStatics);
    CC_SAFE_RELEASE(m_pDynamics);
    CC_SAFE_RELEASE(m_pSortLayer);
}

static CCZIndex *s_pZIndex=NULL;
CCZIndex* CCZIndex::sharedZIndex()
{
	if(!s_pZIndex){
		s_pZIndex=new CCZIndex();
        s_pZIndex->init();
	}
	return s_pZIndex;
}

CCZIndex* CCZIndex::create(CCLayer* sortLayer)
{
    CCZIndex* zIndex=new CCZIndex();
    zIndex->init(sortLayer);
    zIndex->autoRelease();
	return zIndex;
}

bool CCZIndex::init()
{
    m_pStatics=new CCArray(20);
    m_pDynamics=new CCArray(20);
    m_bIsWorking=false;

    m_pfnUpdate=schedule_selector(CCZIndex::update);
	return true;
}

bool CCZIndex::init(CCLayer* sortLayer)
{
    init();
    m_pSortLayer=sortLayer;

	return true;
}


void CCZIndex::insertStatic(CCZIndexNode* node)
{
	//注意insertSort反回的数组已经是加1的，如果使用self.statics=[self insertSort:node data:m_pStatics]，
	//则会使statics_的引用数为2，下一次再执行该函数时，则已以前的statics_无法释放。
    CCArray* results=new CCArray();
	CCArray* results=insertSort(node ,m_pStatics,results);

    CC_SAFE_RELEASE(m_pStatics);
	m_pStatics=results;
	m_bStaticDirty=true;
}

void CCZIndex::insertDynamic(CCZIndexNode*  node)
{
	m_pDynamics->addObject(node);
}

void CCZIndex::removeStatic(CCZIndexNode* node)
{
	m_pStatics->removeObject(node);
}

void CCZIndex::removeDynamic(CCZIndexNode* node)
{
	m_pDynamics->removeObject(node);
}

void CCZIndex::insertSort(CCZIndexNode* node ,CCArray* rects,CCArray& results)
{
	CCRect* src;
    CCRect* rect=node.getRect();
	int side,l=rects->count();
	bool maxAppear=false;

    if(l>0){
		CCZIndexNode fromNode=(CCZIndexNode*)rects->objectAtIndex(l-1);
		side=caculateSideFrom(fromNode->getRect(),rect);
		
		if(side<0){
			results=new CCArray(l+1);
			results->addObjectsFromArray(rects);
			results->addObject(node);
		}else{
			CCArray *maxs=new CCArray(l/2);
			CCArray *mins=new CCArray(l/2);
            
            CCObject* pObject = NULL;
	        CCARRAY_FOREACH(m_openSeq,pObject){
			    CCZIndexNode*it=(CCZIndexNode*)pObject;
				src=it->getRect();
				side=caculateSideFrom(src,rect);
				//NSLog(@"side:%d,from:%f,%f to:%f,%f",side,src.origin.x,src.origin.y,rect.origin.x,rect.origin.y);
				switch (side) {
					case -1:
					case -2:
						mins->addObject(it);
						break;
					case 1:
					case 2:
						maxs->addObject(it);
						maxAppear=true;
						break;
					case 0:
						if (maxAppear) {
							maxs->addObject(it);
						}else {
							mins->addObject(it);
						}
						break;

					default:
						break;
				}
			}
			mins->addObject(node);
			mins->addObjectsFromArray(maxs);
			results=mins;
			maxs->release();
		}
	}
}

void CCZIndex::sort(CCArray& results)
{
	CCArray* temps=new CCArray(m_pStatics);
	CCArray* items=NULL;
	
	//sort dynamics
    CCObject* pObject=NULL;
    CCARRAY_FOREACH(m_pDynamics,pObject){
	    CCZIndexNode* it=(CCZIndexNode*) pObject;
		items=insertSort(it ,temps);
		temps->release();
		temps=items;
	}
	results=items;
}

void CCZIndex::update(ccTime delta)
{
	//update z-index

	if (m_pDynamics->count()>0) {
		
		CCArray* items=new Array();
        sort(items);
		//NSLog(@"%@",m_pSortLayer);
		int i=1;
        CCObject* pObject=NULL;
        CCARRAY_FOREACH(items,pObject){
		    CCZIndexNode* it=(CCZIndexNode*)pObject;
            CCNode* node=(CCNode*)it.getEntity();
			m_pSortLayer->reorderChild(node,i++);
		}
		items->release();
	}else if (m_bStaticDirty) {
		int i=1;
        CCObject* pObject=NULL;
        CCARRAY_FOREACH(m_pStatics,pObject){
            CCZIndexNode* it=(CCZIndexNode*)pObject;
            CCNode* node=(CCNode*)it.getEntity();
		    m_pSortLayer->reorderChild(node,i++);
        }
		m_bStaticDirty=false;
	}
}

void CCZIndex::start()
{
	if(m_bIsWorking) return;
	m_bIsWorking=true;
	CCScheduler::sharedScheduler()->scheduleSelector(m_pfnUpdate,this,1,false);
}

void CCZIndex::stop()
{
	if (m_bIsWorking) {
		CCScheduler::sharedScheduler()->unscheduleSelector(m_pfnUpdate,this);
		m_bIsWorking=false;
	}
}

int CCZIndex::caculateSideFrom(CCRect* pFrom ,CCRect* pTo)
{
	int lr, tb;//如果要确切的知道8个方位。上下左右分别用1,4,2,8表示，中还是用0。这样二二之各就可以确定方位。

	if (to->origin.x > from->origin.x+from->size.width|| fabs(to->origin.x- (from->origin.x+from->size.width))<0.0001 ) {
		//右
		lr = 1;
	}else if(to->origin.x+to->size.width<from.origin.x||fabs(to->origin.x+to->size.width-from->origin.x)<0.0001){
		//左
		lr = -1;
	} else  {//desc.right<=src.right && desc.left>=src.left(内中),desc.right>=src.right && desc.left<=src.left(外中) 都算中
		//中
		lr = 0;
	}
	
	if (to->origin.y > from->origin.y+from.size.height||fabs(to->origin.y-( from->origin.y+from.size.height))<0.0001) {
		//下
		tb = 1;
	} else if (to->origin.y+to.size.height < from->origin.y ||fabs(to->origin.y+to.size.height -from->origin.y)<0.0001) {
		//上
		tb = -1;
	} else {
		//中
		tb = 0;
	}

	return lr + tb;
}

void CCZIndex::setUpdate(SEL_SCHEDULE pfnUpdate)
{
    m_pfnUpdate=pfnUpdate;
}