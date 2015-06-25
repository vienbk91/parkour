#ifndef __TESTSQLITE_H__
#define __TESTSQLITE_H__

#include "cocos2d.h"
#include "sqlite/sqlite3.h"

USING_NS_CC;



class TestSQLite : public cocos2d::Layer
{
public:

	
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TestSQLite);

	void menuCloseCallback(Ref* pSender);
};




#endif // __TESTSQLITE_H__