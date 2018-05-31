/** @file exprtk_unum_posit_adaptop.hpp

    @brief Provides an exprtk adaptor for the Unum Posit arithmetic
    type

    This file is part of the G+Smo library. 

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    
    Author(s): M. Moller
*/

#pragma once

#include <string>
#include <gsUnum/gsUnum.h>

typedef sw::unum::posit<32,2> posit_32_2;

namespace exprtk
{

namespace details
{
namespace numeric { namespace details { struct unum_posit_type_tag; } }

inline bool is_true (const posit_32_2& v);
inline bool is_false(const posit_32_2& v);

template <typename Iterator>
inline bool string_to_real(Iterator& itr_external, const Iterator end, posit_32_2& t, numeric::details::unum_posit_type_tag);

}

namespace helper
{
namespace details
{
inline void print_type(const std::string&, const posit_32_2& v, exprtk::details::numeric::details::unum_posit_type_tag);
}
}

using details::is_true;
}

#include "exprtk.hpp"

namespace exprtk
{
namespace details
{

namespace constant_unum_posit
{
static const double e       =  2.71828182845904523536028747135266249775724709369996;
static const double pi      =  3.14159265358979323846264338327950288419716939937510;
static const double pi_2    =  1.57079632679489661923132169163975144209858469968755;
static const double pi_4    =  0.78539816339744830961566084581987572104929234984378;
static const double pi_180  =  0.01745329251994329576923690768488612713442871888542;
static const double _1_pi   =  0.31830988618379067153776752674502872406891929148091;
static const double _2_pi   =  0.63661977236758134307553505349005744813783858296183;
static const double _180_pi = 57.29577951308232087679815481410517033240547246656443;
static const double log2    =  0.69314718055994530941723212145817656807550013436026;
static const double sqrt2   =  1.41421356237309504880168872420969807856967187537695;
}

namespace numeric
{
namespace details
{
struct unum_posit_type_tag {};

template<> struct number_type<posit_32_2> { typedef unum_posit_type_tag type; };

template <>
struct epsilon_type<unum_posit_type_tag>
{
    static inline posit_32_2 value()
    {
        static const posit_32_2 epsilon = 
            std::numeric_limits<posit_32_2>::epsilon();
        return epsilon;
    }
};

inline bool is_nan_impl(const posit_32_2& v, unum_posit_type_tag)
{
    return v.isNaR();
}

template <typename T>
inline int to_int32_impl(const T& v, unum_posit_type_tag)
{
    return static_cast<int>(v);
    //return static_cast<int>(v.getValue());
}

template <typename T>
inline long long to_int64_impl(const T& v, unum_posit_type_tag)
{
    return static_cast<long long int>(v);
    //return static_cast<long long int>(v.getValue());
}

template <typename T> inline T   abs_impl(const T& v, unum_posit_type_tag) { return sw::unum::abs  (v); }
template <typename T> inline T  acos_impl(const T& v, unum_posit_type_tag) { return sw::unum::acos (v); }
template <typename T> inline T acosh_impl(const T& v, unum_posit_type_tag) { return sw::unum::acosh(v); }
template <typename T> inline T  asin_impl(const T& v, unum_posit_type_tag) { return sw::unum::asin (v); }
template <typename T> inline T asinh_impl(const T& v, unum_posit_type_tag) { return sw::unum::asinh(v); }
template <typename T> inline T  atan_impl(const T& v, unum_posit_type_tag) { return sw::unum::atan (v); }
template <typename T> inline T atanh_impl(const T& v, unum_posit_type_tag) { return sw::unum::atanh(v); }
template <typename T> inline T  ceil_impl(const T& v, unum_posit_type_tag) { return sw::unum::ceil (v); }
template <typename T> inline T   cos_impl(const T& v, unum_posit_type_tag) { return sw::unum::cos  (v); }
template <typename T> inline T  cosh_impl(const T& v, unum_posit_type_tag) { return sw::unum::cosh (v); }
template <typename T> inline T   exp_impl(const T& v, unum_posit_type_tag) { return sw::unum::exp  (v); }
template <typename T> inline T floor_impl(const T& v, unum_posit_type_tag) { return sw::unum::floor(v); }
template <typename T> inline T   log_impl(const T& v, unum_posit_type_tag) { return sw::unum::log  (v); }
template <typename T> inline T log10_impl(const T& v, unum_posit_type_tag) { return sw::unum::log10(v); }
template <typename T> inline T  log2_impl(const T& v, unum_posit_type_tag) { return sw::unum::log2 (v); }
template <typename T> inline T   neg_impl(const T& v, unum_posit_type_tag) { return -v;             }
template <typename T> inline T   pos_impl(const T& v, unum_posit_type_tag) { return  v;             }
template <typename T> inline T   sin_impl(const T& v, unum_posit_type_tag) { return sw::unum::sin  (v); }
template <typename T> inline T  sinh_impl(const T& v, unum_posit_type_tag) { return sw::unum::sinh (v); }
template <typename T> inline T  sqrt_impl(const T& v, unum_posit_type_tag) { return sw::unum::sqrt (v); }
template <typename T> inline T   tan_impl(const T& v, unum_posit_type_tag) { return sw::unum::tan  (v); }
template <typename T> inline T  tanh_impl(const T& v, unum_posit_type_tag) { return sw::unum::tanh (v); }
template <typename T> inline T   cot_impl(const T& v, unum_posit_type_tag) { return sw::unum::cot  (v); }
template <typename T> inline T   sec_impl(const T& v, unum_posit_type_tag) { return sw::unum::sec  (v); }
template <typename T> inline T   csc_impl(const T& v, unum_posit_type_tag) { return sw::unum::csc  (v); }
template <typename T> inline T   r2d_impl(const T& v, unum_posit_type_tag) { return (v  * exprtk::details::constant_unum_posit::_180_pi); }
template <typename T> inline T   d2r_impl(const T& v, unum_posit_type_tag) { return (v  * exprtk::details::constant_unum_posit::pi_180 ); }
template <typename T> inline T   d2g_impl(const T& v, unum_posit_type_tag) { return (v  * posit_32_2(20.0/9.0)); }
template <typename T> inline T   g2d_impl(const T& v, unum_posit_type_tag) { return (v  * posit_32_2(9.0/20.0)); }
template <typename T> inline T  notl_impl(const T& v, unum_posit_type_tag) { return (v != posit_32_2(0) ? posit_32_2(0) : posit_32_2(1)); }
template <typename T> inline T  frac_impl(const T& v, unum_posit_type_tag) { return sw::unum::frac (v); }
template <typename T> inline T trunc_impl(const T& v, unum_posit_type_tag) { return sw::unum::trunc(v); }

inline bool is_true_impl (const posit_32_2& v)
{
    return true;//0.0 != v;
    //return 0.0 != v.getValue();
}

inline bool is_false_impl(const posit_32_2& v)
{
    return !is_true_impl(v);
}

template <typename T>
inline T expm1_impl(const T& v, unum_posit_type_tag)
{
    return sw::unum::expm1(v);
}

template <typename T>
inline T min_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    //using std::min;
    return sw::unum::min(v0,v1);
}

template <typename T>
inline T max_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    //using std::max;
    return sw::unum::max(v0,v1);
}

template <typename T>
inline T nequal_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    const T epsilon  = epsilon_type<T>::value();
    const T eps_norm = (sw::unum::max(T(1),sw::unum::max(sw::unum::abs(v0),sw::unum::abs(v1))) * epsilon);
    return (sw::unum::abs(T(v0 - v1)) > eps_norm) ? T(1) : T(0);
}

template <typename T>
inline T sgn_impl(const T& v, unum_posit_type_tag)
{
    if (v > T(0)) return T(+1);
    else if (v < T(0)) return T(-1);
    else               return T( 0);
}

template <typename T>
inline T log1p_impl(const T& v, unum_posit_type_tag)
{
    return sw::unum::log1p(v);
}

template <typename T>
inline T erf_impl(const T& v, unum_posit_type_tag)
{
    return sw::unum::erf(v);
}

template <typename T>
inline T erfc_impl(const T& v, unum_posit_type_tag)
{
    return sw::unum::erfc(v);
}

template <typename T>
inline T ncdf_impl(const T& v, unum_posit_type_tag)
{
    T cnd = T(0.5) * (T(1) + erf_impl(
                          sw::unum::abs(v) /
                          T(exprtk::details::constant_unum_posit::sqrt2), unum_posit_type_tag()));
    return  (v < T(0)) ? (T(1) - cnd) : cnd;
}

template <typename T>
inline T modulus_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    std::cerr<<"modulus is not derivated\n";
    return T(std::fmod(v0,v1));
    //return T(std::fmod(v0.getValue(),v1.getValue()));
}

