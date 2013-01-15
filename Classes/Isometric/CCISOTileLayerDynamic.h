#ifndef ISO_CCISOTileLayerDynamic_H_
#define ISO_CCISOTileLayerDynamic_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"

NS_CC_BEGIN

class CCISOComponentNode : public CCSprite{

public:
    CCISOComponentNode();
    
	void setColumn(int iColumn)
	{
		m_iColumn = iColumn;
	};

	int getColumn()
	{
		return m_iColumn;
	};

	void setRow(int iRow)
	{
		m_iRow = iRow;
	};

	int getRow()
	{
		return m_iRow;
	};
    
    void setMapCellX(int iMapCellX)
    {
        m_iMapCellX = iMapCellX;
    }
    
    int getMapCellX()
    {
        return m_iMapCellX;
    }
    
    void setMapCellY(int iMapCellY)
    {
        m_iMapCellY = iMapCellY;
    }
    
    int getMapCellY()
    {
        return m_iMapCellY;
    }

private:
	int m_iColumn;
	int m_iRow;
    int m_iMapCellX;
    int m_iMapCellY;
};



class CCISOTileLayerDynamic : public CCISOTileLayer {

public:
	
	CCISOTileLayerDynamic();
	~CCISOTileLayerDynamic(void);
	
    virtual bool init();
	virtual void initOffset(const CCPoint& tOffset);
    virtual void initOffset(float x,float y);

	bool beforeUpdateContent();
	void doUpdateContent();
    void doUpdateComponents();

	void calcComponentsCount();
	void createComponents();
    void initComponents();
    void setupComponents(int iComponentNodeExtendCount);
	void setupComponents(int iComponentNodeExtendCount,const CCPoint& position);
//    virtual void draw();
    
    virtual void setComponentTileColumn(int iComponentTileColumn);
    virtual int getComponentTileColumn();
    
    virtual void setComponentTileRow(int iComponentTileRow);
    virtual int getComponentTileRow();
    
    virtual void setComponentTileExtendCount(int iComponentNodeExtendCount);
    virtual int getComponentTileExtendCount();


    virtual void scroll(const CCPoint& tOffset);
    virtual void scroll(float x,float y);


protected:
    int m_iComponentTileColumn;
    int m_iComponentTileRow;
    
    int m_iComponentTileTotalColumn;
    int m_iComponentTileTotalRow;
    //x,y增加相同的格子数
    int m_iComponentNodeExtendCount;
    
	//CCISOComponentNode** m_pComponents;
	CCArray* m_pComponents;
    
    int m_iLastStartX;
    int m_iLastStartY;
    
    int m_iComponentIndexX;
    int m_iComponentIndexY;
    
};



NS_CC_END

#endif //ISO_CCISOTileLayerDynamic_H_
