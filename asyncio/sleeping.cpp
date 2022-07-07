
#include <thread>
#include <chrono>
int main ()
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10s);
};