/*
 * File: Delegate.hpp
 * Project: Project-TE
 * Created Date: Monday July 1st 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 3:26:28 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef DELEGATE_HPP
#define DELEGATE_HPP

#include <SFML/Window/Event.hpp>

/**
 * Delegate/Closure class that holds a member function with context
 * Used for Callback mechanism for input
 * ?May be used for custom event callbacks also
 */
class delegate
{
public:
  delegate() : obj_type(0), stub_func(0) {}
  /**
   * static function which stores the pointer to object and the related function
   * @template T The type of the object to delegate from
   * @template TMethod The funtion to delegate
   * @param T* contains the object to call the callback on
   * @return delegate A delegate object
   */
  template <class T, bool (T::*TMethod)(sf::Event &)>
  static delegate from_method(T *object_ptr)
  {
    delegate delegate;
    delegate.obj_type = object_ptr;
    delegate.stub_func = &method_stub<T, TMethod>;
    return delegate;
  }
  /**
   * overloaded operator () to call the stored function
   * @param sf::Event & The event that occured to call the callback
   * @return bool whether to continue on the daisy chain or stop 
   */
  bool operator()(sf::Event &ev) const
  {
    return (*stub_func)(obj_type, ev);
  }

  /**
   * check for intilisation of the delegate
   */
  operator bool() const
  {
    return stub_func != 0;
  }

  bool operator!() const
  {
    return !(operator bool());
  }

private:
  typedef bool (*stub_func_type)(void *obj_ptr, sf::Event &);

  void *obj_type;
  stub_func_type stub_func;

  /**
   * method stub actually calls the function 
   * a stub instance is stored as the function pointer
   * @template T The type of the object to delegate from
   * @template TMethod The funtion to delegate
   * @param void * contains the object to call callback on 
   * @param sf::Event & The evnet that occured
   * @return bool whether to continue the daisy chain or stop
   */
  template <class T, bool (T::*TMethod)(sf::Event &)>
  static bool method_stub(void *object_ptr, sf::Event &ev)
  {
    T *p = static_cast<T *>(object_ptr);
    return (p->*TMethod)(ev);
  }
};

#endif