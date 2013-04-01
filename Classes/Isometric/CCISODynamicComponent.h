#ifndef ISO_CCISODynamicComponent_H_
#define ISO_CCISODynamicComponent_H_

#include "cocos2d.h"
#include "CCISOComponentNode.h"

#define ComponentExtendCount 2

NS_CC_BEGIN

class CCISOTileLayer;

class CCISODynamicComponentUpdateDelegator
{
public:
    virtual void updateComponentMapCoordinate(unsigned int index,float deltaMapX,float deltaMapY)=0;
};

class CCISODynamicComponentCreateDelegator
{
public:
    virtual CCSprite* createTile()=0;
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
    
    void setupComponents();
    
    void setupComponents(const CCPoint& position);
    
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
    
    void setUpdateDelegator(CCISODynamicComponentUpdateDelegator* pUpdateDelegator);
    
    void setCreateDelegator(CCISODynamicComponentCreateDelegator* pCreateDelegator);

    //weak ref
    virtual void setTileLayer(CCISOTileLayer* pTileLayer);
    
    virtual CCISOTileLayer* getTileLayer();
    
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
        
    int m_iComponentIndexX;
    int m_iComponentIndexY;
    
    CCISOTileLayer* m_pTileLayer;
    
    CCISODynamicComponentUpdateDelegator* m_pUpdateDelegator;
    CCISODynamicComponentCreateDelegator* m_pCreateDelegator;
    
    
};



NS_CC_END

#endif //ISO_CCISODynamicComponent_H_
