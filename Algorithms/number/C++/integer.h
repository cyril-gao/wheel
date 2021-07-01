#ifndef BIG_INTEGER_H_DC0443B6_D69B_40DE_928F_AF04576FC939
#define BIG_INTEGER_H_DC0443B6_D69B_40DE_928F_AF04576FC939

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <openssl/bn.h>

#include <array>
#include <concepts>
#include <new>
#include <string>
#include <vector>
#include <stdexcept>


class BigInteger
{
    struct AutoBigNum
    {
        BIGNUM* value;
        AutoBigNum() : value(BN_new())
        {
            if (value == nullptr) {
                throw std::bad_alloc();
            }
        }
        AutoBigNum(BIGNUM* p) : value(p) {}
        ~AutoBigNum() { BN_free(value); }
        BIGNUM* release()
        {
            BIGNUM* retval = value;
            value = nullptr;
            return retval;
        }
    };

    struct AutoCtx
    {
        mutable BN_CTX* value;
        AutoCtx() : value(BN_CTX_new())
        {
            if (value == nullptr) {
                throw std::bad_alloc();
            }
        }
        explicit AutoCtx(BN_CTX* p) : value(p)
        {
        }
        ~AutoCtx()
        {
            BN_CTX_free(value);
        }
        AutoCtx(const AutoCtx&) : value(nullptr) {}
        AutoCtx(AutoCtx&& other) : value(other.value)
        {
            other.value = nullptr;
        }
        AutoCtx& operator=(const AutoCtx&) { return *this; }
        AutoCtx& operator=(AutoCtx&& other)
        {
            swap(other);
            return *this;
        }
        void init() const
        {
            if (value == nullptr) {
                value = BN_CTX_new();
                if (value == nullptr) {
                    throw std::bad_alloc();
                }
            }
        }
        void swap(AutoCtx& other) const
        {
            using std::swap;
            swap(value, other.value);
        }
        bool is_null() const { return value == nullptr; }
    };

    BIGNUM* m_bignum;
    mutable AutoCtx m_ctx;

    BigInteger(BIGNUM* bignum) : m_bignum(bignum), m_ctx(nullptr)
    {
        assert(bignum != nullptr);
    }

    void swap(BigInteger&& other)
    {
        BN_swap(m_bignum, other.m_bignum);
    }

    static BN_CTX* get_ctx_ptr(const BigInteger& a, const BigInteger& b)
    {
        BN_CTX* retval = nullptr;
        if (!b.m_ctx.is_null()) {
            retval = b.m_ctx.value;
        } else {
            if (a.m_ctx.is_null()) {
                a.m_ctx.init();
            }
            retval = a.m_ctx.value;
        }
        return retval;
    }
    static BN_CTX* get_ctx_ptr(const BigInteger& a, const BigInteger& b, const BigInteger& c)
    {
        BN_CTX* retval = nullptr;
        if (!b.m_ctx.is_null()) {
            retval = b.m_ctx.value;
        } else if (!c.m_ctx.is_null()) {
            retval = c.m_ctx.value;
        } else {
            if (a.m_ctx.is_null()) {
                a.m_ctx.init();
            }
            retval = a.m_ctx.value;
        }
        return retval;
    }


