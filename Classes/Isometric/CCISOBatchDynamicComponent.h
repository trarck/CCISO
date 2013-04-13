#ifndef ISO_CCISOBatchDynamicComponent_H_
#define ISO_CCISOBatchDynamicComponent_H_

#include "cocos2d.h"
#include "CCISOComponentNode.h"
#include "CCISODynamicComponent.h"

NS_CC_BEGIN

class CCISOTileLayer;

class CCISOBatchDynamicComponent : public CCISODynamicComponent {

public:
	
	CCISOBatchDynamicComponent();
    
	~CCISOBatchDynamicComponent(void);
	
    virtual bool init();
    
	void createComponents();
protected:
    
    virtual void updateNode(CCISOComponentNode* node,float mx,float my);
    
protected:
    
    CCSpriteBatchNode* m_pBatchNode;
    
};



NS_CC_END

#endif //ISO_CCISOBatchDynamicComponent_H_
