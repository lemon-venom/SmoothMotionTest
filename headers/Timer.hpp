#pragma once

#include "Logger.hpp"

#include <thread>
#include <chrono>

typedef std::chrono::high_resolution_clock hiResClock;
typedef std::chrono::duration<double> durationDouble;
typedef std::chrono::time_point<hiResClock, durationDouble> hiResDoubleTimePoint;

class Timer
{
public:

	Timer();
	virtual ~Timer();

	double	tick();

	int32_t	getFps();
	int32_t	getFrameCount();
	double	getFrameTime();
	double	getTotalTime();

	const double fixedTimeStep = 1.0 / 100.0;

	double timeAccumulator = 0.0;

private:


	hiResClock				clock_;
	hiResDoubleTimePoint	currentTime_;
	int32_t					fps_;
	int32_t					frameCount_;
	int32_t					frameCountFps_;
	hiResDoubleTimePoint	previousTime_;
	double					timeFps_;
	double					timeFrame_;
	double					timeTotal_;

};

extern Timer timer;
