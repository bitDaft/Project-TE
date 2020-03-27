/*
 * File: State.hpp
 * Project: Project-TE
 * Created Date: Friday, March 27th 2020, 8:06:37 am
 * Author: bitDaft
 * -----
 * Last Modified: Friday, March 27th 2020 8:11:40 am
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2020 bitDaft
 */


#ifndef ACTIONMAPPER_HPP
#define ACTIONMAPPER_HPP

template<class T>
class State {
public:
    State();
    virtual ~State();
private:
    virtual void Enter(T *);
    virtual void Update(T *)=0;
    virtual void Exit(T *);
};

#include "State.inl"

#endif