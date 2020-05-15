/* Threads compatibility routines for libgcc2 and libobjc.  */
/* Compile this one with gcc.  */
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#define _BUILDING_LIBGCC
#include "gthr-dkp.h"
#include <stddef.h>


int
__gthread_active_p (void)
{
  if (!__has_gthr_impl(active)) {
    return 0;
  }

  return __gthr_impl_active();
}

int
__gthread_create (__gthread_t *__threadid, void *(*__func) (void*),
                  void *__args)
{
  if (!__has_gthr_impl(create)) {
    return -1;
  }

  return __gthr_impl_create(__threadid, __func, __args);
}

int
__gthread_join (__gthread_t __threadid, void **__value_ptr)
{
  if (!__has_gthr_impl(join)) {
    return -1;
  }

  return __gthr_impl_join(__threadid, __value_ptr);
}

int
__gthread_detach (__gthread_t __threadid)
{
  if (!__has_gthr_impl(detach)) {
    return -1;
  }

  return __gthr_impl_detach(__threadid);
}

int
__gthread_equal (__gthread_t __t1, __gthread_t __t2)
{
  if (!__has_gthr_impl(equal)) {
    return -1;
  }

  return __gthr_impl_equal(__t1, __t2);
}

__gthread_t
__gthread_self (void)
{
  if (!__has_gthr_impl(self)) {
    __gthread_t result = { 0 };
    return result;
  }

  return __gthr_impl_self();
}

int
__gthread_yield (void)
{
  if (!__has_gthr_impl(yield)) {
    return -1;
  }

  return __gthr_impl_yield();
}

int
__gthread_once (__gthread_once_t *__once, void (*__func) (void))
{
  if (!__has_gthr_impl(once)) {
    return -1;
  }

  return __gthr_impl_once(__once, __func);
}

int
__gthread_key_create (__gthread_key_t *__key, void (*__dtor) (void *))
{
  if (!__has_gthr_impl(key_create)) {
    return -1;
  }

  return __gthr_impl_key_create(__key, __dtor);
}

int
__gthread_key_delete (__gthread_key_t __key)
{
  if (!__has_gthr_impl(key_delete)) {
    return -1;
  }

  return __gthr_impl_key_delete(__key);
}

void *
__gthread_getspecific (__gthread_key_t __key)
{
  if (!__has_gthr_impl(getspecific)) {
    return NULL;
  }

  return __gthr_impl_getspecific(__key);
}

int
__gthread_setspecific (__gthread_key_t __key, const void *__ptr)
{
  if (!__has_gthr_impl(setspecific)) {
    return -1;
  }

  return __gthr_impl_setspecific(__key, __ptr);
}

void
__gthread_mutex_init_function (__gthread_mutex_t *__mutex)
{
  if (__has_gthr_impl(mutex_init_function)) {
    __gthr_impl_mutex_init_function(__mutex);
  }
}

int
__gthread_mutex_destroy (__gthread_mutex_t *__mutex)
{
  if (!__has_gthr_impl(mutex_destroy)) {
    return -1;
  }

  return __gthr_impl_mutex_destroy(__mutex);
}

int
__gthread_mutex_lock (__gthread_mutex_t *__mutex)
{
  if (!__has_gthr_impl(mutex_lock)) {
    return -1;
  }

  return __gthr_impl_mutex_lock(__mutex);
}

int
__gthread_mutex_trylock (__gthread_mutex_t *__mutex)
{
  if (!__has_gthr_impl(mutex_trylock)) {
    return -1;
  }

  return __gthr_impl_mutex_trylock(__mutex);
}

int
__gthread_mutex_unlock (__gthread_mutex_t *__mutex)
{
  if (!__has_gthr_impl(mutex_unlock)) {
    return -1;
  }

  return __gthr_impl_mutex_unlock(__mutex);
}

int
__gthread_recursive_mutex_init_function (__gthread_recursive_mutex_t *__mutex)
{
  if (!__has_gthr_impl(recursive_mutex_init_function)) {
    return -1;
  }

  return __gthr_impl_recursive_mutex_init_function(__mutex);
}

int
__gthread_recursive_mutex_lock (__gthread_recursive_mutex_t *__mutex)
{
  if (!__has_gthr_impl(recursive_mutex_lock)) {
    return -1;
  }

  return __gthr_impl_recursive_mutex_lock(__mutex);
}

int
__gthread_recursive_mutex_trylock (__gthread_recursive_mutex_t *__mutex)
{
  if (!__has_gthr_impl(recursive_mutex_trylock)) {
    return -1;
  }

  return __gthr_impl_recursive_mutex_trylock(__mutex);
}

int
__gthread_recursive_mutex_unlock (__gthread_recursive_mutex_t *__mutex)
{
  if (!__has_gthr_impl(recursive_mutex_unlock)) {
    return -1;
  }

  return __gthr_impl_recursive_mutex_unlock(__mutex);
}

int
__gthread_recursive_mutex_destroy (__gthread_recursive_mutex_t *__mutex)
{
  if (!__has_gthr_impl(recursive_mutex_destroy)) {
    return -1;
  }

  return __gthr_impl_recursive_mutex_destroy(__mutex);
}

void
__gthread_cond_init_function (__gthread_cond_t *__cond)
{
  if (__has_gthr_impl(cond_init_function)) {
    __gthr_impl_cond_init_function(__cond);
  }
}

int
__gthread_cond_broadcast (__gthread_cond_t *__cond)
{
  if (!__has_gthr_impl(cond_broadcast)) {
    return -1;
  }

  return __gthr_impl_cond_broadcast(__cond);
}

int
__gthread_cond_signal (__gthread_cond_t *__cond)
{
  if (!__has_gthr_impl(cond_signal)) {
    return -1;
  }

  return __gthr_impl_cond_signal(__cond);
}

int
__gthread_cond_wait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex)
{
  if (!__has_gthr_impl(cond_wait)) {
    return -1;
  }

  return __gthr_impl_cond_wait(__cond, __mutex);
}

int
__gthread_cond_timedwait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex,
                          const __gthread_time_t *__abs_timeout)
{
  if (!__has_gthr_impl(cond_timedwait)) {
    return -1;
  }

  return __gthr_impl_cond_timedwait(__cond, __mutex, __abs_timeout);
}

int
__gthread_cond_wait_recursive (__gthread_cond_t *__cond,
                               __gthread_recursive_mutex_t *__mutex)
{
  if (!__has_gthr_impl(cond_wait_recursive)) {
    return -1;
  }

  return __gthr_impl_cond_wait_recursive(__cond, __mutex);
}

int
__gthread_cond_destroy (__gthread_cond_t* __cond)
{
  if (!__has_gthr_impl(cond_destroy)) {
    return -1;
  }

  return __gthr_impl_cond_destroy(__cond);
}
