#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    // write your code here
    int refills = 0;
    int lastStop = 0;
    int i = 0;
    while (lastStop + tank < dist) {
        int currentStop = lastStop;
        while(stops[i] - lastStop <= tank && i < stops.size()) {
            currentStop = stops[i++];
        }
        
        if(currentStop == lastStop) return -1;
        
        lastStop = currentStop;
        refills++;
    }
    
    return refills;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
