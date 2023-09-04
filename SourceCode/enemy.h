#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_MAX   (8)

void enemy_init();
void enemy_deinit();
void enemy_update();
void enemy_render();

void moveEnemy0(OBJ2D* obj);
void moveEnemy1(OBJ2D* obj);
void moveEnemy2(OBJ2D* obj);

#endif//ENEMY_H