/* 
 * File:   binary multiply.cpp
 * Author: Nick Hollis
 *
 * Created on October 8, 2012, 9:31 PM
 */
#include <iostream> 
#include <vector>
#include <cmath> //for pow function
#include <time.h>

using namespace std;

long long multiply(long long x, long long y);
int convert_binary_to_decimal(vector<long> &);
void convert_to_binary(int, vector<long> & );

int main(int argc, char** argv) 
{
    X = rand() % 1000;
    Y = rand() % 1000;
    
    
    cout << X << " times " << Y << " is: " << multiply(X,Y,R,result) << endl;

    return 0;
}

void multiply(vector<int> X, vector<int> Y, vector<int> & R, vector<int> & result)
{

    long long x = convert_binary_to_decimal(X);
    long long y = convert_binary_to_decimal(Y);; 
    long long r = 0; 
    int c = 0; //c for carry
    long long result = 0;//decimal result of the multiplication
    if(x == 0 || y == 0)
    {
        return 0;
    }
    while(y != 1)
    {
        if(y % 2 == 0)  //if y is even
        {
            X.push_back(0); //multiplies x by 2 by 2 adding a zero to the end after the least significant bit
            Y.pop_back();//divides y by 2 by removing the least segnificant bit
        }
        else
        {
            X.push_back(0); //multiplies x by 2 by adding a zero to the end after the least significant bit
            Y.pop_back();//divides y by 2 by removing the least segnificant bit
            r = r + x; // y is odd thus x needs to be added to the result
        }
        y = y / 2; //y is divided by two
        x = x * 2; //x is multiplied by two
    }

    convert_to_binary(r, R); //convert r to binary

    for(int i = 0; i < X.size(); i++)
    {
    if(R.size() < X.size())             //resize R if X > R
    {
        int n = X.size();
        vector<int>::iterator p;
        for (int j=0; j<n; j++)      
        {
            p = R.begin();
            R.insert(p, 0);
        }
    else if(X.size() < R.size())         //resize X if R > X
    {
        int s = R.size();
        vector<int>::iterator p;
        for (int k=0; k<n; k++)      
        {
            s = X.begin();
            X.insert(s, 0);
        }
    }
    
    if(X[i]+R[i]+carry == 3)
    {
    result.push_back(1);
    c = 1;
    }
    else if(X[i]+R+carry == 2)
    {
    result.push_back(0);
    c = 1;
    }
    else
    {
    result.push_back(X[i]+R[i]+carry);
    c = 0;
    } 
    }
    if(c == 1)
    {
        result.push_back(1);
    }
    return;
}
    
void convert_to_binary(int random, vector<int> & binary)
{                                       //converts given decimal to binary
    int r;  //r for remainder
    vector<int> temp;
    if(random <=1)
    {
        binary.push_back(random);
        return;
    }
    r = random % 2;
    convert_to_binary(random >> 1, binary);
    binary.push_back(r);                //stores binary in a vector
    
    return;
}

