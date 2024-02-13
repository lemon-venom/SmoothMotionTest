#include "../headers/Entity.hpp"
#include "../headers/Logger.hpp"
#include "../headers/Renderer.hpp"
#include "../headers/Timer.hpp"

Renderer* renderer;
Entity entity;

bool quit = false;

void handleInput(SDL_Keycode keycode) {

	switch (keycode) {
	case SDLK_ESCAPE:
		quit = true;
		break;
	case SDLK_v:
		renderer->toggleVSync();
		break;
	case SDLK_l:
		logger.toggleLog();
		break;
	}
}

bool setup() {

	renderer = new Renderer();

	return renderer->initialize();
}

void shutdown()
{
	renderer->shutdown();

	delete renderer;

	SDL_Quit();
}

void update() {

	if (timer.timeAccumulator >= timer.fixedTimeStep)
	{
		entity.updateBegin();

		while (timer.timeAccumulator >= timer.fixedTimeStep)
		{
			entity.update(timer.fixedTimeStep);

			timer.timeAccumulator -= timer.fixedTimeStep;
		}
	}
}

void render() {

	float lerp = timer.timeAccumulator / timer.fixedTimeStep;

	renderer->sceneBegin();

	entity.render(renderer, lerp);

	renderer->sceneComplete();
}

int main(int argc, char* args[]) {

	if (setup() == false) {		
		return 0;
	}

	SDL_Event event;

	while (quit == false) {

		while (SDL_PollEvent(&event)) {

			switch (event.type)	{
			case SDL_QUIT: {
				quit = true;
				break;
			}
			case SDL_KEYDOWN: {
				handleInput(event.key.keysym.sym);
				break;
			}
			default:
				break;
			}
		}

		double frameTime = timer.tick();

		timer.timeAccumulator += frameTime;

		update();

		render();
	}

	shutdown();

	return 0;
}