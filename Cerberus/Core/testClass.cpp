#include "testClass.h"

TestClass::TestClass()
{
	printf("init test class!\n");

	mesh = new CMeshComponent();
	components.push_back(mesh);
}

void TestClass::Update(float deltaTime)
{
	//CEntity::Update(deltaTime);

	position.x += deltaTime;

	rotation += sin(deltaTime);

	scale.y += deltaTime * .3;

}

TestClass::~TestClass()
{
	printf("destroy test class!\n");
}
