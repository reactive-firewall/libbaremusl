/* Copyright (c) 2025 Mr.Walls */
/*
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Berkeley Software Design, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)cdefs.h	8.8 (Berkeley) 1/9/95
 */

/* Shim for musl libc when cdefs is expected */
#ifndef	_SYS_CDEFS_H_
#define	_SYS_CDEFS_H_

#if defined(__cplusplus)
#define	__BEGIN_DECLS	extern "C" {
#define	__END_DECLS	}
#else
#define	__BEGIN_DECLS
#define	__END_DECLS
#endif

/*
 * This code has been put in place to help reduce the addition of
 * compiler specific defines in FreeBSD code.  It helps to aid in
 * having a compiler-agnostic source tree.
 */

#if defined(__clang__) && __clang__
#pragma mark -
#pragma mark Compiler switches

/* shim for darwin sys/cdef.h mutual exclusion */
#ifndef _CDEFS_H_
#if defined(__APPLE__)
#define _CDEFS_H_ _SYS_CDEFS_H_
#endif /* !__APPLE__ */
#endif

#endif /* !__clang__ */

#if defined(__GNUC__)

#if __GNUC__ >= 3
#define	__GNUCLIKE_ASM 3
#define	__GNUCLIKE_MATH_BUILTIN_CONSTANTS
#else
#define	__GNUCLIKE_ASM 2
#endif
#define	__GNUCLIKE___TYPEOF 1
#define	__GNUCLIKE___OFFSETOF 1
#define	__GNUCLIKE___SECTION 1

#define	__GNUCLIKE_CTOR_SECTION_HANDLING 1

#define	__GNUCLIKE_BUILTIN_CONSTANT_P 1

#if (__GNUC_MINOR__ > 95 || __GNUC__ >= 3)
#define	__GNUCLIKE_BUILTIN_VARARGS 1
#define	__GNUCLIKE_BUILTIN_STDARG 1
#define	__GNUCLIKE_BUILTIN_VAALIST 1
#endif

#if defined(__GNUC__)
#define	__GNUC_VA_LIST_COMPATIBILITY 1
#endif

/*
 * Compiler memory barriers, specific to gcc and clang.
 */
#if defined(__clang__) || defined(__GNUC__)
#define	__compiler_membar()	__asm __volatile(" " : : : "memory")
#endif

#define	__GNUCLIKE_BUILTIN_NEXT_ARG 1
#define	__GNUCLIKE_MATH_BUILTIN_RELOPS

#define	__GNUCLIKE_BUILTIN_MEMCPY 1

/* XXX: if __GNUC__ >= 2: not tested everywhere originally, where replaced */
#define	__CC_SUPPORTS_INLINE 1
#define	__CC_SUPPORTS___INLINE 1
#define	__CC_SUPPORTS___INLINE__ 1

#define	__CC_SUPPORTS___FUNC__ 1
#define	__CC_SUPPORTS_WARNING 1

#define	__CC_SUPPORTS_VARADIC_XXX 1 /* see varargs.h */

#define	__CC_SUPPORTS_DYNAMIC_ARRAY_INIT 1

#endif /* __GNUC__ */

/*
 * Macro to test if we're using a specific version of gcc or later.
 */
#if defined(__GNUC__)
#define	__GNUC_PREREQ__(ma, mi)	\
(__GNUC__ > (ma) || __GNUC__ == (ma) && __GNUC_MINOR__ >= (mi))
#else
#define	__GNUC_PREREQ__(ma, mi)	0
#endif

/*
 * Compatibility with compilers and environments that don't support compiler
 * feature checking function-like macros.
 */
#ifndef Compat_h
#define Compat_h "sys/cdefs.h"

///>important
///> The `Compat.h` file contains code that is under the LLVM APACHE Licence, As described here:
///> https://www.llvm.org/docs/DeveloperPolicy.html#new-llvm-project-license-framework
///> and is hearby Acknowledged.
/// See https://clang.llvm.org/docs/LanguageExtensions.html#builtin-unpredictable
///
#if defined(__clang__) && __clang__
#pragma mark -
#pragma mark Compatibility
#endif /* !__clang__ */

#if defined(__clang__) && __clang__
#ifndef __has_builtin
#warning Something is unusual. Compiler Gods Help You.
#endif /* !CONFUSED MACRO */
#else
/// BELOW FROM https://clang.llvm.org/docs/LanguageExtensions.html#feature-checking-macros
#ifndef __has_builtin         // Optional of course.
#define __has_builtin(x) 0  // Compatibility with non-clang compilers.
#endif
// ABOVE FROM https://clang.llvm.org/docs/LanguageExtensions.html#feature-checking-macros
#endif /* !__clang__ */

#if defined(__clang__) && __clang__
#ifndef __has_feature
#error Something is missing. Compiler/Target unsupported.
#endif /* !PANIC MACRO */
#else
/// BELOW FROM https://clang.llvm.org/docs/LanguageExtensions.html#feature-checking-macros
#ifndef __has_feature         // Optional of course.
#define __has_feature(x) 0  // Compatibility with non-clang compilers.
#endif
#ifndef __has_extension
#define __has_extension __has_feature // Compatibility with pre-3.0 compilers.
#endif
// ABOVE FROM https://clang.llvm.org/docs/LanguageExtensions.html#feature-checking-macros
#endif /* !__clang__ */

/// BELOW FROM https://clang.llvm.org/docs/LanguageExtensions.html#has-attribute
#ifndef __has_attribute         // Optional of course.
#define __has_attribute(x) 0  // Compatibility with non-clang compilers.
#endif
// ABOVE FROM https://clang.llvm.org/docs/LanguageExtensions.html#has-attribute

// in similar fashion the unknown __has_cpp_attribute
#ifndef __has_cpp_attribute         // Optional of course.
#define __has_cpp_attribute(x) 0  // Compatibility with non-clang compilers.
#endif

#endif /* Compat_h */

/*
 * The __CONCAT macro is used to concatenate parts of symbol names, e.g.
 * with "#define OLD(foo) __CONCAT(old,foo)", OLD(foo) produces oldfoo.
 * The __CONCAT macro is a bit tricky to use if it must work in non-ANSI
 * mode -- there must be no spaces between its arguments, and for nested
 * __CONCAT's, all the __CONCAT's must be at the left.  __CONCAT can also
 * concatenate double-quoted strings produced by the __STRING macro, but
 * this only works with ANSI C.
 *
 * __XSTRING is like __STRING, but it expands any macros in its argument
 * first.  It is only available with ANSI C.
 */
#if defined(__STDC__) || defined(__cplusplus)
#define	__P(protos)	protos		/* full-blown ANSI C */
#define	__CONCAT1(x,y)	x ## y
#define	__CONCAT(x,y)	__CONCAT1(x,y)
#define	__STRING(x)	#x		/* stringify without expanding x */
#define	__XSTRING(x)	__STRING(x)	/* expand x, then stringify */

#define	__const		const		/* define reserved names to standard */
#define	__signed	signed
#define	__volatile	volatile
#if defined(__cplusplus)
#define	__inline	inline		/* convert to C++ keyword */
#else
#if !(defined(__CC_SUPPORTS___INLINE))
#define	__inline			/* delete GCC keyword */
#endif /* ! __CC_SUPPORTS___INLINE */
#endif /* !__cplusplus */

#else	/* !(__STDC__ || __cplusplus) */
#define	__P(protos)	()		/* traditional C preprocessor */
#define	__CONCAT(x,y)	x/**/y
#define	__STRING(x)	"x"

#if !defined(__CC_SUPPORTS___INLINE)
#define	__const				/* delete pseudo-ANSI C keywords */
#define	__inline
#define	__signed
#define	__volatile
/*
 * In non-ANSI C environments, new programs will want ANSI-only C keywords
 * deleted from the program and old programs will want them left alone.
 * When using a compiler other than gcc, programs using the ANSI C keywords
 * const, inline etc. as normal identifiers should define -DNO_ANSI_KEYWORDS.
 * When using "gcc -traditional", we assume that this is the intent; if
 * __GNUC__ is defined but __STDC__ is not, we leave the new keywords alone.
 */
#ifndef	NO_ANSI_KEYWORDS
#define	const				/* delete ANSI C keywords */
#define	inline
#define	signed
#define	volatile
#endif	/* !NO_ANSI_KEYWORDS */
#endif	/* !__CC_SUPPORTS___INLINE */
#endif	/* !(__STDC__ || __cplusplus) */

#if defined(__clang__) && __clang__
#pragma mark -
#pragma mark Attributes
#endif /* !__clang__ */

/*
 * Compiler-dependent macros to help declare dead (non-returning) and
 * pure (no side effects) functions, and unused variables.  They are
 * null except for versions of compilers that are known to support the features
 * properly (old versions of gcc-2 supported the dead and pure features
 * in a different (wrong) way).  If we do not provide an implementation
 * for a given compiler, let the compile fail if it is told to use
 * a feature that we cannot live without.
 */
