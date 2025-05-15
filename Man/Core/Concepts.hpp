/**
 * @File Concepts.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/5/15
 * @Brief This file is part of Man.
 */
 
#pragma once

#include "Man/Core/Forward.hpp"
#include <concepts>

namespace man {

// clang-format off
template<typename T> concept cBoolType = std::is_same_v<bool, T>;
template<typename T> concept cU32Type  = std::is_same_v<u32, T>;
template<typename T> concept cU64Type  = std::is_same_v<u64, T>;
template<typename T> concept cF32Type  = std::is_same_v<f32, T>;
template<typename T> concept cF64Type  = std::is_same_v<f64, T>;

template<typename T> concept cSignedType     = std::is_signed_v<T>;
template<typename T> concept cUnsignedType   = std::is_unsigned_v<T>;
template<typename T> concept cIntegralType   = std::is_integral_v<T>;
template<typename T> concept cFloatType      = std::is_floating_point_v<T>;
template<typename T> concept cArithmeticType = std::is_arithmetic_v<T>;
// clang-format on

} // namespace man