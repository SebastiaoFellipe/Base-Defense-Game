#include "collision.h"

bool Collision::checkBulletHitBase(std::shared_ptr<Bullet>& bullet, Base& base) {
    return bullet->getBody().intersects(base.getBody());
}

bool Collision::checkBulletHitPlayer(std::shared_ptr<Bullet>& bullet, Player& player) {
    return bullet->getBody().intersects(player.getBody());
}

bool Collision::checkEnemyHitPlayer(Enemy& enemy, Player& player) {
    return enemy.getBody().intersects(player.getBody());
}

bool Collision::checkEnemyHitBase(Enemy& enemy, Base& base) {
    return enemy.getBody().intersects(base.getBody());
}

bool Collision::checkPlayerBulletHitEnemy(std::shared_ptr<Bullet>& bullet, Enemy& enemy) {
    return bullet->getBody().intersects(enemy.getBody());
}

bool Collision::checkPlayerGetsLoot(Player& player, Loot& loot) {
    return player.getBody().intersects(loot.getBody());
}