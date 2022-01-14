#include <iostream>
#include "Cerberus/Core/testClass.h"
#include "Cerberus/Vector3.h"
int main(int argc, char* argv[])
{
    printf("Hello World from TOOLS! \n");
   

    Vector2 TestA = Vector2(5, 5);

  


    Vector2 TestB = Vector2(5, 5);

    Vector2 TestC = Vector2(5, 5);

    


    printf("Testing lerp: (%f, %f, %f) \n", TestC.x, TestC.y);
    return 0;
}