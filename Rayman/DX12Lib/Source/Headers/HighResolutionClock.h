/**
 * High resolution clock used for performing timings.
 */

#pragma once

#include <chrono>

using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds gc_TimestepNano(20000000);

class HighResolutionClock
{
public:
    HighResolutionClock();

    // Tick the high resolution clock.
    // Tick the clock before reading the delta time for the first time.
    // Only tick the clock once per frame.
    // Use the Get* functions to return the elapsed time between ticks.
    void Tick();

    // Reset the clock.
    void Reset();

    double GetDeltaNanoseconds() const;
    double GetDeltaMicroseconds() const;
    double GetDeltaMilliseconds() const;
    double GetDeltaSeconds() const;

    double GetTotalNanoseconds() const;
    double GetTotalMicroseconds() const;
    double GetTotalMilliSeconds() const;
    double GetTotalSeconds() const;
	std::chrono::high_resolution_clock::duration GetTotalTime() const;

	double GetFixedTimeStepSeconds() const;

	const std::chrono::nanoseconds& GetLag();
	void UpdateLag();


private:
    // Initial time point.
    std::chrono::high_resolution_clock::time_point m_T0;
    // Time since last tick.
    std::chrono::high_resolution_clock::duration m_DeltaTime;
    std::chrono::high_resolution_clock::duration m_TotalTime;

	// Lag for fixed deltaTime.
	std::chrono::nanoseconds m_Lag = std::chrono::nanoseconds(0ns);
};