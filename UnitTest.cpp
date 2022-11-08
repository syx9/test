#include "pch.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{

    TEST_CLASS(UnitTest1)
    {
    public:
        
        TEST_METHOD(TestMethod1)
        {
            int n = 3;
            int a[3] = { 2,3,-6 },max=0;
            int i, j, t;
            for (i = 0; i < n; i++)
            {
                t = a[i];
                if (t > max)  max = t;
                for (j = i + 1; j < n; j++)
                {
                    t = t + a[j];
                    if (t > max) max = t;
                }
            }
            int right = 5;
            if(max==right) ;
        }
    };
}
