#include "SoundManager.h"

std::map<std::string, sf::Music*> SoundManager::soundMap {
	{"backgroundMusic", new sf::Music()},
	{"tankShot", new sf::Music()},
	{"tankHit", new sf::Music()},
	{"tankExplosion", new sf::Music()},
	{"movingTank", new sf::Music()},
	{"rotateTurret", new sf::Music()},
	{"helicopterFlying", new sf::Music()}
};

void SoundManager::Initialize()
{
	soundMap["backgroundMusic"]->openFromFile("..\\Sounds\\background_music.mp3");
	soundMap["backgroundMusic"]->setVolume(40.0f);
	soundMap["backgroundMusic"]->setLoop(true);
	soundMap["backgroundMusic"]->play();

	soundMap["tankShot"]->openFromFile("..\\Sounds\\tank_shot.wav");
	soundMap["tankShot"]->setVolume(30.0f);

	soundMap["tankHit"]->openFromFile("..\\Sounds\\tank_hit.wav");
	soundMap["tankHit"]->setVolume(30.0f);

	soundMap["tankExplosion"]->openFromFile("..\\Sounds\\tank_explosion.wav");
	soundMap["tankExplosion"]->setVolume(20.0f);

	soundMap["movingTank"]->openFromFile("..\\Sounds\\moving_tank.wav");
	soundMap["movingTank"]->setVolume(30.0f);
	soundMap["movingTank"]->setLoop(true);

	soundMap["rotateTurret"]->openFromFile("..\\Sounds\\rotate_turret.wav");
	soundMap["rotateTurret"]->setVolume(30.0f);
	soundMap["rotateTurret"]->setLoop(true);

	soundMap["helicopterFlying"]->openFromFile("..\\Sounds\\helicopter_flying.flac");
	soundMap["helicopterFlying"]->setVolume(30.0f);
	soundMap["helicopterFlying"]->setLoop(true);
}

void SoundManager::IncreaseVolume()
{
	for (auto it = soundMap.begin(); it != soundMap.end(); ++it)
		it->second->setVolume(it->second->getVolume() + 10.0f);
}

void SoundManager::DecreaseVolume()
{
	for (auto it = soundMap.begin(); it != soundMap.end(); ++it) {
		if (it->first != "backgroundMusic")
			it->second->setVolume(it->second->getVolume() - 10.0f);
	}
}

void SoundManager::StopAllSounds()
{
	for (auto it = soundMap.begin(); it != soundMap.end(); ++it)
		it->second->stop();
}

void SoundManager::PlayBackgroundMusic()
{
	soundMap["backgroundMusic"]->play();
}

void SoundManager::IncreaseBackgroundMusicVolume()
{
	soundMap["backgroundMusic"]->setVolume(soundMap["backgroundMusic"]->getVolume() + 10.0f);
}

void SoundManager::DecreaseBackgroundMusicVolume()
{
	soundMap["backgroundMusic"]->setVolume(soundMap["backgroundMusic"]->getVolume() - 10.0f);
}

void SoundManager::StopBackgroundMusic()
{
	soundMap["backgroundMusic"]->stop();
}

void SoundManager::PlayTankShot()
{
	soundMap["tankShot"]->play();
}

void SoundManager::PlayTankHit()
{
	soundMap["tankHit"]->play();
}

void SoundManager::StartTurretRotation()
{
	soundMap["rotateTurret"]->play();
}

bool SoundManager::IsPlayingTurretRotation()
{
	return soundMap["rotateTurret"]->getStatus() == sf::SoundSource::Playing;
}

void SoundManager::StopTurretRotation()
{
	soundMap["rotateTurret"]->stop();
}

void SoundManager::PlayTankExplosion()
{
	soundMap["tankExplosion"]->play();
}

void SoundManager::StartMovingTank()
{
	soundMap["movingTank"]->play();
}

bool SoundManager::IsPlayingMovingTank()
{
	return soundMap["movingTank"]->getStatus() == sf::SoundSource::Playing;
}

void SoundManager::StopMovingTank()
{
	soundMap["movingTank"]->stop();
}

void SoundManager::StartFlyingHelicopter()
{
	soundMap["helicopterFlying"]->play();
}

bool SoundManager::IsHelicopterMoving()
{
	return soundMap["helicopterFlying"]->getStatus() == sf::SoundSource::Playing;
}

void SoundManager::StopFlyingHelicopter()
{
	soundMap["helicopterFlying"]->stop();
}
