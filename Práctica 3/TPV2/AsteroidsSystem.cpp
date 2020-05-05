#include "AsteroidsSystem.h"
#include "GameCtrlSystem.h"

void AsteroidsSystem::onCollisionWithBullet(Entity* a, Entity* b) {
    int gen = a->getComponent<AsteroidGeneration>()->generation_;

    // divide Asteroid
    if (gen > 1) {
        Transform* tr = a->getComponent<Transform>();
        createAsteroid(tr, 1, gen - 1);
        createAsteroid(tr, -1, gen - 1);
    }
    Score* sc = mngr_->getHandler<_hdlr_GameState>()->getComponent<Score>();
    sc->points_++;
    a->setActive(false);
    numOfAsteroids_--;
    if (numOfAsteroids_ <= 0)
        mngr_->send<msg::Message>(msg::_NO_MORE_ASTEROIDS_);
};