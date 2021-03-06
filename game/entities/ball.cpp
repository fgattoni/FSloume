#include "ball.h"
#include "tools/utils.h"
#include "rc_manager.h"

Ball::Ball() :
  MovingEntity(),
  m_clamp(),
  m_path(CG::BALL_ANTICIPATION, sf::Color::Red)
{
  m_texture = ResourceManager::getTexture("ball");
  m_sprite.setTexture(*m_texture);
}

void Ball::setX (float x)
{
  m_x = x;
  updateSprite();
}

void Ball::setY (float y)
{
  m_y = y;
  updateSprite();
}

void Ball::clampTo (const sf::FloatRect &clamp)
{
  m_clamp = clamp;
}

void Ball::forceBounce()
{
  m_vy = -3*CG::SLIME_JUMP_SPEED;
}

void Ball::move (float dt)
{
  /* Déplacement avec la vitesse */
  m_x += dt*m_vx;
  m_y += dt*m_vy;

  /* Perte de vitesse avec la gravité */
  m_vy += CG::GRAVITY*dt;

  /* Contact sur les murs */
  if (m_x < m_clamp.left + (float)CG::BALL_RADIUS)
  {
    m_x = m_clamp.left + (float)CG::BALL_RADIUS;
    m_vx = -m_vx*CG::BALL_ELASTICITY;
  }

  if (m_x > m_clamp.left + m_clamp.width - (float)CG::BALL_RADIUS)
  {
    m_x = m_clamp.left + m_clamp.width - (float)CG::BALL_RADIUS;
    m_vx = -m_vx*CG::BALL_ELASTICITY;
  }

  if (m_y < (float)CG::BALL_RADIUS)
  {
    m_y = CG::BALL_RADIUS;
    m_vy = -m_vy;
  }

  if (m_y > m_clamp.top + m_clamp.height - (float)CG::BALL_RADIUS) // Cas spécial : contact au sol
  {
    m_y = m_clamp.top + m_clamp.height - (float)CG::BALL_RADIUS;
    m_vy = -m_vy*CG::BALL_ELASTICITY;
    m_onGround = true;
  }

  updateSprite();
}

void Ball::updateSprite()
{
  m_sprite.setPosition(
      m_x - (float)CG::BALL_RADIUS,
      m_y - (float)CG::BALL_RADIUS
      );
}

sf::Vector2f Ball::getPosition() const
{
  return {m_x, m_y};
}

sf::Vector2f Ball::getSpeed() const
{
  return {m_vx, m_vy};
}

void Ball::setSpeed(const sf::Vector2f &v)
{
  m_vx = v.x;
  m_vy = v.y;
}

void Ball::draw(sf::RenderTexture &w) const
{
  m_path.draw(w);
  w.draw(m_sprite);
}

void Ball::updatePath(int i)
{
  m_path.setPosition(i, m_x, m_y);
}
