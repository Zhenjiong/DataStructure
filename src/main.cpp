#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

enum State {TOP, BOTTOM, DRD, DLD, URU, ULU, DRU, ULD};

struct Horizonal {
  int y;
  int left;
  int right;
  State state;
};

inline bool operator<(const Horizonal& lhs, const Horizonal& rhs) {
  return lhs.right < rhs.right || lhs.left < rhs.left;
}

inline bool operator==(const Horizonal& lhs, const Horizonal& rhs) {
  return lhs.y == rhs.y && lhs.left == rhs.left
      && lhs.right == rhs.right && lhs.state == rhs.state;
}

struct Point {
  int x;
  int y;
};

using m_it = std::multimap<int, Horizonal, std::greater<int> >::iterator;

class Solution {
 public:
  
  Solution(std::vector<Point> inputs);

  void Split();

  m_it find_neartop(m_it _begin, m_it _end, Horizonal h, bool right = false);

  std::vector<Point> data;
  std::multimap<int, Horizonal, std::greater<int> > hlines;
  std::vector<std::vector<Point> > res;
};

int main() {
  
  std::vector<Point> input1 = {Point{48,89},Point{48,118},Point{87,118},Point{87,106},
                               Point{111,106},Point{111,72},Point{86,72},Point{86,33},
                               Point{63,33},Point{63,46},Point{27,46},Point{27,61},
                               Point{63,61},Point{63,89}};
  
  std::vector<Point> input2 = {Point{1,5},Point{2,5},Point{2,4},Point{3,4},Point{3,5},
                               Point{4,5},Point{4,3},Point{5,3},Point{5,8},Point{7,8},
                               Point{7,4},Point{8,4},Point{8,5},Point{12,5},Point{12,1},
                               Point{10,1},Point{10,4},Point{9,4},Point{9,2},Point{6,2},
                               Point{6,1},Point{1,1}};
  
  std::vector<Point> input3 = {Point{1,6},Point{1,1},Point{2,1},Point{2,2},Point{3,2},
                               Point{3,4},Point{4,4},Point{4,1},Point{6,1},Point{6,3},
                               Point{5,3},Point{5,6}};
  
  std::cout << "input1: " << std::endl;
  for (auto p : input1)
    std::cout << '(' << p.x << ", " << p.y << ')' << " ";
  std::cout << '\n' << "result1: " << std::endl;
  Solution s1(input1);

  std::cout << "\n" << "input2: " << std::endl;
  for (auto p : input2)
    std::cout << '(' << p.x << ", " << p.y << ')' << " ";
  std::cout << '\n' << "result2: " << std::endl;
  Solution s2(input2);

  std::cout << "\n" << "input3: " << std::endl;
  for (auto p : input3)
    std::cout << '(' << p.x << ", " << p.y << ')' << " ";
  std::cout << '\n' << "result3: " << std::endl;
  Solution s3(input3);
  
  return 0;
}