    static std::array<BigInteger, 3> euclid(const BigInteger& a, const BigInteger& b)
    {
        assert(!a.is_negative() && !b.is_negative());
        assert(a >= b);
        if (!b.is_zero()) {
            auto dr = a.div(b);
            auto result = euclid(b, dr[1]);
            return std::array<BigInteger, 3> {
                result[0], result[2], result[1] - dr[0] * result[2]
            };
        } else {
            return std::array<BigInteger, 3>{a, BigInteger(1U), BigInteger()};
        }
    }
public:
    BigInteger() : m_bignum(BN_new()), m_ctx(nullptr)
    {
        if (m_bignum != nullptr) {
            BN_zero(m_bignum);
        } else {
            throw std::bad_alloc();
        }
    }
    ~BigInteger() { BN_clear_free(m_bignum); }
    explicit BigInteger(const char * value, int radix = 10) : m_bignum(nullptr), m_ctx(nullptr)
    {
        if (value == nullptr || value[0] == '\0') {
            value = "0";
        }
        if (radix == 10) {
            if (BN_dec2bn(&m_bignum, value) == 0) {
                throw std::invalid_argument(std::string("Bad argument: ") + value);
            }
        } else if (radix == 16) {
            if (BN_hex2bn(&m_bignum, value) == 0) {
                throw std::invalid_argument(std::string("Bad argument: ") + value);
            }
        } else {
            throw std::invalid_argument("Until now the value of radix must be 10 or 16");
        }
    }
    explicit BigInteger(const void * value, size_t length) : // always positive
        m_bignum(
            BN_bin2bn(
                static_cast<const unsigned char *>(value),
                static_cast<int>(length),
                nullptr
            )
        ),
        m_ctx(nullptr)
    {
        if (m_bignum == nullptr) {
            throw std::runtime_error("Failed to create an integral from the byte array");
        }
    }
    explicit BigInteger(std::integral auto value) : m_bignum(BN_new()), m_ctx(nullptr)
    {
        if (m_bignum != nullptr) {
            if (value >= 0) {
                BN_set_word(m_bignum, value);
            } else {
                BN_set_word(m_bignum, -value);
                BN_set_negative(m_bignum, 1);
            }
        } else {
            throw std::bad_alloc();
        }
    }
    explicit BigInteger(std::unsigned_integral auto value) : m_bignum(BN_new()), m_ctx(nullptr)
    {
        if (m_bignum != nullptr) {
            BN_set_word(m_bignum, value);
        } else {
            throw std::bad_alloc();
        }
    }
    explicit BigInteger(const std::string& value, int radix = 10) : BigInteger(value.c_str(), radix)
    {
    }
    BigInteger(const BigInteger& other) : m_bignum(BN_dup(other.m_bignum)), m_ctx(nullptr)
    {
        if (m_bignum == nullptr) {
            throw std::bad_alloc();
        }
    }
    BigInteger(BigInteger&& other) : m_bignum(other.m_bignum), m_ctx(other.m_ctx)
    {
        other.m_bignum = nullptr;
    }
    BigInteger& operator=(const BigInteger& other)
    {
        if (this != &other) {
            BN_copy(m_bignum, other.m_bignum);
        }
        return *this;
    }
    BigInteger& operator=(BigInteger&& other)
    {
        if (this != &other) {
            BN_free(m_bignum);
            m_bignum = other.m_bignum;
            other.m_bignum = nullptr;
            m_ctx = std::move(other.m_ctx);
        }
        return *this;
    }
    void swap(BigInteger& other)
    {
        BN_swap(m_bignum, other.m_bignum);
        m_ctx.swap(other.m_ctx);
    }
    BigInteger& operator=(const std::string& other)
    {
        swap(BigInteger(other));
        return *this;
    }
    BigInteger& operator=(const char * other)
    {
        swap(BigInteger(other));
        return *this;
    }
    BigInteger& operator=(std::integral auto value)
    {
        swap(BigInteger(value));
        return *this;
    }
    BigInteger& operator=(std::unsigned_integral auto value)
    {
        swap(BigInteger(value));
        return *this;
    }


    size_t get_num_bytes() const
    {
        return BN_num_bytes(m_bignum);
    }


    size_t get_num_bits() const
    {
        return BN_num_bits(m_bignum);
    }


    explicit operator std::string() const
    {
        std::string retval;
        auto s = BN_bn2dec(m_bignum);
        if (s != nullptr) {
            retval.assign(s);
            OPENSSL_free(s);
        }
        return retval;
    }
    
    
    explicit operator std::vector<unsigned char>() const
    {
        std::vector<unsigned char> retval(get_num_bytes());
        BN_bn2bin(m_bignum, &retval[0]);
        return retval;
    }


    explicit operator size_t() const
    {
        return static_cast<size_t>(BN_get_word(m_bignum));
    }


    bool is_zero() const
    {
        return BN_is_zero(m_bignum);
    }


