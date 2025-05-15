/**
 * @File Forward.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/5/15
 * @Brief This file is part of Man.
 */

#pragma once

#include "Man/Core/Defines.hpp"

namespace man {

// -------------------------
// Numerics Type Alias

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using u64  = uint64_t;
using uint = unsigned int;

using f32 = float;
using f64 = double;

using size = std::size_t;

#ifdef MAN_DOUBLE_PRECISION
using Real     = f64;
using RealBits = u64;
#else
using Real     = f32;
using RealBits = u32;
#endif // BEE_DOUBLE_PRECISION

static_assert(sizeof(Real) == sizeof(RealBits));

// -------------------------
// Type Declarations


} // namespace man