/*
 * File: t_traits.hpp
 * Project: Project-TE
 * Created Date: Friday August 30th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday September 1st 2019 11:07:21 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef TTRAITS_HPP
#define TTRAITS_HPP

/**
 * A templated class used for member function trait extraction
 */
template <typename T>
struct point_to_mem;

/**
 * A templated class used for member function trait extraction
 */
template <class C, typename T>
struct point_to_mem<T C::*>
{
  using member_type = T;
  using class_type = C;
};

template <typename T>
struct is_pointer
{
  static const bool value = false;
  using class_type = T;
};

template <typename T>
struct is_pointer<T *>
{
  static const bool value = true;
  using class_type = T;
};

#endif