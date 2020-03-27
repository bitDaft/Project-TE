/*
 * File: StateMachine.inl
 * Project: Project-TE
 * Created Date: Friday, March 27th 2020, 5:50:26 pm
 * Author: bitDaft
 * -----
 * Last Modified: Friday, March 27th 2020 7:41:54 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2020 bitDaft
 */

template <class T>
StateMachine<T>::StateMachine(T *obj_entity)
    : entity(obj_entity),
      currentState(nullptr),
      globalState(nullptr)
{
}

template <class T>
StateMachine<T>::~StateMachine() {}

template <class T>
void StateMachine<T>::setCurrentState(State<T> *newCurrentState)
{
    currentState = newCurrentState;
}

template <class T>
void StateMachine<T>::setGlobalState(State<T> *newGlobalState)
{
    globalState = newGlobalState;
}

template <class T>
void StateMachine<T>::update(const sf::Time &dt)
{
    if (globalState)
    {
        globalState->update(entity, dt);
    }
    if (currentState)
    {
        currentState->update(entity, dt);
    }
}

template <class T>
void StateMachine<T>::transitionToState(State<T> *nextState)
{
    if (!nextState)
    {
        return;
    }

    currentState->exit(entity);
    currentState = nextState;
    currentState->enter(entity);
}
