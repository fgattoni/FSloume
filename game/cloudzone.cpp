/*
 * cloud.cpp
 * Copyright (C) 2017 flo <flo@knightknight>
 *
 * Distributed under terms of the MIT license.
 */

#include "cloudzone.h"
#include "config.h"
#include <random>
#include <sstream>


Cloud::Cloud(const std::string &tex_name)
{
  m_texture = ResourceManager::getTexture(tex_name);
  m_sprite.setTexture(*m_texture.lock());
  m_sprite.setScale((float)CG::CLOUD_WIDTH/(*m_texture.lock()).getSize().x,
      (float)CG::CLOUD_HEIGHT/(*m_texture.lock()).getSize().y);
}

void Cloud::updateSprite()
{
  m_sprite.setPosition(m_x - CG::CLOUD_WIDTH/2, m_y - CG::CLOUD_HEIGHT/2);
}

void Cloud::animate(float dt)
{
  m_x += m_vx * dt;
  m_y += m_vy * dt;
  updateSprite();
}

void Cloud::setSpeed(float vx, float vy)
{
  m_vx = vx;
  m_vy = vy;
}

void Cloud::draw (sf::RenderWindow &w) const
{
  w.draw(m_sprite);
}

void Cloud::setPosition (float x, float y)
{
  m_x = x;
  m_y = y;
  updateSprite();
}

CloudZone::CloudZone(sf::FloatRect zone, size_t how_many) : m_zone(zone),
  m_clouds()
{
  m_clouds.reserve(how_many);

  std::random_device rd;
  std::mt19937 twister (rd());
  std::uniform_int_distribution<int> dist_rc(1,2);

  for (size_t i = 0; i < how_many; ++i)
  {
    std::ostringstream oss;
    oss << "rc_cloud" << dist_rc(twister) << "_png";
    m_clouds.push_back({oss.str()});
  }


  std::uniform_real_distribution<float> dist_x(m_zone.left-CG::CLOUD_WIDTH/2,
      m_zone.width+CG::CLOUD_WIDTH/2);
  std::uniform_real_distribution<float> dist_y(m_zone.top, m_zone.top + m_zone.height);
  std::uniform_real_distribution<float> dist_vx(CG::CLOUD_MIN_SPEED_X, CG::CLOUD_MAX_SPEED_X);
  std::uniform_real_distribution<float> dist_vy(CG::CLOUD_MIN_SPEED_Y, CG::CLOUD_MAX_SPEED_Y);

  for (Cloud &c : m_clouds)
  {
    c.setPosition(dist_x(twister), dist_y(twister));
    c.setSpeed(dist_vx(twister), dist_vy(twister));
  }
}

void CloudZone::animate(float dt)
{
  // TODO: check for bounds
  for (Cloud &c : m_clouds)
  {
    if (c.m_x - CG::CLOUD_WIDTH > m_zone.left + m_zone.width)
      c.m_x = m_zone.left - CG::CLOUD_WIDTH;
    if (c.m_y - CG::CLOUD_HEIGHT > m_zone.top + m_zone.height ||
        c.m_y + CG::CLOUD_HEIGHT < m_zone.top)
      c.m_vy *= -1;
    c.animate(dt);
  }
}

void CloudZone::updateSprite()
{

}

void CloudZone::draw(sf::RenderWindow &w) const
{
  for (const Cloud &c : m_clouds)
    c.draw(w);

}
