#include "Object.h"

void Object::Init()
{
	ThrowDelay = 50;
}

void Object::Update()
{
	if (ThrowDelay >= 50)
	{
		ThrowBox box;

		box.rt.left = rand() % (WINSIZEX - 30);		// 0 ~ 610
		box.rt.right = box.rt.left + 30;			// 30 ~ 640
		box.rt.top = -30;
		box.rt.bottom = 0;

		box.speed = Level;

		// ������ �ڽ� ��� �߰�
		vecBox.push_back(box);
		ThrowDelay = 0;
	}
	else ThrowDelay += Level;
}

void Object::Render()
{
	// �߰��� ����� �ڽ����� �׸���
	for (int i = 0; i < vecBox.size(); i++)
		RECT_DRAW(vecBox[i].rt);
}
