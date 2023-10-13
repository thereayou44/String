#include "string.hpp"

String::String() { str_ = nullptr; }
String::~String() { delete[] str_; }

String::String(size_t size, char character) {
  str_ = new char[size + 1];
  str_size_ = size;
  capacity_ = size + 1;
  for (size_t i = 0; i < size; i++) {
    str_[i] = character;
  }
  str_[str_size_] = '\0';
}

String::String(const char* copy_str) {
  str_size_ = strlen(copy_str);
  capacity_ = strlen(copy_str) + 1;
  str_ = new char[capacity_];
  memcpy(str_, copy_str, str_size_ + 1);
}

String::String(const String& str_to_copy) {
  str_size_ = str_to_copy.str_size_;
  capacity_ = str_to_copy.capacity_;
  str_ = new char[capacity_];
  memcpy(str_, str_to_copy.str_, str_to_copy.str_size_ + 1);
}

String& String::operator=(String const& str_to_copy) {
  str_size_ = str_to_copy.str_size_;
  capacity_ = str_to_copy.capacity_;
  delete[] str_;
  str_ = new char[capacity_];
  memcpy(str_, str_to_copy.str_, str_to_copy.str_size_ + 1);
  return *this;
}

String& String::operator=(const char* to_copy) {
  size_t new_size = strlen(to_copy);
  str_size_ = new_size;
  capacity_ = new_size + 1;
  delete[] str_;
  str_ = new char[capacity_];
  str_[new_size] = '\0';
  memcpy(str_, to_copy, new_size);
  return *this;
}

void String::Clear() { str_size_ = 0; }

void String::PushBack(char character) {
  if (capacity_ - str_size_ <= 2) {
    capacity_ *= 2;
    if (str_ != nullptr) {
      char* tmp = new char[capacity_];
      memcpy(tmp, str_, str_size_);
      delete[] str_;
      str_ = tmp;
    } else {
      str_ = new char[capacity_ + 1];
    }
  }
  str_[str_size_] = character;
  str_size_++;
  str_[str_size_] = '\0';
}

void String::PopBack() {
  if (str_size_ != 0) {
    str_size_--;
    memmove(str_ + 1, str_, str_size_);
  }
}

void String::Resize(size_t new_size) {
  str_size_ = new_size;
  if (new_size > capacity_) {
    capacity_ = new_size + 1;
    char* tmp = new char[capacity_];
    delete[] str_;
    str_ = tmp;
    str_[new_size] = '\0';
  }
}

void String::Resize(size_t new_size, char character) {
  if (str_size_ > new_size) {
    str_size_ = new_size;
  } else {
    if (capacity_ < new_size) {
      capacity_ = new_size + 1;
      char* tmp = new char[new_size + 1];
      strncpy(tmp, str_, str_size_ + 1);
      delete[] str_;
      str_ = new char[capacity_];
      strncpy(str_, tmp, str_size_ + 1);
      delete[] tmp;
    }
    for (size_t i = str_size_; i < new_size; i++) {
      str_[i] = character;
    }
    str_size_ = new_size;
  }
}

void String::Reserve(size_t new_cap) {
  if (capacity_ < new_cap) {
    capacity_ = new_cap;
    char* tmp = new char[capacity_];
    memcpy(tmp, str_, str_size_);
    delete[] str_;
    str_ = tmp;
  }
}

void String::ShrinkToFit() {
  if (capacity_ > str_size_) {
    capacity_ = str_size_;
    delete[] str_;
    str_ = new char[capacity_];
  }
}

void String::Swap(String& other) {
  String tmp = *this;
  *this = other;
  other = tmp;
}

char& String::operator[](int index) { return str_[index]; }

char String::operator[](int index) const { return str_[index]; }

char& String::Front() { return str_[0]; }

char String::Front() const { return str_[0]; }

char& String::Back() { return str_[str_size_ - 1]; }

char String::Back() const { return str_[str_size_ - 1]; }

bool String::Empty() const { return (str_size_ == 0); }

size_t String::Size() const { return str_size_; }

size_t String::Capacity() const { return capacity_; }

const char* String::Data() const { return str_; }

char* String::Data() { return str_; }

String& String::operator+=(const String& to_sum) {
  if (capacity_ < str_size_ + to_sum.str_size_) {
    char* tmp;
    capacity_ += to_sum.capacity_;
    tmp = new char[capacity_];
    memcpy(tmp, str_, str_size_);
    delete[] str_;
    memcpy(tmp + str_size_, to_sum.str_, to_sum.str_size_);
    str_size_ += to_sum.str_size_;
    str_ = new char[capacity_];
    memcpy(str_, tmp, capacity_);
    str_[str_size_] = '\0';
    delete[] tmp;
  } else {
    memcpy(str_ + str_size_, to_sum.str_, to_sum.str_size_);
    str_size_ += to_sum.str_size_;
  }

  return *this;
}

