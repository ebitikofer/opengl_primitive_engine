#ifndef INSTANCE_H
#define INSTANCE_H

#include <Angel.h>
#include "engine.h"
#include "utility.h"
#include "game.h"
#include "models.h"

#define SKY_R 0.1
#define SKY_G 0.0
#define SKY_B 0.05

#define COLOR_SKY 1

// Motion rates
#define RATE_PLAYER	  0.5
#define RATE_GUN	    1

// Color vec3s
vec3 sky = vec3(SKY_R, SKY_G, SKY_B);
// vec3 sky = vec3(0.05, 0.0, 0.1);
// vec3 sky = vec3(0.8, 1.0, 1.0);

// std::uniform_real_distribution<double> sickness(0.0, 0.005);

vec3 pickup_size[NUM_PICKUPS] = { vec3(0.0, 0.0, 0.0) };

const GLfloat view_lr = 3.5; // 5.0 * DegreesToRadians;
const GLfloat view_ud = 2.5; // 5.0 * DegreesToRadians;

GLint timer = 0;
GLint done_timer = 0;
GLint reload_timer = 0;
GLint recharge_timer = 0;
GLint pickup_timer[NUM_PICKUPS] = { 0 };

GLfloat disp_rot = 0.0;

float display_rot = 0.0;

bool fire_gun = false, reload = true, action = false, fire_mode = true;
float elevation = 0.0, frame = 3.0;
int score = 0, health = 5, shield = 7, magazine = 0, bullet_ammo = 0, rocket_ammo = 0;
int clip_size = 0;
int bullet_hud = 0;
bool solid_part = true, game_over = false;
int count = 0;

bool release = true, burst = false;

bool done = false;

int gun_type = 0;
int prev_gun_type = 0;

bool follow[4] = { false };

bool suckable = false;

GLfloat sensitivity = 1.2;

GLfloat speed_boost = 1.0;

vec3 active_bullet_size = vec3(0.0, 0.0, 0.0);
vec3 active_bullet_color = vec3(0.0, 0.0, 0.0);
GLfloat active_bullet_speed = 0.0;

vec3 bullet[NUM_BULLET] = { vec3(0.0, 0.0, 0.0) };
vec3 bullet_size[NUM_BULLET] = { vec3(0.0, 0.0, 0.0) };
vec3 bullet_color[NUM_BULLET] = { vec3(0.0, 0.0, 0.0) };
GLfloat bullet_dist[NUM_BULLET] = { 0.0 };
GLint bullet_type[NUM_BULLET] = { 0 };
GLfloat bullet_speed[NUM_BULLET] = { 0.0 };
GLfloat bullet_theta[NUM_BULLET] = { 0 };
GLfloat bullet_phi[NUM_BULLET] = { 0 };

bool debug = false,
     view_toggle = true,
     debug_toggle = true,
     fire_mode_toggle = true,
     get_gun = false,
     get_launcher = false,
     get_laser = false,
     get_vaccuum = false,
     get_coffee = false,
     get_bullet = false,
     get_rocket = false,
     get_health = false,
     get_shield = false,
     get_key = false,
     active[NUM_BULLET] = { false },
     robot_collision = false;
     // get_item[] = false;

bool filler = false;

int reload_time = 3000;

bool rooms[NUM_ROOMS] = { false };
bool displayed[NUM_ROOMS] = { false };
vec4 bounds[NUM_ROOMS] = {
  vec4(0.0, -25.0, 0.0, -25.0),
  vec4(0.0, -25.0, 25.0, 0.0),
  vec4(25.0, 0.0, 0.0, -25.0),
  vec4(25.0, 0.0, 25.0, 0.0),
  // vec4(-25.0, -50.0, 40.0, 0.0),
  // vec4(-25.0, -50.0, 0.0, -50.0),
  // vec4(0.0, -25.0, 0.0, -50.0),
  // vec4(25.0, 0.0, 0.0, -25.0),
  vec4(25.0, 0.0, -25.0, -50.0),
  vec4(50.0, 25.0, -25.0, -50.0),
  vec4(50.0, 25.0, 20.0, -25.0),
  vec4(25.0, -12.5, 40.0, 0.0),
  vec4(50.0, 25.0, 40.0, 25.0),
  vec4(50.0, -50.0, 50.0, 40.0)
};

void set_room(vec3 location, vec3 bound) {
  for (int i = 0; i < NUM_ROOMS; i++) {
    if (location.x - bound.x / 2 < bounds[i].x &&
        location.x + bound.x / 2 > bounds[i].y &&
        location.z - bound.z / 2 < bounds[i].z &&
        location.z + bound.z / 2 > bounds[i].w ) {
      if (!displayed[i]) {
        std::cout << "ROOM" << (i + 1) << std::endl;
        displayed[i] = true;
      } else {
      }
      rooms[i] = true;
    } else {
      displayed[i] = false;
      rooms[i] = false;
    }
  }
}

