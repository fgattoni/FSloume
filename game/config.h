#ifndef F_MAIN_H
#define F_MAIN_H

#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

/* TODO: organiser en master constantes, constantes de démarrage
 * et constantes liées */

class Config
{
private:
  void updateParams();
public:
  /* Taille du plateau en px */
  static int WIDTH;
  static int HEIGHT;

  /* Nb max de doigts gérés (android) */
  static const size_t NB_MAX_FINGERS = 10;

  /* Taille de base de la police */
  static unsigned int FONT_BASE_SIZE_PX;

  /* Taille d'un slime en px */
  static int SLIME_WIDTH;
  static int SLIME_HEIGHT;
  static int PUPIL_RADIUS;
  // Maximise la taille de l'œil avec les coordonnées choisies
  static int EYE_RADIUS_SQUARED;
  static int EYE_RADIUS;

  /* Taille du filet */
  static int NET_WIDTH;
  static int NET_HEIGHT;

  /* Taille de la balle */
  static int BALL_RADIUS;

  /* Taille du panneau danger */
  static int DANGERPT_WIDTH;

  /* Taille du nuage */
  static int CLOUD_WIDTH;
  static int CLOUD_HEIGHT;

  /* Taille des mires */
  static unsigned int TARGET_WIDTH;
  static unsigned int TARGET_HEIGHT;

  /* Pas d'anticipation sur le mouvement de la balle */
  static int BALL_ANTICIPATION;

  /* Paramètres physiques */
  static float JUMP_DURATION; // Durée du saut en s
  static int JUMP_MAX_HEIGHT;
  static int SLIME_HORIZONTAL_SPEED;
  static float SLIME_TIME_BOOST; // Temps en s où on peut booster
  static float SLIME_DOUBLE_JUMP_TIME; // Temps en s avant de pouvoir double-jump
  static float SLIME_HEIGHT_GROUND_POUND; // Hauteur min pour une charge au sol
  static float BALL_ELASTICITY; // Elasticité de la balle, entre 0 et 1
  static float SLIME_ELASTICITY; // Elasticité du sloume, entre 0 et 1
  // Calculés automatiquement
  static float GRAVITY;
  static int SLIME_JUMP_SPEED;

  Config();
};

typedef Config CG;

#endif
