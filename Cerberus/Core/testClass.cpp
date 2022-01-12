#include "testClass.h"

TestClass::TestClass()
{
	printf("init test class!\n");
}

void TestClass::Update(float deltaTime)
{
	//CEntity::Update(deltaTime);

	printf("update test class!\n");
}

TestClass::~TestClass()
{
	printf("destroy test class!\n");
}
