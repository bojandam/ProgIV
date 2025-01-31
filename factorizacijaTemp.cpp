#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
typedef long long LL;

vector<bool> slozen;
vector<int> prosti;
void generate(int n) {

    slozen.resize(n);
    int sq = sqrt(n);
    for (int i = 2; i < sq; i++) {
        if (!slozen[i]) {
            for (int j = 2 * i; j < n; j += i)
                slozen[j] = true;
            prosti.push_back(i);
        }
    }
}
vector < pair<LL, int> >factor(LL x) {
    vector< pair< LL, int> > rez;
    if (prosti[prosti.size() - 1] * prosti[prosti.size() - 1] < x) generate(x);
    for (int i : prosti) {
        if (i * i > x) break;
        int k = 0;
        while (!(x % i))
        {
            k++; x /= i;
        }
        if (k) { rez.push_back({ i, k }); }
        if (x == 1) { break; }


    }
    if (x > 1) rez.push_back({ x,1 });
    return rez;
}
vector < pair<LL, int> > fact(LL x) {
    vector<pair<LL, int>> rez;
    for (LL i = 2; i * i <= x; i += 2) {
        int k = 0;
        while (!(x % i))
        {
            k++; x /= i;
        }
        if (k) { rez.push_back({ i, k }); }
        if (x == 1) { break; }
        if (i == 2) i--;
    }
    if (x > 1) rez.push_back({ x,1 });
    return rez;
}


int main() {

    long long x; generate(10000);
    while (cin >> x)
    {
        auto f = factor(x);
        for (auto el : f) {
            cout << el.first << "^" << el.second << ", ";
        }
        cout << endl;
    }

}