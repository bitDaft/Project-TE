/*
 * File: IUpdatable.hpp
 * Project: Project-TE
 * Created Date: Monday November 18th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday December 1st 2019 12:25:49 pm
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
  void enableUpdate();
  void disableUpdate();

private:
  virtual void update(const sf::Time &) = 0;

private:
  int _1;
  int _2;
  bool canUpdate;
  static UpdateManager *_u;
};

#endif