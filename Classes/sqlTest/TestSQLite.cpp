#include "sqlTest\TestSQLite.h"

#define dbName "userVien"

using namespace std;
USING_NS_CC;

using namespace cocos2d;
Scene* TestSQLite::createScene()
{
	auto scene = Scene::create();
    auto layer = TestSQLite::create();
    scene->addChild(layer);

	return scene;
}

bool TestSQLite::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

	sqlite3 *pdb=NULL;

	std::string path = FileUtils::sharedFileUtils()->getWritablePath();
	path += dbName;
	
	std::string sql;
	int result;
	result=sqlite3_open(path.c_str(),&pdb);
	
	if(result!=SQLITE_OK){
		cocos2d::log("open database failed, number%d",result);
	}

	result=sqlite3_exec(pdb,"create table student(ID integer primary key autoincrement,name text,sex text)",NULL,NULL,NULL);
		
	if(result!=SQLITE_OK){
		cocos2d::log("create table failed");
	}

	sql="insert into student values(1,'zhycheng','male')";
	result=sqlite3_exec(pdb,sql.c_str(),NULL,NULL,NULL);
	if(result!=SQLITE_OK){
		cocos2d::log("insert data failed!");
	}

	sql="insert into student values(2,'liuyali','female')";
	result=sqlite3_exec(pdb,sql.c_str(),NULL,NULL,NULL);
	if(result!=SQLITE_OK){
		cocos2d::log("insert data failed!");
	}
		
	sql="insert into student values(3,'zhy_cheng','male')";
	result=sqlite3_exec(pdb,sql.c_str(),NULL,NULL,NULL);
	if(result!=SQLITE_OK){
		cocos2d::log("insert data failed!");
	}

	char **re;
	int r,c;
	sqlite3_get_table(pdb,"select * from student",&re,&r,&c,NULL);
	cocos2d::log("row is %d,column is %d",r,c);
		
	LabelTTF *liu=LabelTTF::create(re[2*c+1],"Arial",24);
	liu->setPosition(ccp(200,200));
	addChild(liu,1);
	sqlite3_free_table(re);
	sqlite3_close(pdb);

	return true;
}
void TestSQLite::menuCloseCallback(Ref* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}
