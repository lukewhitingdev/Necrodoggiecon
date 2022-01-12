#include "testClass.h"
#include "Utility/Debug/Debug.h"

TestClass::TestClass()
{
	Debug::Log("init test class!\n");

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
	Debug::Log("destroy test class!\n");
}
