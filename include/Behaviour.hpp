/*
 * File: Behaviour.hpp
 * Project: Project-TE
 * Created Date: Saturday, March 28th 2020, 3:48:14 pm
 * Author: bitDaft
 * -----
 * Last Modified: Saturday, March 28th 2020 5:33:04 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2020 bitDaft
 */

#ifndef BEHAVIOUR_HPP
#define BEHAVIOUR_HPP

#include <SFML/System/Time.hpp>

#include "StateMachine.hpp"

/**
 * Inheriting from this class denotes the class as one that implements a behaviour
 */
class Behaviour
{
public:
    // constructor destructor
    Behaviour();
    virtual ~Behaviour();

    template <typename T>
	StateMachine<T> *const getStateMachine();
    
private:

};

#endif