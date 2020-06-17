#ifndef TIMER_H
#define TIMER_H

#include <chrono>

/// Class to handle timing within C++ codes
/// Example usage in test_timer.cpp
class Timer
{
  public:
    ///Class constructor gets current time.
    Timer(): begin(clock::now()) {};
    ///Sets the starting time to right now
    void reset(){ begin = clock::now(); }
    ///Returns how much time has elapsed.
    double elapsed() const{ return std::chrono::duration_cast<seconds>(clock::now() - begin).count(); }

  private:
    ///two type aliases for within the class
    using clock = std::chrono::high_resolution_clock;
    using seconds = std::chrono::duration<double, std::ratio<1> >;
    
    ///Only store when you started timing
    std::chrono::time_point<clock> begin;
};

#endif
