#include <complex>
#include <cmath>
#include <iostream>
#include <stdio.h>

int inversion_modulo(int x, int y)
{
    // if (x > y)
    // {
    //     return inversion_modulo(y,x);
    // }
    int y_orig = y;
    int q;
    int r =-999;
    int s_old = 0;
    int s_new = 1;
    int temp = 0;
    int ans;
    while(r != 0)
    {
        // printf("asdf\n");
        s_old = temp;
        q = (int) (y / x);
        r = y - q*x;
        y = x;
        x = r;
        temp = s_new;
        s_new = s_old - q*s_new;
        // printf("q:%d r:%d s_old:%d temp:%d s_new:%d \n",q,r, s_old, temp,s_new);
    }
    if (temp < 0)
    {
        temp += y_orig;
    }
    return temp;
}
float f(int l, int y)
{
    float sum = 0;
    int temp;
    int temp2;
    float temp3;
    int five_const; 
    five_const = inversion_modulo(5,std::pow(2,l));
    temp2 = five_const;
    for (int j = 0; j < l; j++)
    {
        // printf("j = %d\n",j);
        // printf("temp2: %d\n",temp2);
        temp2 %= (int)std::pow(2,l);
        temp = (int)std::pow(2,j)*y*temp2;
        // printf("temp = %d\n", temp);
        temp3 = std::real(std::exp((std::complex <float>) (2*3.14159265358979323*1i*std::pow(2,-l)*temp)))/l;
        sum += temp3;
        temp2 *= five_const;
        //exp and cos do different values, but sin does 0 wtf??
        // printf("f(%d,%d): Term %d=%f\n",l,y,j,temp3);
    }
    // printf("f(%d,%d)=%f\n",l,y,sum);
    return sum;
    //5^-1 mod 8 =5s
}
int main(int argc, char const *argv[])
{
    int count = 40;
    for (int l = 1; l < count; ++l)
    {
        printf("l: %d\n", l);
        float large = -2; // magic, fix
        for (int j = 1; j <= std::pow(2,l)-1; j+=2)
        {
            large = std::max(large, f(l,j));
            // printf("y:%d = %f\n",j, f(l,j));
        }
        printf("large: %f\n", large);
    }
    // for(int i = 2; i < 10; ++i)
    // {
    //     printf("%d inverted mod %f is: %d\n",5,std::pow(2,i),inversion_modulo(5,std::pow(2,i)));
    // }
    // printf("he\n");
    // printf("%d inverted mod %d is: %d\n",89,232,inversion_modulo(89,232));
    return 0;
}
