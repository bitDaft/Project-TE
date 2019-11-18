Random thoughts and musings

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
  
  physics system
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
  - each of these draw functions can simple return an image which will be rendered once for efficiency.
  - it also allows us to do postfx and shader stuff later on.
  - the issue lies in the design of this system and how to merge it with current system in place.
  - Game will have a state machine, basically screens, each screen transitions to different state.
  - we can use a stack. but we need to traverse from bottom to top for all of it
  - Game generates an sf::Image. goes through state stack, checks drawable flag, if true draws onto image and return image.
  - This image is then sent to the next state till top. drawing all drawable states.
  - Then a queue of all drawable objects is traversed. for each object through its state stack from bottom to top drawing each state that is valid
  - this final image is then rendered to the screen . so only one render call occurs and postfx can be done on image before render.
  - same goes for update queue and updation of game and entities.

## implementing state system
  - we need new queue system for updation and drawing.
  - seems almost same system. just change in whether drawing or updating.
  - each drawing or updating queue will have list of objects which will be traversed to do respective function.
  - it will loop through each object and run its respective function 
  - each of these stored objects will inherit from an interface representing drawable and/or updatable.
  - should there be multiple queues for different layers of drawing / different priority for updation? probably. lets make it adjustable.
  - eg drawable layers background, main, and foreground layer for drawing.
  - eg updation layers static background, particles, main entities etc. 
  - once these objects are created push them onto stack and then each loop go through these objects and run its function
  - for drawable the order is important as to what gets drawn first. which led to the multiple queue idea.
  - what about using priority queue to arrange entities so painters algorithm takes place for proper drawing
  - eg for drawing lets have 3 layer. background, main, foreground. each has a priority from 1-5.
  - i think that can work. the programmer can decide the number of layers and the priority of each object.
  - almost follows similar structure to drawing on browser for each z index and priority depending on html structure for same z index
  - lower the priority number the farther it is drawn.
  - 0 be the default priority and the limit of priority can be self imposed by dev. 
  - how will this system work with states?
  - if state is drawing should the state inherit drawable? but we dont want all states to have draw and update if they are not needed
  - what if the entity is inheriting drawable but also has a state system to draw? should the user manually call the states draw?
  - since there is a state stack of drawing but the drawing priority of each state and may be different and may be interleaved with other entities states?
  - this is giving me a headache...
  - back to basics... state system is used for updations. should rendering be done by state?
  - let the object do the rendering?
  - if the object does the rendering how does an overlay pause menu with transparency work?
  - we can use scene graphs for this. each screen may have a scene graph
  - but changing to pause state is a game state and not another object. 
  - but if we wanted the game to be rendered below the pause screen both the gameplay state and the pause state will need to be rendered
  - this is basically rendering of two states over one each other at the same time.
  - if only one state of each object need to be rendered then no issue arises.
  - but here we need to render two different states with objects that are specific to each state
  - so if a state goes out of the render pipeline then any objects under it also should not be rendered.
  - like the gameplay state which causes the player to be render. but if not gameplay dont render the player either.
  - but if in pause and i need the last game screen which will lead to the player also needing to be rendered and then render the pause screen on top of it
  - so each of these screens may have its own rendered queue
  - the reason for separate render queue is dont want to loop through the queue if that screen os not being rendered.
  - if the screen is not rendered each of the object will need to be updated to not render every time. unnecessary.
  - the thing is this may not only be relevant for the game state but may arise in any of the object substates.
  - scene graph?
  - so no need to create a specific screen class? right?
  - implement it into the state system itself?
  - let the state system have an update and draw queue? 
  - should the update be not attached to state?
  - the update can be global. as each object has updatable flag. if set update else not. so all updatables can be pushed onto global queue.
  - what about destruction of an object and removal of it from the update queue?
  - once an object is destroyed move it up the chain to game to remove it or send an event saying an object has died and an id handle so that it may be removed from the queue.
  - cool.. glbal updation can work this way. i think this is feasable.

  - ## notes on global updation.
  - there will be updatable interface for inheriting by objects needing updation.
  - the updation system will have a queue containing these updatable obejcts..
  - as before should there be multiple queues to allow for priority as z-index
  - objects should be pushed automatically or manually have to be added every time a new object is created?
  - should probably be automatic but should allow the dev to configure the priority and to which queue it should go to.maybe?
  - ### further notes.
    - later we might need to have movement update, physics update and stuff. so that it resembles an entity system. and can update the same aspect at the same time instead of going through all of it at once and having race condition issue

  - every game loop it will loop through this queue and execute their update function
  - since we are not updating by components like movement, physics, collision etc and updating the entire object at a time the ordering in the queue might matter if something significant arises. will need to test the impact of this ordering.
  - since the game is updating in small chunks, i dont think it will affect it to that high degree. if not processed in one frame it will be processed in the next. 
  - since we have fast update cycles it should appear smooth. test at what point does it actually might affect gameplay.
  - during construction of entities itself specify the queue and the priority in the queue, otherwise default 1 queue and same priority.
  - updation seems like done. this can be implemented.
  - if entity is inheriting interface then the updation should be auotmativally delegated to the state machine if state machine is used.
  - in construction why not also accept a parameter pointer to state machine if state machine exist, in which case the default update function just calls the states update function.?so the person might not have to write the update code delegation to state manually
  - seems pretty good system for updation. 
  - any other issues?
  - cant think of any at the moment
  - this can be implemented, and it also has a solution for updation if state machine is used.
  - should look into a way where pointer to state machine can be sent automatically while construction
  - so only objects needing updation may be added to the queue and processed.
  - what about an animation system. should the animation be part of this updation code?
  - lets think about it later.
  - will this system need to interact with drawing system.? dont think so.
  - should keep the two separate
  - but consider if we wanted to pause the game
  - the game should be paused but the new game state like pause its menu should still be updating
  - so should each screen of game have an update queue. so once the state of game changes then only objects in those states update.
  - but this binds updation system to state system. same issue as drawing system.
  - once any state is set non updatable then all objects under it also stop updating. so no need to go to each object and pause it. 
  - this pause issue is the only roadblock to global updation system
  - once a solution has been found updation system can be implemented. 
  - if a solution can be found here it can passed onto drawable and allow for state with drawing too.
  - now that i think about it only the game states need an update queue, all the objects underneath it can be stored inside this queue
  - should we create a specific overriden class for state machine simply for game class for update queue.
  - now that i think about it most(almost all) of the objects that will need updating and all will be part of gameplay
  - will there be any objects which will be used in menu state or pause state?
  - if not i can just forego the updation loop while not in the gameplay state, thus no updation will need to occur for objects if the state is in pause state.
  - rendering can occur on a different pipeline, so forget anout rendering for now,
  - let me try to think of some objects which mught be in different states other than gameplay which might need updation.
  - consider a few basic states of a game: menu, options, credits, play, pause, stop, reload save, end?, (these are top of my head)
  - the update function will basically handle position, movement, interaction, proximity triggers, inputs reactions,sprite shifting?, (of the top of my head)
  - in menu options etc what kind of objects might need updation?
  - there will mostly be just ui elements.. so check whether collision or in or out, and click callback. the object itself does not update anything in there.is there any objects that might need updation? cant think of any.
  - so the system we will go for the above pause issue will be to simply stop processing the update queue if the state aint play state.
  - since we dont have as statemachine setup lets thinkhow it will integrate and work with the state system
  - the game will inherit from state machine, and initialise it, there will be an inital default play state so incase no states are defined the default state play will be directly be used. so no setup necessary and all the updation code will work
  - in case new states needed to be added(most likely will be) the user will need to override the initial state of game state machine and since each state will encapsulate the transitions there will have to be a code to go to the defaut play state from some state,
  -  so only the objcets will need to be initialised to be added to the update queue and there will be no unnecessaru manual update calls for each object. 
  -  create 2 new functions for startUpdatingObjects() and stopUpdatingObjects() so no need to have default play state. if custom states are made the user can call start update and stop update in the respective start and end functions of the state. so in case it needs updating in other states it can update also. this can work
  -  this seems flexible. so the user can start or disable when needed and no need for its own state at the start of the game
  -  lets go with this solution for now and see if we hit any roadblocks.
  
  ### implementing global updation queue
  - an updation class which contains a queue. 
  - it should be initialised at the start.
  - the number of queues needed can be set for priority stuff.
  - at every game loop the updation of this is called.
  - it will go through each queue in order and call each objects update function.
  - 2 functions toggle whether to allow or prevent updation.
  - the game is in no updation mode at the start and will have to call function to allow updation.
  - an interface updatable exist to allow objects to be updated which will be stored in the queue.
  - can the execution of specific queue be disabled. yes i think this is needed. so partial queues can run
  - lets get to developing then.  
    
  - lets now think about state system and drawing 
  - should the two be part of the same system
  - depending on the state the sprite to be drawn can change. like running jumping falling etc
  - even the game class can have main, running pause states.
  - but consider drawing a pause screen on top of a game running screen.
  - here there are other objects that are drawn if the game screen is drawn. then we need to draw the pause screen
  - so there is a hierarchy of drawing objects
  - if one object is not drawn any under it is also not drawn.