template <typename T>
inline T pow_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    return sw::unum::pow(v0, v1 );// note: exponent considered constant
    //return pow(v0, v1.getValue() );// note: exponent considered constant
}

template <typename T>
inline T logn_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    return sw::unum::log(v0) / sw::unum::log(v1);
}

template <typename T>
inline T sinc_impl(const T& v, unum_posit_type_tag)
{
    if (sw::unum::abs(v) >= epsilon_type<posit_32_2>::value())
        return(sw::unum::sin(v) / v);
    else
        return T(1);
}

template <typename T>
inline T xor_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    return (is_false_impl(v0) != is_false_impl(v1)) ? T(1) : T(0);
}

template <typename T>
inline T xnor_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    const bool v0_true = is_true_impl(v0);
    const bool v1_true = is_true_impl(v1);
    if ((v0_true &&  v1_true) || (!v0_true && !v1_true))
        return T(1);
    else
        return T(0);
}

template <typename T>
inline T equal_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    const T epsilon  = epsilon_type<T>::value();
    const T eps_norm = (sw::unum::max(T(1),sw::unum::max(sw::unum::abs(v0),sw::unum::abs(v1))) * epsilon);
    return (sw::unum::abs(T(v0-v1)) <= eps_norm) ? T(1) : T(0);
}

