#ifndef __MONEY_H__
#define __MONEY_H__

#include "Definitions.h"
#include "cocos2d.h"

USING_NS_CC;

class MoneyGenerator {
	public:
	static MoneyGenerator * _instance;
	static MoneyGenerator * getInstance();

	Vector<Node*> GenerateMoney();
	void removeMoney();
	void obtainMoney(Node* mon);
	~MoneyGenerator();

	private:
	MoneyGenerator();
	void generMoney(float x, float y);

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	Vector<Node*> Money;
};

#endif // __MONEY_H__
