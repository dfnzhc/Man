/**
 * @File Defines.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/5/15
 * @Brief This file is part of Man.
 */

#pragma once

#include <cmath>
#include <cstddef>


// -------------------------
// Check C++ Standard

#if !defined(__cpp_concepts)
#  error "C++20 or newer standard is essential."
#endif

// -------------------------
// Invalid Some Defines

#ifdef max
#  undef max
#endif
#ifdef min
#  undef min
#endif
#ifdef isnan
#  undef isnan
#endif
#ifdef isinf
#  undef isinf
#endif
#ifdef log2
#  undef log2
#endif

// -------------------------
// Compiler

#if defined(_MSC_VER)
#  define MAN_COMPILER_MSVC 1
#elif defined(__clang__)
#  define MAN_COMPILER_CLANG 1
#elif defined(__GNUC__) && !defined(__clang__)
#  define MAN_COMPILER_GCC 1
#else
#  error Unknown Compiler
#endif

// -------------------------
// Platform

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
#  define MAN_PLATFORM_WINDOWS 1
#elif defined(__unix__) || defined(__unix) || defined(__linux__)
#  define MAN_PLATFORM_LINUX 1
#elif defined(__APPLE__) || defined(__MACH__)
#  define MAN_PLATFORM_MAC 1
#else
#  error Unknown Platform
#endif

// -------------------------
// CUDA

#if defined(__CUDA_ARCH__) || defined(__CUDACC__)
#  ifndef MAN_GPU_CODE
#    define MAN_GPU_CODE 1
#  endif
#  define MAN_GPU                __device__
#  define MAN_CPU                __host__
#  define MAN_INLINE             __forceinline__
#  define MAN_CONST              __device__ const
#  define CONST_STATIC_INIT(...) void(0) /* ignore */
#else
#  ifndef MAN_CPU_CODE
#    define MAN_CPU_CODE 1
#  endif
#  define MAN_GPU                /* ignore */
#  define MAN_CPU                /* ignore */
#  define MAN_CONST              const
#  define MAN_INLINE             inline
#  define CONST_STATIC_INIT(...) = __VA_ARGS__
#endif

#define MAN_FUNC MAN_CPU MAN_GPU

// -------------------------
// Utility Macros

// has builtin
#ifdef __has_builtin
#  define MAN_HAS_BUILTIN(x) __has_builtin(x)
#else
#  define MAN_HAS_BUILTIN(x) 0
#endif

// force inline
#if MAN_COMPILER_MSVC
#  define MAN_FORCE_INLINE __forceinline
#elif MAN_COMPILER_GCC || MAN_COMPILER_CLANG
#  define MAN_FORCE_INLINE __attribute__((always_inline)) inline
#else
#  define MAN_FORCE_INLINE inline
#endif

// no inline
#if MAN_COMPILER_MSVC
#  define MAN_NO_INLINE __declspec(noinline)
#elif MAN_COMPILER_GCC || MAN_COMPILER_CLANG
#  define MAN_NO_INLINE __attribute__((noinline))
#else
#  define MAN_NO_INLINE
#endif

// likely & unlikely
#if MAN_COMPILER_GCC || MAN_COMPILER_CLANG
#  define MAN_LIKELY(x)   __builtin_expect(!!(x), 1)
#  define MAN_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#  define MAN_LIKELY(x)   (x)
#  define MAN_UNLIKELY(x) (x)
#endif

// assume
#if MAN_COMPILER_MSVC
#  define MAN_ASSUME(condition) __assume(condition)

#elif MAN_COMPILER_CLANG
#  if MAN_HAS_BUILTIN(__builtin_assume)
#    define MAN_ASSUME(condition) __builtin_assume(condition)
#  else
#    define MAN_ASSUME(condition) do { if (!(condition)) __builtin_unreachable(); } while(0)
#  endif

#elif MAN_COMPILER_GCC
#  define MAN_ASSUME(condition) do { if (MAN_UNLIKELY(!(condition))) __builtin_unreachable(); } while(0)
#else
#  define MAN_ASSUME(condition) ((void)0)
#endif

// alignas
#if MAN_COMPILER_MSVC
#  define MAN_ALIGNAS(N) __declspec(align(N))
#elif MAN_COMPILER_GCC || MAN_COMPILER_CLANG
#  define MAN_ALIGNAS(N) __attribute__((aligned(N)))
#else
#  define MAN_ALIGNAS(N) alignas(N)
#endif

// debug break
#if (defined(_DEBUG) || !defined(NDEBUG)) && MAN_CPU_CODE // Debug break in device code is tricky/different

#  if MAN_PLATFORM_WINDOWS && MAN_COMPILER_MSVC
#    define MAN_DEBUG_BREAK() __debugbreak()
#  elif MAN_COMPILER_GCC
#    if MAN_HAS_BUILTIN(__builtin_trap)
#      define MAN_DEBUG_BREAK() __builtin_trap()
#    else
#      define MAN_DEBUG_BREAK() __asm__ volatile("int $0x03")
#    endif

#  elif MAN_COMPILER_CLANG
#    if MAN_HAS_BUILTIN(__builtin_debugtrap)
#      define MAN_DEBUG_BREAK() __builtin_debugtrap()
#    else
#      define MAN_DEBUG_BREAK() __asm__ volatile("int $0x03")
#    endif

#  else
#    include <cassert> // Required for assert
#    define MAN_DEBUG_BREAK() assert(false && "MAN_DEBUG_BREAK: Reached generic breakpoint")
#  endif

#else
#  define MAN_DEBUG_BREAK() ((void)0) // No-op in release or CUDA device code by default
#endif

// restrict
#if MAN_COMPILER_MSVC
#  define MAN_RESTRICT __restrict
#elif MAN_COMPILER_GCC || MAN_COMPILER_CLANG
#  define MAN_RESTRICT __restrict__
#else
#  define MAN_RESTRICT
#endif

// nodiscard
#if MAN_COMPILER_MSVC
#  define MAN_NODISCARD [[nodiscard]]
#elif MAN_COMPILER_GCC || MAN_COMPILER_CLANG
#  define MAN_NODISCARD __attribute__((warn_unused_result))
#else
# define MAN_NODISCARD
#endif

// no unique address
#define MAN_NO_UNIQUE_ADDRESS [[no_unique_address]]