    bool is_one() const
    {
        return BN_is_one(m_bignum);
    }


    bool is_odd() const
    {
        return BN_is_odd(m_bignum);
    }


    bool is_even() const
    {
        return !BN_is_odd(m_bignum);
    }


    bool is_negative() const
    {
        return BN_is_negative(m_bignum);
    }


    bool operator==(const BigInteger& other) const
    {
        return (
            m_bignum == other.m_bignum ||
            BN_cmp(m_bignum, other.m_bignum) == 0
        );
    }
    bool operator==(const std::string& other) const
    {
        return static_cast<std::string>(*this) == other;
    }
    bool operator==(const char * other) const
    {
        auto str = static_cast<std::string>(*this);
        return strcmp(str.c_str(), other) == 0;
    }
    bool operator==(std::integral auto value) const
    {
        return operator==(BigInteger(value));
    }
    bool operator==(std::unsigned_integral auto value) const
    {
        return operator==(BigInteger(value));
    }


    bool operator!=(const BigInteger& other) const
    {
        return !operator==(other);
    }
    bool operator!=(const std::string& other) const
    {
        return !operator==(other);
    }
    bool operator!=(const char * other) const
    {
        return !operator==(other);
    }
    bool operator!=(std::integral auto value) const
    {
        return !operator==(value);
    }
    bool operator!=(std::unsigned_integral auto value) const
    {
        return !operator==(value);
    }


    bool operator>(const BigInteger& other) const
    {
        return (m_bignum != other.m_bignum && BN_cmp(m_bignum, other.m_bignum) > 0);
    }
    bool operator>(const std::string& other) const
    {
        return operator>(BigInteger(other));
    }
    bool operator>(const char * other) const
    {
        return operator>(BigInteger(other));
    }
    bool operator>(std::integral auto value) const
    {
        return operator>(BigInteger(value));
    }
    bool operator>(std::unsigned_integral auto value) const
    {
        return operator>(BigInteger(value));
    }


    bool operator<=(const BigInteger& other) const
    {
        return !operator>(other);
    }
    bool operator<=(const std::string& other) const
    {
        return operator<=(BigInteger(other));
    }
    bool operator<=(const char * other) const
    {
        return operator<=(BigInteger(other));
    }
    bool operator<=(std::integral auto value) const
    {
        return operator<=(BigInteger(value));
    }
    bool operator<=(std::unsigned_integral auto value) const
    {
        return operator<=(BigInteger(value));
    }


    bool operator>=(const BigInteger& other) const
    {
        return (m_bignum == other.m_bignum || BN_cmp(m_bignum, other.m_bignum) >= 0);
    }
    bool operator>=(const std::string& other) const
    {
        return operator>=(BigInteger(other));
    }
    bool operator>=(const char * other) const
    {
        return operator>=(BigInteger(other));
    }
    bool operator>=(std::integral auto value) const
    {
        return operator>=(BigInteger(value));
    }
    bool operator>=(std::unsigned_integral auto value) const
    {
        return operator>=(BigInteger(value));
    }


    bool operator<(const BigInteger& other) const
    {
        return (m_bignum != other.m_bignum || BN_cmp(m_bignum, other.m_bignum) < 0);
    }
    bool operator<(const std::string& other) const
    {
        return operator<(BigInteger(other));
    }
    bool operator<(const char * other) const
    {
        return operator<(BigInteger(other));
    }
    bool operator<(std::integral auto value) const
    {
        return operator<(BigInteger(value));
    }
    bool operator<(std::unsigned_integral auto value) const
    {
        return operator<(BigInteger(value));
    }


