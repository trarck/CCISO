#ifndef ISO_CCISOTileLayerOptimization_H_
#define ISO_CCISOTileLayerOptimization_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"

NS_CC_BEGIN
static const CCSize testSize=CCSizeMake(480,320);

/**
 动态更新可显示区域,只渲染显示区域的tile.
 */
class CCISOTileLayerOptimization : public CCISOTileLayer {

public:
	
	CCISOTileLayerOptimization();
	~CCISOTileLayerOptimization(void);
	
    virtual bool init();

    /**
     * 初始化偏移
     */
	virtual void initOffset(const CCPoint& tOffset);
    virtual void initOffset(float x,float y);

    /**
     * 更新前检查
     */
	bool beforeUpdateContent();
    
    /**
     * 更新内容
     */
	void doUpdateContent();
    void doUpdateContent2();

    /**
     * 移动位置
     * 只作判断使用，不改变显示位置
     */
    virtual void scroll(const CCPoint& tOffset);
    virtual void scroll(float x,float y);
    
	bool isCellChange();
    void visitTileShowable();
    void visitTileShowable2();
    
    /**
     * test bounding
     */
    virtual void draw();
    
	void addTileAt(float x,float y);

protected:

	CCPoint m_tLastStartPoint;
//	int m_iStartX;
//	int m_iStartY;
};



NS_CC_END

#endif //ISO_CCISOTileLayerOptimization_H_
