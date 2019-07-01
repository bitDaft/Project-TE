/*
 * File: Delegate.hpp
 * Project: Project-TE
 * Created Date: Monday July 1st 2019
 * Author: bitDaft
 * -----
 * Last Modified: Monday July 1st 2019 8:00:42 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef DELEGATE_HPP
#define DELEGATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class delegate
{
public:
  delegate() : obj_type(0), stub_func(0) {}

  template <class T,typename B, B TMethod>
  // template <class T, T TMethod>
  static delegate from_method1(T *object_ptr)
  {
    delegate delegate;
    delegate.obj_type = object_ptr;
    delegate.stub_func = &method_stub<T, TMethod>;
    return delegate;
  }
  template <class T, void (T::*TMethod)(sf::RenderWindow &, sf::Event &)>
  // template <class T, T TMethod>
  static delegate from_method(T *object_ptr)
  {
    delegate delegate;
    delegate.obj_type = object_ptr;
    delegate.stub_func = &method_stub<T, TMethod>;
    return delegate;
  }

  void operator()(sf::RenderWindow &wind, sf::Event &ev) const
  {
    return (*stub_func)(obj_type, wind, ev);
  }

  operator bool() const
  {
    return stub_func != 0;
  }

  bool operator!() const
  {
    return !(operator bool());
  }

private:
  typedef void (*stub_func_type)(void *obj_ptr, sf::RenderWindow &, sf::Event &);

  void *obj_type;
  stub_func_type stub_func;

  template <class T, void (T::*TMethod)(sf::RenderWindow &, sf::Event &)>
  // template <class T, T TMethod>
  static void method_stub(void *object_ptr, sf::RenderWindow &wind, sf::Event &ev)
  {
    T *p = static_cast<T *>(object_ptr);
    return (p->*TMethod)(wind, ev);
  }
};

#endif