void check_keys() {

  for (int i = 0; i < 256; i++) {
    if (key_buffer[i]){
      switch (i) {
        case 033: { } break; // Escape Key
        case 'Q': exit(EXIT_SUCCESS); break; // Quit
        case 'w': {
          for (int i = 0; i < NUM_PLAYERS; i++) {
            for (int j = 0; j < PARTS_PLAYER; j++) {
              players[i][j].velocity.z -= speed_boost * sin(theta*M_PI/180)/2; players[i][j].velocity.x -= speed_boost * cos(theta*M_PI/180)/2;
            }
          }
        } break;
        case 's': {
          for (int i = 0; i < NUM_PLAYERS; i++) {
            for (int j = 0; j < PARTS_PLAYER; j++) {
              players[i][j].velocity.z += speed_boost * sin(theta*M_PI/180)/2; players[i][j].velocity.x += speed_boost * cos(theta*M_PI/180)/2;
            }
          }
        } break;
        case 'a': {
          for (int i = 0; i < NUM_PLAYERS; i++) {
            for (int j = 0; j < PARTS_PLAYER; j++) {
              players[i][j].velocity.x -= speed_boost * sin(theta*M_PI/180)/2; players[i][j].velocity.z += speed_boost * cos(theta*M_PI/180)/2;
            }
          }
        } break;
        case 'd': {
          for (int i = 0; i < NUM_PLAYERS; i++) {
            for (int j = 0; j < PARTS_PLAYER; j++) {
              players[i][j].velocity.x += speed_boost * sin(theta*M_PI/180)/2; players[i][j].velocity.z -= speed_boost * cos(theta*M_PI/180)/2;
            }
          }
        } break;
        case ' ': {
          for (int i = 0; i < NUM_PLAYERS; i++) {
            for (int j = 0; j < PARTS_PLAYER; j++) {
              if (!players[i][j].fall) players[i][j].jump = true;
            }
          }
        } break; // Action
        case 'f': { action = true; } break; // Action
        case '/': { if (reload) { fire_gun = true; reload = false; } } break; // Shoot
        case '1': { if (get_gun) { gun_type = 1; } } break; // medium size medium speed bullet
        case '2': { if (get_launcher) { gun_type = 2; } } break; // large size slow speed rocket
        case '3': { if (get_laser) { gun_type = 3; } } break; // small size fast speed beam
        case 'v': { if (fire_mode_toggle) { fire_mode = !fire_mode; fire_mode_toggle = false; } } break;
        case 'c': if (view_toggle) { perspective = !perspective; view_toggle = false; } break; //fire
        // Utility
        case '-': /* lights[0] = !lights[0]; glUniform1i(Lights[0], lights[0]); */ health -= 1; break;
        case '=': /* lights[1] = !lights[1]; glUniform1i(Lights[1], lights[1]); */ health += 1; break;
        case 'W': { solid_part = !solid_part; } break; //wire
        case 'z': zNear *= 1.1; zFar /= 1.1; break;
        case 'Z': zNear /= 1.1; zFar *= 1.1; break;
        case 'r': radius *= 1.5; break;
        case 'R': radius /= 1.5; break;
        case 'X': fovy -= 5; if (fovy < 0) { fovy = 1; } break;
        case 'V': fovy += 5; /* break; */ if (fovy > 179) { fovy = 179; } break;
        case '~': zNear = 0.1; zFar = 300.0; radius = 3.0; theta = 0.0; phi = 0.0; break; // reset
        case '`': if (debug_toggle) { debug = !debug; debug_toggle = false; } break;
        default: { } break; // Default

      }
    } else {
      switch (i) {
        case '/': { fire_gun = false; if (clip_size == 3 || ( clip_size == 25 && fire_mode) || ( clip_size == 100 && !fire_mode )) { reload = true; } } break; // Stop firing, not the same as bullet landing
        case ' ': {
          for (int i = 0; i < NUM_PLAYERS; i++) {
            for (int j = 0; j < PARTS_PLAYER; j++) {
              players[0][0].jump = false;
            }
          }
        } break; //wire
        case 'f': { action = false; } break; //wire
        case 'v': { fire_mode_toggle = true; } break;
        case 'c': { view_toggle = true; } break; //fire
        case '`': { debug_toggle = true; } break; //fire
      }
    }

    if (spec_buffer[i]) {
      switch (i) {
        case GLUT_KEY_RIGHT: theta += view_lr; break; // Look angle right
        case GLUT_KEY_LEFT:  theta -= view_lr; break; // Look angle left
        case GLUT_KEY_DOWN:  phi += view_ud;   break; // Look angle down
        case GLUT_KEY_UP:    phi -= view_ud;   break; // Look angle up
      }
    }
  }

}

