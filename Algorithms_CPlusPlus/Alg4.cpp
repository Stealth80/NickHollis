/* 
 * File:   main.cpp
 * Author: Nick Hollis
 *
 * Created on October 7, 2012, 9:20 PM
 */
#include <cstdlib>  //for rand function
#include <cmath>    //floor and pow functions
#include "math.h"
#include <iostream>
#include <vector>  
#include <ctime>   //to seed rand function

using namespace std;

void generate_binary_number(vector<int> &, int);     //generates binary numbers
void chunk_binary_number(vector<int>, vector<int> &);
long long convert_binary_to_decimal(vector<int>); 
void convert_to_binary(int, vector<int> & );
void binary_add(vector<int>, vector<int>, vector<int> &);
long long multiply(vector<int> &, vector<int> &);
void rem_to_bin(long long, vector<int> &); //for multiply function
void binary_subtract(vector<long> &, vector<long> &, vector<long> &);
void binary_divide(vector<long> &, vector<long> &, int &, int &);
void binary_mod(vector<long> &, vector<long> &, int &, int &);
long long modexp(vector<int>, vector<int>, vector<int>, vector<int> &);   //function for modular exoponentiation
bool primality(vector<int>);  //test for primality

int main(int argc, char** argv) 
{
    srand( time(0) );  //seed rand
    int num_of_primes;
    cout << "How many primes do you want?  ";        //prompt user for number of primes to find
    cin >> num_of_primes;
        
    int n;
    cout << "Enter size in bits of binary numbers. ";   //prompt user for size of n bit numbers to generate
    cin >> n;
    while(n<3)
    {
        cout << endl;
        cout << "Number of bits must be larger than 2."  << endl;
        cout << "Enter size in bits of binary numbers. ";   //reprompt user for size of n bit numbers to generate if not larger than 2
        cin >> n;
    }
    
    int count = 0;  //to count number 'til prime is found
    int prime_numbers; // to track how many primes have been found
    long long is_prime;  //for testing primality
    long long x;
    long long y;
    long long mod_N;
    vector<int> binary_x(n);   //vectors to hold binary numbers
    vector<int> binary_y(n);
    vector<int> binary_N(n); 
    vector<int> X(n);			//vectors to hold "chunked" numbers
	vector<int> Y(n);
    vector<int> N(n); 
    vector<int> z;
    while(prime_numbers < num_of_primes) //loop to find random numbers until we find the requested number of primes
    {
                                   //generate 3 random numbers
        generate_binary_number(binary_x, n);                   
        generate_binary_number(binary_y, n);
        generate_binary_number(binary_N, n);
        
		chunk_binary_number(binary_x, X);
		chunk_binary_number(binary_y, Y);
		chunk_binary_number(binary_N, N);

        is_prime = modexp(X, Y, N, z);   //function for modular exponentiation
        count++;
         
        bool prime;
        prime = primality(N);                     //test for primality
        if(prime)
        {
            x = convert_binary_to_decimal(X);           //if N is a prime, will print it.
            y = convert_binary_to_decimal(Y);
            mod_N = convert_binary_to_decimal(N);
            long long Z = convert_binary_to_decimal(z);
            cout << "Prime found:  x = " << x
            << "   y = " << y << "   N = " 
                    << mod_N << "   and returned value = " << Z << endl << endl << endl;
            prime_numbers++;
        }
    }
    return 0;
}

long long modexp(vector<int> X, vector<int> Y, vector<int> N, vector<int> & z)  //function for modular exponentiation
{
    z.push_back(1);                          //set z = 1;
   
    long long mod_N = convert_binary_to_decimal(N);
    long long m;
    long long result;
    bool y_is_zero = true;
    long long Z;
    for (int i = 0; i < Y.size(); i++)
    {
        if(Y[i] != 0)
        {                                           //if y = 0
            y_is_zero = false;
        }
    }
    if(y_is_zero)                                      
    {
        z[0] = 1;                          //return  z = 1;
        for(int i = 1; i<z.size(); i++)
        {
            z[i] = 0;
        }
    }
    
    ;                                 //floor (y/2)
    
    Z = modexp(X, Y, N, z);    //recursively call modular exponentiation
    
    if (Y[0] % 2 == 0)                       //if y is even
    {
        m = multiply(z, z);
        result = m % mod_N;                          //return z^2 mod N
        convert_to_binary(result, z);
    }
    else
    {                                   //else (y is odd) return x*z^2 mod N
        m = multiply(z, z);
        vector<int> temp;
        convert_to_binary(m, temp);
        m = multiply(X, temp);
        result = m % mod_N;
        convert_to_binary(result, z);   
        cout << endl << result << endl;
    }
    return result;
}

void generate_binary_number(vector<int> & binary_num, int numsize)
{
    
    int binary;
    int countdown = numsize-1;
    while(countdown >=1)
    {
        binary = rand() % 2;
        binary_num[countdown] = binary;
        countdown--;
    }
    binary_num[0] = 1;
}