    BigInteger& operator+=(std::unsigned_integral auto value)
    {
        if (BN_add_word(m_bignum, value) != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to add the two integers");
        }
    }
    BigInteger& operator-=(std::unsigned_integral auto value)
    {
        if (BN_sub_word(m_bignum, value) != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to sub the two integers");
        }
    }
    BigInteger& operator*=(std::unsigned_integral auto value)
    {
        if (BN_mul_word(m_bignum, value) != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to mul the two integers");
        }
    }
    BigInteger& operator/=(std::unsigned_integral auto value)
    {
        if (BN_div_word(m_bignum, value) != static_cast<BN_ULONG>(-1)) {
            return *this;
        } else {
            throw std::runtime_error("Failed to div the two integers");
        }
    }
    BigInteger& operator%=(std::unsigned_integral auto value)
    {
        auto result = BN_mod_word(m_bignum, value);
        if (result != static_cast<BN_ULONG>(-1) && BN_set_word(m_bignum, result) != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to mod the two integers");
        }
    }


    BigInteger operator+(const BigInteger& other) const
    {
        AutoBigNum result;
        if (BN_add(result.value, m_bignum, other.m_bignum) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to add the two integers");
        }
    }
    BigInteger operator+(const std::string& other) const
    {
        return operator+(BigInteger(other));
    }
    BigInteger operator+(const char * other) const
    {
        return operator+(BigInteger(other));
    }
    BigInteger operator+(std::integral auto value) const
    {
        return operator+(BigInteger(value));
    }
    BigInteger operator+(std::unsigned_integral auto value) const
    {
        BigInteger copy(*this);
        copy += value;
        return copy;
    }

    BigInteger& operator+=(const BigInteger& other)
    {
        if (BN_add(m_bignum, m_bignum, other.m_bignum) != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to add the two integers");
        }
    }
    BigInteger& operator+=(const std::string& other)
    {
        return operator+=(BigInteger(other));
    }
    BigInteger& operator+=(const char * other)
    {
        return operator+=(BigInteger(other));
    }
    BigInteger& operator+=(std::integral auto value)
    {
        return operator+=(BigInteger(value));
    }


    BigInteger operator-(const BigInteger& other) const
    {
        AutoBigNum result;
        if (BN_sub(result.value, m_bignum, other.m_bignum) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to sub the two integers");
        }
    }
    BigInteger operator-(const std::string& other) const
    {
        return operator-(BigInteger(other));
    }
    BigInteger operator-(const char * other) const
    {
        return operator-(BigInteger(other));
    }
    BigInteger operator-(std::integral auto value) const
    {
        return operator-(BigInteger(value));
    }
    BigInteger operator-(std::unsigned_integral auto value) const
    {
        BigInteger copy(*this);
        copy -= value;
        return copy;
    }

    BigInteger& operator-=(const BigInteger& other)
    {
        if (BN_sub(m_bignum, m_bignum, other.m_bignum) != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to sub the two integers");
        }
    }
    BigInteger& operator-=(const std::string& other)
    {
        return operator-=(BigInteger(other));
    }
    BigInteger& operator-=(const char * other)
    {
        return operator-=(BigInteger(other));
    }
    BigInteger& operator-=(std::integral auto value)
    {
        return operator-=(BigInteger(value));
    }


    BigInteger operator*(const BigInteger& other) const
    {
        AutoBigNum result;
        if (BN_mul(result.value, m_bignum, other.m_bignum, get_ctx_ptr(*this, other)) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to multiply the two integers");
        }
    }
    BigInteger operator*(const std::string& other) const
    {
        return operator*(BigInteger(other));
    }
    BigInteger operator*(const char * other) const
    {
        return operator*(BigInteger(other));
    }
    BigInteger operator*(std::integral auto value) const
    {
        return operator*(BigInteger(value));
    }
    BigInteger operator*(std::unsigned_integral auto value) const
    {
        BigInteger copy(*this);
        copy *= value;
        return copy;
    }

    BigInteger& operator*=(const BigInteger& other)
    {
        if (BN_mul(m_bignum, m_bignum, other.m_bignum, get_ctx_ptr(*this, other)) != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to multiply the two integers");
        }
    }
    BigInteger& operator*=(const std::string& other)
    {
        return operator*=(BigInteger(other));
    }
    BigInteger& operator*=(const char * other)
    {
        return operator*=(BigInteger(other));
    }
    BigInteger& operator*=(std::integral auto value)
    {
        return operator*=(BigInteger(value));
    }


