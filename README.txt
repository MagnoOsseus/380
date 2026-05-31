The 4 main trees in the project are the farmer, the chicken, the rooster, and the wolf. Each one has different behaviors depending on what is happening in the simulation.

Decorators: D_DaytimeOnly,D_CooldownFly,D_CooldownFight
Leaf nodes: L_IsNighttime, L_GoToSleep, L_GoHome, L_HungryAnimals, L_FeedAnimals, L_CutDown, L_Lunchtime, L_GoLunch, L_WakeUp
L_ChaseWolf, L_IsPanicking, L_RunCrazy, L_MakePanicNoise, L_IsHungry, L_ReadyToLayEgg, L_LayEgg, L_WantsToFight, L_FightOtherChicken
L_WanderLikeChicken, L_JustBecameDay, L_CrowLoudly, L_WantsToFly, L_TryToFlyAndFail, L_IsFarmerChasing
L_FleeToSafety, L_EatChicken, L_TriggerPanicEvent, _FindTargetChicken, ChaseChicken ,L_WantsToSleep
L_SleepDaytime, L_WanderRandomly, L_WolfAlertActive,L_GoToSleepArea, L_GoToWaitForFood
L_WaitForFood,L_IsNightMature, L_IsThirsty,L_GoToWater, L_DrinkWater

The FarmSimState class is used to store important information about the whole simulation. For example, it keeps track of things like wolf alerts, panic states, action timers, and important positions in the map. Basically, this class helps all the characters share information and react better to what is happening in the farm.

What I liked the most about this project was making the behavior trees and creating different nodes to build all the behaviors I wanted. I liked being able to give each character its own logic and make them act differently depending on the situation.

What I liked the least about the project was that the framework did not have many tools for interaction between NPCs or for handling global information like the day and night cycle that I wanted to implement. 

The main difficulty I had during the project was making all the NPCs share information correctly. That was the hardest part for me, because many of the behaviors depended on global states or things happening in other parts of the simulation. 