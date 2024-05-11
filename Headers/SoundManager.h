#pragma once
#include <map>
#include <SFML/Audio.hpp>

class SoundManager
{
public:

    //Management
    static void Initialize();
    static void IncreaseVolume();
    static void DecreaseVolume();

    //Background Music related
    static void PlayBackgroundMusic();
    static void IncreaseBackgroundMusicVolume();
    static void DecreaseBackgroundMusicVolume();
    static void StopBackgroundMusic();

    //Shooting related
    static void PlayTankShot();
    static void PlayTankHit();
    static void PlayTankExplosion();

    //Turret related
    static void StartTurretRotation();
    static bool IsPlayingTurretRotation();
    static void StopTurretRotation();

    //Moving tank related
    static void StartMovingTank();
    static bool IsPlayingMovingTank();
    static void StopMovingTank();

    //Moving helicopter related
    static void StartFlyingHelicopter();
    static bool IsHelicopterMoving();
    static void StopFlyingHelicopter();
private:
    static std::map<std::string, sf::Music*> soundMap;
};