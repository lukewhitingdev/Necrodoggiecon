#include <iostream>
#include "Cerberus/Core/testClass.h"
#include "Cerberus/Vector3.h"
#include "Cerberus/CWorld.h"
#include "Cerberus/Engine.h"
int main(int argc, char* argv[])
{
    printf("Hello World from TOOLS! \n");
   

    Vector2 TestA = Vector2(5, 5);

  


    Vector2 TestB = Vector2(5, 5);

    Vector2 TestC = Vector2(5, 5);

    std::map<Vector3, float> tileContainer;
    tileContainer[Vector3(1, 1, 0)] = 5;

    tileContainer[Vector3(0, 1, 0)] = 1;

    tileContainer[Vector3(-2, -5, -3)] = 15;

        tileContainer[Vector3(3, 4, 7)] = 8;
        tileContainer[Vector3(2, 5, 1)] = 4;
        
    printf("Testing map: (%f, %f) \n", tileContainer[Vector3(2, 5, 1)], tileContainer[Vector3(-2, -5, -3)]);
    return 0;
}