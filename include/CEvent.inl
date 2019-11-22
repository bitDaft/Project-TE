/*
 * File: CEvent.inl
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday November 22nd 2019 9:01:54 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "CEvent.hpp"

template <typename dataType>
CEVENT<dataType>::CEVENT() : EventProxy<CEVENT<dataType>>(-1),
                             data(NULL),
                             preventClear(false)
{
}

template <typename dataType>
CEVENT<dataType>::CEVENT(int t, dataType *d) : EventProxy<CEVENT<dataType>>(t),
                                               data(d),
                                               preventClear(false)
{
}

template <typename dataType>
CEVENT<dataType>::~CEVENT()
{
  data = NULL;
}

template <typename dataType>
dataType *CEVENT<dataType>::getData()
{
  return data;
}

template <typename dataType>
void CEVENT<dataType>::clearT()
{
  if (!preventClear)
  {
    delete data;
  }
}
template <typename dataType>
void CEVENT<dataType>::preventT()
{
  preventClear = true;
}