    std::array<BigInteger, 2> div(const BigInteger& other) const
    {
        AutoBigNum d, r;
        if (BN_div(d.value, r.value, m_bignum, other.m_bignum, get_ctx_ptr(*this, other)) != 0) {
            return std::array<BigInteger, 2>{BigInteger(d.release()), BigInteger(r.release())};
        } else {
            throw std::runtime_error("Failed to divide the two integers");
        }
    }
    BigInteger operator/(const BigInteger& other) const
    {
        AutoBigNum result;
        if (BN_div(result.value, nullptr, m_bignum, other.m_bignum, get_ctx_ptr(*this, other)) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to divide the two integers");
        }
    }
    BigInteger operator/(const std::string& other) const
    {
        return operator/(BigInteger(other));
    }
    BigInteger operator/(const char * other) const
    {
        return operator/(BigInteger(other));
    }
    BigInteger operator/(std::integral auto other) const
    {
        return operator/(BigInteger(other));
    }
    BigInteger operator/(std::unsigned_integral auto other) const
    {
        BigInteger copy(*this);
        copy /= other;
        return copy;
    }

    BigInteger& operator/=(const BigInteger& other)
    {
        if (BN_div(m_bignum, nullptr, m_bignum, other.m_bignum, get_ctx_ptr(*this, other)) != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to divide the two integers");
        }
    }
    BigInteger& operator/=(const std::string& other)
    {
        return operator/=(BigInteger(other));
    }
    BigInteger& operator/=(const char * other)
    {
        return operator/=(BigInteger(other));
    }
    BigInteger& operator/=(std::integral auto other)
    {
        return operator/=(BigInteger(other));
    }


    BigInteger operator%(const BigInteger& other) const
    {
        AutoBigNum result;
        if (BN_mod(result.value, m_bignum, other.m_bignum, get_ctx_ptr(*this, other)) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to mod the two integers");
        }
    }
    BigInteger operator%(const std::string& other) const
    {
        return operator%(BigInteger(other));
    }
    BigInteger operator%(const char * other) const
    {
        return operator%(BigInteger(other));
    }
    BigInteger operator%(std::integral auto other) const
    {
        return operator%(BigInteger(other));
    }
    BigInteger operator%(std::unsigned_integral auto other) const
    {
        BigInteger copy(*this);
        copy %= other;
        return copy;
    }


    BigInteger mod(const BigInteger& other) const
    {
        AutoBigNum result;
        if (BN_nnmod(result.value, m_bignum, other.m_bignum, get_ctx_ptr(*this, other)) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to mod the two integers");
        }
    }
    BigInteger mod(const std::string& other) const
    {
        return mod(BigInteger(other));
    }
    BigInteger mod(const char * other) const
    {
        return mod(BigInteger(other));
    }
    BigInteger mod(std::integral auto other) const
    {
        return mod(BigInteger(other));
    }
    BigInteger mod(std::unsigned_integral auto other) const
    {
        return mod(BigInteger(other));
    }


    BigInteger sqr() const
    {
        AutoBigNum result;
        m_ctx.init();
        if (BN_sqr(result.value, m_bignum, m_ctx.value) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to sqr the integer");
        }
    }


    BigInteger exp(const BigInteger& exponent) const
    {
        AutoBigNum result;
        if (BN_exp(result.value, m_bignum, exponent.m_bignum, get_ctx_ptr(*this, exponent)) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to raise the integer to the specific power");
        }
    }
    BigInteger exp(const std::string& exponent) const
    {
        return exp(BigInteger(exponent));
    }
    BigInteger exp(const char* exponent) const
    {
        return exp(BigInteger(exponent));
    }
    BigInteger exp(std::integral auto exponent) const
    {
        return exp(BigInteger(exponent));
    }
    BigInteger exp(std::unsigned_integral auto exponent) const
    {
        return exp(BigInteger(exponent));
    }


    BigInteger operator-() const
    {
        BigInteger retval(*this);
        BN_set_negative(retval.m_bignum, BN_is_negative(retval.m_bignum));
        return retval;
    }


