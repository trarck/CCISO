#include "CCMessageManager.h"
#include "GameMessages.h"
#include "Unit.h"

NS_CC_BEGIN

//guid通常由服务端生成建议从1000000开始，有时候客户端也需要一些临时的对象，guid由客户端生成从0-10000000

Unit::Unit()


{
    CCLOG("Unit create");
}

Unit::~Unit()
{
    CCLOG("Unit destroy");
}

NS_CC_END
