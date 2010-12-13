/*
      Copyright (C) 2010 Nicolas Bourdaud <nicolas.bourdaud@epfl.ch>

    This file is part of the rtfilter library

    The rtfilter library is free software: you can redistribute it and/or
    modify it under the terms of the version 3 of the GNU General Public
    License as published by the Free Software Foundation.
  
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef COMPLEX_SIMD_H
#define COMPLEX_SIMD_H

#include <pmmintrin.h>

static inline 
__m128 complex_mul_ps(__m128 a, __m128 b)
{
	//a0+ia1 * b0+ib1 = a0*(b0+ib1) + ia1*(b0+ib1)
	//                = (a0b0-a1b1) + i(a1b0+a0b1)
	__m128 pl, ph, coef;
	coef = _mm_moveldup_ps(a);
	pl = _mm_mul_ps(coef, b);
	coef = _mm_movehdup_ps(a);
	ph = _mm_mul_ps(coef, b);
	ph = _mm_shuffle_ps(ph, ph, _MM_SHUFFLE(2,3,0,1));
	return _mm_addsub_ps(pl, ph);
}


static inline
__m128 realcomp_mul_ps(__m128 a, __m128 b, int part)
{
	__m128 in;
	if (part == 0)
		in = _mm_shuffle_ps(b, b, _MM_SHUFFLE(1,1,0,0));
	else
		in = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3,3,2,2));
	return _mm_mul_ps(in, a);
}


static inline
__m128 complex_set1_ps(complex float a)
{
	/*__m128 c;
	c = _mm_loadl_pi(c, (const void*)&a);
	c = _mm_loadh_pi(c, (const void*)&a);
	return c;*/
	return _mm_castpd_ps(_mm_loaddup_pd((const void*)&a));
}


static inline 
__m128d complex_mul_pd(__m128d a, __m128d b)
{
	//a0+ia1 * b0+ib1 = a0*(b0+ib1) + ia1*(b0+ib1)
	//                = (a0b0-a1b1) + i(a1b0+a0b1)
	__m128d pl, ph, coef;
	coef = _mm_movedup_pd(a);
	pl = _mm_mul_pd(coef, b);
	coef = _mm_shuffle_pd(a, a, _MM_SHUFFLE2(1,1));
	ph = _mm_mul_pd(coef, b);
	ph = _mm_shuffle_pd(ph, ph, _MM_SHUFFLE2(0,1));
	return _mm_addsub_pd(pl, ph);
}


static inline
__m128d realcomp_mul_pd(__m128d a, __m128d b, int part)
{
	__m128d in;
	if (part == 0)
		in = _mm_shuffle_pd(b, b, _MM_SHUFFLE2(0,0));
	else
		in = _mm_shuffle_pd(b, b, _MM_SHUFFLE2(1,1));
	return _mm_mul_pd(in, a);
}


static inline
__m128d complex_set1_pd(complex double a)
{
	/*__m128 c;
	c = _mm_loadl_pi(c, (const void*)&a);
	c = _mm_loadh_pi(c, (const void*)&a);
	return c;*/
	return _mm_loadu_pd((const double*)&a);
}


#endif /* COMPLEX_SIMD_H */
