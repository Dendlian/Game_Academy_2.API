#include "Object.h"

void Object::Init()
{
	BlockDelay = 0;
	RandDelay = 100;

	isFlying = false;
	RandFly = 0;
}

void Object::Update()
{
	
	if (BlockDelay == 0) RandDelay = 50 + rand() % 200;
	if (BlockDelay == 0) RandFly = rand() % 100;

	if (RandFly > 40)
	{
		if (BlockDelay >= RandDelay)
		{
			BlockBox box;
			box.Player_Object.left = WINSIZEX;
			box.Player_Object.right = box.Player_Object.left + 20;
			box.Player_Object.top = WINSIZEY - 120;
			box.Player_Object.bottom = WINSIZEY - 75;
			box.speed = Level * 3 + 2;
			vecBox.push_back(box);
			BlockDelay = 0;
		}
		else BlockDelay++;
	}
	else
	{
		if (BlockDelay >= RandDelay && RandFly <= 40)
		{
			BlockBox box;
			box.Player_Object.left = WINSIZEX;
			box.Player_Object.right = box.Player_Object.left + 50;
			box.Player_Object.top = WINSIZEY - 180;
			box.Player_Object.bottom = WINSIZEY - 170;
			box.speed = Level * 3 + 2;
			vecBox.push_back(box);
			BlockDelay = 0;
		}
		else BlockDelay++;
	}
}

void Object::Render()
{
	for (int i = 0; i < vecBox.size(); i++)
		RECT_DRAW(vecBox[i].Player_Object);
}
