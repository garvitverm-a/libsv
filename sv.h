#ifndef __sv_string__
#define __sv_string__

namespace
{
using byte      = char;
using size_type = unsigned long;
}  // namespace

namespace sv
{
class string;
class string_builder;

namespace string_literals
{
constexpr string operator""_sv(const byte* s, size_type s_len) noexcept;
}  // namespace string_literals

class string
{
    friend class string_builder;
    friend constexpr string string_literals::operator""_sv(const byte* s, size_type s_len) noexcept;

  public:
    using builder   = string_builder;
    using size_type = ::size_type;
    using iterator  = const byte*;

    string(const byte* s) noexcept;
    constexpr string(const string::builder& s) noexcept;

    string::builder as_builder() const noexcept;
    size_type length() const noexcept;

    string substring(size_type end) const noexcept;
    string substring(size_type start, size_type end) const noexcept;

    iterator begin() const noexcept;
    iterator end() const noexcept;

  private:
    constexpr string(const byte* s, size_type s_len) noexcept;

    const byte* _data    = nullptr;
    const size_type _len = 0;
};

class string_builder
{
    friend class string;

  public:
    using size_type = string::size_type;
    using iterator  = byte*;

    string_builder(::byte* s);
    explicit string_builder(const string& s);
    string_builder(size_type capacity);
    ~string_builder();

    string as_view() const noexcept;
    size_type length() const;

    iterator begin() const;
    iterator end() const;

    string::builder operator+(const string& other) const;
    string::builder operator+(const string::builder& other) const;
    string::builder& operator+=(const string& other);
    string::builder& operator+=(const string::builder& other);

    string substring(size_type end) const noexcept;
    string substring(size_type start, size_type end) const noexcept;

  private:
    constexpr string_builder(::byte* s, size_type s_len);

    byte* _data         = nullptr;
    size_type _len      = 0;
    size_type _capacity = 0;
    bool _allocated     = false;
};

constexpr string::string(const byte* s, string::size_type s_len) noexcept : _data(s), _len(s_len) {};

constexpr string string_literals::operator""_sv(const byte* s, size_type s_len) noexcept
{
    return string(s, s_len);
}
}  // namespace sv

#ifndef NO_OSTREAM
#    include <ostream>

std::ostream& operator<<(std::ostream& os, sv::string s);
std::ostream& operator<<(std::ostream& os, sv::string::builder s);
#endif

#endif
