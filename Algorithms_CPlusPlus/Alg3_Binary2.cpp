/* 
 * File:   HW3.cpp
 * Author: Nick Hollis
 * Shown here, an alternative way to do binary division ("it-divide" I believe) using a loop instead of recursion that seems to work.
 * Created on September 12, 2012, 1:31 PM
 */

#include <iostream>
#include <vector>


using namespace std;
vector<long> x;
vector<long> y;
vector<long> subtract_result;
int r =0;    //for remainder
int q = 0;    //for quotient

void convert_to_binary(int, vector<long> & );
void binary_subtract(vector<long> &, vector<long> &, vector<long> &);
void binary_divide(vector<long> &, vector<long> &, int &, int &);
int convert_binary_to_decimal(vector<long> &);

int main(int argc, char** argv) 
{
    int num1;                                   //receive numbers from user
    cout << "Enter first number: ";                                                     //prompt user for input
    cin >> num1;
    convert_to_binary(num1, x);
    
    int num2;
    cout << "Enter second number to subtract / divide by: ";
    cin >> num2;                    //second number must be smaller than the first
    while(num2 > num1)
    {
        cout << "Error:  second number must be smaller than the first." << endl;
        cout << "Enter a value smaller than the first to subtract / divide by: ";
        cin >> num2;
    }
    convert_to_binary(num2, y);                                                         //convert input to binary
    
    vector<long>::iterator yit;
    while(x.size() > y.size())         //resize y to match size of x if needed
    {
        yit = y.begin();
        y.insert(yit, 0);
    }   
    
    binary_subtract(x, y, subtract_result);                                             //call function for subtract
    cout << "x = ";
    for (int l =0; l<x.size(); l++)
    {
        cout << x[l];
    }
    cout << endl;
    
    cout << "y = ";
    for (int m = 0; m<y.size(); m++)
    {
        cout << y[m];
    }
    cout << endl << endl;
    cout << "x minus y = ";
    for(int s=0; s< subtract_result.size(); s++)                          
    {
        cout << subtract_result[s];                                                   //output subtract result to user
    }
    
    binary_divide(x, y, q, r);
    cout << endl << endl << "x / y = ";
    cout << q << " with remainder:  " << r << endl << endl;
    return 0;
}

void convert_to_binary(int num, vector<long> & binary)
{                                       //converts given decimal to binary
    int remainder;  //r for remainder
    if(num <=1)
    {
        binary.push_back(num);
        return;
    }
    remainder = num % 2;
    convert_to_binary(num >> 1, binary);
    binary.push_back(remainder);                //stores binary in a vector
    return;
}

void binary_subtract(vector<long> & x, vector<long> & y, vector<long> & subtract_result)        //function to subtract y from x
{
    
    if (x.size() > subtract_result.size())  //resize result vector to match x for subtraction
    {
        subtract_result.resize(x.size());
    }
    
    vector<long> x1(x.size());
    for (int j = 0; j<x1.size(); j++)  //copy x into x1 vector for the subtract
    {
        x1[j] = x[j];
    }
    
    int borrow = 0;
    for (int c = x1.size()-1; c>=0; c--)
    {
        if(x1[c] == 1 && y[c] == 1)             //1 - 1 = 0
        {
            subtract_result[c] = 0;
        }
        else if (x1[c] == 0 && y[c] == 0)       //0 - 0 = 0
        {
            subtract_result[c] = 0;

        }
        else if (x1[c] == 1 && y[c] == 0)       //1 - 0 = 1
        {
            subtract_result[c] = 1;
        }
        else if (x1[c] == 0 && y[c] == 1)       //0 - 1 must borrow
        {
            borrow = 1;
            while(x1[c-borrow] == 0)
            {
                borrow++;
            }
            x1[c-borrow] = 0;                   //borrow
            borrow--;
            while (borrow > 0)
            {
                x1[c-borrow] = 1;
                borrow--;
            }
            subtract_result[c] = 1;             //0-1 = 1 after borrowing
        }
        else 
        {
            cout << "Error in subtraction" << endl;
            return;
        }
    }
    return;
}

void binary_divide(vector<long> & x, vector<long> & y, int & q, int & r)        //function to compute and output x/y
{    
    int y1 = convert_binary_to_decimal(y);
    int number;
    int x2 = convert_binary_to_decimal(x);
    
    for(int i=0; i<x.size(); i++)
    {
        if(x[i] == 1)                   //if x is odd
        {
                r=r++;                  //r = r+1
        }
        if(r >= y1)                     //if r>=y1
        {
                r = r-y1;               //r = r - y
                q = q + 1;              //q = q + 1
        }

        number = q*y1 + r;
        if(number != x2)                
        {
                q = 2*q;                //q = 2q
                r = 2*r;                //r = 2r
        }
    }
//    bool zero = true;
//    
//    for(int i=x.size()-1; i>=0; i--)
//    {
//        if (x[i] != 0)                 //check x to see if it is zero
//        {
//            zero = false;
//            if(x.size() == 1)
//                zero = true;
//        }
//    }
//    
//    if(zero)                          //if x is zero  (base case)
//    {
//        r = 0;                        //r = 0
//        q = 0;                        //q = 0
//        return;
//    }
//    x.pop_back();    
//    binary_divide(x, y, q, r);          //divide(floor(x/2), y)
//    q = 2*q;     
//    r = 2*r;                         //r = 2r 
//    
//   if (x[0] == 1)                    // if x is odd
//    {
//        r = r + 1;                       // r = r + 1
//    }
//    
//    int y1 = convert_binary_to_decimal(y);
//    if (r >= y1)                       //if r >= y
//    {
//        r = r - y1;       //r = r - y
//        q = q + 1;        //q = q + 1
//    }
return;    
}
int convert_binary_to_decimal(vector<long> & binary)
{
    int s = binary.size();
    int num = 0 + binary[s-1];
    int pwr = 1;
    for (int i = s-2; i>=0; i--)
    {
        pwr = pwr*2;
        num = num + (binary[i] * pwr);
    }
    return num;
}