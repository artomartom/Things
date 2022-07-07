#pragma once

#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <assert.h>

using namespace std;
using namespace std::chrono;

auto startTime{high_resolution_clock::now()};
int currCount{};
int maxCount{20};

mutex m{};
void Even()
{
  for (;;)
  {
    if ((currCount % 2) == 0)
    {
      lock_guard<mutex> lq{m};
      cout << currCount;
      currCount += 1;
      if (currCount > maxCount)
      {
        return;
      }
      else
      {
        cout << ", ";
      }
    }
    else
    {
      cout << ".";
    };

    // std::this_thread::sleep_for(500ms);
  };
};

void Odd()
{
  for (;;)
  {
    if ((currCount % 2) == 1)
    {
      lock_guard<mutex> lq{m};
      cout << currCount << ", ";
      currCount += 1;
    }
    else
    {
      cout << ".";
    };

    if (currCount > maxCount - 1)
      return;
    // std::this_thread::sleep_for(500ms);
  };
};

int main()
{

  thread odd(&Odd);
  thread even(&Even);

  odd.join();
  even.join();
  return 0;
};
