/*
 * File: InputManager.hpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 2:45:35 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */
#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "ActionMapper.hpp"
#include <vector>
#include <SFML/Window/Event.hpp>
#include <Entity.hpp>

class InputManager : private sf::NonCopyable
{
public:
  InputManager(Entity *);
  ~InputManager();

  void setActionMapper(ActionMapper *);
  void processInputsRealtime();
  void processInputsEvent(sf::Event::KeyEvent &);
  // template <auto T>
  // void bindActionToReaction(unsigned int action)
  // {
  //   using className = typename point_to_mem<decltype(T)>::class_type;
  //   className *tthis = static_cast<className *>(objThis);
  //   _reactionMap[action] = delegate::from_method<className, T>(tthis);
  // }
  // void bindActionToReaction(unsigned int action, delegate callback);
  // void executeCallback(unsigned int action, sf::Event &event);

  // void clearBinding(unsigned int key);

  // void clearAllBinding();

private:
  // it has a actionmapper obj
  // it contains a stack
  ActionMapper *_actionMapper;
  std::vector<std::shared_ptr<Entity>> _itemList;
};

#endif