#if defined(__has_attribute)
#if __has_attribute(weak)
#ifndef __weak_symbol
/// Use this to declare `__attribute__((weak))` when available.
#define	__weak_symbol	__attribute__((weak))
#endif /* !__weak_symbol */
#else /* !__attribute__ ((__weak__)) */
#ifndef __weak_symbol
#warning No support for weak symbols
/// Use this to declare `__attribute__((weak))` when available.
#define __weak_symbol
#endif /* !__weak_symbol */
#endif /* END ((__weak__)) */
/*
 * __pure2 can be used for functions that are only a function of their scalar
 * arguments (meaning they can't dereference pointers).
 *
 * __stateful_pure can be used for functions that have no side effects,
 * but depend on the state of the memory.
 */
#if __has_attribute(__noreturn__)
#ifndef __dead2
/// Use this to declare `__attribute__((__noreturn__))` when available.
#define	__dead2	__attribute__((__noreturn__))
#endif /* !__dead2 */
#else /* !__attribute__ ((__noreturn__)) */
#ifndef __dead2
#warning No support for functions with the noreturn attribute
/// Use this to declare `__attribute__((__noreturn__))` when available.
#define __dead2
#endif /* !__dead2 */
#endif /* END ((__noreturn__)) */

#if __has_attribute(__const__)
#ifndef __pure2
/// Use this to declare `__attribute__((__const__))` when available.
#define	__pure2	__attribute__((__const__))
#endif /* !__pure2 */
#else /* !__attribute__ ((__const__)) */
#ifndef __pure2
#warning No support for zero-side effect functions
/// Use this to declare `__attribute__((__const__))` when available.
#define __pure2
#endif /* !__pure2 */
#endif /* END ((__const__)) */
/* __unused denotes variables and functions that may not be used, preventing
 * the compiler from warning about it if not used.
 */
#if !defined(__GNUC__)
#if __has_attribute(__unused__)
#ifndef __unused
/// Use this to declare `__attribute__((__unused__))` when available.
#define	__unused	__attribute__((__unused__))
#endif /* !__unused */
#else /* !__attribute__ ((__unused__)) */
#ifndef __unused
#warning No support for unused symbols
#define __unused	/**/
#endif /* !__unused */
#endif /* END ((__unused__)) */
#endif /* !defined(__GNUC__) */
/* __used forces variables and functions to be included even if it appears
 * to the compiler that they are not used (and would thus be discarded).
 */
#if __has_attribute(__used__)
#ifndef __used
/// Use this to declare `__attribute__((__used__))` when available.
#define	__used	__attribute__((__used__))
#endif /* !__used */
#else /* !__attribute__ ((__used__)) */
#ifndef __used
#warning No support for used symbols
/// Use this to declare `__attribute__((__used__))` when available.
#define __used
#endif /* !__used */
#endif /* END ((__used__)) */

/* XXX still need to refactor based on def/undef of __packed */
#if __has_attribute(__packed__)
#ifndef __packed
/// Use this to declare `__attribute__((__packed__))` when available.
#define	__packed	__attribute__((__packed__))
#endif /* !__packed */
#else /* !__attribute__ ((__packed__)) */
/* fallback: define pragma-based start/end and helpers only here */
#ifndef __packed_start

/* Portable pragma emitters:
 - MSVC: use __pragma
 - Others: use standard _Pragma */
#if defined(_MSC_VER)
#define __PACK_PRAGMA_PUSH1 __pragma(pack(push,1))
#define __PACK_PRAGMA_POP   __pragma(pack(pop))
#else
#define __PACK_PRAGMA_STR(x) _Pragma(#x)
#define __PACK_PRAGMA_PUSH1  __PACK_PRAGMA_STR(pack(push,1))
#define __PACK_PRAGMA_POP    __PACK_PRAGMA_STR(pack(pop))
#endif

/* Non-empty tokens for fallback:
 - Place __packed_start before a struct definition and __packed_end after it:
    __packed_start
    struct X { ... };
    __packed_end
 - This ensures 1-byte packing for the region between start and end. */
#define __packed_start __PACK_PRAGMA_PUSH1
#define __packed_end   __PACK_PRAGMA_POP

/* Fallback helpers (visible only in fallback branch) */

/* Reserve exact bytes without including headers. */
#define PACKED_BYTES(name, n)       unsigned char name[n]

/* Multi-byte integer storage as bytes (n bytes). */
#define PACKED_FIELD_INT(name, n)   unsigned char name[n]

/* Forced packed struct type composed of byte arrays:
 PACKED_STRUCT_FORCE(tag) { ... } PACKED_STRUCT_FORCE_END(tag);
 yields typedef 'tag' with exact size equal to sum of bytes. */
#define PACKED_STRUCT_FORCE(name)        struct name##_packed_force {
#define PACKED_STRUCT_FORCE_END(name)    }; typedef struct name##_packed_force name

#endif /* !__packed_start */
#endif /* __has_attribute(__packed__) */

/* XXX Find out what to do for __aligned and __section */
#if __has_attribute(__aligned__)
#ifndef __aligned
/// Use this to declare `__attribute__((__aligned__(x)))` when available.
#define	__aligned(x)	__attribute__((__aligned__(x)))
#endif /* !__aligned */
#else /* !__attribute__ ((__aligned__)) */
#ifndef __aligned
#warning "No support for __aligned__ attribute, program may fail to compile at all."
#endif /* !__aligned */
#endif /* END ((__aligned__)) */
#if __has_attribute(__section__)
#ifndef __section
/// Use this to declare `__attribute__((__section__(x)))` when available.
#define	__section(x)	__attribute__((__section__(x)))
#endif /* !__section */
#elif defined(_MSC_VER) // Microsoft Visual compiler
#warning "No support for __section__ attribute, program may fail to compile at all."
#define __section(x) __declspec(section(x))
#elif defined(__TI_COMPILER_VERSION) // Texas Instruments Compiler
// Using __CONCAT for dynamic section names - might not need __concat
#define __section(x) _Pragma(__XSTRING(DATA_SECTION(__CONCAT(x))))
#else /* !__attribute__ ((__section__)) */
#ifndef __section
#warning "No support for __section__ attribute, program may fail to compile at all."
// If none of the above compilers are recognized, do nothing
#endif
#endif /* END ((__section__)) */

#if __has_attribute(__pure__)
#ifndef __pure
/// Use this to declare `__attribute__((__pure__))` when available.
#define	__pure	__attribute__((__pure__))
#endif /* !__pure */
#else /* !__attribute__ ((__pure__)) */
#ifndef __stateful_pure
#warning "No support for __pure__ functions"
/// Use this to declare `__attribute__((__pure__))` when available.
#define __pure
#endif /* !__pure */
#endif /* END ((__pure__)) */

#ifdef _SYS_CDEFS_H_
#define __stateful_pure __pure
/* __cold marks code used for debugging or that is rarely taken
 * and tells the compiler to optimize for size and outline code.
 */
#if __has_attribute(cold)
#ifndef __cold
/// Use this to declare `__attribute__((__cold__))` when available.
#define	__cold	__attribute__((__cold__))
#endif /* !__cold */
#else /* !__attribute__ ((__cold__)) */
#ifndef __cold
#warning No support for cold functions
/// Use this to declare `__attribute__((__cold__))` when available.
#define __cold
#endif /* !__cold */
#endif /* END ((__cold__)) */
/* __returns_nonnull marks functions that return a non-null pointer. */
#if __has_attribute(returns_nonnull)
#ifndef __cold
/// Use this to declare `__attribute__((returns_nonnull))` when available.
#define	__returns_nonnull	__attribute((returns_nonnull))
#endif /* !__returns_nonnull */
#else /* !__attribute__ ((returns_nonnull)) */
#ifndef __returns_nonnull
#warning No support for marking functions that return a non-null pointer
/// Use this to declare `__attribute__((returns_nonnull))` when available.
#define __returns_nonnull
#endif /* !__returns_nonnull */
#endif /* END ((returns_nonnull)) */

#endif /* !_SYS_CDEFS_H_ */

#if __has_attribute(__alloc_size__)
#ifndef __alloc_size
/// Use this to declare `__attribute__((__alloc_size__(x)))` when available.
#define	__alloc_size(x)	__attribute__((__alloc_size__(x)))
/// Use this to declare `__attribute__((__alloc_size__(n, x)))` when available.
#define	__alloc_size2(n, x)	__attribute__((__alloc_size__(n, x)))
#endif /* !__alloc_size */
#else /* !__attribute__ ((__alloc_size__)) */
#ifndef __alloc_size
/// Use this to declare `__attribute__((__alloc_size__(x)))` when available.
#define __alloc_size(x)
#define	__alloc_size2(n, x)
#endif /* !__alloc_size */
#endif /* END ((__alloc_size__(x))) */
#if __has_attribute(__alloc_align__)
#ifndef __alloc_align
/// Use this to declare `__attribute__((__alloc_align__(x)))` when available.
#define	__alloc_align(x)	__attribute__((__alloc_align__(x)))
#endif /* !__alloc_align */
#else /* !__attribute__ ((__alloc_align__)) */
#ifndef __alloc_align__
/// Use this to declare `__attribute__((__alloc_align__(x)))` when available.
#define __alloc_align__(x)
#endif /* !__alloc_align */
#endif /* END ((__alloc_align__(x))) */