    BigInteger& operator++()
    {
        return operator+=(1U);
    }
    BigInteger& operator--()
    {
        return operator-=(1U);
    }
    BigInteger operator++(int)
    {
        BigInteger retval(*this);
        operator+=(1U);
        return retval;
    }
    BigInteger operator--(int)
    {
        BigInteger retval(*this);
        operator-=(1U);
        return retval;
    }


    BigInteger& set_bit(size_t n)
    {
        if (BN_set_bit(m_bignum, static_cast<int>(n)) != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to set the n in the integer to 1");
        }
    }
    BigInteger& clear_bit(size_t n)
    {
        if (BN_clear_bit(m_bignum, static_cast<int>(n)) != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to set the n in the integer to 1");
        }
    }
    bool is_bit_set(size_t n) const
    {
        return BN_is_bit_set(m_bignum, static_cast<int>(n));
    }
    BigInteger& mask_bits(size_t n)
    {
        if (BN_mask_bits(m_bignum, static_cast<int>(n)) != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to truncate the integer to a n bit integer");
        }
    }
    BigInteger operator<<(size_t n) const
    {
        int errcode = 0;
        AutoBigNum result;
        if (n == 1) {
            errcode = BN_lshift1(result.value, m_bignum);
        } else {
            errcode = BN_lshift(result.value, m_bignum, static_cast<int>(n));
        }
        if (errcode != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to shift the integer left by n bits");
        }
    }
    BigInteger& operator<<=(size_t n)
    {
        int errcode = 0;
        if (n == 1) {
            errcode = BN_lshift1(m_bignum, m_bignum);
        } else {
            errcode = BN_lshift(m_bignum, m_bignum, static_cast<int>(n));
        }
        if (errcode != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to shift the integer left by n bits");
        }
    }
    BigInteger operator>>(size_t n) const //if it is negative, the result is a litter different
    {
        int errcode = 0;
        AutoBigNum result;
        if (n == 1) {
            errcode = BN_rshift1(result.value, m_bignum);
        } else {
            errcode = BN_rshift(result.value, m_bignum, static_cast<int>(n));
        }
        if (errcode != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to shift the integer right by n bits");
        }
    }
    BigInteger& operator>>=(size_t n)
    {
        int errcode = 0;
        AutoBigNum result;
        if (n == 1) {
            errcode = BN_rshift1(m_bignum, m_bignum);
        } else {
            errcode = BN_rshift(m_bignum, m_bignum, static_cast<int>(n));
        }
        if (errcode != 0) {
            return *this;
        } else {
            throw std::runtime_error("Failed to shift the integer right by n bits");
        }
    }


    ///////////////////////////////////////////////////////////////////////
    friend bool operator==(const std::string& lhs, const BigInteger& rhs)
    {
        return rhs.operator==(lhs);
    }
    friend bool operator!=(const std::string& lhs, const BigInteger& rhs)
    {
        return rhs.operator!=(lhs);
    }
    friend bool operator>(const std::string& lhs, const BigInteger& rhs)
    {
        return rhs < lhs;
    }
    friend bool operator>=(const std::string& lhs, const BigInteger& rhs)
    {
        return rhs <= lhs;
    }
    friend bool operator<(const std::string& lhs, const BigInteger& rhs)
    {
        return rhs > lhs;
    }
    friend bool operator<=(const std::string& lhs, const BigInteger& rhs)
    {
        return rhs >= lhs;
    }
    friend BigInteger operator+(const std::string& lhs, const BigInteger& rhs)
    {
        return rhs.operator+(lhs);
    }
    friend BigInteger operator-(const std::string& lhs, const BigInteger& rhs)
    {
        return BigInteger(lhs) - rhs;
    }
    friend BigInteger operator*(const std::string& lhs, const BigInteger& rhs)
    {
        return rhs * lhs;
    }
    friend BigInteger operator/(const std::string& lhs, const BigInteger& rhs)
    {
        return BigInteger(lhs) / rhs;
    }
    friend BigInteger operator%(const std::string& lhs, const BigInteger& rhs)
    {
        return BigInteger(lhs) % rhs;
    }


