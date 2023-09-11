// #include <iostream>
// #include <set>

// using namespace std;

// int main() {

//   int n;
//   cin >> n;
//   set<int> output;
//   for (int i = 0; i < n; ++i) {
//     int tt;
//     cin >> tt;
//     output.insert(tt);
//   }
//   int result = 0;
//   for (auto s : output) {
//     result = result + s;
//   }
//   cout << result;

//   return 0;
// }
// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// int main() {
//   int t;
//   cin >> t;
//   vector<vector<int> > total;
//   for (int i = 0; i < t; ++i) {
//     vector<int> temp_a;
//     vector<int> temp_b;
//     int n;
//     cin >> n;
//     for (int j = 0; j < n; ++j) {
//       int num;
//       cin >> num;
//       temp_a.push_back(num);
//     }
//     for (int k = 0; k < n-1; ++k) {
//       int num2;
//       cin >> num2;
//       temp_b.push_back(num2);
//     }
//     total.push_back(temp_a);
//     total.push_back(temp_b);
//   }

//   for (int i = 0; i < t; ++i) {
//     int n = total[2*i].size();
//     auto it = total[2*i+1].begin();
//     vector<int> ori_a = total[2*i];
//     for (int k = 1; k < n; ++k) {
//       sort(total[2*i].begin(), total[2*i].end());
//       if (total[2*i].size() % 2 == 1)
//         cout << total[2*i][total[2*i].size()/2] << " ";
//       else
//         cout << 0.5 * (total[2*i][total[2*i].size()/2] + total[2*i][total[2*i].size()/2-1]) << " ";
      
//       int pos = (*it) - 1;
//       ++it;
//       auto de = ori_a.begin() + pos;
//       total[2*i].erase(find(total[2*i].begin(), total[2*i].end(),*de));



//     }
//     cout << total[2*i][0] << endl;
//   }
  

//   return 0;
// }

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int main() {
  int n,k;
  cin >> n >> k;
  vector<int> data;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    data.push_back(x);
  }
  int res = 0;
  for (auto x : data)
    res+= x;
  cout << res;
  
  return 0;
}