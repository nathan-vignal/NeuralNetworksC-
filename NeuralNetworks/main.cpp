#include <iostream>
#include <vector>
#include "Network.h"

using namespace std;

int main()
{
    /*
    for(unsigned i=0 ; i<10 ; ++i){
        unsigned j(0);
        cout << j<< endl;
        ++j;

    } */

 /*   cout << "machacar" << endl;
    Layer layer0(4,2);
    Layer layer1(4,2);
    cout << &layer0<< endl;
    cout << &layer1<< endl;
*/

    vector<vector<float>> input = {{1,1,1,0}};
    vector<vector<float>> output = {{1,1,1,0}};
    Network network((unsigned short)4,(unsigned short)4,input,output);

    cout << network;
    //network.feedforward();

    return 0;
}
