#ifndef ISO_CCISOTileLayerDynamic_H_
#define ISO_CCISOTileLayerDynamic_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"

NS_CC_BEGIN

class CCISOComponentNode : public CCSprite{

public:
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

private:
	int m_iColumn;
	int m_iRow;
};

class CCISOTileLayerDynamic : public CCISOTileLayer {

public:
	
	CCISOTileLayerDynamic();
	~CCISOTileLayerDynamic(void);
	
    virtual bool init();

	virtual void setPosition(const CCPoint& newPosition);

//	bool beforeUpdateContent();
//	void doUpdateContent();

	void calcComponentsCount();
	void createComponents();
	
    virtual void draw();
    
    virtual void setComponentTileColumn(int iComponentTileColumn);
    virtual int getComponentTileColumn();
    
    virtual void setComponentTileRow(int iComponentTileRow);
    virtual int getComponentTileRow();
    
    virtual void setComponentTileExtendCount(int iComponentTileExtendCount);
    virtual int getComponentTileExtendCount();


protected:
    int m_iComponentTileColumn;
    int m_iComponentTileRow;
    //x,y增加相同的格子数
    int m_iComponentTileExtendCount;
    
	//CCISOComponentNode** m_pComponents;
	CCArray* m_pComponents;
};



NS_CC_END

#endif //ISO_CCISOTileLayerDynamic_H_
