#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    using clock = chrono::high_resolution_clock;

    auto lastTime = clock::now();

    cout << "Engine Start\n";
    cin.get();

    bool running = true;

    while(running)
    {
        auto now = clock::now();
        chrono::duration<float> delta = now - lastTime;
        lastTime = now;

        float deltaTime = delta.count();
        cout << "Delta Time: " << deltaTime << " seconds\n";

        this_thread::sleep_for(chrono::milliseconds(16));
    }

    return 0;
}