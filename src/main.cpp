#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector<int>& nums, int l, int r) {
  // break condition: only one element to sort
  if (l >= r) return;

  int i = l;
  int j = r;
  // choose a random num as a reference axis
  // here I use the last num
  int index = nums[r];
  while (i < j) {
    // find the bigger one then swap to right
    while (i < j && nums[i] <= index)
      ++i;
    if (i < j) {
      swap(nums[i], nums[j]);
      --j;
    }

    // find the smaller or equal one then swap to left
    while (i < j && nums[j] > index)
      --j;
    if (i < j) {
      swap(nums[i], nums[j]);
      ++i;
    }
  }
  // now i == j and nums[i] is the correct place
  // for this index
  nums[i] = index;

  quickSort(nums, l, i-1);
  quickSort(nums, i+1, r);
}

void bubbleSort(vector<int> &nums) {
  for (int i = 0; i < nums.size() - 1; ++i) {
    for (int j = 0; j < nums.size() - i - 1; ++j) {
      if (nums[j] > nums[j+1])
        std::swap(nums[j], nums[j+1]);
    }
  }
}

int main () {
  vector<int> in = {5,2,1,4,3,1};
  int n = in.size();
  quickSort(in, 0, n-1);
  // bubbleSort(in);
  for (auto i : in)
    cout << i << " ";
  return 0;
}