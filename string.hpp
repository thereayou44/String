#include <cstring>
#include <iostream>
#include <vector>

class String {
 private:
  char* str_;
  size_t capacity_ = 1;
  size_t str_size_ = 0;

 public:
  String();

  ~String();

  String(size_t size, char character);

  String(const char* copy_str);

  String(const String& str_to_copy);

  String& operator=(String const& str_to_copy);

  String& operator=(const char* to_copy);

  void Clear();

  void PushBack(char character);

  void PopBack();

  void Resize(size_t new_size);

  void Resize(size_t new_size, char character);

  void Reserve(size_t new_cap);

  void ShrinkToFit();

  void Swap(String& other);

  char& operator[](int index);

  char operator[](int index) const;

  char& Front();

  char Front() const;

  char& Back();

  char Back() const;

  bool Empty() const;

  size_t Size() const;

  size_t Capacity() const;

  const char* Data() const;

  char* Data();

  String& operator+=(const String& to_sum);

  String& operator*=(int k_times);

  friend std::ostream& operator<<(std::ostream& os, const String& to_cout);

  friend std::istream& operator>>(std::istream& os, String& to_cin);

  std::vector<String> Split(const String& delim = " ") const;

  String Join(const std::vector<String>& strings) const;

  friend bool operator<(const String& first, const String& to_compare);

  friend bool operator>(const String& first, const String& to_compare);

  friend bool operator<=(const String& first, const String& to_compare);

  friend bool operator>=(const String& first, const String& to_compare);

  friend bool operator==(const String& first, const String& to_compare);

  friend bool operator!=(const String& first, const String& to_compare);

  friend String operator+(const String& first, const String& to_sum);

  friend String operator*(const String& first, int k_times);
};