/* __unavailable causes the compiler to error out when encountering
 * code using the tagged function
 */
#if __has_attribute(unavailable)
#ifndef __unavailable
/// Use this to declare `__attribute__((__unavailable__))` when available.
#define	__unavailable	__attribute__((__unavailable__))
#endif /* !__unavailable */
#else /* !__attribute__ ((__unavailable__)) */
#ifndef __unavailable
#warning No support for unavailable functions
/// Use this to declare `__attribute__((__unavailable__))` when available.
#define __unavailable
#endif /* !__unavailable */
#endif /* END ((__unavailable__)) */

/* Delete pseudo-keywords wherever they are not available or needed. */
//#ifndef __dead
//#define __dead
//#define __pure
//#endif

#endif /* !__has_attribute */

#if defined(__clang__) && __clang__
#pragma mark -
#pragma mark BSD C11 Clobbering
#endif /* !__clang__ */

/*
 * Keywords added in C11.
 */

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L

#if !__has_extension(c_alignas)
#if (defined(__cplusplus) && __cplusplus >= 201103L) || __has_extension(cxx_alignas)
#define	_Alignas(x)		alignas(x)
#else
/* XXX: Only emulates _Alignas(constant-expression); not _Alignas(type-name). */
#define	_Alignas(x)		__aligned(x)
#endif
#endif

#if defined(__cplusplus) && __cplusplus >= 201103L
#define	_Alignof(x)		alignof(x)
#else
#define	_Alignof(x)		__alignof(x)
#endif

#if !defined(__cplusplus) && !__has_extension(c_atomic) && !__has_extension(cxx_atomic) && !__GNUC_PREREQ__(4, 7)
/*
 * No native support for _Atomic(). Place object in structure to prevent
 * most forms of direct non-atomic access.
 */
#define	_Atomic(T)		struct { T volatile __val; }
#endif

#if defined(__cplusplus) && __cplusplus >= 201103L
#define	_Noreturn		[[noreturn]]
#else
#define	_Noreturn		__dead2
#endif

#if !__has_extension(c_static_assert)
#if __has_extension(cxx_static_assert)
#define	_Static_assert(x, y)	static_assert(x, y)
#elif __GNUC_PREREQ__(4,6) && !defined(__cplusplus)
/* Nothing, gcc 4.6 and higher has _Static_assert built-in */
#elif defined(__COUNTER__)
#define	_Static_assert(x, y)	__Static_assert(x, __COUNTER__)
#define	__Static_assert(x, y)	___Static_assert(x, y)
#define	___Static_assert(x, y)	typedef char __assert_ ## y[(x) ? 1 : -1] \
__unused
#else
#define	_Static_assert(x, y)	struct __hack
#endif
#endif

#if !__has_extension(c_thread_local)
/*
 * XXX: Some compilers (Clang 3.3, GCC 4.7) falsely announce C++11 mode
 * without actually supporting the thread_local keyword. Don't check for
 * the presence of C++11 when defining _Thread_local.
 */
#if __has_extension(cxx_thread_local)
#define	_Thread_local		thread_local
#else
#define	_Thread_local		__thread
#endif
#endif /* !__has_extension(c_thread_local) */

#endif /* __STDC_VERSION__ || __STDC_VERSION__ < 201112L */

/* __exported denotes symbols that should be exported even when symbols
 * are hidden by default.
 */
#define __exported      __attribute__((__visibility__("default")))
/* Don't hide symbols that the might be need to be used from outside */
#define __exported_hidden

#if __GNUC_PREREQ__(4, 0)
//TODO: Refactor this into the has attributes section above
#define	__null_sentinel	__attribute__((__sentinel__))
#define	__hidden	__attribute__((__visibility__("hidden")))
#endif

#if defined(__clang__) && __clang__
#pragma mark -
#pragma mark Extensions
#endif /* !__clang__ */

/* __deprecated causes the compiler to produce a warning when encountering
 * code using the deprecated functionality.
 * __deprecated_msg() does the same, and compilers that support it will print
 * a message along with the deprecation warning.
 * This may require turning on such warning with the -Wdeprecated flag.
 * __deprecated_enum_msg() should be used on enums, and compilers that support
 * it will print the deprecation warning.
 */
#define __deprecated    __attribute__((__deprecated__))

#if __has_extension(attribute_deprecated_with_message) || \
        (defined(__GNUC__) && ((__GNUC__ >= 5) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5))))
	#define __deprecated_msg(_msg) __attribute__((__deprecated__(_msg)))
#else
	#define __deprecated_msg(_msg) __attribute__((__deprecated__))
#endif

#if __has_extension(enumerator_attributes)
	#define __deprecated_enum_msg(_msg) __deprecated_msg(_msg)
#else
	#define __deprecated_enum_msg(_msg)
#endif


/*
 * Emulation of C11 _Generic().  Unlike the previously defined C11
 * keywords, it is not possible to implement this using exactly the same
 * syntax.  Therefore implement something similar under the name
 * __generic().  Unlike _Generic(), this macro can only distinguish
 * between a single type, so it requires nested invocations to
 * distinguish multiple cases.
 */

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) || \
__has_extension(c_generic_selections)
#define	__generic(expr, t, yes, no)					\
_Generic(expr, t: yes, default: no)
#elif __GNUC_PREREQ__(3, 1) && !defined(__cplusplus)
#define	__generic(expr, t, yes, no)					\
__builtin_choose_expr(						\
__builtin_types_compatible_p(__typeof(expr), t), yes, no)
#endif

/*
 * C99 Static array indices in function parameter declarations.  Syntax such as:
 * void bar(int myArray[static 10]);
 * is allowed in C99 but not in C++.  Define __min_size appropriately so
 * headers using it can be compiled in either language.  Use like this:
 * void bar(int myArray[__min_size(10)]);
 */
#if !defined(__cplusplus) && \
(defined(__clang__) || __GNUC_PREREQ__(4, 6)) && \
(!defined(__STDC_VERSION__) || (__STDC_VERSION__ >= 199901))
#define __min_size(x)	static (x)
#else
#define __min_size(x)	(x)
#endif

/*
 * NeXT:
 * We use `__restrict' as a way to define the `restrict' type qualifier
 * without disturbing older software that is unaware of C99 keywords.
 * FreeBSD:
 * GCC 2.95 provides `__restrict' as an extension to C90 to support the
 * C99-specific `restrict' type qualifier.  We happen to use `__restrict' as
 * a way to define the `restrict' type qualifier without disturbing older
 * software that is unaware of C99 keywords.
 */
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901
#define __restrict
#else
#define __restrict      restrict
#endif

#if __GNUC_PREREQ__(2, 96)
#define	__malloc_like	__attribute__((__malloc__))
#define	__pure		__attribute__((__pure__))
#else
#define	__malloc_like
#define	__pure
#endif

/* Declaring inline functions within headers is error-prone due to differences
 * across various versions of the C language and extensions.  __header_inline
 * can be used to declare inline functions within system headers.  In cases
 * where you want to force inlining instead of letting the compiler make
 * the decision, you can use __header_always_inline.
 *
 * Be aware that using inline for functions which compilers may also provide
 * builtins can behave differently under various compilers.  If you intend to
 * provide an inline version of such a function, you may want to use a macro
 * instead.
 *
 * The check for !__GNUC__ || __clang__ is because gcc doesn't correctly
 * support c99 inline in some cases:
 * http://gcc.gnu.org/bugzilla/show_bug.cgi?id=55965
 */

#if defined(__cplusplus) || (__STDC_VERSION__ >= 199901L && !defined(__GNUC_GNU_INLINE__) && \
(!defined(__GNUC__) || defined(__clang__)))
# define __header_inline		inline
#elif defined(__GNUC__) && defined(__GNUC_STDC_INLINE__)
#warning "using GNU inline behavior, things may break."
# define __header_inline		extern __inline __attribute__((__gnu_inline__))
#elif defined(__GNUC__)
# define __header_inline		extern __inline
#else
/* If we land here, we've encountered an unsupported compiler,
 * so hopefully it understands static __inline as a fallback.
 */
# define __header_inline		static __inline
#endif

#if defined(__clang__) && __clang__
#define __header_always_inline	__header_inline [[clang::always_inline]]
#else
#ifdef __GNUC__
#define __header_always_inline	__header_inline __attribute__((__always_inline__))
#else
/* Unfortunately, we're using a compiler that we don't know how to force to
 * inline.  Oh well.
 */
# define __header_always_inline	__header_inline
#endif
#endif

#if __GNUC_PREREQ__(3, 1)
/* #define	__noinline	__attribute__ ((__noinline__)) */
#define	__noinline	__attribute__((__noinline__))
#else
#define	__noinline
#endif

#if __GNUC_PREREQ__(3, 4)
#define	__fastcall	__attribute__((__fastcall__))
#define	__result_use_check	__attribute__((__warn_unused_result__))
#else
#define	__fastcall
#define	__result_use_check
#endif

