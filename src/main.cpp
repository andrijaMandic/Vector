#include "vect.h"

using namespace std;

int main()
{
    // Vaši testovi dolaze ovdje.   
    Vect<int> V1, V2(5,1);

    cout << "V1 = " << V1 << endl;
    cout << "V2 = " << V2 << endl;

    V1.push_back(3);
    V1.push_back(4);
    V1.push_back(6);
    V1.push_back(4);
    V1.push_back(2);
    cout << "_____________________\n";
    cout << "V1 = " << V1 << endl;
    cout << "V2 = " << V2 << endl;

    V2 = V1;
    cout << "_____________________\n";
    cout << "V1 = " << V1 << endl;
    cout << "V2 = " << V2 << endl;

    Vect<int> V3 = std::move(V2);
    cout << "_____________________\n";
    cout << "V1 = " << V1 << endl;
    cout << "V2 = " << V2 << endl;
    cout << "V3 = " << V3 << endl;

    V2 = V1 + V3;
    cout << "_____________________\n";
    cout << "V1 = " << V1 << endl;
    cout << "V2 = " << V2 << endl;
    cout << "V3 = " << V3 << endl;
    
    // Vect<int> obj1(5,1);

    // obj1 += obj1;

    // obj1 *= 3;

    // for( int i = 0; i < 5; ++i){
    //     cout << obj1[i] << " ";
    // } 
    // cout << endl;

    // cout << obj1 << endl;
    return 0;
}
