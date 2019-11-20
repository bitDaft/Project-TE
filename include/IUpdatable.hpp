/*
 * File: IUpdatable.hpp
 * Project: Project-TE
 * Created Date: Monday November 18th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday November 20th 2019 11:02:17 am
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
  static UpdateManager *_u;
};

#endif