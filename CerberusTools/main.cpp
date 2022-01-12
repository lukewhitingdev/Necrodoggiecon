#include <iostream>
#include "Cerberus/Core/testClass.h"
#include "Cerberus/Vector3.h"
int main(int argc, char* argv[])
{
    printf("Hello World from TOOLS! \n");
   

    Vector3 TestA = Vector3(0.25, 0.25, 0.25);

    Vector3 TestB = Vector3(-0.2, -0.1, -0.75);

   float MagTest = TestA.Determinant(TestB);


    printf("Determinant: %f \n", MagTest);
    return 0;
}