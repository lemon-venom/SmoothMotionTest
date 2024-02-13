#include "..\headers\Timer.hpp"

Timer timer;

Timer::Timer()
{
	frameCount_ = -1;
	fps_ = 0;
	frameCountFps_ = 0;
	timeFps_ = 0.0;
	timeFrame_ = 0.0;
	timeTotal_ = 0.0;
}

Timer::~Timer()
{
}

int32_t Timer::getFps()
{
	return fps_;
}

int32_t Timer::getFrameCount()
{
	return frameCount_;
}

double Timer::getFrameTime()
{
	return timeFrame_;
}

double Timer::getTotalTime()
{
	return timeTotal_;
}


double Timer::tick()
{
	if (frameCount_ == -1)
	{
		currentTime_ = clock_.now();
		previousTime_ = clock_.now();

		frameCount_ = 0;

		// Start time at 0.
		return 0.0;
	}

	previousTime_ = currentTime_;

	currentTime_ = clock_.now();

	frameCount_++;

	frameCountFps_++;

	durationDouble time_span = currentTime_ - previousTime_;

	timeFrame_ = time_span.count();

	timeTotal_ += timeFrame_;

	timeFps_ += timeFrame_;

	if (timeFps_ >= 1.0)
	{
		fps_ = frameCountFps_;

		frameCountFps_ = 0;

		timeFps_ = 0.0;

	}

	return timeFrame_;
}
