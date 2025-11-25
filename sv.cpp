#include "sv.h"

#include <cstring>
#include <iostream>
#include <ostream>

namespace sv
{

constexpr string::builder::string_builder(byte* s, string::size_type s_len)
    : _data((byte*)s), _len(s_len), _capacity(s_len)
{
    this->_data[this->_len] = '\0';
}

constexpr string::string(const string::builder& s) noexcept : _data(s._data), _len(s._len) {}

string::builder::string_builder(const string& s) : _len(s._len), _capacity(s._len), _allocated(true)
{
    this->_data             = new byte[s._len + 1];
    this->_data             = (byte*)memcpy(this->_data, s._data, s._len);
    this->_data[this->_len] = '\0';
}

string::builder::string_builder(string::builder::size_type capacity)
{
    this->_data      = new byte[capacity];
    this->_capacity  = capacity;
    this->_allocated = true;
}

string::builder::~string_builder()
{
    if (this->_allocated)
    {
        delete[] this->_data;
    }
}

// constexpr string string_literals::operator""_sv(const byte *s, string::size_type s_len) noexcept
// {
//     return string(s, s_len);
// }

string::iterator string::begin() const noexcept
{
    return _data;
}

string::builder::iterator string::builder::begin() const
{
    return _data;
}

string::iterator string::end() const noexcept
{
    return _data + _len;
}

string::builder::iterator string::builder::end() const
{
    return _data + _len;
}

string::builder string::as_builder() const noexcept
{
    return string::builder(const_cast<string&>(*this));
}

string string::builder::as_view() const noexcept
{
    return string(*this);
}

string::builder string::builder::operator+(const string& other) const
{
    return *this + string::builder(other);
}

string::builder string::builder::operator+(const string::builder& other) const
{
    string::builder s(this->_len + other._len + 1);
    s._len              = this->_len + other._len;
    s._data             = (byte*)memcpy(s._data, this->_data, this->_len);
    s._data[this->_len] = '\0';
    s._data             = std::strcat(s._data, other._data);
    return s;
}

string::builder& string::builder::operator+=(const string::builder& other)
{
    *this = *this + other;
    return const_cast<string::builder&>(*this);
}

string string::substring(string::size_type end) const noexcept
{
    return this->substring(0, end);
}
string string::substring(string::size_type start, string::size_type end) const noexcept
{
    return string(this->_data + start, end - start);
}

string string::builder::substring(size_type end) const noexcept
{
    return this->as_view().substring(end);
}
string string::builder::substring(size_type start, size_type end) const noexcept
{
    return this->as_view().substring(start, end);
}
}  // namespace sv

std::ostream& operator<<(std::ostream& os, sv::string s)
{
    for (const char& c : s)
    {
        os << c;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, sv::string::builder s)
{
    for (const char& c : s)
    {
        os << c;
    }

    return os;
}
