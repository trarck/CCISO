//
//  ZIndex.

#ifndef ISO_CCZIndex_H_
#define ISO_CCZIndex_H_

#include "cocos2d.h"
#include "CCZIndexNode.h"

NS_CC_BEGIN

class CCGameEntity;

typedef enum {
	ZIndex_Static,
	ZIndex_Dynamic
} ZIndexType;

class CCZIndex : public CCObject {

public:
    CCZIndex();
    ~CCZIndex();

    CCZIndex* sharedZIndex();
    CCZIndex* create(CCLayer* sortLayer);
    bool init();
    bool init(CCLayer* sortLayer);

    void insertStatic(CCZIndexNode* node);
    void insertDynamic(CCZIndexNode* node);
    void removeStatic(CCZIndexNode* node);
    void removeDynamic(CCZIndexNode* node);

    CCArray* insertSort(CCZIndexNode* node ,CCArray* rects);
    CCArray* sort();
    void sortStatics();
    //动态指定。
    void start();
    void stop();
    int caculateSideFrom(CCRect* pFrom ,CCRect* pTo);

	void update(float delta);
    void setUpdate(SEL_SCHEDULE pfnUpdate);

protected:
	CCArray *m_pStatics;
	CCArray *m_pDynamics;
	CCLayer *m_pSortLayer;
	bool m_bIsWorking;
	bool m_bStaticDirty;
    //弱引用
    SEL_SCHEDULE m_pfnUpdate;
};


NS_CC_END

#endif //ISO_CCZIndex_H_
