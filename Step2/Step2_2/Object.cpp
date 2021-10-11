#include "Object.h"

void Object::Init()
{
	ThrowDelay = 40;
	RandOriental = 0;
}

void Object::Update()
{
	if (ThrowDelay >= 40)
	{
		RandOriental = rand() % 200 + 1;
		RandMove = rand() % 100;
	}
	if (ThrowDelay >= 40)
	{
		ThrowBox box;
		switch (RandOriental % 4)
		{
		case 0:
			box.initspace = TOP;
			box.rt.left = rand() % (WINSIZEX - 20);
			box.rt.right = box.rt.left + 20;
			box.rt.top = -20;
			box.rt.bottom = 0;
			box.speed = Level;
			break;
		case 1:
			box.initspace = BOTTOM;
			box.rt.left = rand() % (WINSIZEX - 20);
			box.rt.right = box.rt.left + 20;
			box.rt.top = WINSIZEY;
			box.rt.bottom = WINSIZEY + 20;
			box.speed = Level;
			break;
		case 2:
			box.initspace = LEFT;
			box.rt.left = -20;
			box.rt.right = 0;
			box.rt.top = rand() % (WINSIZEY - 20);
			box.rt.bottom = box.rt.top + 20;
			box.speed = Level;
			break;
		case 3:
			box.initspace = RIGHT;
			box.rt.left = WINSIZEX;
			box.rt.right = WINSIZEX + 20;
			box.rt.top = rand() % (WINSIZEY - 20);
			box.rt.bottom = box.rt.top + 20;
			box.speed = Level;
			break;
		}
		if (RandMove % 2 == 0)
			box.v_speed = Level * ((rand() % 30) / 10);
		else box.v_speed = -(Level * ((rand() % 30) / 10));
		vecBox.push_back(box);
		ThrowDelay = 0;
	}
	else ThrowDelay += Level;
}

void Object::Render()
{
	// 추가한 요소의 박스들을 그리기
	for (int i = 0; i < vecBox.size(); i++)
		RECT_DRAW(vecBox[i].rt);
}
