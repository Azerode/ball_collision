#include "../include/ball.h"
#include <math.h>

ball objects[MAX_OBJECT];

static float calcVelocityA(float mass_a, float mass_b, float v_a, float v_b) {
  float sum_mass = mass_a + mass_b;
  return ((mass_a - mass_b) / sum_mass) * v_a + ((2 * mass_b) / sum_mass) * v_b;
}

static float calcVelocityB(float mass_a, float mass_b, float v_a, float v_b) {
  float sum_mass = mass_a + mass_b;
  return ((2 * mass_a) / sum_mass) * v_a + ((mass_b - mass_a) / sum_mass) * v_b;
}

void applyVelocity(ball *obj) {
  obj->position.x += obj->velocity.x;
  obj->position.y += obj->velocity.y;
}

float distance(Vector2 *v_a, Vector2 *v_b) {

  float partX = (v_b->x - v_a->x) * (v_b->x - v_a->x);
  float partY = (v_b->y - v_a->y) * (v_b->y - v_a->y);

  return sqrtf(partX + partY);
}

void calcElacticCollision(ball *a, ball *b) {

  // Step 1 : calcul the normal vector between the center of the ball
  float dist_ab = distance(&a->position, &b->position);

  if (dist_ab == 0)
    return;

  vector normal = {(b->position.x - a->position.x) / dist_ab,
                   (b->position.y - a->position.y) / dist_ab};
  
  // Step 1.bis : move the ball to respect real physic
  if (dist_ab > 0){
    float overlap = (a->r + b->r - dist_ab) / 2.0f;
    a->position.x -= normal.x * (overlap);
    a->position.y -= normal.y * (overlap);
    b->position.x += normal.x * (overlap);
    b->position.y += normal.y * (overlap);
  }

  // Step 2 : calcul the keeped energy for each ball with the 
  // scalar product
  // a = v1.x * v2.x + v1.y * v2.y
  float e_a = a->velocity.x * normal.x + a->velocity.y * normal.y;
  float e_b = b->velocity.x * normal.x + b->velocity.y * normal.y;


  // Step 3: apply the keeped energy on the velocity of each ball
  vector v_a = {
      e_a * normal.x,
      e_a * normal.y,
  };

  vector v_b = {
      e_b * normal.x,
      e_b * normal.y,
  };

  // Step 4 : calcul the collision with 1D with 
  // the new velocity
  float a2 = calcVelocityA(a->mass, b->mass, e_a, e_b);
  float b2 = calcVelocityB(a->mass, b->mass, e_a, e_b);


  // Step 5: apply the ortogonal vector to apply the angle
  // vo = x = a->position.x - v_a.x, y = a->position.y - v_a.y
  a->velocity.x = a2 * normal.x + a->velocity.x - v_a.x;
  a->velocity.y = a2 * normal.y + a->velocity.y - v_a.y;
  b->velocity.x = b2 * normal.x + b->velocity.x - v_b.x;
  b->velocity.y = b2 * normal.y + b->velocity.y - v_b.y;
}