    friend bool operator==(const char* lhs, const BigInteger& rhs)
    {
        return rhs.operator==(lhs);
    }
    friend bool operator!=(const char* lhs, const BigInteger& rhs)
    {
        return rhs.operator!=(lhs);
    }
    friend bool operator>(const char* lhs, const BigInteger& rhs)
    {
        return rhs < lhs;
    }
    friend bool operator>=(const char* lhs, const BigInteger& rhs)
    {
        return rhs <= lhs;
    }
    friend bool operator<(const char* lhs, const BigInteger& rhs)
    {
        return rhs > lhs;
    }
    friend bool operator<=(const char* lhs, const BigInteger& rhs)
    {
        return rhs >= lhs;
    }
    friend BigInteger operator+(const char* lhs, const BigInteger& rhs)
    {
        return rhs.operator+(lhs);
    }
    friend BigInteger operator-(const char* lhs, const BigInteger& rhs)
    {
        return BigInteger(lhs) - rhs;
    }
    friend BigInteger operator*(const char* lhs, const BigInteger& rhs)
    {
        return rhs * lhs;
    }
    friend BigInteger operator/(const char* lhs, const BigInteger& rhs)
    {
        return BigInteger(lhs) / rhs;
    }
    friend BigInteger operator%(const char* lhs, const BigInteger& rhs)
    {
        return BigInteger(lhs) % rhs;
    }


    friend bool operator==(std::integral auto lhs, const BigInteger& rhs)
    {
        return rhs.operator==(lhs);
    }
    friend bool operator!=(std::integral auto lhs, const BigInteger& rhs)
    {
        return rhs.operator!=(lhs);
    }
    friend bool operator>(std::integral auto lhs, const BigInteger& rhs)
    {
        return rhs < lhs;
    }
    friend bool operator>=(std::integral auto lhs, const BigInteger& rhs)
    {
        return rhs <= lhs;
    }
    friend bool operator<(std::integral auto lhs, const BigInteger& rhs)
    {
        return rhs > lhs;
    }
    friend bool operator<=(std::integral auto lhs, const BigInteger& rhs)
    {
        return rhs >= lhs;
    }
    friend BigInteger operator+(std::integral auto lhs, const BigInteger& rhs)
    {
        return rhs.operator+(lhs);
    }
    friend BigInteger operator-(std::integral auto lhs, const BigInteger& rhs)
    {
        return BigInteger(lhs) - rhs;
    }
    friend BigInteger operator*(std::integral auto lhs, const BigInteger& rhs)
    {
        return rhs * lhs;
    }
    friend BigInteger operator/(std::integral auto lhs, const BigInteger& rhs)
    {
        return BigInteger(lhs) / rhs;
    }
    friend BigInteger operator%(std::integral auto lhs, const BigInteger& rhs)
    {
        return BigInteger(lhs) % rhs;
    }


    friend bool operator==(std::unsigned_integral auto lhs, const BigInteger& rhs)
    {
        return rhs.operator==(lhs);
    }
    friend bool operator!=(std::unsigned_integral auto lhs, const BigInteger& rhs)
    {
        return rhs.operator!=(lhs);
    }
    friend bool operator>(std::unsigned_integral auto lhs, const BigInteger& rhs)
    {
        return rhs < lhs;
    }
    friend bool operator>=(std::unsigned_integral auto lhs, const BigInteger& rhs)
    {
        return rhs <= lhs;
    }
    friend bool operator<(std::unsigned_integral auto lhs, const BigInteger& rhs)
    {
        return rhs > lhs;
    }
    friend bool operator<=(std::unsigned_integral auto lhs, const BigInteger& rhs)
    {
        return rhs >= lhs;
    }
    friend BigInteger operator+(std::unsigned_integral auto lhs, const BigInteger& rhs)
    {
        return rhs.operator+(lhs);
    }
    friend BigInteger operator-(std::unsigned_integral auto lhs, const BigInteger& rhs)
    {
        return BigInteger(lhs) - rhs;
    }
    friend BigInteger operator*(std::unsigned_integral auto lhs, const BigInteger& rhs)
    {
        return rhs * lhs;
    }
    friend BigInteger operator/(std::unsigned_integral auto lhs, const BigInteger& rhs)
    {
        return BigInteger(lhs) / rhs;
    }
    friend BigInteger operator%(std::unsigned_integral auto lhs, const BigInteger& rhs)
    {
        return BigInteger(lhs) % rhs;
    }