Solution::Solution(std::vector<Point> inputs)
  : data(inputs), hlines(), res() {
  int npoints = inputs.size();

  // need reverse
  int index = 0;
  int max_y = inputs[index].y;
  for (int i = 0; i < npoints; ++i) {
    if (inputs[i].y > max_y) {
      max_y = inputs[i].y;
      index = i;
    }
  }
  int nex = (index + 1) % npoints;
  int pre = (index - 1 + npoints) % npoints;
  if (inputs[nex].y == inputs[index].y) {
    if (inputs[nex].x < inputs[index].x)
      std::reverse(data.begin(), data.end());
  }
  else if (inputs[pre].y == inputs[index].y) {
    if (inputs[index].x < inputs[pre].x)
      std::reverse(data.begin(), data.end());
  }
  
  // build map
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

void Solution::Split() {
  while (!hlines.empty()) {
    auto it = hlines.begin();
    while (it->second.state == TOP) ++it;
    auto temp = it->second;
    auto counter = hlines.count(it->first);
    if (counter == 1) {
      it = hlines.erase(it);
      if (temp.state == BOTTOM) {
        auto top = find_neartop(hlines.begin(), it, temp);
        std::vector<Point> r;
        r.push_back(Point{temp.left, temp.y});
        r.push_back(Point{top->second.right, top->first});
        res.push_back(r);
        hlines.erase(top);
      }
      else if (temp.state == DRD) {
        auto top = find_neartop(hlines.begin(), it, temp);
        std::vector<Point> r;
        r.push_back(Point{top->second.left, temp.y});
        r.push_back(Point{temp.left, top->first});
        res.push_back(r);
        hlines.insert({temp.y, Horizonal{temp.y, top->second.left, temp.right, TOP}});
        hlines.erase(top);
      }
      else if (temp.state == DLD) {
        auto top = find_neartop(hlines.begin(), it, temp);
        std::vector<Point> r;
        r.push_back(Point{top->second.left, temp.y});
        r.push_back(Point{temp.right, top->first});
        res.push_back(r);
        hlines.insert({temp.y, Horizonal{temp.y, top->second.left, temp.left, TOP}});
        hlines.erase(top);
      }
      else if (temp.state == ULU) {
        auto top = find_neartop(hlines.begin(), it, temp);
        std::vector<Point> r;
        r.push_back(Point{top->second.left, temp.y});
        r.push_back(Point{top->second.right, top->first});
        res.push_back(r);
        hlines.insert({temp.y, Horizonal{temp.y, temp.right, top->second.right, TOP}});
        hlines.erase(top);
      }
      else if (temp.state == URU) {
        auto top = find_neartop(hlines.begin(), it, temp);
        std::vector<Point> r;
        r.push_back(Point{top->second.left, temp.y});
        r.push_back(Point{top->second.right, top->first});
        res.push_back(r);
        hlines.insert({temp.y, Horizonal{temp.y, temp.left, top->second.right, TOP}});
        hlines.erase(top);
      }
      else if (temp.state == DRU) {
        auto top = find_neartop(hlines.begin(), it, temp, false);
        std::vector<Point> r1;
        r1.push_back(Point{top->second.left, temp.y});
        r1.push_back(Point{temp.left, top->first});
        res.push_back(r1);
        hlines.insert({temp.y, Horizonal{temp.y, top->second.left, temp.right, URU}});
        hlines.erase(top);
      }
      else if (temp.state == ULD) {
        auto top = find_neartop(hlines.begin(), it, temp);
        std::vector<Point> r;
        r.push_back(Point{top->second.left, temp.y});
        r.push_back(Point{top->second.right, top->first});
        res.push_back(r);
        hlines.insert({temp.y, Horizonal{temp.y, top->second.left, temp.left, TOP}});
        hlines.insert({temp.y, Horizonal{temp.y, temp.right, top->second.right, TOP}});
        hlines.erase(top);
      }
    }
    // counter != 1
    else {
      std::set<Horizonal> s;
      int height = temp.y;
      std::vector<Horizonal> bots;
      std::vector<Horizonal> ulds;
      do {
        if (temp.state == BOTTOM) {
          bots.push_back(temp);
        }
        else if (temp.state == ULD) {
          auto top = find_neartop(hlines.begin(), it, temp);
          s.insert(top->second);
          ulds.push_back(temp);
        }
        else {
          s.insert(temp);
          if (temp.state == DRU) {
            auto ltop = find_neartop(hlines.begin(), it, temp, false);
            auto rtop = find_neartop(hlines.begin(), it, temp, true);
            s.insert(ltop->second);
            s.insert(rtop->second);
          }
          else {
            auto top = find_neartop(hlines.begin(), it, temp);
            s.insert(top->second);
          }
        }
        it = hlines.erase(it);
        if (it == hlines.end())
          break;
        temp = it->second;
      } while (temp.y == height);

      auto l = s.cbegin();
      auto r = s.cbegin();
      if (!s.empty())
        ++r;
      while (r != s.cend()) {
        auto bef = r; --bef;
        while (r != s.cend() && bef->right >= r->left) {
          ++r; ++bef;
        }
        // [l, r). r maybe is end
        for (auto k = l; k != r; ++k) {
          if (k->state == TOP) {
            std::vector<Point> rr;
            rr.push_back(Point{k->left, height});
            rr.push_back(Point{k->right, k->y});
            res.push_back(rr);

            auto q = hlines.begin();
            while (q != hlines.end()) {
              if (q->second == *k)
                break;
              ++q;
            }
            hlines.erase(q);
          }
        }

        std::set<int> lr_new = {l->left, bef->right};
        for (auto p : ulds) {
          if (l->left < p.left && p.right < bef->right) {
            lr_new.insert(p.left);
            lr_new.insert(p.right);
          }
        }
        auto lr = lr_new.begin();
        while (lr != lr_new.end()) {
          auto nex = lr; ++nex;
          hlines.insert({height, Horizonal{height, *lr, *nex, TOP}});
          ++lr; ++lr;
        }

        if (r != s.cend()) {
          l = r;
          ++r;
        }
      }
      
      // delete bots's top
      for (auto &bot : bots) {
        auto top = find_neartop(hlines.begin(), hlines.end(), bot);
        std::vector<Point> r;
        r.push_back(Point{top->second.left, height});
        r.push_back(Point{top->second.right, top->first});
        res.push_back(r);
        hlines.erase(top);
      }
    }
  }
}

m_it Solution::find_neartop(m_it _begin, m_it _end, Horizonal h, bool right) {
  auto it = _begin;
  while (it != _end) {
    if (h.state == BOTTOM && it->second.left == h.left)
      break;
    else if (h.state == DRD && it->second.right == h.left)
      break;
    else if (h.state == DLD && it->second.right == h.right)
      break;
    else if (h.state == ULU && it->second.left == h.left)
      break;
    else if (h.state == URU && it->second.left == h.right)
      break;
    else if (h.state == ULD && it->second.left < h.left && h.right < it->second.right)
      break;
    else if (h.state == DRU && !right && it->second.right == h.left)
      break;
    else if (h.state == DRU && right && it->second.left == h.right)
      break;
    else
      ++it;

  }
  return it;
}
