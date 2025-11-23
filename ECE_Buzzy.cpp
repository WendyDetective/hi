\
#include "ECE_Buzzy.h"
#include <iostream>

bool ECE_Buzzy::loadTexture(const std::string& path) {
    if (!texture.loadFromFile(path)) {
        std::cerr << "Failed to load buzzy texture: " << path << std::endl;
        return false;
    }
    setTexture(texture);
    auto bounds = getLocalBounds();
    setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    return true;
}

void ECE_Buzzy::update(float dt, float windowW) {
    fireCooldown -= dt;
    // 键盘移动由 main 管理（也可以放这里）
    // 保证不出界
    sf::Vector2f p = getPosition();
    float halfW = getGlobalBounds().width/2.f;
    if (p.x < halfW) setPosition(halfW, p.y);
    if (p.x > windowW - halfW) setPosition(windowW - halfW, p.y);
}

std::unique_ptr<ECE_LaserBlast> ECE_Buzzy::fire() {
    if (fireCooldown > 0.f) return nullptr;
    fireCooldown = fireCooldownMax;
    auto laser = std::make_unique<ECE_LaserBlast>(false); // 玩家激光
    // 激光从实体下方发出（题目中 buzzy 在上部，发向下方）
    sf::Vector2f pos = getPosition();
    float startY = pos.y + getGlobalBounds().height/2.f + 10.f;
    laser->setPosition(pos.x, startY);
    laser->setVelocity(0.f, +420.f); // 朝下移动 (y 正方向)
    return laser;
}
