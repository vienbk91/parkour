#include "cocos2d.h"


USING_NS_CC;

struct UIDialogButton {
private:
    std::string _name;
    cocos2d::ccMenuCallback &_action;
    int _tag;

public:

    UIDialogButton(std::string name, cocos2d::ccMenuCallback &action,int tag=1)
        : _name(name), _action(action), _tag(tag) {}

    std::string name() const { return _name; }
    cocos2d::ccMenuCallback action() const { return _action; }
    int tag() const { return _tag; }
};

class UIDialog : public Layer
{
protected:
    Layer* _uiLayer;

public:
    static UIDialog* create(std::string title,
                            std::string content,
                            std::vector<UIDialogButton*> buttons);
    virtual bool init();
    virtual void view(std::string title,
                     std::string content,
                     std::vector<UIDialogButton*> buttons);
    void close();
};