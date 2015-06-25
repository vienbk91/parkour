#ifndef BOWMANSTORYSCENE_H_
#define BOWMANSTORYSCENE_H_

#include "cocos2d.h"
#include "BowManSelectMap.h"
#include "SqlUtils.h"

/*
Ghi chu: Neu ten class nam trong cung 1 thu muc thi ko can goi ten thu muc ra
*/

USING_NS_CC;

class BowManStoryScene : public cocos2d::Layer

{
public:
	BowManStoryScene();
	~BowManStoryScene();

	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(BowManStoryScene);


	Label* storyLabel1;
	Label* storyLabel2;
	Label* storyLabel3;
	Label* storyLabel4;
	Label* storyLabel5;

	int sotoryIndex;


	void story1();
	void story2();
	void story3();
	void story4();
	void story5();

	void skipCallback(Ref*);
	void closeStory();

	string getNameUser();

	/*
	void update1(float dt);
	void update2(float dt);
	void update3(float dt);
	void update4(float dt);
	*/

protected:

	// Tag background
	enum Tag_Background
	{
		Tbg_Story1 = 1 ,
		Tbg_Story2 = 2 ,
		Tbg_Story3 = 3 ,
		Tbg_Story4 = 4 ,
		Tbg_Story5 = 5
	};

	// Tag label

	enum Tag_Label
	{
		Tlb_Story1 = 1 ,
		Tlb_Story2 = 2 ,
		Tlb_Story3 = 3 ,
		Tlb_Story4 = 4 ,
		Tlb_Story5 = 5
	};

	enum Tag_Skip
	{
		T_SkipStory1 = 1 ,
		T_SkipStory2 = 2 ,
		T_SkipStory3 = 3 ,
		T_SkipStory4 = 4 ,
		T_SkipStory5 = 5
	};

	enum Tag_Action
	{
		T_actionStory1 = 1 ,
		T_actionStory2 = 2 ,
		T_actionStory3 = 3 ,
		T_actionStory4 = 4 ,
		T_actionStory5 = 5
	};


private:

};

#endif //BOWMANSTORYSCENE_H_