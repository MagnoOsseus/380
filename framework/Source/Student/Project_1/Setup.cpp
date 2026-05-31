#include <pch.h>
#include "Projects/ProjectOne.h"
#include "Agent/CameraAgent.h"

void ProjectOne::setup()
{
    Agent::add_model("Assets\\tree.sdkmesh", Agent::AgentModel::Tree);
    Agent::add_model("Assets\\car.sdkmesh", Agent::AgentModel::Car);
    Agent::add_model("Assets\\bird.sdkmesh", Agent::AgentModel::Bird);
    Agent::add_model("Assets\\ball.sdkmesh", Agent::AgentModel::Ball);
    Agent::add_model("Assets\\hut.sdkmesh", Agent::AgentModel::Hut);

    // Main character: uses Farmer behavior so it can handle lunch/home/sleep states
    auto man = agents->create_behavior_agent("Farmer", BehaviorTreeTypes::Farmer);
    man->set_scaling(0.8f);
    man->set_position(Vec3(58.0f, 0.0f, 50.0f));

    // Cabin where the character can eat and sleep
    auto cabin = agents->create_behavior_agent("Cabin", BehaviorTreeTypes::Idle, Agent::AgentModel::Hut);
    cabin->set_position(Vec3(40.0f, 0.0f, 50.0f));
    cabin->set_scaling(0.35f);

    // Chickens
    auto chicken1 = agents->create_behavior_agent("Chicken", BehaviorTreeTypes::Chicken, Agent::AgentModel::Bird);
    chicken1->set_scaling(0.010f);
    chicken1->set_position(Vec3(70.0f, 0.0f, 38.0f));
    chicken1->set_movement_speed(8.0f);

    auto chicken2 = agents->create_behavior_agent("Chicken", BehaviorTreeTypes::Chicken, Agent::AgentModel::Bird);
    chicken2->set_scaling(0.010f);
    chicken2->set_position(Vec3(76.0f, 0.0f, 42.0f));
    chicken2->set_movement_speed(8.0f);

    auto chicken3 = agents->create_behavior_agent("Chicken", BehaviorTreeTypes::Chicken, Agent::AgentModel::Bird);
    chicken3->set_scaling(0.010f);
    chicken3->set_position(Vec3(72.0f, 0.0f, 46.0f));
    chicken3->set_movement_speed(8.0f);

    // Rooster
    auto rooster = agents->create_behavior_agent("Rooster", BehaviorTreeTypes::Rooster, Agent::AgentModel::Bird);
    rooster->set_scaling(0.012f);
    rooster->set_position(Vec3(66.0f, 0.0f, 44.0f));
    rooster->set_color(Vec3(0.85f, 0.25f, 0.2f));
    rooster->set_movement_speed(9.0f);

    // Wolf represented by a ball mesh
    auto wolf = agents->create_behavior_agent("Wolf", BehaviorTreeTypes::Wolf, Agent::AgentModel::Ball);
    wolf->set_scaling(0.55f);
    wolf->set_position(Vec3(18.0f, 0.0f, 20.0f));
    wolf->set_color(Vec3(0.2f, 0.2f, 0.2f));
    wolf->set_movement_speed(11.0f);

    // Trees to chop - placed together away from the cabin
    auto tree1 = agents->create_behavior_agent("Tree", BehaviorTreeTypes::Idle, Agent::AgentModel::Tree);
    tree1->set_pitch(PI / 2);
    tree1->set_scaling(0.75f);
    tree1->set_color(Vec3(0, 0.5f, 0));
    tree1->set_position(Vec3(20.0f, 0.0f, 72.0f));

    auto tree2 = agents->create_behavior_agent("Tree", BehaviorTreeTypes::Idle, Agent::AgentModel::Tree);
    tree2->set_pitch(PI / 2);
    tree2->set_scaling(0.75f);
    tree2->set_color(Vec3(0, 0.5f, 0));
    tree2->set_position(Vec3(28.0f, 0.0f, 78.0f));

    // Use latest map (includes the new scenario map)
    if (terrain->num_maps() > 0)
    {
        terrain->goto_map(static_cast<unsigned>(terrain->num_maps() - 1));
    }

    terrain->pathLayer.set_enabled(true);

    auto camera = agents->get_camera_agent();
    camera->set_position(Vec3(-62.0f, 70.0f, terrain->mapSizeInWorld * 0.5f));
    camera->set_pitch(0.610865); // 35 degrees

    audioManager->SetVolume(0.5f);
    audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");
}
