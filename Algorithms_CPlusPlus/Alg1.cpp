/* 
 * File:   main.cpp
 * Author: Nick Hollis
 */

#include <cstdlib>
#include <iostream>
#include <vector>


using namespace std;
//int fib_count = 0;    //for testing
                       
double Gfib2(vector<vector<int> > &, vector<long> &, int);  //calculates G
void Gfib2_binary_add(vector<vector<int> >&, int);        //add binary numbers
double convert_to_decimal(vector<vector<int> >&,  int);  //converts a binary number to decimal

int main()
{  
   cout << "Enter n: ";   //prompt for nth number to compute
   int n;
   cin >> n;
   while (n < 0)
   {                            //present error if someone enters zero or neg #
       cout << "n must be positive." << endl << endl;
       cout << "Enter n: ";
       cin >> n;
   }
       
   vector<vector<int> > b(n, vector<int>(0) );  //create 2-dimensional vector to hold nth number and it's binary component
   vector<long> decimal(2);
   decimal[0] = 0;
   decimal[1] = 1;
   b[0].push_back(0);  //set b[0] equal to 0
   b[1].push_back(1);  //set b[1] equal to 1
             
   double G = Gfib2(b, decimal, n);  //call function to calculate G(n)
   cout << "Gfib(" << n << ") = " << G << endl;   //output G(n) to user
   return 0;
}

double Gfib2(vector<vector<int> > & b, vector<long> & decimal, int n)
{  
   double result; 
   if (n == 0)
   {
	   result = 0;
	   return result;
   }
   if (n == 1)
   {
       result = 1;
       return result;
   }
   for (int i = 2; i<n; i++)
   {                                            //loop to calculate G(n)
       Gfib2_binary_add(b, i);       //adds (n-1)+ 3*(n-2) binary numbers
       result = convert_to_decimal(b, i);   //convert G(n) from binary to decimal and store it.
       decimal.push_back(result);
   }
   
   return result;  //return result
}

void Gfib2_binary_add(vector<vector<int> >& b, int i)
{                               //add n-2 + n-2 + n-2 = 3*(n-2) + n-1 in binary numbers
    int r = 0; //for the carry
    int t = b[i-1].size();
    int add = 0;
    if(b[i-1].size() > b[i-2].size())
                b[i-2].resize(b[i-1].size());    //resize binary numbers to match current result size
    b[i].resize(b[i-1].size());
    for(int j=0; j<t; j++)   //loop with nested if statements to perform binary addition 1
    {                                                   //(n-2)+(n-2) = 2*(n-2)
        add = b[i-2][j] + b[i-2][j] + r;
        if(add == 3)                    //1+1+1 = 1  carry 1
        {                          
            b[i][j] = 1;      
            r = 1;
        }
            
        else if (add == 2)             //1+0+1 = 0  carry 1 or
        {                              //0+1+1 = 0  carry 1 or    
            b[i][j] = 0;               //1+1+0 = 0  carry 1 
            r = 1;
        }
        
        else if (add == 1)   
        {                               //1+0+0 = 1  carry 0 or
            b[i][j] = 1;                //0+1+0 = 1  carry 0 or
            r = 0;                      //0+0+1 = 1  carry 0
        }
        
        else if (add == 0)
        {
            b[i][j] = 0;                //0+0 = 0  carry 0
            r = 0;
        }
        else 
            cout << "error in remainder:  r cannot be more than 1" << endl;
    }
    
    if(r == 1)
    {
         b[i].push_back(r);
    }
    if(b[i].size() > b[i-2].size())
                b[i-2].resize(b[i].size());    //resize binary numbers to match current result size
    if(b[i].size() > b[i-1].size())
                b[i-1].resize(b[i].size());
	t = b[i].size();
    r = 0;
    for(int j=0; j<t; j++)   //loop with nested if statements to perform binary addition 2
    {                                                   //2*(n-2)+(n-2)= 3*(n-2)
        add = b[i][j] + b[i-2][j] + r;
        if(add == 3)                    //1+1+1 = 1  carry 1
        {                          
            b[i][j] = 1;      
            r = 1;
        }
            
        else if (add == 2)             //1+0+1 = 0  carry 1 or
        {                              //0+1+1 = 0  carry 1 or    
            b[i][j] = 0;               //1+1+0 = 0  carry 1 
            r = 1;
        }
        
        else if (add == 1)   
        {                               //1+0+0 = 1  carry 0 or
            b[i][j] = 1;                //0+1+0 = 1  carry 0 or
            r = 0;                      //0+0+1 = 1  carry 0
        }
        
        else if (add == 0)
        {
            b[i][j] = 0;                //0+0 = 0  carry 0
            r = 0;
        }
        else 
            cout << "error in remainder:  r cannot be more than 1" << endl;
    }    
    if(r == 1)
    {
        b[i].push_back(r);
    }
    if(b[i].size() > b[i-2].size())
                b[i-2].resize(b[i].size());    //resize binary numbers to match current result size
    if(b[i].size() > b[i-1].size())
                b[i-1].resize(b[i].size());
	t = b[i].size();
    r = 0;
    for(int j=0; j<t; j++)   //loop with nested if statements to perform binary addition 3
    {                                                      //(n-1) + 3*(n-2)
        add = b[i][j] + b[i-1][j] + r;
        if(add == 3)                    //1+1+1 = 1  carry 1
        {                          
            b[i][j] = 1;      
            r = 1;
        }
            
        else if (add == 2)             //1+0+1 = 0  carry 1 or
        {                              //0+1+1 = 0  carry 1 or    
            b[i][j] = 0;               //1+1+0 = 0  carry 1 
            r = 1;
        }
        
        else if (add == 1)   
        {                               //1+0+0 = 1  carry 0 or
            b[i][j] = 1;                //0+1+0 = 1  carry 0 or
            r = 0;                      //0+0+1 = 1  carry 0
        }
        
        else if (add == 0)
        {
            b[i][j] = 0;              //0+0 = 0  carry 0
            r = 0;
        }
        else 
            cout << "error in remainder:  r cannot be more than 1" << endl;
        
        
    }
    if(r == 1)
    {
        b[i].push_back(r);
    }
	t = b[i].size();
    return;
}

double convert_to_decimal(vector<vector<int> > & b, int c)  //converts binary to decimal
{
    double num = 0 + b[c][0] * 1;     //num for number
    int pwr = 1;    //increases by power of 2 for conversion
    int s = b[c].size();
    for (int k=1; k<s; k++)
    {
        pwr = pwr * 2;
        num = num + b[c][k] * pwr;
    }
    return num;
}