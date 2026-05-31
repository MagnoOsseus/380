#pragma once

// Include all node headers in this file

// Example Control Flow Nodes
#include "ControlFlow/C_ParallelSequencer.h"
#include "ControlFlow/C_RandomSelector.h"
#include "ControlFlow/C_Selector.h"
#include "ControlFlow/C_Sequencer.h"

// Student Control Flow Nodes


// Example Decorator Nodes
#include "Decorator/D_Delay.h"
#include "Decorator/D_InvertedRepeater.h"
#include "Decorator/D_RepeatFourTimes.h"

// Student Decorator Nodes
#include "Decorator/D_DaytimeOnly.h"
#include "Decorator/D_Cooldown.h"
#include "Decorator/D_CooldownFly.h"
#include "Decorator/D_CooldownFight.h"

// Example Leaf Nodes
#include "Leaf/L_CheckMouseClick.h"
#include "Leaf/L_Idle.h"
#include "Leaf/L_MoveToFurthestAgent.h"
#include "Leaf/L_MoveToMouseClick.h"
#include "Leaf/L_MoveToRandomPosition.h"
#include "Leaf/L_PlaySound.h"

// Student Leaf Nodes
#include "Leaf/L_IsNighttime.h"
#include "Leaf/L_GoToSleep.h"
#include "Leaf/L_GoHome.h"
#include "Leaf/L_HungryAnimals.h"
#include "Leaf/L_FeedAnimals.h"
#include "Leaf/L_CutDown.h"
#include "Leaf/L_Lunchtime.h"
#include "Leaf/L_GoLunch.h"
#include "Leaf/L_WakeUp.h"
#include "Leaf/L_ChaseWolf.h"
#include "Leaf/L_IsPanicking.h"
#include "Leaf/L_RunCrazy.h"
#include "Leaf/L_MakePanicNoise.h"
#include "Leaf/L_IsHungry.h"
#include "Leaf/L_ReadyToLayEgg.h"
#include "Leaf/L_LayEgg.h"
#include "Leaf/L_WantsToFight.h"
#include "Leaf/L_FightOtherChicken.h"
#include "Leaf/L_WanderLikeChicken.h"
#include "Leaf/L_JustBecameDay.h"
#include "Leaf/L_CrowLoudly.h"
#include "Leaf/L_WantsToFly.h"
#include "Leaf/L_TryToFlyAndFail.h"
#include "Leaf/L_IsFarmerChasing.h"
#include "Leaf/L_FleeToSafety.h"
#include "Leaf/L_EatChicken.h"
#include "Leaf/L_TriggerPanicEvent.h"
#include "Leaf/L_FindTargetChicken.h"
#include "Leaf/L_ChaseChicken.h"
#include "Leaf/L_WantsToSleep.h"
#include "Leaf/L_SleepDaytime.h"
#include "Leaf/L_WanderRandomly.h"
#include "Leaf/L_WolfAlertActive.h"
#include "Leaf/L_GoToSleepArea.h"
#include "Leaf/L_GoToWaitForFood.h"
#include "Leaf/L_WaitForFood.h"
#include "Leaf/L_IsNightMature.h"
#include "Leaf/L_IsThirsty.h"
#include "Leaf/L_GoToWater.h"
#include "Leaf/L_DrinkWater.h"
