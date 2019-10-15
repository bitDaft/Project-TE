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
  