    friend BigInteger mod_add(const BigInteger& a, const BigInteger& b, const BigInteger& m)
    {
        AutoBigNum result;
        auto ctx_ptr = get_ctx_ptr(a, b, m);
        if (BN_mod_add(result.value, a.m_bignum, b.m_bignum, m.m_bignum, ctx_ptr) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to do (a + b) % m");
        }
    }

    friend BigInteger mod_sub(const BigInteger& a, const BigInteger& b, const BigInteger& m)
    {
        AutoBigNum result;
        auto ctx_ptr = get_ctx_ptr(a, b, m);
        if (BN_mod_sub(result.value, a.m_bignum, b.m_bignum, m.m_bignum, ctx_ptr) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to do (a - b) % m");
        }
    }

    friend BigInteger mod_mul(const BigInteger& a, const BigInteger& b, const BigInteger& m)
    {
        AutoBigNum result;
        auto ctx_ptr = get_ctx_ptr(a, b, m);
        if (BN_mod_mul(result.value, a.m_bignum, b.m_bignum, m.m_bignum, ctx_ptr) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to do (a * b) % m");
        }
    }

    friend BigInteger mod_sqr(const BigInteger& a, const BigInteger& m)
    {
        AutoBigNum result;
        auto ctx_ptr = get_ctx_ptr(a, m);
        if (BN_mod_sqr(result.value, a.m_bignum, m.m_bignum, ctx_ptr) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to do (a * a) % m");
        }
    }

    friend BigInteger mod_exp(const BigInteger& a, const BigInteger& p, const BigInteger& m)
    {
        AutoBigNum result;
        auto ctx_ptr = get_ctx_ptr(a, p, m);
        if (BN_mod_exp(result.value, a.m_bignum, p.m_bignum, m.m_bignum, ctx_ptr) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to do (a ** b) % m");
        }
    }

    friend BigInteger mod_inverse(const BigInteger& a, const BigInteger& m)
    {
        AutoBigNum result;
        auto ctx_ptr = get_ctx_ptr(a, m);
        if (BN_mod_inverse(result.value, a.m_bignum, m.m_bignum, ctx_ptr) != nullptr) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to compute the inverse of a modulo m");
        }
    }

    friend BigInteger gcd(const BigInteger& a, const BigInteger& b)
    {
        AutoBigNum result;
        auto ctx_ptr = get_ctx_ptr(a, b);
        if (BN_gcd(result.value, a.m_bignum, b.m_bignum, ctx_ptr) != 0) {
            return BigInteger(result.release());
        } else {
            throw std::runtime_error("Failed to compute the greatest common divisor of a and b");
        }
    }

    /*
     * gcd = a * x + b * y
     * the first element in the return value is gcd;
     * the second element in the return value is x;
     * the third element in the return value is y.
     */
    friend std::array<BigInteger, 3> euclid(const BigInteger& a, const BigInteger& b)
    {
        auto make_sure_x_is_positive = [](const BigInteger& a, const BigInteger& b, std::array<BigInteger, 3>&& result) {
            while (result[1].is_negative()) {
                result[1] += b;
                result[2] -= a;
            }
            return result;
        };
        if (a >= b) {
            return make_sure_x_is_positive(a, b, BigInteger::euclid(a, b));
        } else {
            auto result = BigInteger::euclid(b, a);
            result[1].swap(result[2]);
            return make_sure_x_is_positive(a, b, std::move(result));
        }
    }


    friend std::string to_string(const BigInteger& n)
    {
        return static_cast<std::string>(n);
    }
};

#endif // BIG_INTEGER_H_DC0443B6_D69B_40DE_928F_AF04576FC939
