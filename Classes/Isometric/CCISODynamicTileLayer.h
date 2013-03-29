#ifndef ISO_CCISODynamicTileLayer_H_
#define ISO_CCISODynamicTileLayer_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"
#include "CCISODynamicComponent.h"

NS_CC_BEGIN

/**
 动态更新可显示区域,只渲染显示区域的tile.
 */
class CCISODynamicTileLayer : public CCISOTileLayer {

public:
	
	CCISODynamicTileLayer();
    
	~CCISODynamicTileLayer(void);
	
    virtual bool init();
    
    virtual bool init(CCSize& mapTileSize,CCPoint& offset);


    //设置m_pDynamicComponent的column and row
    void setComponentColumnAndRow();
    /**
     * 更新前检查
     */
	bool beforeUpdateContent();
    
    /**
     * 更新内容
     */
	void doUpdateContent();

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
    
    void setScreenSize(const CCSize& screenSize);

public:
    
    virtual void setDynamicComponent(CCISODynamicComponent* pDynamicComponent);
    
    virtual CCISODynamicComponent* getDynamicComponent();
   
    
protected:

    CCISODynamicComponent* m_pDynamicComponent;
    
    /**
     * 上次移动的地图位置
     */
    int m_iLastStartX;
    int m_iLastStartY;
    
//	CCPoint m_tLastStartPoint;
    
    CCSize m_tScreenSize;
//	int m_iStartX;
//	int m_iStartY;
};



NS_CC_END

#endif //ISO_CCISODynamicTileLayer_H_
