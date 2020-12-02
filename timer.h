#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>

class Timer {
public:
  Timer();
  ~Timer();
  void start();

  void stop();
  double elapsedMilliseconds();
  double elapsedNanoseconds();
  double elapsedSeconds();

private:
  std::chrono::time_point<std::chrono::system_clock> m_StartTime;
  std::chrono::time_point<std::chrono::system_clock> m_EndTime;
  bool m_bRunning = false;
};
