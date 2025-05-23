#include <iostream>

#include <ronin/framework.h>
#include <ronin/World.h>

using namespace RoninEngine;

class TestWorld : public Runtime::World
{
public:
    TestWorld() : World("Test World") {}

    void OnStart(){
        GetGUI()->PushLabel("Hello! This is Open Art Of War 2: COMMUNITY\n"
                            "It's game in still plan", {500,300, 100, 32});
        Version ver = RoninSimulator::GetVersion().Engine_Version;
        std::string verstr = std::string("Engine v") + std::to_string(ver.major) + '.' + std::to_string(ver.minor) + '.' + std::to_string(ver.patch);
        GetGUI()->PushLabel(verstr, {500,360, 100, 32});
        Runtime::Primitive::CreateCamera2D();
    }
};

int main(int argc, char *argv[])
{
    RoninSimulator::Init();
    RoninSimulator::Show(Resolution::GetMidResolution(), false);
    RoninSimulator::SetDebugMode(true);
    RoninSimulator::LoadWorldAfterSplash<TestWorld>();
    RoninSimulator::Simulate();
    RoninSimulator::Finalize();

    return 0;
}
