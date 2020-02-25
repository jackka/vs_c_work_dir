//Task 2.2.2
#include <stdio.h>

int main()
{
   double x;
   double a;
   double b = 0;
   int n; // значение максимальной степени

   printf("Vvedite n=");
   scanf("%d",&n);

   printf("Vvedite x=");
   scanf("%lf",&x);

   printf("Vvedite a=");
   for(int i=n;i>=0;i--){ // последовательно уменьшаем степень сверху вниз
     scanf("%lf",&a);
     b=a*i+x*b;
   }
   b=b/x;

   printf("Iskomoe zhachenie = %f",b);

    return 0;
}

//dx^3 + ax^2 + bx+c = c + x(b + x(a + x(d + 0)))
//3dx^2 + 2ax^1 + b = b + x(2a + x(3d + 0)))




