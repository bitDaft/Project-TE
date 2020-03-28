/*
 * File: Behaviour.inl
 * Project: Project-TE
 * Created Date: Saturday, March 28th 2020, 4:40:52 pm
 * Author: bitDaft
 * -----
 * Last Modified: Saturday, March 28th 2020 5:33:13 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2020 bitDaft
 */

template <typename T>
StateMachine<T> *const Behaviour::getStateMachine()
{
    BehaviourProxy<T> *t = dynamic_cast<BehaviourProxy<T> *>(this);
    return t->getStateMachine();
}