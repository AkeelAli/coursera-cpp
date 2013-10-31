// Include the required libraries
#include <iostream>
#include <vector>

// Specify the namespace used
using namespace std;

// Define the size 'N' of the vector
const int N = 40;

// Inline function summing the first 'n' integers
// from vector 'd' into the variable 'p'
inline void sum(int& p, int n, const vector<int>& d)
{
    p = 0;
    for(int i = 0; i < n; ++i)
        p += d.at(i);
}

int main()
{
    int accum = 0;
    // Create a vector 'data' with 'N' integers
    vector<int> data(N);

    //Store the values 0 to N-1 into the vector 'data'
    for(int i = 0; i < N; ++i)
        data.at(i) = i;

    // Sum-up the first N integers of 'data' into 'accum'
    sum(accum, N, data);

    // Print the accumulator 'accum'
    cout << "sum is " << accum << endl;

    return 0;
}