#if __GNUC_PREREQ__(4, 1)
#define	__returns_twice	__attribute__((__returns_twice__))
#else
#define	__returns_twice
#endif

#if __has_builtin(__builtin_unreachable)
#define	__unreachable()	__builtin_unreachable()
#else
#define	__unreachable()	((void)0)
#endif

/*
 * GNU C version 2.96 adds explicit branch prediction so that
 * the CPU back-end can hint the processor and also so that
 * code blocks can be reordered such that the predicted path
 * sees a more linear flow, thus improving cache behavior, etc.
 *
 * The following two macros provide us with a way to utilize this
 * compiler feature.  Use __predict_true() if you expect the expression
 * to evaluate to true, and __predict_false() if you expect the
 * expression to evaluate to false.
 *
 * A few notes about usage:
 *
 *	* Generally, __predict_false() error condition checks (unless
 *	  you have some _strong_ reason to do otherwise, in which case
 *	  document it), and/or __predict_true() `no-error' condition
 *	  checks, assuming you want to optimize for the no-error case.
 *
 *	* Other than that, if you don't know the likelihood of a test
 *	  succeeding from empirical or other `hard' evidence, don't
 *	  make predictions.
 *
 *	* These are meant to be used in places that are run `a lot'.
 *	  It is wasteful to make predictions in code that is run
 *	  seldomly (e.g. at subsystem initialization time) as the
 *	  basic block reordering that this affects can often generate
 *	  larger code.
 */
#if __GNUC_PREREQ__(2, 96)
#define	__predict_true(exp)     __builtin_expect((exp), 1)
#define	__predict_false(exp)    __builtin_expect((exp), 0)
#else
#define	__predict_true(exp)     (exp)
#define	__predict_false(exp)    (exp)
#endif

#define	__null_sentinel	__attribute__((__sentinel__))
#define	__hidden	__attribute__((__visibility__("hidden")))

/* Compatibility with compilers and environments that don't support the
 * nullability feature.
 */

#if !__has_feature(nullability)
#ifndef __nullable
#define __nullable
#endif
#ifndef __nonnull
#define __nonnull
#endif
#ifndef __null_unspecified
#define __null_unspecified
#endif
#ifndef _Nullable
#define _Nullable
#endif
#ifndef _Nonnull
#define _Nonnull
#endif
#ifndef _Null_unspecified
#define _Null_unspecified
#endif
#endif

/*
 * __disable_tail_calls causes the compiler to not perform tail call
 * optimization inside the marked function.
 */
#if __has_attribute(disable_tail_calls)
#define __disable_tail_calls    __attribute__((__disable_tail_calls__))
#else
#define __disable_tail_calls
#endif

/*
 * __not_tail_called causes the compiler to prevent tail call optimization
 * on statically bound calls to the function.  It has no effect on indirect
 * calls.  Virtual functions, objective-c methods, and functions marked as
 * "always_inline" cannot be marked as __not_tail_called.
 */
#if __has_attribute(not_tail_called)
#define __not_tail_called       __attribute__((__not_tail_called__))
#else
#define __not_tail_called
#endif

/*
 * __result_use_check warns callers of a function that not using the function
 * return value is a bug, i.e. dismissing malloc() return value results in a
 * memory leak.
 */
#if __has_attribute(warn_unused_result)
#define __result_use_check __attribute__((__warn_unused_result__))
#else
#define __result_use_check
#endif

/*
 * __swift_unavailable causes the compiler to mark a symbol as specifically
 * unavailable in Swift, regardless of any other availability in C.
 */
#if __has_feature(attribute_availability_swift)
#define __swift_unavailable(_msg)       __attribute__((__availability__(swift, unavailable, message=_msg)))
#else
#define __swift_unavailable(_msg)
#endif

/*
 * Attributes to support Swift concurrency.
 */
#if __has_attribute(__swift_attr__)
#define __swift_unavailable_from_async(_msg)    __attribute__((__swift_attr__("@_unavailableFromAsync(message: \"" _msg "\")")))
#define __swift_nonisolated                     __attribute__((__swift_attr__("nonisolated")))
#define __swift_nonisolated_unsafe              __attribute__((__swift_attr__("nonisolated(unsafe)")))
#else
#define __swift_unavailable_from_async(_msg)
#define __swift_nonisolated
#define __swift_nonisolated_unsafe
#endif

/*
 * __abortlike is the attribute to put on functions like abort() that are
 * typically used to mark assertions. These optimize the codegen
 * for outlining while still maintaining debugability.
 */
#ifndef __abortlike
#define __abortlike __dead2 __cold __not_tail_called
#endif

/*
 * Compiler-dependent macros that bracket portions of code where the
 * "-Wunreachable-code" warning should be ignored. Please use sparingly.
 */
#if defined(__clang__)
# define __unreachable_ok_push \
	 _Pragma("clang diagnostic push") \
	 _Pragma("clang diagnostic ignored \"-Wunreachable-code\"")
# define __unreachable_ok_pop \
	 _Pragma("clang diagnostic pop")
#elif defined(__GNUC__) && ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
# define __unreachable_ok_push \
	 _Pragma("GCC diagnostic push") \
	 _Pragma("GCC diagnostic ignored \"-Wunreachable-code\"")
# define __unreachable_ok_pop \
	 _Pragma("GCC diagnostic pop")
#else
# define __unreachable_ok_push
# define __unreachable_ok_pop
#endif

/*
 * We define this here since <stddef.h>, <sys/queue.h>, and <sys/types.h>
 * require it.
 */
#if __GNUC_PREREQ__(4, 1)
#define	__offsetof(type, field)	 __builtin_offsetof(type, field)
#else
#ifndef __cplusplus
#define	__offsetof(type, field) \
((__size_t)(__uintptr_t)((const volatile void *)&((type *)0)->field))
#else
#define	__offsetof(type, field)					\
(__offsetof__ (reinterpret_cast <__size_t>			\
(&reinterpret_cast <const volatile char &>	\
(static_cast<type *> (0)->field))))
#endif
#endif
#define	__rangeof(type, start, end) \
(__offsetof(type, end) - __offsetof(type, start))

/*
 * Given the pointer x to the member m of the struct s, return
 * a pointer to the containing structure.  When using GCC, we first
 * assign pointer x to a local variable, to check that its type is
 * compatible with member m.
 */
#if __GNUC_PREREQ__(3, 1)
#define	__containerof(x, s, m) ({					\
const volatile __typeof(((s *)0)->m) *__x = (x);		\
__DEQUALIFY(s *, (const volatile char *)__x - __offsetof(s, m));\
})
#else
#define	__containerof(x, s, m)						\
__DEQUALIFY(s *, (const volatile char *)(x) - __offsetof(s, m))
#endif

/*
 * Compiler-dependent macros to declare that functions take printf-like
 * or scanf-like arguments.  They are null except for versions of gcc
 * that are known to support the features properly (old versions of gcc-2
 * didn't permit keeping the keywords out of the application namespace).
 */
#if !__GNUC_PREREQ__(2, 7)
#define	__printflike(fmtarg, firstvararg)
#define	__scanflike(fmtarg, firstvararg)
#define	__format_arg(fmtarg)
#define	__strfmonlike(fmtarg, firstvararg)
#define	__strftimelike(fmtarg, firstvararg)
#else
#define	__printflike(fmtarg, firstvararg) \
__attribute__((__format__ (__printf__, fmtarg, firstvararg)))
#define	__scanflike(fmtarg, firstvararg) \
__attribute__((__format__ (__scanf__, fmtarg, firstvararg)))
#define	__format_arg(fmtarg)	__attribute__((__format_arg__ (fmtarg)))
#define	__strfmonlike(fmtarg, firstvararg) \
__attribute__((__format__ (__strfmon__, fmtarg, firstvararg)))
#define	__strftimelike(fmtarg, firstvararg) \
__attribute__((__format__ (__strftime__, fmtarg, firstvararg)))
#endif

/*
 * Compiler-dependent macros to declare that functions take printf-like
 * or scanf-like arguments.  They are null except for versions of gcc
 * that are known to support the features properly.  Functions declared
 * with these attributes will cause compilation warnings if there is a
 * mismatch between the format string and subsequent function parameter
 * types.
 */
#define __printflike(fmtarg, firstvararg) \
__attribute__((__format__ (__printf__, fmtarg, firstvararg)))
//#define __printf0like(fmtarg, firstvararg) \
__attribute__((__format__ (__printf0__, fmtarg, firstvararg)))
#define __scanflike(fmtarg, firstvararg) \
__attribute__((__format__ (__scanf__, fmtarg, firstvararg)))
#define __osloglike(fmtarg, firstvararg) \
__attribute__((__format__ (__os_log__, fmtarg, firstvararg)))

/* Compiler-dependent macros that rely on FreeBSD-specific extensions. */
#if defined(__FreeBSD_cc_version) && __FreeBSD_cc_version >= 300001 && \
defined(__GNUC__)
#define	__printf0like(fmtarg, firstvararg) \
__attribute__((__format__ (__printf0__, fmtarg, firstvararg)))
#else
#define	__printf0like(fmtarg, firstvararg)
#endif

