#include <bits/stdc++.h>
#define endl "\n"
#define int long long
#define CODEGOD                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
using namespace std;

void solve()
{
    vector<int> nums;

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }

    int len = nums.size();

    // next permutation
    if (next_permutation(nums.begin(), nums.end()))
    {
        for (int i = 0; i < len; i++)
        {
            cout << nums[i] << " ";
        }
    }
    else
    {
        for( int i = len - 1; i >= 0; i--)
        {
            cout << nums[i] << " ";
        }
    }

}

signed main()
{
    CODEGOD;
    int t = 1;
    //  cin >> t;
    while (t--)
    {
        /* code */
        solve();
    }
}