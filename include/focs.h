/* focs.h - Functional Open C Structures
 * Copyright (C) 2018 Quytelda Kahja
 *
 * This file is part of focs.
 *
 * focs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * focs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with focs.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef __FOCS_H
#define __FOCS_H

#define __nonulls __attribute__((nonnull))
#define __pure    __attribute__((pure))
#define __unused  __attribute__((unused))

/**
 * Pick the minimum of two comparable values.
 * @param m First comparable value
 * @param n Second comparable value
 *
 * @return the the lesser of two comparable parameters `m` and `n`.
 * In the case that `m` and `n` are compared and found to be equal,
 * then `m` is returned.
 */
#define MIN(m, n)				\
	({					\
		typeof(m) m_ = m;		\
		typeof(n) n_ = n;		\
		((m_ <= n_) ? m_ : n_);		\
	})

/**
 * Pick the maximum of two comparable values.
 * @param m First comparable value
 * @param n Second comparable value
 *
 * @return the the greater of two comparable parameters `m` and `n`.
 * In the case that `m` and `n` are compared and found to be equal,
 * then `m` is returned.
 */
#define MAX(m, n)				\
	({					\
		typeof(m) m_ = m;		\
		typeof(n) n_ = n;		\
		((m_ >= n_) ? m_ : n_);		\
	})

/**
 * Set errno and return from the current function with some value.
 * @param err The error number to set errno to
 * @param val The optional value to return
 *
 * Set errno to `err`, then return from the current function.  The value
 * supplied as the second argument will be the return value of the function.
 */
#define return_with_errno(err, val)		\
	({					\
		errno = err;			\
		return val;			\
	})

/**
 * Set errno then jump to the specified label.
 * @param err The error number to set errno to
 * @param lable The label to jump to
 *
 * Set errno to `err`, then execute `goto label` inside the function,
 * effectively jumping to `label`.
 */
#define goto_with_errno(err, label)		\
	({					\
		errno = err;			\
		goto label;			\
	})

/**
 * Free a pointer, then set it's value to NULL.
 * @param ptr A pointer to allocated memory to free
 *
 * If `ptr` is NULL already, this macro has no effect.
 */
#define free_null(ptr)				\
	({					\
		free(ptr);			\
		ptr = NULL;			\
	})

/**
 * Modulo operation
 * @param a The divisor
 * @param n The dividend
 *
 * This modulo operation is distinct from the ISO C99 remainder operation
 * represented by the operator '%', which will produce negative results
 * if the divisor is negative and always takes the sign of the dividend.
 *
 * This operation is guaranteed to always return a positive integer.  Both `a`
 * and `n` should be signed types if either `a` or `n` may be negative.
 *
 * See: https://en.wikipedia.org/wiki/Modulo_operation
 *
 * @return The remainder of the quotient `(a / n)`.
 */
#define mod(a, n)				\
	({					\
		typeof(a) a_ = (a);		\
		typeof(n) n_ = (n);		\
		((a_ % n_) + n_) % n_;		\
	})

/**
 * Check if a memory address is block aligned.
 * @param addr   The address or address span to check
 * @param size   The block size in bytes
 * @param offset The offset for the beginning of the block list
 *
 * @return `true` if `addr` is aligned to `size` with `offset`.
 */
#define aligned(addr, size, offset) (((addr) - (offset)) % (size) == 0)

#endif /* __FOCS_H */
