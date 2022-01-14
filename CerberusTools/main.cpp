#include <iostream>
#include "Cerberus/Core/testClass.h"
#include "Cerberus/Vector3.h"
int main(int argc, char* argv[])
{
    printf("Hello World from TOOLS! \n");
   

    Vector3 TestA = Vector3(5, 5, 5);

  


    Vector3 TestB = Vector3(10, 10, 10);

    Vector3 TestC = Vector3(0.25, 0.25, 0.25);

    TestC = TestC.Lerp(TestA, TestB, 0.5);


    printf("Testing lerp: (%f, %f, %f) \n", TestC.x, TestC.y, TestC.z);
    return 0;
}