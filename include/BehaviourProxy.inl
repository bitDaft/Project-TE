/*
 * File: BehaviourProxy.inl
 * Project: Project-TE
 * Created Date: Saturday, March 28th 2020, 4:36:41 pm
 * Author: bitDaft
 * -----
 * Last Modified: Saturday, March 28th 2020 5:32:18 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2020 bitDaft
 */


template <typename T>
BehaviourProxy<T>::BehaviourProxy(State<T> *current,State<T> *global){
    _SM = new StateMachine<T>(dynamic_cast<T *>(this));
    _SM->setCurrentState(current);
    _SM->setGlobalState(current);
}

template <typename T>
BehaviourProxy<T>::~BehaviourProxy(){
    delete _SM;
}

template <typename T>
StateMachine<T> *const BehaviourProxy<T>::getStateMachine{
    return _SM;
}