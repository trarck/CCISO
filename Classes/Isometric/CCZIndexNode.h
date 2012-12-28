//
//  ZIndexNode.

#ifndef ISO_CCZIndexNode_H_
#define ISO_CCZIndexNode_H_

#include "cocos2d.h"

NS_CC_BEGIN


class CCZIndexNode : public CCObject {

public:
    CCZIndexNode();
    ~CCZIndexNode();
    
    void setRect(CCRect* rect);
    CCRect* getRect();
    
    //弱引用
    void setEntity(CCObject* entity);
    CCObject* getEntity();
protected:
    CCObject* m_pEntity;
    CCRect* m_pRect;
};


NS_CC_END

#endif //ISO_CCZIndexNode_H_
