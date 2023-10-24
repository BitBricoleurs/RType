/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main
*/

#include "Animate.hpp"
#include "AnimateDeath.hpp"
#include "AnimateShot.hpp"
#include "AudioEngineSystem.hpp"
#include "BaseVelocity.hpp"
#include "ColorR.hpp"
#include "CurveDown.hpp"
#include "DetectLifeLost.hpp"
#include "Game.hpp"
#include "GameEngine.hpp"
#include "GameOver.hpp"
#include "IncreaseDifficulty.hpp"
#include "KillBird.hpp"
#include "PhysicsEngineMovementSystem2D.hpp"
#include "RenderEngineSystem.hpp"
#include "Score.hpp"
#include "Shoot.hpp"
#include "Shooter.hpp"
#include "SpawnBird.hpp"
#include "SpriteComponent.hpp"
#include "StartNewGame.hpp"
#include "SyncPosSprite.hpp"
#include "ToggleFullScreen.hpp"
#include "UpdateScore.hpp"
#include "Vect2.hpp"
#include "VelocityComponent.hpp"
#include "WindowInfoComponent.hpp"
#include "rect.hpp"

void create_background(GameEngine::GameEngine &engine) {
  Utils::Vect2 pos2(0, 0);
  Utils::rect rect2(0, 0, 2560, 1440);

  Utils::ColorR tint = {255, 255, 255, 255};
  float scale = 0.75f;
  float rotation = 0.0f;

  auto bg = engine.createEntity();
  auto spritecomponent = std::make_shared<RenderEngine::SpriteComponent>(
      "assets/hunter/background.png", pos2, rect2, 1, scale, rotation, tint);
  engine.bindComponentToEntity(bg, spritecomponent);
}

std::shared_ptr<Animation> initAnimation(int frames, int width, int height,
                                         bool twoDirections, int direction) {
  auto animation = std::make_shared<Animation>();

  animation->frameHeight = height;
  animation->frameWidth = static_cast<float>(width) / frames;
  animation->twoDirections = twoDirections;
  animation->frames = frames;
  int i = 0;

  for (i = 0; i < frames / 2; i++) {
    Utils::Vect2 spritePos = {i * static_cast<float>(width) / frames, 0};
    animation->spritePositionsLeft.push_back(spritePos);
  }
  for (; i < frames; i++) {
    Utils::Vect2 spritePos = {i * static_cast<float>(width) / frames, 0};
    if (!twoDirections) {
      animation->spritePositionsLeft.push_back(spritePos);
    } else {
      animation->spritePositionsRight.push_back(spritePos);
    }
  }
  if (direction > 1)
    if (twoDirections)
      animation->currentFrame = animation->spritePositionsRight[0];
    else
      animation->currentFrame = animation->spritePositionsLeft[0];
  else
    animation->currentFrame = animation->spritePositionsLeft[0];

  return animation;
}

void create_shooter(GameEngine::GameEngine &engine, float width, float height) {
  size_t shooterID = engine.createEntity();

  auto animation = initAnimation(5, 2500, 500, false, 0);
  auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
      "assets/hunter/shooter.png", Utils::Vect2(0, 0),
      Utils::rect(animation->currentFrame.x, animation->currentFrame.y,
                  animation->frameWidth, animation->frameHeight),
      3, 1.0f, 0.0f, Utils::ColorR(255, 255, 255, 255));

  auto positionComponent = std::make_shared<PhysicsEngine::PositionComponent2D>(
      Utils::Vect2(1920 / 2 - spriteComponent->rect1.w / 2,
                   1080 - spriteComponent->rect1.h + 20));
  spriteComponent->pos = positionComponent->pos;
  auto shooterComponent = std::make_shared<Shooter>();
  auto audioComponent =
      std::make_shared<AudioEngine::AudioComponent>("assets/hunter/shoot.wav");

  engine.bindComponentToEntity(shooterID, audioComponent);
  engine.bindComponentToEntity(shooterID, animation);
  engine.bindComponentToEntity(shooterID, spriteComponent);
  engine.bindComponentToEntity(shooterID, positionComponent);
  engine.bindComponentToEntity(shooterID, shooterComponent);
}

void init_game(GameEngine::GameEngine &engine) {
  size_t id = engine.createEntity();
  auto gameComp = std::make_shared<Game>();
  auto veloComp = std::make_shared<BaseVelocity>(Utils::Vect2(6, 0));
  auto scoreComp = std::make_shared<Score>();
  auto textComponent = std::make_shared<RenderEngine::TextComponent>(
      "Score: 0", Utils::Vect2(800, 0), 64, 100,
      Utils::ColorR{255, 255, 255, 255});

  engine.bindComponentToEntity(id, scoreComp);
  engine.bindComponentToEntity(id, textComponent);
  engine.bindComponentToEntity(id, gameComp);
  engine.bindComponentToEntity(id, veloComp);
}

int main(int ac, char **av) {
  GameEngine::GameEngine engine;

  create_background(engine);
  init_game(engine);

  auto spawnBirdSystem = std::make_shared<SpawnBird>();
  auto renderSystem =
      std::make_shared<RenderEngine::RenderEngineSystem>("POC Engine");
  create_shooter(engine, renderSystem->getScreenWidth(),
                 renderSystem->getScreenHeight());

  auto sync = std::make_shared<SyncPosSprite>();
  auto movement =
      std::make_shared<PhysicsEngine::PhysicsEngineMovementSystem2D>();
  auto animate = std::make_shared<Animate>();
  auto killBird = std::make_shared<KillBird>();
  auto animateDeath = std::make_shared<AnimateDeath>();
  auto shoot = std::make_shared<Shoot>();
  auto animateShot = std::make_shared<AnimateShot>();
  auto audioSys = std::make_shared<AudioEngine::AudioEngineSystem>();
  auto scoreSys = std::make_shared<UpdateScore>();
  auto gameOver = std::make_shared<GameOver>();
  auto startNewGame = std::make_shared<StartNewGame>();
  auto detectLifeLost = std::make_shared<DetectLifeLost>();
  auto curveDown = std::make_shared<CurveDown>();
  auto increaseDiff = std::make_shared<IncreaseDifficulty>();

  engine.addEvent("PLAY_SOUND", audioSys);
  engine.scheduleEvent("UPDATE_SOUNDS", 1);
  engine.addEvent("UPDATE_SOUNDS", audioSys);

  engine.addEvent("spawnBird", spawnBirdSystem);
  engine.scheduleEvent("spawnBird", 75);

  engine.addEvent("render", renderSystem);
  engine.addEvent("killBird", killBird);
  engine.addEvent("animate", animate);
  engine.addSystem("MovementSystem", movement, 2);
  engine.addSystem("SyncPosSPrite", sync, 3);
  engine.addSystem("RenderEngineSystem", renderSystem, 4);
  engine.addEvent("animateDeath", animateDeath);
  engine.addEvent("MouseLeftButtonPressed", shoot);
  engine.addEvent("animateShot", animateShot);
  engine.addEvent("updateScore", scoreSys);
  engine.addEvent("gameOver", gameOver);
  engine.addEvent("startNewGame", startNewGame);
  engine.addSystem("detectLifeLost", detectLifeLost);
  engine.addEvent("curveDown", curveDown);
  engine.addEvent("increaseDiff", increaseDiff);
  engine.scheduleEvent("increaseDiff", (60 * 15));

  engine.run();
  return 0;
}