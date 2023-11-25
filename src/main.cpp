#include <iostream>
#include <vector>
#include <map>
#include <set>

enum State {TOP, BOTTOM, DRD, DLD, URU, ULU, DRU, ULD};

struct Horizonal {
  int y;
  int left;
  int right;
  State state;
};

inline bool operator<(const Horizonal& lhs, const Horizonal& rhs) {
  return lhs.right < rhs.left;
}

struct Point {
  int x;
  int y;
};

class Solution {
 public:
  
  Solution(std::vector<Point> inputs)
    : data(inputs), hlines(), res() {
    int npoints = inputs.size();
    // need reverse


    for (int i = 0; i < npoints; ++i) {
      int next = (i + 1) % npoints;
      if (data[i].y == data[next].y) {
        int nexnex = (i + 2) % npoints;
        int pre = (i - 1 + npoints) % npoints;
        bool fir_up = data[i].y > data[pre].y;
        bool sec_ri = data[next].x > data[i].x;
        bool thr_up = data[nexnex].y > data[next].y;

        Horizonal h;
        h.y = data[i].y;
        if (sec_ri) {
          h.left = data[i].x;
          h.right = data[next].x;
        }
        else {
          h.left = data[next].x;
          h.right = data[i].x;
        }
        if (fir_up) {
          if (sec_ri) {
            if (thr_up)
              h.state = URU;
            else
              h.state = TOP;
          }
          else {
            if (thr_up)
              h.state = ULU;
            else
              h.state = ULD;
          }
        }
        else {
          if (sec_ri) {
            if (thr_up)
              h.state = DRU;
            else
              h.state = DRD;
          }
          else {
            if (thr_up)
              h.state = BOTTOM;
            else
              h.state = DLD;
          }
        }
        hlines.insert({data[i].y, h});
      }
    }

    Split();

    for (auto &r : res)
      std::cout << '(' << r[0].x << ", " << r[0].y << ')' << " "
                << '(' << r[1].x << ", " << r[1].y << ')' << std::endl;
  }

  void Split();

  std::vector<Point> data;
  std::multimap<int, Horizonal, std::greater<int> > hlines;
  std::vector<std::vector<Point> > res;
};

int main() {
  
  std::vector<Point> input1 = {Point{48,89},Point{48,118},Point{87,118},Point{87,106},
                               Point{111,106},Point{111,72},Point{86,72},Point{86,33},
                               Point{63,33},Point{63,46},Point{27,46},Point{27,61},
                               Point{63,61},Point{63,89}};
  
  Solution s1(input1);
  return 0;
}

void Solution::Split() {
  while (!hlines.empty()) {
    auto it = hlines.begin();
    while (it->second.state == TOP) ++it;
    auto temp = it->second;
    auto counter = hlines.count(it->first);
    it = hlines.erase(it);
    auto top = hlines.begin();
    if (temp.state == BOTTOM) {
      while (top != it) {
        if (top->second.left == temp.left)
          break;
        ++top;
      }
      std::vector<Point> r;
      r.push_back(Point{temp.left, temp.y});
      r.push_back(Point{top->second.right, top->first});
      res.push_back(r);
      hlines.erase(top);
    }
    else {
      if (counter == 1) {
        if (temp.state == DRD) {
          while (top != it) {
            if (top->second.right == temp.left)
              break;
            ++top;
          }
          std::vector<Point> r;
          r.push_back(Point{top->second.left, temp.y});
          r.push_back(Point{temp.left, top->first});
          res.push_back(r);
          hlines.insert({temp.y, Horizonal{temp.y, top->second.left, temp.right, TOP}});
          hlines.erase(top);
        }
        else if (temp.state == DLD) {
          while (top != it) {
            if (top->second.right == temp.right)
              break;
            ++top;
          }
          std::vector<Point> r;
          r.push_back(Point{top->second.left, temp.y});
          r.push_back(Point{temp.right, top->first});
          res.push_back(r);
          hlines.insert({temp.y, Horizonal{temp.y, top->second.left, temp.left, TOP}});
          hlines.erase(top);
        }
        else if (temp.state == ULU) {
          while (top != it) {
            if (top->second.left == temp.left)
              break;
            ++top;
          }
          std::vector<Point> r;
          r.push_back(Point{top->second.left, temp.y});
          r.push_back(Point{top->second.right, top->first});
          res.push_back(r);
          hlines.insert({temp.y, Horizonal{temp.y, temp.right, top->second.right, TOP}});
          hlines.erase(top);
        }
        else if (temp.state == URU) {
          while (top != it) {
            if (top->second.left == temp.right)
              break;
            ++top;
          }
          std::vector<Point> r;
          r.push_back(Point{top->second.left, temp.y});
          r.push_back(Point{top->second.right, top->first});
          res.push_back(r);
          hlines.insert({temp.y, Horizonal{temp.y, temp.left, top->second.right, TOP}});
          hlines.erase(top);
        }
        else if (temp.state == DRU) {
          while (top != it) {
            if (top->second.right == temp.left)
              break;
            ++top;
          }
          std::vector<Point> r1;
          r1.push_back(Point{top->second.left, temp.y});
          r1.push_back(Point{temp.left, top->first});
          res.push_back(r1);
          hlines.insert({temp.y, Horizonal{temp.y, top->second.left, temp.right, URU}});
          hlines.erase(top);
        }
        else if (temp.state == ULD) {
          while (top != it) {
            if (top->second.left < temp.left && top->second.right > temp.right)
              break;
            ++top;
          }
          std::vector<Point> r;
          r.push_back(Point{top->second.left, temp.y});
          r.push_back(Point{top->second.right, top->first});
          res.push_back(r);
          hlines.insert({temp.y, Horizonal{temp.y, top->second.left, temp.left, TOP}});
          hlines.insert({temp.y, Horizonal{temp.y, temp.right, top->second.right, TOP}});
          hlines.erase(top);
        }
      }
      else {
        auto it2 = it;
        while (it2->first == it->first) {
          ++it2;
        }
        std::cout << "test" << std::endl;

      }
    }
  }
}