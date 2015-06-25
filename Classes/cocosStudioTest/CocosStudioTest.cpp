#include "CocosStudioTest.h"

USING_NS_CC;
using namespace cocostudio;


Scene* CocosStudioTest::createScene()
{
	auto scene = Scene::create();
	auto layer = CocosStudioTest::create();

	scene->addChild(layer);

	return scene;

}


bool CocosStudioTest::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();
	
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
		"cocosStudioTest_img/effectAttackFire0.png"
		, "cocosStudioTest_img/effectAttackFire0.plist"
		, "cocosStudioTest_img/effectAttackFire.ExportJson"
		);

	armature = Armature::create("effectAttackFire");
	armature->setPosition(size.width / 2, size.height / 2);
	armature->getAnimation()->playByIndex(0);
	armature->setScale(2.0f);

	this->addChild(armature);

	MenuItemImage* back = MenuItemImage::create("parkour_img/back_btn.png", "parkour_img/back_btn1.png", CC_CALLBACK_1(CocosStudioTest::rebootCallback, this));
	back->setPosition(Vec2(size.width - 40, size.height - 40));

	Menu* menu = Menu::create(back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void CocosStudioTest::rebootCallback(Ref *pSEnder){
	Director::getInstance()->replaceScene(ListViewGameScene::createScene());
}