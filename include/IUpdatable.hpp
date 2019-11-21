/*
 * File: IUpdatable.hpp
 * Project: Project-TE
 * Created Date: Monday November 18th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday November 21st 2019 10:43:54 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef IUPDATABLE_HPP
#define IUPDATABLE_HPP

#include <SFML/System/Time.hpp>
class UpdateManager;

class IUpdatable
{
public:
  IUpdatable(int);
  virtual ~IUpdatable();
  void callUpdate(const sf::Time &);
  static void initialize(UpdateManager *);

protected:
private:
  virtual void update(const sf::Time &) = 0;

private:
  int _1;
  int _2;
  static UpdateManager *_u;
};

#endif