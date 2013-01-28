#ifndef ISO_CCISODynamicComponent_H_
#define ISO_CCISODynamicComponent_H_

#include "cocos2d.h"
#include "CCISOComponentNode.h"

NS_CC_BEGIN

class CCISODynamicComponentUpdateDelegator
{
public:
    virtual void updateComponentMapCoordinate(unsigned int index,float deltaMapX,float deltaMapY)=0;
};

class CCISODynamicComponent : public CCNode {

public:
	
	CCISODynamicComponent();
    
	~CCISODynamicComponent(void);
	
    virtual bool init();

	bool beforeUpdateContent();
    
	void doUpdateContent();
    
    void doUpdateComponents();

	void calcComponentsCount();
    
	void createComponents();
    
    void initComponents();
    
    void setupComponents(int iComponentNodeExtendCount);
    
	void setupComponents(int iComponentNodeExtendCount,const CCPoint& position);
    
    CCArray* getComponents();

    virtual void initOffset(const CCPoint& tOffset);
    
    virtual void initOffset(float x,float y);
    
    virtual void scroll(const CCPoint& tOffset);
    
    virtual void scroll(float x,float y);
    
    virtual void setComponentTileColumn(int iComponentTileColumn);
    
    virtual int getComponentTileColumn();
    
    virtual void setComponentTileRow(int iComponentTileRow);
    
    virtual int getComponentTileRow();
    
    virtual void setComponentTileExtendCount(int iComponentNodeExtendCount);
    
    virtual int getComponentTileExtendCount();

    virtual void setOffset(const CCPoint& tOffset);
    
	virtual void setOffset(float x,float y);

    virtual CCPoint getOffset();
    
    void setDelegator(CCISODynamicComponentUpdateDelegator* pDelegator);
    
protected:
    
    virtual void updateMapCoordinate(unsigned int nodeIndex,float deltaMapX,float deltaMapY);
    
protected:
    
    int m_iComponentTileColumn;
    int m_iComponentTileRow;
    
    int m_iComponentTileTotalColumn;
    int m_iComponentTileTotalRow;
    //x,y增加相同的格子数
    int m_iComponentNodeExtendCount;
    
	//CCISOComponentNode** m_pComponents;
	CCArray* m_pComponents;
    
    /**
     * 地图的偏移量。屏幕坐标
     * 可能层的原点和地图的原点不在一起。
     */
	CCPoint m_tOffset;
    
    /**
     * 偏移量的地图坐标
     */
	int m_iStartX;
	int m_iStartY;

    
    int m_iLastStartX;
    int m_iLastStartY;
    
    /**
     地图的一个图块大小
     */
    CCSize m_tMapTileSize;
    
    CCSize m_tScreenSize;
    
    int m_iComponentIndexX;
    int m_iComponentIndexY;
    
    CCISODynamicComponentUpdateDelegator* m_pDelegator;
};



NS_CC_END

#endif //ISO_CCISODynamicComponent_H_