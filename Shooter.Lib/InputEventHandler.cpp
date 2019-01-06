#include "InputEventHandler.h"

InputEventHandler::InputEventHandler(IInputManager& inputManager) :
	_inputManager(inputManager) {}

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
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::UP, MovementType::STARTED);
			break;
		case sf::Keyboard::S:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::DOWN, MovementType::STARTED);
			break;
		case sf::Keyboard::Q:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::LEFT, MovementType::STARTED);
			break;
		case sf::Keyboard::D:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::RIGHT, MovementType::STARTED);
			break;
		}
	}
	break;

	case sf::Event::EventType::KeyReleased:
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Z:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::UP, MovementType::STOPPED);
			break;
		case sf::Keyboard::S:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::DOWN, MovementType::STOPPED);
			break;
		case sf::Keyboard::Q:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::LEFT, MovementType::STOPPED);
			break;
		case sf::Keyboard::D:
			_updatePlayerMovementStateCommand.execute(gameState, MovementDirection::RIGHT, MovementType::STOPPED);
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