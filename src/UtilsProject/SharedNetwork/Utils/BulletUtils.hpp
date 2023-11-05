//
// Created by Clément Lagasse on 11/10/2023.
//

#pragma once

enum BulletOwner {
    PLAYER,
    ENEMY
};

enum BulletType {
    NORMAL,
    CHARGEDStage1,
    CHARGEDStage2,
    CHARGEDStage3,
    CHARGEDStage4,
    CHARGEDStage5,
};

enum BulletTypeEntity {
    PlayerBullet,
    PlayerBulletInvolve,
    EnemyBullet,
};
