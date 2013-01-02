/**
 * MapCellInfo由成员函数来实现
 */

#ifndef ISO_CCAstar_H_
#define ISO_CCAstar_H_

#include "cocos2d.h"
#include "CCAstarNode.h"

NS_CC_BEGIN

#define DEFAULT_NEARS_LENGTH 8

// #define WorkDisable 0x1

#define ASTAR_G_LINE 10
#define ASTAR_G_CROSS 14


typedef bool (CCObject::*SEL_CheckBarrierHandler)(int x,int y);
#define check_barrier_selector(_SELECTOR) (SEL_CheckBarrierHandler)(&_SELECTOR)
typedef bool (*FUN_CheckBarrierHandler)(int x,int y);

class CCAstar : public CCObject {
public:
	
	CCAstar();
	~CCAstar(void);

	bool init();
	
	virtual void setMinX(int minX);
	virtual int getMinX();
	virtual void setMinY(int minY);
	virtual int getMinY();
	virtual void setMaxX(int maxX);
	virtual int getMaxX();
	virtual void setMaxY(int maxY);
	virtual int getMaxY();

	static CCAstar* sharedAstar();

	void setBounding(int minX ,int minY,int maxX,int maxY);
	void setStart(int x ,int y);
	void setEnd(int x ,int y);
	void reset();

	bool search();
	bool checkNearby();
	
	void getNext();
    void setOpenSeqNode(CCAstarNode* node ,int g);
	void addToOpen(CCAstarNode* node);
	void removeFromOpen(CCAstarNode* node);
	bool isInOpen(int x ,int y);
	
	CCAstarNode* getFromOpen(int x ,int y);

	void addToClose(int x,int y);
	bool isInClose(int x ,int y);

	int getH(int x ,int y);

	bool isOut(int x ,int y);
	
	
	bool isWorkableWithCrossSide(int x ,int y ,int stepX ,int stepY);
	bool isCrossSideWorkable(int x ,int y ,int stepX,int stepY);
	bool isEnd(int x ,int  y) ;
	bool isEnd(int x,int y ,int stepX ,int stepY);

	//由具体应用实现
	bool isWorkable(int x ,int y) ;
	void setCheckBarrierHandle(SEL_CheckBarrierHandler checkBarrierHandle,CCObject* target);
	// //可以由子类继承isWorkable 实现调用函数接口
	// void setCheckBarrierHandle(FUN_CheckBarrierHandler isWorkable);
	

	CCArray* getPath();
	CCArray* getPathWithStart();
	CCArray* getPathWithEnd();
	CCArray* getPathWithStartEnd();

protected:	
	int m_minX;
	int m_minY;
	int m_maxX;
	int m_maxY;
	
	CCAstarNode* m_start;
	CCAstarNode* m_end;
	CCAstarNode* m_current;
	
	CCArray* m_openSeq;//开启队列，存放每个结点。结点属性,parent 父结点，x,y地图坐,f,g,h路径评分
	
	//opens closes与地图相关，一般用二维数组
	//这里使用"y,x"做为关键字，BOOL做为值的dictionary来在存储。键可替换y右移16位加上x的数值
	//当然也可以根据搜索范围(minX,minY,maxX,maxY)来生成数组，数组值是BOOL
	//TODO 比较二种方法哪种快。最好应该是关于x，y的二维hash表算法最快。
	//二元hash:先创建关于y的hash,值为关于x的hash。这样查找时间为O(2)
	CCDictionary* m_opens;//开起列表,设置地图上的坐标，表示开启状态
	CCDictionary* m_closes;//关闭列表,存放已经到达过的点
	
	//都是若引用
	SEL_CheckBarrierHandler m_checkBarrierHandle;
	CCObject* m_target;
};

NS_CC_END

#endif // ISO_CCAstar_H_