template <typename T>
inline T round_impl(const T& v, unum_posit_type_tag)
{
    return sw::unum::round(v);
}

template <typename T>
inline T roundn_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    const T p10 = pow(T(10),floor(v1));
    if (v0 < T(0))
        return T(sw::unum::ceil (T((v0 * p10) - T(0.5))) / p10);
    else
        return T(sw::unum::floor(T((v0 * p10) + T(0.5))) / p10);
}

template <typename T>
inline bool is_integer_impl(const T& v, unum_posit_type_tag)
{
    return std::ceil(v) == v;
    //return std::ceil(v.getValue()) == v.getValue();
}

template <typename T>
inline T root_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    return sw::unum::pow(v0,T(1) / v1);
}

template <typename T>
inline T hypot_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    return sw::unum::hypot(v0,v1);
}

template <typename T>
inline T atan2_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    return sw::unum::atan2(v0,v1);
}

template <typename T>
inline T shr_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    return v0 * (T(1) / sw::unum::pow(T(2.0),v1));
}

template <typename T>
inline T shl_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    return v0 * sw::unum::pow(T(2.0),v1);
}

template <typename T>
inline T and_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    return (is_true_impl(v0) && is_true_impl(v1)) ? T(1) : T(0);
}

template <typename T>
inline T nand_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    return (is_false_impl(v0) || is_false_impl(v1)) ? T(1) : T(0);
}

template <typename T>
inline T or_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    return (is_true_impl(v0) || is_true_impl(v1)) ? T(1) : T(0);
}

template <typename T>
inline T nor_impl(const T& v0, const T& v1, unum_posit_type_tag)
{
    return (is_false_impl(v0) && is_false_impl(v1)) ? T(1) : T(0);
}
}
}

template <typename Iterator>
inline bool string_to_real(Iterator& itr_external, 
                           const Iterator end, posit_32_2& t, 
                           numeric::details::unum_posit_type_tag)
{
    const std::string num(itr_external,end);
    t = ::atof(num.c_str());
    return true;
}

inline bool is_true (const posit_32_2& v) 
{ return details::numeric::details::is_true_impl (v); }

inline bool is_false(const posit_32_2& v) 
{ return details::numeric::details::is_false_impl(v); }
}

namespace helper
{
namespace details
{
inline void print_type(const std::string&, const posit_32_2& v, 
                       exprtk::details::numeric::details::unum_posit_type_tag)
{
    std::cout << pretty_print(v) << "\n";
    //printf("%f",v.getValue());
}
}
}
}