#if defined(__GNUC__)
#define	__strong_reference(sym,aliassym)	\
extern __typeof (sym) aliassym __attribute__ ((__alias__ (#sym)))
#ifdef __STDC__
#define	__weak_reference(sym,alias)	\
__asm__(".weak " #alias);	\
__asm__(".equ "  #alias ", " #sym)
#define	__warn_references(sym,msg)	\
__asm__(".section .gnu.warning." #sym);	\
__asm__(".asciz \"" msg "\"");	\
__asm__(".previous")
#define	__sym_compat(sym,impl,verid)	\
__asm__(".symver " #impl ", " #sym "@" #verid)
#define	__sym_default(sym,impl,verid)	\
__asm__(".symver " #impl ", " #sym "@@@" #verid)
#else
#define	__weak_reference(sym,alias)	\
__asm__(".weak alias");		\
__asm__(".equ alias, sym")
#define	__warn_references(sym,msg)	\
__asm__(".section .gnu.warning.sym"); \
__asm__(".asciz \"msg\"");	\
__asm__(".previous")
#define	__sym_compat(sym,impl,verid)	\
__asm__(".symver impl, sym@verid")
#define	__sym_default(impl,sym,verid)	\
__asm__(".symver impl, sym@@@verid")
#endif	/* __STDC__ */
#endif	/* __GNUC__ */

#define	__GLOBL1(sym)	__asm__(".globl " #sym)
#define	__GLOBL(sym)	__GLOBL1(sym)

#if defined(__GNUC__)
#define	__IDSTRING(name,string)	__asm__(".ident\t\"" string "\"")
#else
/*
 * The following definition might not work well if used in header files,
 * but it should be better than nothing.  If you want a "do nothing"
 * version, then it should generate some harmless declaration, such as:
 *    #define	__IDSTRING(name,string)	struct __hack
 */
#define	__IDSTRING(name,string)	static const char name[] __unused = string
#endif

#ifndef __COPYRIGHT
#ifndef	NO__COPYRIGHT
#define __COPYRIGHT(s) __IDSTRING(copyright,s)
#else
#define	__COPYRIGHT(s)	struct __hack
#endif
#endif

#ifndef __RCSID
#define __RCSID(s) __IDSTRING(rcsid,s)
#endif

#ifndef __SCCSID
#define __SCCSID(s) __IDSTRING(sccsid,s)
#endif

#ifndef __PROJECT_VERSION
#define __PROJECT_VERSION(s) __IDSTRING(project_version,s)
#endif

/*
 * Embed the rcs id of a source file in the resulting library.  Note that in
 * more recent ELF binutils, we use .ident allowing the ID to be stripped.
 * Usage:
 *	__FBSDID("$FreeBSD$");
 */
#ifndef	__FBSDID
#if !defined(STRIP_FBSDID) && !defined(__APPLE__) && !defined(__RAVYNOS__)
#define	__FBSDID(s)	__IDSTRING(__CONCAT(__rcsid_,__LINE__),s)
#else
/* Source compatibility only, ID string not emitted in object file */
#define __FBSDID(s)
#endif
#endif

#ifndef __DECONST
#define __DECONST(type, var)    __CAST_AWAY_QUALIFIER(var, const, type)
#endif

#ifndef __DEVOLATILE
#define __DEVOLATILE(type, var) __CAST_AWAY_QUALIFIER(var, volatile, type)
#endif

#ifndef __DEQUALIFY
#define __DEQUALIFY(type, var)  __CAST_AWAY_QUALIFIER(var, const volatile, type)
#endif

/*
 * __alloc_align can be used to label function arguments that represent the
 * alignment of the returned pointer.
 */
#ifndef __alloc_align
#if __has_attribute(alloc_align)
#define __alloc_align(n) __attribute__((alloc_align(n)))
#else
#define __alloc_align(n)
#endif
#endif // __alloc_align

/*
 * __alloc_size can be used to label function arguments that represent the
 * size of memory that the function allocates and returns. The one-argument
 * form labels a single argument that gives the allocation size (where the
 * arguments are numbered from 1):
 *
 * void	*malloc(size_t __size) __alloc_size(1);
 *
 * The two-argument form handles the case where the size is calculated as the
 * product of two arguments:
 *
 * void	*calloc(size_t __count, size_t __size) __alloc_size(1,2);
 */
#ifndef __alloc_size
#if __has_attribute(alloc_size)
#define __alloc_size(...) __attribute__((alloc_size(__VA_ARGS__)))
#else
#define __alloc_size(...)
#endif
#endif // __alloc_size

/*
 * Facilities below assist adoption of -Wunsafe-buffer-usage, an off-by-default
 * Clang compiler warning that helps the developer minimize unsafe, raw
 * buffer manipulation in the code that may lead to buffer overflow
 * vulnerabilities.
 *
 * They are primarily designed for modern C++ code where -Wunsafe-buffer-usage
 * comes with automatic fix-it hints that help the developer transform
 * their code to use modern C++ containers, which may be made bounds-safe by
 * linking against a version of the C++ standard library that offers
 * bounds-checked containers.
 * They can be used in plain C, but -fbounds-safety is the preferred solution
 * for plain C (see also <ptrcheck.h>).
 *
 * Attribute __unsafe_buffer_usage can be used to label functions that should be
 * avoided as they may perform or otherwise introduce unsafe buffer manipulation
 * operations. The attribute can also be attached to class/struct fields that
 * are used in unsafe buffer manipulations.
 *
 * Calls to attribute annotated functions are flagged by -Wunsafe-buffer-usage, similar to
 * how unchecked buffer manipulation operations are flagged when observed
 * by the compiler directly. Similarly, use of and assignment to the struct/class fields
 * that have the attribute also get flagged by the compiler.
 *
 *   // An unsafe function that needs to be avoided.
 *   __unsafe_buffer_usage
 *   void foo(int *buf, size_t size);
 *
 *   // A safe alternative to foo().
 *   void foo(std::span<int> buf);
 *
 *   void bar(size_t idx) {
 *       int array[5];
 *
 *       // Direct unsafe buffer manipulation through subscript operator:
 *       array[idx] = 3;  // warning: function introduces unsafe buffer manipulation [-Wunsafe-buffer-usage]
 *       // Unsafe buffer manipulation through function foo():
 *       foo(array, 5);   // warning: function introduces unsafe buffer manipulation [-Wunsafe-buffer-usage]
 *       // Checked buffer manipulation, with bounds information automatically
 *       // preserved for the purposes of runtime checks in standard library:
 *       foo(array);      // no warning
 *   }
 *
 *   struct Reader {
 *      // Field involved in unsafe buffer manipulation
 *      __unsafe_buffer_usage
 *      void *ptr;
 *
 *      __unsafe_buffer_usage
 *      size_t sz, count;
 *   };
 *
 *   void add_element(Reader rdr, int value) {
 *      if(rdr.count < rdr.sz) { // warning: unsafe buffer access [-Wunsafe-buffer-usage]
 *         rdr.ptr[rdr.count] = value; // warning: unsafe buffer access [-Wunsafe-buffer-usage]
 *         rdr.count++; // warning: unsafe buffer access [-Wunsafe-buffer-usage]
 *      }
 *   }
 *
 * While annotating a function as __unsafe_buffer_usage has an effect similar
 * to annotating it as __deprecated, the __unsafe_buffer_usage attribute
 * should be used whenever the resulting warning needs to be controlled
 * by the -Wunsafe-buffer-usage flag (which is turned off in codebases that
 * don't attempt to achieve bounds safety this way) as opposed to -Wdeprecated
 * (enabled in most codebases).
 *
 * The attribute suppresses all -Wunsafe-buffer-usage warnings inside the
 * function's body as it is explictly marked as unsafe by the user and
 * introduces new warnings at each call site to help the developers avoid the
 * function entirely. Most of the time it does not make sense to annotate a
 * function as __unsafe_buffer_usage without providing the users with a safe
 * alternative.
 *
 * Pragmas __unsafe_buffer_usage_begin and __unsafe_buffer_usage_end
 * annotate a range of code as intentionally containing unsafe buffer
 * operations. They suppress -Wunsafe-buffer-usage warnings
 * for unsafe operations in range:
 *
 *   __unsafe_buffer_usage_begin
 *   array[idx] = 3; // warning suppressed
 *   foo(array, 5);  // warning suppressed
 *   __unsafe_buffer_usage_end
 *
 * These pragmas are NOT a way to mass-annotate functions with the attribute
 * __unsafe_buffer_usage. Functions declared within the pragma range
 * do NOT get annotated automatically.
 */
#if __has_cpp_attribute(clang::unsafe_buffer_usage)
#define __has_safe_buffers 1
#define __unsafe_buffer_usage [[clang::unsafe_buffer_usage]]
#elif __has_attribute(unsafe_buffer_usage)
#define __has_safe_buffers 1
#define __unsafe_buffer_usage __attribute__((__unsafe_buffer_usage__))
#else
#define __has_safe_buffers 0
#define __unsafe_buffer_usage
#endif
#if __has_safe_buffers
#define __unsafe_buffer_usage_begin _Pragma("clang unsafe_buffer_usage begin")
#define __unsafe_buffer_usage_end   _Pragma("clang unsafe_buffer_usage end")
#else
#define __unsafe_buffer_usage_begin
#define __unsafe_buffer_usage_end
#endif

#if defined(__clang__) && __clang__
#pragma mark -
#pragma mark Musl Stuff
#endif /* !__clang__ */

#if !defined(__intptr_t)
#define intptr_t	__intptr_t
#endif

#if !defined(__uintptr_t)
#define uintptr_t	__uintptr_t
#endif

/*
 * COMPILATION ENVIRONMENTS -- see compat(5) for additional detail
 *
 * DEFAULT	By default newly complied code will get POSIX APIs plus
 *		Apple API extensions in scope.
 *
 *		Most users will use this compilation environment to avoid
 *		behavioral differences between 32 and 64 bit code.
 *
 * LEGACY	Defining _NONSTD_SOURCE will get pre-POSIX APIs plus Apple
 *		API extensions in scope.
 *
 *		This is generally equivalent to the Tiger release compilation
 *		environment, except that it cannot be applied to 64 bit code;
 *		its use is discouraged.
 *
 *		We expect this environment to be deprecated in the future.
 *
 * STRICT	Defining _POSIX_C_SOURCE or _XOPEN_SOURCE restricts the
 *		available APIs to exactly the set of APIs defined by the
 *		corresponding standard, based on the value defined.
 *
 *		A correct, portable definition for _POSIX_C_SOURCE is 200112L.
 *		A correct, portable definition for _XOPEN_SOURCE is 600L.
 *
 *		Apple API extensions are not visible in this environment,
 *		which can cause Apple specific code to fail to compile,
 *		or behave incorrectly if prototypes are not in scope or
 *		warnings about missing prototypes are not enabled or ignored.
 *
 * In any compilation environment, for correct symbol resolution to occur,
 * function prototypes must be in scope.  It is recommended that all Apple
 * tools users add either the "-Wall" or "-Wimplicit-function-declaration"
 * compiler flags to their projects to be warned when a function is being
 * used without a prototype in scope.
 */

#if defined(__clang__) && __clang__
#pragma mark -
#pragma mark Darwin Stuff
#endif /* !__clang__ */

/* These settings are particular to each product. */
/* Platform: MacOSX */
#if defined(__i386__)
#define __DARWIN_ONLY_64_BIT_INO_T      0
#define __DARWIN_ONLY_UNIX_CONFORMANCE  0
#define __DARWIN_ONLY_VERS_1050         0
#elif defined(__x86_64__)
#define __DARWIN_ONLY_64_BIT_INO_T      0
#define __DARWIN_ONLY_UNIX_CONFORMANCE  1
#define __DARWIN_ONLY_VERS_1050         0
#else
#define __DARWIN_ONLY_64_BIT_INO_T      1
#define __DARWIN_ONLY_UNIX_CONFORMANCE  1
#define __DARWIN_ONLY_VERS_1050         1
#endif

/*
 * The __DARWIN_ALIAS macros are used to do symbol renaming; they allow
 * legacy code to use the old symbol, thus maintaining binary compatibility
 * while new code can use a standards compliant version of the same function.
 *
 * __DARWIN_ALIAS is used by itself if the function signature has not
 * changed, it is used along with a #ifdef check for __DARWIN_UNIX03
 * if the signature has changed.  Because the __LP64__ environment
 * only supports UNIX03 semantics it causes __DARWIN_UNIX03 to be
 * defined, but causes __DARWIN_ALIAS to do no symbol mangling.
 *
 * As a special case, when XCode is used to target a specific version of the
 * OS, the manifest constant __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
 * will be defined by the compiler, with the digits representing major version
 * time 100 + minor version times 10 (e.g. 10.5 := 1050).  If we are targeting
 * pre-10.5, and it is the default compilation environment, revert the
 * compilation environment to pre-__DARWIN_UNIX03.
 */
#if !defined(__DARWIN_UNIX03)
#  if   __DARWIN_ONLY_UNIX_CONFORMANCE
#    if defined(_NONSTD_SOURCE)
#      error "Can't define _NONSTD_SOURCE when only UNIX conformance is available."
#    endif /* _NONSTD_SOURCE */
#    define __DARWIN_UNIX03     1
#  elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && ((__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ - 0) < 1040)
#    define __DARWIN_UNIX03     0
#  elif defined(_DARWIN_C_SOURCE) || defined(_XOPEN_SOURCE) || defined(_POSIX_C_SOURCE)
#    if defined(_NONSTD_SOURCE)
#      error "Can't define both _NONSTD_SOURCE and any of _DARWIN_C_SOURCE, _XOPEN_SOURCE or _POSIX_C_SOURCE."
#    endif /* _NONSTD_SOURCE */
#    define __DARWIN_UNIX03     1
#  elif defined(_NONSTD_SOURCE)
#    define __DARWIN_UNIX03     0
#  else /* default */
#    if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && ((__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ - 0) < 1050)
#      define __DARWIN_UNIX03   0
#    else /* __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 1050 */
#      define __DARWIN_UNIX03   1
#    endif /* __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 1050 */
#  endif /* _DARWIN_C_SOURCE || _XOPEN_SOURCE || _POSIX_C_SOURCE || __LP64__ */
#endif /* !__DARWIN_UNIX03 */

#if !defined(__DARWIN_64_BIT_INO_T)
#  if   defined(_DARWIN_USE_64_BIT_INODE)
#    if defined(_DARWIN_NO_64_BIT_INODE)
#      error "Can't define both _DARWIN_USE_64_BIT_INODE and _DARWIN_NO_64_BIT_INODE."
#    endif /* _DARWIN_NO_64_BIT_INODE */
#    define __DARWIN_64_BIT_INO_T 1
#  elif defined(_DARWIN_NO_64_BIT_INODE)
#    if __DARWIN_ONLY_64_BIT_INO_T
#      error "Can't define _DARWIN_NO_64_BIT_INODE when only 64-bit inodes are available."
#    endif /* __DARWIN_ONLY_64_BIT_INO_T */
#    define __DARWIN_64_BIT_INO_T 0
#  else /* default */
#    if __DARWIN_ONLY_64_BIT_INO_T
#      define __DARWIN_64_BIT_INO_T 1
#    elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && ((__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ - 0) < 1060) || __DARWIN_UNIX03 == 0
#      define __DARWIN_64_BIT_INO_T 0
#    else /* default */
#      define __DARWIN_64_BIT_INO_T 1
#    endif /* __DARWIN_ONLY_64_BIT_INO_T */
#  endif
#endif /* !__DARWIN_64_BIT_INO_T */

#if !defined(__DARWIN_VERS_1050)
#  if   __DARWIN_ONLY_VERS_1050
#    define __DARWIN_VERS_1050 1
#  elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && ((__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ - 0) < 1050) || __DARWIN_UNIX03 == 0
#    define __DARWIN_VERS_1050 0
#  else /* default */
#    define __DARWIN_VERS_1050 1
#  endif
#endif /* !__DARWIN_VERS_1050 */

#if !defined(__DARWIN_NON_CANCELABLE)
#    define __DARWIN_NON_CANCELABLE 0
#endif /* !__DARWIN_NON_CANCELABLE */

/*
 * symbol suffixes used for symbol versioning
 */
#if __DARWIN_UNIX03
#  if __DARWIN_ONLY_UNIX_CONFORMANCE
#    define __DARWIN_SUF_UNIX03         /* nothing */
#  else /* !__DARWIN_ONLY_UNIX_CONFORMANCE */
#    define __DARWIN_SUF_UNIX03         "$UNIX2003"
#  endif /* __DARWIN_ONLY_UNIX_CONFORMANCE */

#  if __DARWIN_64_BIT_INO_T
#    if __DARWIN_ONLY_64_BIT_INO_T
#      define __DARWIN_SUF_64_BIT_INO_T /* nothing */
#    else /* !__DARWIN_ONLY_64_BIT_INO_T */
#      define __DARWIN_SUF_64_BIT_INO_T "$INODE64"
#    endif /* __DARWIN_ONLY_64_BIT_INO_T */
#  else /* !__DARWIN_64_BIT_INO_T */
#    define __DARWIN_SUF_64_BIT_INO_T   /* nothing */
#  endif /* __DARWIN_64_BIT_INO_T */

#  if __DARWIN_VERS_1050
#    if __DARWIN_ONLY_VERS_1050
#      define __DARWIN_SUF_1050         /* nothing */
#    else /* !__DARWIN_ONLY_VERS_1050 */
#      define __DARWIN_SUF_1050         "$1050"
#    endif /* __DARWIN_ONLY_VERS_1050 */
#  else /* !__DARWIN_VERS_1050 */
#    define __DARWIN_SUF_1050           /* nothing */
#  endif /* __DARWIN_VERS_1050 */

#  if __DARWIN_NON_CANCELABLE
#    define __DARWIN_SUF_NON_CANCELABLE "$NOCANCEL"
#  else /* !__DARWIN_NON_CANCELABLE */
#    define __DARWIN_SUF_NON_CANCELABLE /* nothing */
#  endif /* __DARWIN_NON_CANCELABLE */

#else /* !__DARWIN_UNIX03 */
#  define __DARWIN_SUF_UNIX03           /* nothing */
#  define __DARWIN_SUF_64_BIT_INO_T     /* nothing */
#  define __DARWIN_SUF_NON_CANCELABLE   /* nothing */
#  define __DARWIN_SUF_1050             /* nothing */
#endif /* __DARWIN_UNIX03 */

#define __DARWIN_SUF_EXTSN              "$DARWIN_EXTSN"

/*
 * symbol versioning macros
 */
#define __DARWIN_ALIAS(sym)             __asm("_" __STRING(sym) __DARWIN_SUF_UNIX03)
#define __DARWIN_ALIAS_C(sym)           __asm("_" __STRING(sym) __DARWIN_SUF_NON_CANCELABLE __DARWIN_SUF_UNIX03)
#define __DARWIN_ALIAS_I(sym)           __asm("_" __STRING(sym) __DARWIN_SUF_64_BIT_INO_T __DARWIN_SUF_UNIX03)
#define __DARWIN_NOCANCEL(sym)          __asm("_" __STRING(sym) __DARWIN_SUF_NON_CANCELABLE)
#define __DARWIN_INODE64(sym)           __asm("_" __STRING(sym) __DARWIN_SUF_64_BIT_INO_T)

#define __DARWIN_1050(sym)              __asm("_" __STRING(sym) __DARWIN_SUF_1050)
#define __DARWIN_1050ALIAS(sym)         __asm("_" __STRING(sym) __DARWIN_SUF_1050 __DARWIN_SUF_UNIX03)
#define __DARWIN_1050ALIAS_C(sym)       __asm("_" __STRING(sym) __DARWIN_SUF_1050 __DARWIN_SUF_NON_CANCELABLE __DARWIN_SUF_UNIX03)
#define __DARWIN_1050ALIAS_I(sym)       __asm("_" __STRING(sym) __DARWIN_SUF_1050 __DARWIN_SUF_64_BIT_INO_T __DARWIN_SUF_UNIX03)
#define __DARWIN_1050INODE64(sym)       __asm("_" __STRING(sym) __DARWIN_SUF_1050 __DARWIN_SUF_64_BIT_INO_T)

#define __DARWIN_EXTSN(sym)             __asm("_" __STRING(sym) __DARWIN_SUF_EXTSN)
#define __DARWIN_EXTSN_C(sym)           __asm("_" __STRING(sym) __DARWIN_SUF_EXTSN __DARWIN_SUF_NON_CANCELABLE)

/*
 * symbol release macros
 */
#if defined(__has_include)
#if __has_include(<sys/_symbol_aliasing.h>)
#include <sys/_symbol_aliasing.h>
#endif
#endif

#if defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
#define __DARWIN_ALIAS_STARTING(_mac, _iphone, x)   __DARWIN_ALIAS_STARTING_IPHONE_##_iphone(x)
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#define __DARWIN_ALIAS_STARTING(_mac, _iphone, x)   __DARWIN_ALIAS_STARTING_MAC_##_mac(x)
#else
#define __DARWIN_ALIAS_STARTING(_mac, _iphone, x)   x
#endif


/*
 * POSIX.1 requires that the macros we test be defined before any standard
 * header file is included.  This permits us to convert values for feature
 * testing, as necessary, using only _POSIX_C_SOURCE.
 *
 * Here's a quick run-down of the versions:
 *  defined(_POSIX_SOURCE)		1003.1-1988
 *  _POSIX_C_SOURCE == 1L		1003.1-1990
 *  _POSIX_C_SOURCE == 2L		1003.2-1992 C Language Binding Option
 *  _POSIX_C_SOURCE == 199309L		1003.1b-1993
 *  _POSIX_C_SOURCE == 199506L		1003.1c-1995, 1003.1i-1995,
 *					and the omnibus ISO/IEC 9945-1: 1996
 *  _POSIX_C_SOURCE == 200112L		1003.1-2001
 *  _POSIX_C_SOURCE == 200809L		1003.1-2008
 *
 * In addition, the X/Open Portability Guide, which is now the Single UNIX
 * Specification, defines a feature-test macro which indicates the version of
 * that specification, and which subsumes _POSIX_C_SOURCE.
 */

/* Deal with IEEE Std. 1003.1-1990, in which _POSIX_C_SOURCE == 1L. */
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE == 1L
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE         199009L
#endif

/* Deal with IEEE Std. 1003.2-1992, in which _POSIX_C_SOURCE == 2L. */
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE == 2L
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE         199209L
#endif

/* Deal with various X/Open Portability Guides and Single UNIX Spec. */
#ifdef _XOPEN_SOURCE
#if _XOPEN_SOURCE - 0L >= 700L && (!defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE - 0L < 200809L)
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE         200809L
#elif _XOPEN_SOURCE - 0L >= 600L && (!defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE - 0L < 200112L)
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE         200112L
#elif _XOPEN_SOURCE - 0L >= 500L && (!defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE - 0L < 199506L)
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE         199506L
#endif
#endif

/*
 * Deal with all versions of POSIX.  The ordering relative to the tests above is
 * important.
 */
#if defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE         198808L
#endif

/* POSIX C deprecation macros */
#if defined(__has_include)
#if __has_include(<sys/_posix_availability.h>)
#include <sys/_posix_availability.h>
#endif
#endif

#define __POSIX_C_DEPRECATED(ver) ___POSIX_C_DEPRECATED_STARTING_##ver

/*
 * Set a single macro which will always be defined and can be used to determine
 * the appropriate namespace.  For POSIX, these values will correspond to
 * _POSIX_C_SOURCE value.  Currently there are two additional levels corresponding
 * to ANSI (_ANSI_SOURCE) and Darwin extensions (_DARWIN_C_SOURCE)
 */
#define __DARWIN_C_ANSI         010000L
#define __DARWIN_C_FULL         900000L

#if   defined(_ANSI_SOURCE)
#define __DARWIN_C_LEVEL        __DARWIN_C_ANSI
#elif defined(_POSIX_C_SOURCE) && !defined(_DARWIN_C_SOURCE) && !defined(_NONSTD_SOURCE)
#define __DARWIN_C_LEVEL        _POSIX_C_SOURCE
#else
#define __DARWIN_C_LEVEL        __DARWIN_C_FULL
#endif

/* If the developer has neither requested a strict language mode nor a version
 * of POSIX, turn on functionality provided by __STDC_WANT_LIB_EXT1__ as part
 * of __DARWIN_C_FULL.
 */
#if !defined(__STDC_WANT_LIB_EXT1__) && !defined(__STRICT_ANSI__) && __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define __STDC_WANT_LIB_EXT1__ 1
#endif

/*
 * long long is not supported in c89 (__STRICT_ANSI__), but g++ -ansi and
 * c99 still want long longs.  While not perfect, we allow long longs for
 * g++.
 */
#if (defined(__STRICT_ANSI__) && (__STDC_VERSION__ - 0 < 199901L) && !defined(__GNUG__))
#define __DARWIN_NO_LONG_LONG 1
#else
#define __DARWIN_NO_LONG_LONG 0
#endif

/*****************************************
*  Public darwin-specific feature macros
*****************************************/

/*
 * _DARWIN_FEATURE_64_BIT_INODE indicates that the ino_t type is 64-bit, and
 * structures modified for 64-bit inodes (like struct stat) will be used.
 */
#if __DARWIN_64_BIT_INO_T
#define _DARWIN_FEATURE_64_BIT_INODE            1
#endif

/*
 * _DARWIN_FEATURE_64_ONLY_BIT_INODE indicates that the ino_t type may only
 * be 64-bit; there is no support for 32-bit ino_t when this macro is defined
 * (and non-zero).  There is no struct stat64 either, as the regular
 * struct stat will already be the 64-bit version.
 */
#if __DARWIN_ONLY_64_BIT_INO_T
#define _DARWIN_FEATURE_ONLY_64_BIT_INODE       1
#endif

/*
 * _DARWIN_FEATURE_ONLY_VERS_1050 indicates that only those APIs updated
 * in 10.5 exists; no pre-10.5 variants are available.
 */
#if __DARWIN_ONLY_VERS_1050
#define _DARWIN_FEATURE_ONLY_VERS_1050          1
#endif

/*
 * _DARWIN_FEATURE_ONLY_UNIX_CONFORMANCE indicates only UNIX conforming API
 * are available (the legacy BSD APIs are not available)
 */
#if __DARWIN_ONLY_UNIX_CONFORMANCE
#define _DARWIN_FEATURE_ONLY_UNIX_CONFORMANCE   1
#endif

/*
 * _DARWIN_FEATURE_UNIX_CONFORMANCE indicates whether UNIX conformance is on,
 * and specifies the conformance level (3 is SUSv3)
 */
#if __DARWIN_UNIX03
#define _DARWIN_FEATURE_UNIX_CONFORMANCE        3
#endif


/*
 * This macro casts away the qualifier from the variable
 *
 * Note: use at your own risk, removing qualifiers can result in
 * catastrophic run-time failures.
 */
#ifndef __CAST_AWAY_QUALIFIER
/*
 * XXX: this shouldn't ignore anything more than -Wcast-qual,
 * but the old implementation made it an almighty cast that
 * ignored everything, so things break left and right if you
 * make it only ignore -Wcast-qual.
 */
#ifdef __GNUC__ /* Check if the compiler is GCC */
#define __CAST_AWAY_QUALIFIER_PUSH() \
	_Pragma("GCC diagnostic push") \
	_Pragma("GCC diagnostic ignored \"-Wcast-qual\"") \
	_Pragma("GCC diagnostic ignored \"-Wcast-align\"") \
	_Pragma("GCC diagnostic ignored \"-Waddress-of-packed-member\"")
#elif defined(__clang__) /* Check if the compiler is Clang */
#define __CAST_AWAY_QUALIFIER_PUSH() \
	_Pragma("clang diagnostic push") \
	_Pragma("clang diagnostic ignored \"-Wcast-qual\"") \
	_Pragma("clang diagnostic ignored \"-Wcast-align\"") \
	_Pragma("clang diagnostic ignored \"-Waddress-of-packed-member\"")
#else
#define __CAST_AWAY_QUALIFIER_PUSH() /* Fallback for non-GCC and non-Clang compilers */
#endif

#ifdef __GNUC__ /* Check if the compiler is GCC */
#define __CAST_AWAY_QUALIFIER_POP() \
	_Pragma("GCC diagnostic pop")
#elif defined(__clang__) /* Check if the compiler is Clang */
#define __CAST_AWAY_QUALIFIER_POP() \
	_Pragma("clang diagnostic pop")
#else
#define __CAST_AWAY_QUALIFIER_POP() /* Fallback for non-GCC and non-Clang compilers */
#endif

#ifndef MAKE_COMPILER_HAPPY_H
#define MAKE_COMPILER_HAPPY_H

#ifdef __GNUC__ // Check if the compiler is GCC or Clang
#define make_compiler_happy(m) \
	({ \
		__CAST_AWAY_QUALIFIER_PUSH(); \
		m; \
		__CAST_AWAY_QUALIFIER_POP(); \
	})
#elif defined(__clang__) // Check if the compiler is Clang
#define make_compiler_happy(m) \
	({ \
		__CAST_AWAY_QUALIFIER_PUSH(); \
		m; \
		__CAST_AWAY_QUALIFIER_POP(); \
	})
#else
#define make_compiler_happy(m) m // Fallback for non-GCC and non-Clang compilers
#endif

#endif /* !MAKE_COMPILER_HAPPY_H */

#define __CAST_AWAY_QUALIFIER(variable, qualifier, type) \
	make_compiler_happy( \
		({ \
			((type)(__uintptr_t)(qualifier void *)(variable)); \
		}) \
	)

#endif /* !__CAST_AWAY_QUALIFIER */

/*
 * __XNU_PRIVATE_EXTERN is a linkage decoration indicating that a symbol can be
 * used from other compilation units, but not other libraries or executables.
 */
#ifndef __XNU_PRIVATE_EXTERN
#define __XNU_PRIVATE_EXTERN __attribute__((visibility("hidden")))
#endif

#if __has_include(<ptrcheck.h>)
#include <ptrcheck.h>
#else
#if __has_feature(bounds_safety)
#error -fbounds-safety is enabled, but <ptrcheck.h> is missing. \
        This will lead to difficult-to-diagnose compilation errors.
#endif /* __has_feature(bounds_safety) */

/*
 * We intentionally define to nothing pointer attributes which do not have an
 * impact on the ABI. __indexable and __bidi_indexable are not defined because
 * of the ABI incompatibility that makes the diagnostic preferable.
 */
#define __has_ptrcheck 0
#define __single
#define __unsafe_indexable
#define __counted_by(N)
#define __counted_by_or_null(N)
#define __sized_by(N)
#define __sized_by_or_null(N)
#define __ended_by(E)
#define __terminated_by(T)
#define __null_terminated

/*
 * Similarly, we intentionally define to nothing the
 * __ptrcheck_abi_assume_single and __ptrcheck_abi_assume_unsafe_indexable
 * macros because they do not lead to an ABI incompatibility. However, we do not
 * define the indexable and unsafe_indexable ones because the diagnostic is
 * better than the silent ABI break.
 */
#define __ptrcheck_abi_assume_single()
#define __ptrcheck_abi_assume_unsafe_indexable()

/* __unsafe_forge intrinsics are defined as regular C casts. */
#define __unsafe_forge_bidi_indexable(T, P, S) ((T)(P))
#define __unsafe_forge_single(T, P) ((T)(P))
#define __unsafe_forge_terminated_by(T, P, E) ((T)(P))
#define __unsafe_forge_null_terminated(T, P) ((T)(P))
#define __terminated_by_to_indexable(P) (P)
#define __unsafe_terminated_by_to_indexable(P) (P)
#define __null_terminated_to_indexable(P) (P)
#define __unsafe_null_terminated_to_indexable(P) (P)
#define __unsafe_terminated_by_from_indexable(T, P, ...) (P)
#define __unsafe_null_terminated_from_indexable(P, ...) (P)

/* decay operates normally; attribute is meaningless without pointer checks. */
#define __array_decay_dicards_count_in_parameters

/* this is a write-once variable; not useful without pointer checks. */
#define __unsafe_late_const

#define __ptrcheck_unavailable
#define __ptrcheck_unavailable_r(REPLACEMENT)

#endif /* !__has_include(<ptrcheck.h>) */


#define __ASSUME_PTR_ABI_SINGLE_BEGIN       __ptrcheck_abi_assume_single()
#define __ASSUME_PTR_ABI_SINGLE_END         __ptrcheck_abi_assume_unsafe_indexable()

#if __has_ptrcheck
#define __header_indexable                  __indexable
#define __header_bidi_indexable             __bidi_indexable
#else
#define __header_indexable
#define __header_bidi_indexable
#endif

/*
 * Architecture validation for current SDK
 */
#if !defined(__sys_cdefs_arch_unknown__) && defined(__i386__)
#elif !defined(__sys_cdefs_arch_unknown__) && defined(__x86_64__)
#elif !defined(__sys_cdefs_arch_unknown__) && defined(__arm__)
#elif !defined(__sys_cdefs_arch_unknown__) && defined(__arm64__)
#else
#error Unsupported architecture
#endif



#define __compiler_barrier() __asm__ __volatile__("" ::: "memory")

#if __has_attribute(enum_extensibility)
#define __enum_open __attribute__((__enum_extensibility__(open)))
#define __enum_closed __attribute__((__enum_extensibility__(closed)))
#else
#define __enum_open
#define __enum_closed
#endif // __has_attribute(enum_extensibility)

#if __has_attribute(flag_enum)
#define __enum_options __attribute__((__flag_enum__))
#else
#define __enum_options
#endif

/*
 * Similar to OS_ENUM/OS_CLOSED_ENUM/OS_OPTIONS/OS_CLOSED_OPTIONS
 *
 * This provides more advanced type checking on compilers supporting
 * the proper extensions, even in C.
 */
#if __has_feature(objc_fixed_enum) || __has_extension(cxx_fixed_enum) || \
        __has_extension(cxx_strong_enums)
#define __enum_decl(_name, _type, ...) \
	        typedef enum : _type __VA_ARGS__ __enum_open _name
#define __enum_closed_decl(_name, _type, ...) \
	        typedef enum : _type __VA_ARGS__ __enum_closed _name
#define __options_decl(_name, _type, ...) \
	        typedef enum : _type __VA_ARGS__ __enum_open __enum_options _name
#define __options_closed_decl(_name, _type, ...) \
	        typedef enum : _type __VA_ARGS__ __enum_closed __enum_options _name
#else
#define __enum_decl(_name, _type, ...) \
	        typedef _type _name; enum __VA_ARGS__ __enum_open
#define __enum_closed_decl(_name, _type, ...) \
	        typedef _type _name; enum __VA_ARGS__ __enum_closed
#define __options_decl(_name, _type, ...) \
	        typedef _type _name; enum __VA_ARGS__ __enum_open __enum_options
#define __options_closed_decl(_name, _type, ...) \
	        typedef _type _name; enum __VA_ARGS__ __enum_closed __enum_options
#endif



#define __kernel_ptr_semantics
#define __kernel_data_semantics
#define __kernel_dual_semantics



#if defined(KERNEL_PRIVATE) && \
        __has_attribute(xnu_data_size) && \
        __has_attribute(xnu_returns_data_pointer)
/*
 * Annotate function parameters to specify that they semantically
 * represent the size of a data-only backing storage.
 */
# define __xnu_data_size __attribute__((xnu_data_size))
/*
 * Annotate function declarations to specify that the pointer they return
 * points to a data-only backing storage.
 */
# define __xnu_returns_data_pointer __attribute__((xnu_returns_data_pointer))
#else
# define __xnu_data_size
# define __xnu_returns_data_pointer
#endif


#endif /* !_CDEFS_H_ */