void chunk_binary_number(vector<int> binary, vector<int> & result)
{
	int R;
	R = binary[1]+2;
	for(int i = 2; i<binary.size(); i++);
	{
		R = R*2;
		if(binary[i] == 1)
		{
			R = R + 1;
		}
	}
	
	while(R>9)
	{
		result.push_back(R % 10);
		R = R/10;
	}
	result.push_back(R);
}

long long convert_binary_to_decimal(vector<int> binary)
{
    int s = binary.size();
    long long num = 0 + binary[s-1];
    int pwr = 1;
    for (int i = s-2; i>=0; i--)
    {
        pwr = pwr*2;
        num = num + (binary[i] * pwr);
    }
    return num;
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

bool primality(vector<int> N)
{
	
    //if(modexp(2, prime-1, prime)==1)
		//return true;
	//else
		//return false;
}

void binary_add(vector<int> b1, vector<int> b2, vector<int> & result)
{                               //add 2 binary numbers
    int r = 0; //for the carry
    int t = b1.size();
    int add = 0;
    vector<int>::iterator iter;
    
    for(int j=0; j<t; j++)   //loop with nested if statements to perform binary addition
    {    
        add = b1[j] + b2[j] + r;
        if(add == 3)                    //1+1+1 = 1  carry 1
        {                          
            result[j] = 1;      
            r = 1;
        }
            
        else if (add == 2)             //1+0+1 = 0  carry 1 or
        {                              //0+1+1 = 0  carry 1 or    
            result[j] = 0;             //1+1+0 = 0  carry 1 
            r = 1;
        }
        
        else if (add == 1)   
        {                               //1+0+0 = 1  carry 0 or
            result[j] = 1;              //0+1+0 = 1  carry 0 or
            r = 0;                      //0+0+1 = 1  carry 0
        }
        
        else if (add == 0)
        {
            result[j] = 0;              //0+0 = 0  carry 0
            r = 0;
        }
        else 
            cout << "error in remainder:  r cannot be more than 1" << endl;
        
        
    }
    if(r == 1)
    {
        iter = result.begin();
        result.insert(iter, r);
//        result.push_back(r);
    }
    return;
}


        /*disclaimer:  since my multiply did not work in program 2; this mulitply is borrowed, with permission, from Abigail Coleman  
         * it has been altered to tailor to this program and match my code.
         */
long long multiply(vector<int> & num1, vector<int> & num2)
{
vector<int> answer;    
long long x = convert_binary_to_decimal(num1);
long long y = convert_binary_to_decimal(num2);
long long divider = y; //consider divider to be y'
long long dividen = x; //consider dividen to be x'
long long r = 0; //r is the addition of the x' when y is odd
int carry = 0; //used for the binary addition
long long result = 0;//decimal result of the multiplication
if(y == 0 || x == 0)
{
return 0;
}
while(divider != 1)
{
if(divider % 2 == 0)
{
num1.insert(num1.begin(), 0); //multiplies x by 2, when multiplying binary number by 2 you can 
  //add a zero to the end by the least significant bit
num2.erase(num2.begin());//divides y by 2, when dividing a binary number by 2 you can take away 
  //the least segnificant bit

}
else
{
num1.insert(num1.begin(), 0); //multiplies x by 2, when multiplying binary number by 2 you can 
  //add a zero to the end by the least significant bit
num2.erase(num2.begin());//divides y by 2, when dividing a binary number by 2 you can take away 
  //the least segnificant bit
r = r + dividen; // y is odd thus x' needs to be added to the result
}
divider = divider / 2; //y' is divided by two
dividen = dividen * 2; //x' is multiplied by two
}

rem_to_bin(r, num1);//converts the r to binary so its binary can be added to the x' binary number

for(int i = 0; i < num1.size(); i++)
{
if(num1.size() < num1.size())
num1.resize(num1.size());
else if(num1.size() < num1.size())
num1.resize(num1.size());
/*above makes sure that the r vector and the x vector are the same size to prevent trying to add
a number from a vector that doesnt exist, which returns a run time error in the program*/

if(num1[i]+num1[i]+carry == 3)
{
answer.push_back(1);
carry = 1;
}
else if(num1[i]+num1[i]+carry == 2)
{
answer.push_back(0);
carry = 1;
}
else
{
answer.push_back(num1[i]+num1[i]+carry);
carry = 0;
} 
}
if(carry == 1)
answer.push_back(1);

for(double i = 0; i < answer.size(); i++)//loops through the binary answer vector and turns it into a decimal number
{
if(answer[i] == 1)
result = result + pow(2,i);
}

return result;
}

void rem_to_bin(long long r, vector<int> & num1)
{
long long dividen = r;

    while(dividen != 0)
    {
        num1.push_back(dividen % 2);
        dividen = dividen / 2;
    }

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
	return;    
}

void binary_mod(vector<long> & x, vector<long> & y, int & q, int & r)        //function to compute and output x%y
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
	return;    
}