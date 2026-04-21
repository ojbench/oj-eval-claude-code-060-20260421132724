#pragma once
#include <vector>

template <typename T>
struct Expect {
  T v;
  bool ok;
  bool neg;

  explicit Expect(const T &value) : v(value), ok(true), neg(false) {}

  Expect &Not() {
    neg = !neg;
    return *this;
  }

  Expect &toBe(const T &y) {
    bool cond = (v == y);
    if (neg) cond = !cond;
    ok = ok && cond;
    return *this;
  }

  Expect &le(const T &y) {
    bool cond = !(y < v); // v <= y
    if (neg) cond = !cond;
    ok = ok && cond;
    return *this;
  }

  Expect &ge(const T &y) {
    bool cond = !(v < y); // v >= y
    if (neg) cond = !cond;
    ok = ok && cond;
    return *this;
  }

  Expect &lt(const T &y) {
    bool cond = (v < y);
    if (neg) cond = !cond;
    ok = ok && cond;
    return *this;
  }

  Expect &gt(const T &y) {
    bool cond = (y < v); // v > y
    if (neg) cond = !cond;
    ok = ok && cond;
    return *this;
  }

  Expect &toBeOneOf(const std::vector<T> &vec) {
    bool found = false;
    for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
      if (v == *it) { found = true; break; }
    }
    bool cond = found;
    if (neg) cond = !cond;
    ok = ok && cond;
    return *this;
  }

  operator bool() const { return ok; }
};

template <typename T>
Expect<T> expect(const T &x) { return Expect<T>(x); }
