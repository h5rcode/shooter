#include "InputEventHandler.h"

std::vector<GameEvent> InputEventHandler::handle(IGameState& gameState, sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::EventType::MouseButtonPressed:
	{
		switch (event.mouseButton.button)
		{
		case sf::Mouse::Button::Left:
			return _attackCommand.execute(gameState);

		case sf::Mouse::Button::Right:
			return _useCommand.execute(gameState);
		}
	}
	break;

	case sf::Event::EventType::KeyPressed:
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Z:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::UP, MovementType::START);
			break;
		case sf::Keyboard::S:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::DOWN, MovementType::START);
			break;
		case sf::Keyboard::Q:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::LEFT, MovementType::START);
			break;
		case sf::Keyboard::D:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::RIGHT, MovementType::START);
			break;
		}
	}
	break;

	case sf::Event::EventType::KeyReleased:
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Z:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::UP, MovementType::STOP);
			break;
		case sf::Keyboard::S:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::DOWN, MovementType::STOP);
			break;
		case sf::Keyboard::Q:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::LEFT, MovementType::STOP);
			break;
		case sf::Keyboard::D:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::RIGHT, MovementType::STOP);
			break;
		}
	}
	break;

	case sf::Event::Closed:
	{
		gameState.stop();
	}
	break;
	}

	return std::vector<GameEvent>();
}