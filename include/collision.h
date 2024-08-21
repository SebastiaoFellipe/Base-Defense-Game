#ifndef COLLISION_H
#define COLLISION_H

#include <memory>
#include "player.h"
#include "enemy.h"
#include "base.h"
#include "bullet.h"
#include "loot.h"
#include <SFML/Graphics.hpp>

class Collision {
public:
    static bool checkBulletHitBase(std::shared_ptr<Bullet>& bullet, Base& base);
    static bool checkBulletHitPlayer(std::shared_ptr<Bullet>& bullet, Player& player);
    static bool checkEnemyHitPlayer(Enemy& enemy, Player& player);
    static bool checkEnemyHitBase(Enemy& enemy, Base& base);
    static bool checkPlayerBulletHitEnemy(std::shared_ptr<Bullet>& bullet, Enemy& enemy);
    static bool checkPlayerGetsLoot(Player& player, Loot& loot);
};

#endif // COLLISION_H
