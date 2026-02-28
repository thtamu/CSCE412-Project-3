#include <chrono>
#include <atomic>
#include "constants.h"
#include "Stopper.h"

std::chrono::steady_clock::time_point Stopper::startPoint;
std::atomic<bool> Stopper::started{false};