String operator+(const String& first, const String& to_sum) {
  String sum;
  sum.Reserve(to_sum.str_size_ + first.str_size_ + 1);
  sum.str_size_ = to_sum.str_size_ + first.str_size_;
  strncpy(sum.str_, first.str_, first.str_size_);
  strncpy(sum.str_ + first.str_size_, to_sum.str_, to_sum.str_size_);
  sum[sum.str_size_] = '\0';
  return sum;
}

String operator*(const String& first, int k_times) {
  String result("");
  if (k_times != 0) {
    result.Reserve(k_times * first.capacity_);
    for (int iter = 0; iter < k_times; iter++) {
      for (size_t idx = 0; idx < first.str_size_; idx++) {
        result.str_[first.str_size_ * iter + idx] = first.str_[idx];
      }
    }
    result.str_size_ = k_times * first.str_size_;
    result[result.str_size_] = '\0';
  }
  return result;
}

String& String::operator*=(int k_times) {
  *this = *this * k_times;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const String& to_cout) {
  for (size_t i = 0; i < to_cout.str_size_; i++) {
    os << to_cout.str_[i];
  }

  return os;
}

std::istream& operator>>(std::istream& os, String& to_cin) {
  const int kMaxBuf = 1000;
  char* buf = new char[kMaxBuf];
  os >> buf;
  const size_t kSize = strlen(buf);
  to_cin.str_size_ = kSize;
  to_cin.capacity_ = kSize + 1;
  delete[] to_cin.str_;
  to_cin.str_ = new char[to_cin.capacity_];
  for (size_t i = 0; i < to_cin.str_size_; i++) {
    to_cin.str_[i] = buf[i];
  }
  delete[] buf;
  return os;
}

std::vector<String> String::Split(const String& delim) const {
  char* cpy_str = str_;
  size_t prev_size;
  std::vector<String> result;
  while (strstr(cpy_str, delim.str_) != nullptr) {
    char* prev_str = cpy_str;
    prev_size = strlen(prev_str);
    cpy_str = strstr(cpy_str, delim.str_) + delim.str_size_;
    size_t substr_size = prev_size - strlen(cpy_str) - delim.str_size_;
    char* substr = new char[substr_size + 1];
    strncpy(substr, prev_str, substr_size);
    substr[substr_size] = '\0';
    result.emplace_back(substr);
    delete[] substr;
  }
  result.emplace_back(cpy_str);
  return result;
}

String String::Join(const std::vector<String>& strings) const {
  String result("");
  for (size_t i = 0; i < strings.size(); i++) {
    result += strings[i];
    if (i != strings.size() - 1) {
      result += *this;
    }
  }
  return result;
}
bool operator<(const String& first, const String& to_compare) {
  if (to_compare.str_size_ > first.str_size_) {
    return true;
  }
  size_t idx = 0;
  while (to_compare.str_[idx] == first.str_[idx]) {
    idx++;
  }
  return (to_compare.str_[idx] > first.str_[idx]);
}

bool operator>(const String& first, const String& to_compare) {
  if (to_compare.str_size_ < first.str_size_) {
    return true;
  }
  size_t idx = 0;
  while (to_compare.str_[idx] == first.str_[idx]) {
    idx++;
  }
  return (to_compare.str_[idx] < first.str_[idx]);
}

bool operator<=(const String& first, const String& to_compare) {
  if (to_compare.str_size_ > first.str_size_) {
    return true;
  }
  size_t idx = 0;
  while (to_compare.str_[idx] == first.str_[idx]) {
    idx++;
  }
  return (to_compare.str_[idx] >= first.str_[idx]);
}

bool operator>=(const String& first, const String& to_compare) {
  if (to_compare.str_size_ < first.str_size_) {
    return true;
  }
  size_t idx = 0;
  while (to_compare.str_[idx] == first.str_[idx]) {
    idx++;
  }
  return (to_compare.str_[idx] <= first.str_[idx]);
}

bool operator==(const String& first, const String& to_compare) {
  if (first.str_size_ != to_compare.str_size_) {
    return false;
  }

  for (size_t i = 0; i < first.str_size_; i++) {
    if (first.str_[i] != to_compare.str_[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const String& first, const String& to_compare) {
  if (first.str_size_ != to_compare.str_size_ ||
      first.capacity_ != to_compare.capacity_) {
    return true;
  }

  for (size_t i = 0; i < first.str_size_; i++) {
    if (first.str_[i] != to_compare.str_[i]) {
      return true;
    }
  }
  return false;
}
