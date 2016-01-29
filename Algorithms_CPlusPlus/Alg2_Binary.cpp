/* 
 * File:   main.cpp
 * Author: Owner
 * Created on September 8, 2012, 6:01 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;


void convert_to_binary(int, vector<int> & );
int binary_multiply(vector<int> &, vector<int> &, vector<int> &);
void binary_add(vector<int>, vector<int>, vector<int> &);
void make_vectors_same_size (vector<int> &, vector<int> &, vector<int> &);

int main(int argc, char** argv) 
{
    vector<int> binary1;
    vector<int> binary2;
    vector<int> result;
    srand(time(0));
    
    int random = 4;//rand()%10;                     //generate first random integer 
    cout << random << " x ";                          
    convert_to_binary(random, binary1);     //convert it to binary
//    for(int t=0; t<binary1.size(); t++)
//    {
//        cout << binary1[t];
//    }
//    cout << endl;
    random = 5;//rand()%10;                         //generate second random integer 
    cout << random << " = ";
    convert_to_binary(random, binary2);     //convert it to binary 
//    for(int t=0; t<binary2.size(); t++)
//    {
//        cout << binary2[t];
//    }
//    cout << endl;
    int ops = 0;             //variable for storing # of basic operations 
    ops = binary_multiply(binary1, binary2, result);    //calculates a binary multiply
    for(int t=result.size()-1; t>=0; t--)                          
    {
        cout << result[t];              //output to user
    }
    cout << endl;
    cout << "with " << ops << " elementary operations performed." << endl;
    return 0;
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

int binary_multiply(vector<int> & x, vector<int> & y, vector<int> & z)
{
    int ops_counter=0;          //initialize ops counter to count basic operations
    
    if (x.size() > y.size())
    {        
        y.resize(x.size(), 0);  //make sure vectors are all the same size
    }        
    else if (y.size() > x.size())
    {
        x.resize(y.size(), 0);
    }
    
    z.resize(x.size(), 0);                           //z = 0
    ops_counter = ops_counter+3;  //test and resize adds 3 to ops_counter
        
    int n = y.size();           //function it-multiply discussed in class
    vector<int> zcopy;
    ops_counter++;              //declaration adds 1 to ops_counter
    
    vector<int>::iterator p;
    for (int i=0; i<n; i++)      //for i = n-1 down to 0
    {
        p = z.begin();
        z.insert(p, 0);    //shift     //z = 2z
//        binary_add(z, z, z);            
        ops_counter = ops_counter+4*z.size();            //binary_add adds 4 per loop
        
        make_vectors_same_size (x, y, z);
        ops_counter = ops_counter +2;
        
        ops_counter++;          //test y[i] adds one to ops counter
        if (y[i] == 1)                    //if y[i] = 1
        {
            binary_add(z, x, z);      //z = z+x
            ops_counter = ops_counter+4*z.size();      //binary_add adds 4 ops per loop
        }
        
        make_vectors_same_size (x, y, z);
        ops_counter = ops_counter +2;
    }
    return ops_counter;               //returns operations count to function
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

void make_vectors_same_size (vector<int> & x, vector<int> & y, vector<int> & z)
{
    vector<int>::iterator xit;
    if(z.size() > x.size())  //resize x to match z if needed
    {
        x.resize(z.size(), 0);
    }
                 
    if(z.size() > y.size(), 0)  //resize y to match z if needed
    {
        y.resize(z.size());
    }
}