// animation function, runs the updating of the variables
void animation(void) {

  static GLint lasttime = glutGet(GLUT_ELAPSED_TIME);
  GLint nowtime = glutGet(GLUT_ELAPSED_TIME);
  GLint dtime = nowtime - lasttime;

  // timer += dtime;
  // if (timer >= 100) {
  //   std::cout << timer << std::endl;
  //   timer = 0;
  // }

  if (done) {
    done_timer += dtime;
    if (done_timer >= 1000) {
      done = false;
      done_timer = 0;
    }
  }

  set_room(players[0][0].position, character_bounds);

  check_keys();

  if (mouse_button == 0 && changed) {
    if (mouse_button_state == GLUT_DOWN) {
      if (reload) { fire_gun = true; reload = false; release = false; }
    } else if (mouse_button_state == GLUT_UP) {
      fire_gun = false;
      release = true;
      if ( clip_size == 3 || (clip_size == 25 && fire_mode) || ( clip_size == 100 && !fire_mode) ) {
        reload = true;
      }
    }
    changed = false;
  }
  else if (mouse_button == 1 && changed) { changed = false; }
  else if (mouse_button == 2 && changed) {
    if (mouse_button_state == GLUT_DOWN) { fovy -= 15.0; }
    else if (mouse_button_state == GLUT_UP) { fovy += 15.0; }
    changed = false;
  }
  else if (mouse_button == 3 && changed) {
    gun_type++;
    if (gun_type > 3) {
      gun_type = 1;
    }
    changed = false;
  }
  else if (mouse_button == 4 && changed) {
    gun_type--;
    if (gun_type < 1) {
      gun_type = 3;
    }
    changed = false;
  }

  theta += xoffset * sensitivity;
  phi -= yoffset * sensitivity;

  xoffset = 0.0;
  yoffset = 0.0;

  if (phi > 90.0) {
    phi = 90.0;
  } else if (phi < -89.0) {
    phi = -89.0;
  }

  if (pickup[0]) { get_gun = true; bullet_ammo += 25; gun_type = 1; }
  if (pickup[1]) { get_vaccuum = true; }
  if (pickup[2]) { get_key = true; }
  if (pickup[3]) { get_coffee = true; energize = true; }
  if (pickup[4]) { get_bullet = true; resupply = true; bullet_ammo += 50; }
  if (pickup[5]) { get_rocket = true; resupply = true; rocket_ammo += 6; }
  if (pickup[6]) { get_health = true; heal = true; if (health < 5) { health += 3; } if (health > 5) { health = 5; } }
  if (pickup[7]) { get_shield = true; strengthen = true; if (shield < 7) { shield += 3; } if (shield > 7) { shield = 7; } }
  if (pickup[8]) { get_launcher = true; rocket_ammo += 3; gun_type = 2; }
  if (pickup[9]) { get_laser = true; gun_type = 3; }

  if (gun_type != prev_gun_type) {
    switch (gun_type) {
      case 1: { active_bullet_size = vec3(BULLET_W, BULLET_H, BULLET_D); active_bullet_color = vec3(0.28, 0.26, 0.1); active_bullet_speed = 1.0; clip_size = 25; magazine = clip_size; } break; // medium size medium speed bullet
      case 2: { active_bullet_size = vec3(ROCKET_W, ROCKET_H, ROCKET_D); active_bullet_color = vec3(0.27, 0.32, 0.17); active_bullet_speed = 0.5; clip_size = 3; magazine = clip_size; } break; // large size slow speed rocket
      case 3: { active_bullet_size = vec3(LASER_W, LASER_H, LASER_D); active_bullet_color = vec3(1.0, 0.25, 0.75); active_bullet_speed = 2.5; clip_size = 100; magazine = clip_size; } break; // small size fast speed beam
    }
    prev_gun_type = gun_type;
  }

  speed_boost = 1.0;

  // if (rotatep) move_angle += 20.0 / 1000.0 * (time - lasttime);
  // doorAngle += doorAngleIncr / 1000.0 * (time - lasttime);
  // if (doorAngle > 60.0) doorAngleIncr *= -1.0;
  // if (doorAngle < 0.0) { doorAngle = 0.0; doorAngleIncr *= -1.0; }
  // // Do the animation code here in idle, not in display. Code for moving 2nd cube
  // trans += transinc / 1000.0 * ( time - lasttime );
  // if (trans > 1.5) { trans = 1.5; transinc *= -1; }
  // if (trans < -1.5) { trans = -1.5; transinc *= -1; }

  static int step;

  // pickup_size[0] = vec3(1.0, 1.0, 1.0);
  // pickup_size[1] = vec3(2.5, 1.0, 2.5);
  // pickup_size[2] = vec3(2.5, 1.0, 2.5);
  // pickup_size[3] = vec3(2.5, 1.0, 2.5);
  // pickup_size[4] = vec3(1.0, 1.0, 1.0);
  // pickup_size[5] = vec3(2.5, 1.0, 2.5);
  // pickup_size[6] = vec3(2.5, 1.0, 2.5);
  // pickup_size[7] = vec3(2.5, 1.0, 2.5);

  if (frame >= 0.0 && frame <= 360.0) {
    if (step == 0 || step == 2) {
      if (frame == 0.0) frame = 1.0;
      if (frame == 360) step++;
      if (frame < 360) frame = frame + 1.0;
      for (int i = 0; i < 5; i++){ ghost_height[i] = sin((frame - i)*M_PI/30); }
      display_rot = frame;
      // display_rot += 0.1;
      // if (display_rot > 359.9) { display_rot = 0.0; }
    } else if (step == 1 || step == 3) {
      if (frame == 0.0) step++;
      if (frame > 0) frame = frame - 1.0;
      for (int i = 0; i < 5; i++){ ghost_height[i] = -sin((frame - i)*M_PI/30); }
      display_rot = -frame;
    }
  }
  if (step == 4) step = 0;

  if (health == 0) death = true;

  if (get_coffee) {
    speed_boost = 2.0;
    pickup_timer[3] += dtime;
    if (pickup_timer[3] >= 10000) {
      pickup_timer[3] = 0;
      get_coffee = false;
    }
    pickup[3] = false;
  }



  if (get_gun || get_launcher || get_laser) {

    if (clip_size == 100 & !fire_mode) {

      if (!release) {

        recharge_timer += dtime;
        if (recharge_timer >= 100) {
          recharge_timer = 0;
          if (magazine > 1) {
            magazine--;
          }
          // std::cout << "MAG: " << magazine << std::endl;
        }

        burst = true;

      } else {

        if (burst) {
          GLfloat charge = (GLfloat)(5.0 * (100 - magazine) / 100);
          GLfloat drag = (GLfloat)(5.0 * (magazine) / 100);
          std::cout << "CHARGE: " << charge << std::endl;
          for (int i = 0; i < NUM_BULLET; i++) {
            if (!active[i]) {
              active[i] = true;
              bullet[i] = players[0][0].position;
              bullet_theta[i] = theta;
              bullet_phi[i] = phi;
              bullet_dist[i] = 0.0;
              bullet_type[i] = gun_type;
              bullet_size[i] = vec3(active_bullet_size.x * charge, active_bullet_size.y * charge, active_bullet_size.z * charge);
              bullet_color[i] = active_bullet_color;
              bullet_speed[i] = active_bullet_speed * drag;
              break;
            }
          }
          magazine = clip_size;
          reload = true;

          burst = false;

        }

      }

      bullet_hud = 100 - magazine;

    } else {

      if (magazine <= 0) {

        if (clip_size == 25) {
          if (bullet_ammo > 0) {

            reload_timer += dtime;
            if (reload_timer >= 1000) {
              std::cout << "reload uzi" << std::endl;
              reload_timer = 0;
              magazine = clip_size;
            }

          }
        }

        if (clip_size == 3) {
          if (fire_mode) { reload_time = 3000; } else { reload_time = 5000; }
          if (rocket_ammo > 0) {

            reload_timer += dtime;
            if (reload_timer >= reload_time) {
              std::cout << "reload rockets" << std::endl;
              reload_timer = 0;
              magazine = clip_size;
            }

          }
        }

      }


      if (clip_size == 100) {
        if (fire_mode && magazine < 100) {
          recharge_timer += dtime;
          if (recharge_timer >= 100) {
            recharge_timer = 0;
            magazine++;
            std::cout << "MAG: " << magazine << std::endl;
          }
        }
      }

      if (fire_gun || !release) {
        for (int i = 0; i < NUM_BULLET; i++) {
          if (magazine > 0) {
            if (!active[i]) {
              fire_gun = false;
              active[i] = true;
              bullet[i] = players[0][0].position;
              bullet_theta[i] = theta;
              bullet_phi[i] = phi;
              bullet_dist[i] = 0.0;
              bullet_type[i] = gun_type;
              bullet_size[i] = active_bullet_size;
              bullet_color[i] = active_bullet_color;
              bullet_speed[i] = active_bullet_speed;
              magazine--;
              std::cout << "MAG: " << magazine << std::endl;
              if (clip_size == 25) {
                bullet_ammo--;
                std::cout << "BULLETS: " << bullet_ammo << std::endl;
              }
              if (clip_size == 3) {
                rocket_ammo--;
                std::cout << "ROCKETS: " << rocket_ammo << std::endl;
              }
              if ((clip_size == 25 && fire_mode) || clip_size == 3) {
                release = true;
              }
              break;
            }
          }
        }
      } else {
        if ((clip_size == 25 && !fire_mode) || (clip_size == 100 && fire_mode)) {
          release = true;
          reload = true;
        }
      }

      bullet_hud = magazine;

    }

  }

  // if (get_launcher) {
  // }
  //
  // if (get_laser) {
  // }

  if (get_vaccuum) {
    for (int i = 0; i < NUM_GHOSTS; i++) {
      for (int j = 0; j < PARTS_GHOST; j++) {
        if (suckable && fire_gun) { ghosts[i][j].health = 0; }
        ghosts[i][j].grow_shrink(vec3(ghosts[i][j].health/100, ghosts[i][j].health/100, ghosts[i][j].health/100));
      }
    }
  }
  if (get_bullet) {
    // magazine = clip_size;
    pickup_timer[4] += dtime;
    if (pickup_timer[4] >= 10000) {
      pickup_timer[4] = 0;
      get_bullet = false;
    }
    pickup[4] = false;
  }

  if (get_rocket) {
    // magazine = clip_size;
    pickup_timer[5] += dtime;
    if (pickup_timer[5] >= 10000) {
      pickup_timer[5] = 0;
      get_rocket = false;
    }
    pickup[5] = false;
  }

  if (get_health) {
    pickup_timer[6] += dtime;
    if (pickup_timer[6] >= 10000) {
      pickup_timer[6] = 0;
      get_health = false;
    }
    pickup[6] = false;
  }

  if (get_shield) {
    pickup_timer[7] += dtime;
    if (pickup_timer[7] >= 10000) {
      pickup_timer[7] = 0;
      get_shield = false;
    }
    pickup[7] = false;
  }

  if (get_key) { exit(EXIT_SUCCESS); }

  // for (int i = 0; i < NUM_ENEMIES; i++) {
    if (p_die[0]) {
      health--;
      hurt = true;
      p_die[0] = false;
    }// exit(EXIT_FAILURE);
    if (p_die[1]) {
      if (shield > 0) {
        shield--;
        hurt = true;
      } else {
        health -= 2;
        hurt = true;
      }
      p_die[1] = false;
    }// exit(EXIT_FAILURE);
    if (p_die[2]) {
      if (shield > 0) {
        shield -= 2;
        hurt = true;
      } else {
        health--;
        hurt = true;
      }
      magazine--;
      if (clip_size == 25) {
        bullet_ammo--;
      }
      if (clip_size == 3) {
        rocket_ammo--;
      }
      p_die[2] = false;
    }// exit(EXIT_FAILURE);
    if (p_die[3]) {
      if (shield > 0) {
        shield--;
        hurt = true;
      } else {
        health--;
        hurt = true;
      }
      p_die[3] = false;
    }// exit(EXIT_FAILURE);
  // }

  if(hurt) {
    players[0][0].velocity.z += 20.0 * sin(theta*M_PI/180)/2;
    players[0][0].velocity.x += 20.0 * cos(theta*M_PI/180)/2;
  }

  vec3 ghost_parts_diff[PARTS_GHOST] = {
    vec3(0.0, ghost_height[0] + 0.5, 0.0),
    vec3(0.0, ghost_height[1] + 0.0, 0.0),
    vec3(0.0 + 0.5 * cos(105 * M_PI/180), ghost_height[2] - 1.0, 0.0 + 0.5 * sin(105 * M_PI/180)),
    vec3(0.0 + 0.5 * cos(225 * M_PI/180), ghost_height[3] - 1.0, 0.0 + 0.5 * sin(225 * M_PI/180)),
    vec3(0.0 + 0.5 * cos(345 * M_PI/180), ghost_height[4] - 1.0, 0.0 + 0.5 * sin(345 * M_PI/180))
  };

  for (int i = 0; i < NUM_PLAYERS; i++) {
    for (int j = 0; j < PARTS_PLAYER; j++) {
      players[i][j].gravity_update();
      players[i][j].move_and_face(vec3(0, theta, 0));
    }
  }

  for (int i = 0; i < NUM_GUNS; i++) {
    for (int j = 0; j < PARTS_GUN; j++) {
      guns[i][j].move_and_face(vec3(0, display_rot, 0));
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, gun_loc[i], pickup_size[0], pickup[0], 1.0, false, filler);
  }

  // for (int i = 0; i < NUM_GUNS; i++) {
  //   for (int j = 0; j < PARTS_GUN; j++) {
  //     gun_hud[i][j].move_and_face(vec3(0, display_rot, 0));
  //   }
  // }

  for (int i = 0; i < NUM_LAUNCHERS; i++) {
    for (int j = 0; j < PARTS_LAUNCHER; j++) {
      launchers[i][j].move_and_face(vec3(0, display_rot, 0));
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, launcher_loc[i], pickup_size[8], pickup[8], 1.0, false, filler);
  }

  for (int i = 0; i < NUM_LASERS; i++) {
    for (int j = 0; j < PARTS_LASER; j++) {
      lasers[i][j].move_and_face(vec3(0, display_rot, 0));
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, laser_loc[i], pickup_size[9], pickup[9], 1.0, false, filler);
  }

  for (int i = 0; i < NUM_VACCUUMS; i++) {
    for (int j = 0; j < PARTS_VACCUUM; j++) {
      vaccuums[i][j].move_and_face(vec3(0, display_rot, 0));
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, vacuum_loc[i], pickup_size[1], pickup[1], 1.0, false, filler);
  }

  for (int i = 0; i < NUM_COFFEES; i++) {
    for (int j = 0; j < PARTS_COFFEE; j++) {
      coffees[i][j].move_and_face(coffee_parts_rot[j]);
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, coffee_loc[i], pickup_size[3], pickup[3], 1.0, false, filler);
  }

  for (int i = 0; i < NUM_BULLETS; i++) {
    for (int j = 0; j < PARTS_BULLET; j++) {
      bullets[i][j].move_and_face(vec3(0, display_rot, 45));
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, bullet_loc[i], pickup_size[4], pickup[4], 1.0, false, filler);
  }

  for (int i = 0; i < NUM_ROCKETS; i++) {
    for (int j = 0; j < PARTS_ROCKET; j++) {
      rockets[i][j].move_and_face(vec3(0, display_rot, 45));
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, rocket_loc[i], pickup_size[5], pickup[5], 1.0, false, filler);
  }

  for (int i = 0; i < NUM_HEALTHS; i++) {
    for (int j = 0; j < PARTS_HEALTH; j++) {
      healths[i][j].move_and_face(vec3(display_rot, display_rot, display_rot));
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, health_loc[i], pickup_size[6], pickup[6], 1.0, false, filler);
  }

  for (int i = 0; i < NUM_SHIELDS; i++) {
    for (int j = 0; j < PARTS_SHIELD; j++) {
      shields[i][j].move_and_face(vec3(display_rot, display_rot, display_rot));
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, shield_loc[i], pickup_size[7], pickup[7], 1.0, false, filler);
  }

  for (int i = 0; i < NUM_KEYS; i++) {
    for (int j = 0; j < PARTS_KEY; j++) {
      keys[i][j].move_and_face(vec3(0, display_rot, 0));
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, key_loc[i], pickup_size[2], pickup[2], 1.0, false, filler);
  }

  for (int i = 0; i < NUM_GHOSTS; i++) {
    for (int j = 0; j < PARTS_GHOST; j++) {
      if (follow[0]) { ghosts[i][j].chase_(players[0][0].position, 0.1); }
      ghosts[i][j].move_and_face(vec3(ghost_parts_rot[j].x, ghosts[i][j].rotation.y, ghost_parts_rot[j].z));
      ghosts[i][j].gravity_update();
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, ghosts[i][0].position, character_bounds, p_die[0], 0.0, true, filler);
    collision(players[0][0].position, character_bounds, players[0][0].velocity, ghosts[i][0].position, character_bounds, suckable, 15.0, false, filler);
    collision(players[0][0].position, character_bounds, players[0][0].velocity, ghosts[i][0].position, character_bounds, follow[0], 15.0, false, filler);
  }

  for (int i = 0; i < NUM_ZOMBIES; i++) {
    for (int j = 0; j < PARTS_ZOMBIE; j++) {
      if (follow[1]) { zombies[i][j].chase_(players[0][0].position, (i + 1) * 0.05); }
      zombies[i][j].move_and_face(vec3(0, zombies[i][j].rotation.y, 0));
      zombies[i][j].gravity_update();
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, zombies[i][0].position, character_bounds, p_die[1], 0.0, true, filler);
    collision(players[0][0].position, character_bounds, players[0][0].velocity, zombies[i][0].position, character_bounds, follow[1], 20.0, false, filler);
  }

  for (int i = 0; i < NUM_WEREWOLFS; i++) {
    for (int j = 0; j < PARTS_WEREWOLF; j++) {
      if (follow[2]) { werewolfs[i][j].chase_(players[0][0].position, 0.05); }
      werewolfs[i][j].move_and_face(vec3(0, werewolfs[i][j].rotation.y, 0));
      werewolfs[i][j].gravity_update();
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, werewolfs[i][0].position, character_bounds, p_die[2], 0.0, true, filler);
    collision(players[0][0].position, character_bounds, players[0][0].velocity, werewolfs[i][0].position, character_bounds, follow[2], 30.0, false, filler);
  }

  for (int i = 0; i < NUM_AGENCIES; i++) {
    for (int j = 0; j < PARTS_AGENCIE; j++) {
      if (follow[3]) { agencies[i][j].chase_(players[0][0].position, 0.1); }
      agencies[i][j].move_and_face(vec3(0, agencies[i][j].rotation.y, 0));
      agencies[i][j].gravity_update();
    }
    collision(players[0][0].position, character_bounds, players[0][0].velocity, agencies[i][0].position, character_bounds, p_die[3], 0.0, true, filler);
    collision(players[0][0].position, character_bounds, players[0][0].velocity, agencies[i][0].position, character_bounds, follow[3], 25.0, false, filler);
  }

  for (int i = 0; i < NUM_FLOORS; i++) {
    for (int j = 0; j < PARTS_FLOOR; j++) {
      for (int k = 0; k < NUM_PLAYERS; k++) {
        for (int l = 0; l < PARTS_PLAYER; l++) {
          collision(players[k][l].position, character_bounds, players[k][l].velocity, floors[i][j].position, floors[i][j].size, collide[i], 0.0, true, players[k][l].collide);
        }
      }
      for (int k = 0; k < NUM_ZOMBIES; k++) {
        for (int l = 0; l < PARTS_ZOMBIE; l++) {
          collision(zombies[k][l].position, character_bounds, zombies[k][l].velocity, floors[i][j].position, floors[i][j].size, collide[i], 0.0, true, zombies[k][l].collide);
        }
      }
      for (int k = 0; k < NUM_GHOSTS; k++) {
        for (int l = 0; l < PARTS_GHOST; l++) {
          collision(ghosts[k][l].position, character_bounds, ghosts[k][l].velocity, floors[i][j].position, floors[i][j].size, collide[i], 0.0, true, ghosts[k][l].collide);
        }
      }
      for (int k = 0; k < NUM_WEREWOLFS; k++) {
        for (int l = 0; l < PARTS_WEREWOLF; l++) {
          collision(werewolfs[k][l].position, character_bounds, werewolfs[k][l].velocity, floors[i][j].position, floors[i][j].size, collide[i], 0.0, true, werewolfs[k][l].collide);
        }
      }
      for (int k = 0; k < NUM_AGENCIES; k++) {
        for (int l = 0; l < PARTS_AGENCIE; l++) {
          collision(agencies[k][l].position, character_bounds, agencies[k][l].velocity, floors[i][j].position, floors[i][j].size, collide[i], 0.0, true, agencies[k][l].collide);
        }
      }
    }
  }

  if(!debug) {

    // for (int i = 0; i < NUM_OBJECTS; i++) {
      // collision(players[0][0].position, character_bounds, players[0][0].velocity, wall_loc[i], wall_size[i], collide[i]);
    // }

    for (int i = 0; i < NUM_BULLET; i++) {
      vec3 bullet_adj_pos = vec3(
        bullet[i].x - bullet_dist[i] * cos(bullet_theta[i] * M_PI/180) * cos(bullet_phi[i] * M_PI/180),
        bullet[i].y - bullet_dist[i] * sin(bullet_phi[i] * M_PI/180),
        bullet[i].z - bullet_dist[i] * sin(bullet_theta[i] * M_PI/180) * cos(bullet_phi[i] * M_PI/180)
      );
      if (active[i]) {

        for (int j = 0; j < NUM_GHOSTS; j++) { collision(bullet_adj_pos, bullet_size[i], players[0][0].velocity, ghosts[j][0].position, character_bounds, g_die[j], 1.0, false, filler); }
        for (int j = 0; j < NUM_ZOMBIES; j++) { collision(bullet_adj_pos, bullet_size[i], players[0][0].velocity, zombies[j][0].position, character_bounds, z_die[j], 1.0, false, filler); }
        for (int j = 0; j < NUM_WEREWOLFS; j++) { collision(bullet_adj_pos, bullet_size[i], players[0][0].velocity, werewolfs[j][0].position, character_bounds, w_die[j], 1.0, false, filler); }
        for (int j = 0; j < NUM_AGENCIES; j++) { collision(bullet_adj_pos, bullet_size[i], players[0][0].velocity, agencies[j][0].position, character_bounds, a_die[j], 1.0, false, filler); }

        for (int k = 0; k < NUM_GHOSTS; k++) {

          if (g_die[k]) {
            int damage = 0;
            switch (bullet_type[i]) {
              case 1: damage = 0; break;
              case 2: damage = 0; break;
              case 3: damage = 25; break;
            }
            if (!done) {
              for (int j = 0; j < PARTS_GHOST; j++) {
                if (ghosts[k][j].health >= 0) {
                  ghosts[k][j].health -= damage;
                  done = true;
                }
              }
            }
          }

        }
        for (int k = 0; k < NUM_ZOMBIES; k++) {

          if (z_die[k]) {
            int damage = 0;
            switch (bullet_type[i]) {
              case 1: damage = 25; break;
              case 2: damage = 50; break;
              case 3: damage = 50; break;
            }
            if (!done) {
              for (int j = 0; j < PARTS_ZOMBIE; j++) {
                if (zombies[k][j].health > 0) {
                  zombies[k][j].health -= damage;
                  done = true;
                }
              }
            }
          }

        }
        for (int k = 0; k < NUM_WEREWOLFS; k++) {

          if (w_die[k]) {
            int damage = 0;
            switch (bullet_type[i]) {
              case 1: damage = 0; break;
              case 2: damage = 50; break;
              case 3: damage = 25; break;
            }
            if (!done) {
              for (int j = 0; j < PARTS_WEREWOLF; j++) {
                if (werewolfs[k][j].health > 0) {
                  werewolfs[k][j].health -= damage;
                  done = true;
                }
              }
            }
          }

        }
        for (int k = 0; k < NUM_AGENCIES; k++) {

          if (a_die[k]) {
            int damage = 0;
            switch (bullet_type[i]) {
              case 1: damage = 50; break;
              case 2: damage = 50; break;
              case 3: damage = 50; break;
            }
            if (!done) {
              for (int j = 0; j < PARTS_AGENCIE; j++) {
                if (agencies[k][j].health >= 0) {
                  agencies[k][j].health -= damage;
                  done = true;
                }
              }
            }
          }

        }
      }
    }

  }

  for (int i = 0; i < NUM_GHOSTS; i++) {
    for (int j = 0; j < PARTS_GHOST; j++) {
      ghosts[i][j].grow_shrink(vec3(ghosts[i][j].health/100, ghosts[i][j].health/100, ghosts[i][j].health/100));
    }
  }

  for (int i = 0; i < NUM_ZOMBIES; i++) {
    for (int j = 0; j < PARTS_ZOMBIE; j++) {
      zombies[i][j].grow_shrink(vec3(zombies[i][j].health/100, zombies[i][j].health/100, zombies[i][j].health/100));
    }
  }

  for (int i = 0; i < NUM_WEREWOLFS; i++) {
    for (int j = 0; j < PARTS_WEREWOLF; j++) {
      werewolfs[i][j].grow_shrink(vec3(werewolfs[i][j].health/100, werewolfs[i][j].health/100, werewolfs[i][j].health/100));
    }
  }

  for (int i = 0; i < NUM_AGENCIES; i++) {
    for (int j = 0; j < PARTS_AGENCIE; j++) {
      agencies[i][j].grow_shrink(vec3(agencies[i][j].health/100, agencies[i][j].health/100, agencies[i][j].health/100));
    }
  }

  // for (int i = 0; i < NUM_FLOORS; i++) {
  //   for (int j = 0; j < PARTS_FLOOR; j++) {
  //     for (int k = 0; k < NUM_WEREWOLFS; k++) {
  //       for (int l = 0; l < PARTS_WEREWOLF; l++) {
  //         werewolfs[k][l].collision(floors[i][j].position, floors[i][j].size, robot_collision, 0.0, false);
  //       }
  //     }
  //   }
  // }

  // for (int i = 0; i < NUM_DOORS; i++) {
  //   collision(players[0][0].position, character_bounds, door_loc[i], door_size[i], doors[i]);
  // }

  // for (int i = 0; i < NUM_INTERACTABLES; i++) {
  //   collision(players[0][0].position, character_bounds, inter_loc[i], inter_size[i], proximal[i]);
  // }


  for (int i = 0; i < NUM_WEREWOLFS; i++) {
    for (int j = 0; j < PARTS_WEREWOLF; j++) {
      werewolfs[i][j].position_update();
      werewolfs[i][j].check_fall_death();
    }
  }

  for (int i = 0; i < NUM_ZOMBIES; i++) {
    for (int j = 0; j < PARTS_ZOMBIE; j++) {
      zombies[i][j].position_update();
      zombies[i][j].check_fall_death();
    }
  }

  for (int i = 0; i < NUM_GHOSTS; i++) {
    for (int j = 0; j < PARTS_GHOST; j++) {
      ghosts[i][j].position_update();
      ghosts[i][j].check_fall_death();
    }
  }

  for (int i = 0; i < NUM_AGENCIES; i++) {
    for (int j = 0; j < PARTS_AGENCIE; j++) {
      agencies[i][j].position_update();
      agencies[i][j].check_fall_death();
    }
  }

  for (int i = 0; i < NUM_PLAYERS; i++) {
    for (int j = 0; j < PARTS_PLAYER; j++) {
      players[i][j].position_update();
      players[i][j].check_fall_death();
    }
  }

  title_bar = " X: " + std::to_string(players[0][0].position.x)
            + " Y: " + std::to_string(players[0][0].position.y)
            + " Z: " + std::to_string(players[0][0].position.z)
            + " WD: " + std::to_string(w_die[0]);
            // 0.01 * (time - lasttime)); // + " l:" + std::to_string(l) + " r:" + std::to_string(r) + " f:" + std::to_string(f) + " b:" + std::to_string(b);

  if (health <= 0) { exit(EXIT_SUCCESS); }

  // ENVIRONMENT
  disp_rot = display_rot;

  lasttime = nowtime;

  glutPostRedisplay();

}

#endif
