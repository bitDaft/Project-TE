## Other Notes
  - current entity update system is managed manually. change it to some queue based system for auto updation.
  - animation system
  - dynamics sytem
  - spriting system
  - physics system


## state sytsem notes

  - want to able to simply define states in a fsm without state objects.
  - single state object callback functions for all states of fsm
  - fsm state update callback binding
  - kind of like the visitor pattern
  - eg:-
    ```c++
    // IS THIS EVEN FEASABLE ???
    // DRAWBACKS ???
    class FSM{
      ...
    };
    class CallbackObj{
      void callback1(...){...}
      void callback2(...){...}
      void callback3(...){...}
    };

    FSM fsm;
    CallbackObj cObj;

    fsm.addState("state1"); // add states
    fsm.addState("state2");
    fsm.addState("state3");
    fsm.setStartState("state1"); // set start state
    fsm.bind("state1","state2",trigger1); // unidirectional binding
    fsm.bind("state2","state3",trigger2); 
    fsm.bind("state3","state2",trigger3); 
    fsm.bindc<callback1>("state1",cObj); // callback binding
    fsm.bindc<callback2>("state2",cObj); 
    fsm.bindc<callback3>("state3",cObj); 
    fsm.finalize(); // finish setting up fsm
    ```

  ***WHAT ARE TRIGGERS!?!111!???***  
  hmmmmmm.. let me see  
  
  physics sytem
  animation system

## new insights into state system

  - after research and thought new ideas of state system has sent the project into haitus.
  - have to redesign the entire state system involving new ideas
  - the new features / ideas etc will be outline below and the changes required of the state system

## the epiphany of state system
  - the state system can also be used to draw the state of something and have the update function too
  - consider drawing for now
  - if we need screens that need to be drawn on top of another due to state change we can simply loop through the state and execute draw for each screen
  - similarly for their execution
  - we can have simple flags dictating whether to be drawable and updatable
  - this allows to control drawing and updation of each screen. so states becomes screens for all
  - each of these draw functions can simple return an image which will be rendered once for efficiendy.
  - it also allows us to do postfx and shader stuff later on.
  - the issue lies in the design of this system and how to merge it with current system in place.