/*
 * File: BehaviourProxy.hpp
 * Project: Project-TE
 * Created Date: Saturday, March 28th 2020, 4:34:21 pm
 * Author: bitDaft
 * -----
 * Last Modified: Saturday, March 28th 2020 5:35:44 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2020 bitDaft
 */

#ifndef BEHAVIOURPROXY_HPP
#define BEHAVIOURPROXY_HPP

#include <SFML/System/Time.hpp>

#include "Behaviour.hpp"
#include "StateMachine.hpp"
#include "State.hpp"

template <typename T>
class BehaviourProxy : class Behaviour
{
public:
    // constructor destructor
    BehaviourProxy(State<T> *, State<T> * = nullptr);
    virtual ~BehaviourProxy();

    virtual void update(const sf::Time &) = 0;

    StateMachine<T> *const getStateMachine();

private:
    StateMachine<T> *_SM;
};

#include "BehaviourProxy.inl"

#endif