/*
 * File: State.hpp
 * Project: Project-TE
 * Created Date: Friday, March 27th 2020, 8:06:37 am
 * Author: bitDaft
 * -----
 * Last Modified: Friday, March 27th 2020 6:11:27 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2020 bitDaft
 */

#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/System/Time.hpp>

template <class T>
class State
{
public:
    State();
    virtual ~State();

private:
    virtual void enter(T *);
    virtual void update(T *, const sf::Time &) = 0;
    virtual void exit(T *);
};

#include "State.inl"

#endif