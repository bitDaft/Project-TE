/*
 * File: StateMachine.hpp
 * Project: Project-TE
 * Created Date: Friday, March 27th 2020, 5:42:39 pm
 * Author: bitDaft
 * -----
 * Last Modified: Friday, March 27th 2020 6:11:12 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2020 bitDaft
 */

#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <SFML/System/Time.hpp>

#include "State.hpp"

template <class T>
class StateMachine
{
public:
    StateMachine(T *);
    virtual ~StateMachine();

    void setCurrentState(State<T> *);
    void setGlobalState(State<T> *);

    void update(const sf::Time &);
    void transitionToState(State<T> *);

private:
    T *entity;
    State<T> *currentState;
    State<T> *globalState;
};

#include "StateMachine.inl"

#endif