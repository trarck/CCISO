//
//  AstarNode.h
//  isometric
//
#ifndef ISO_CCAstarNode_H_
#define ISO_CCAstarNode_H_

#include "cocos2d.h"

NS_CC_BEGIN


class CCAstarNode : public CCObject {

public:
	
	CCAstarNode();
	~CCAstarNode(void);
	
    bool init();
    bool init(int x,int y);
	bool init(int x ,int y ,int g ,int h);
    
	virtual void setX(int x);
	virtual int getX();
	virtual void setY(int y);
	virtual int getY();
	virtual void setG(int g);
	virtual int getG();
	virtual void setH(int h);
	virtual int getH();
	virtual void setF(int f);
	virtual int getF();
	virtual void setParent(CCAstarNode* parent);
	virtual CCAstarNode* getParent();

    
	

protected:
	CCAstarNode* m_parent;
	int m_x;
	int m_y;
	int m_g;
	int m_h;
	int m_f;
};



NS_CC_END

#endif //ISO_CCAstarNode_H_
