#include <catch2/catch.hpp>
#include <tuple>
#include <array>
#include <SFML/System/Vector3.hpp>
#include "../../game/tools/utils.h"

typedef sf::Vector2f Pt; // Point
typedef sf::Vector2f Sp; // Speed
/* M, V, R, M', R', V', dt, t expected */
typedef std::tuple<Pt, float, Sp, Pt, float, Sp, float, float> TestData;

TEST_CASE( "Test de collision entre cercles mouvants", "[collideTwoCircles]")
{
  const float inf = std::numeric_limits<float>::infinity();
  Pt M, Mp;
  float R, Rp;
  Sp V, Vp;
  float dt, t_expect;

#define AFFECT_SYMBOLS_FROM(s) \
  M = std::get<0>(s); \
  R = std::get<1>(s); \
  V = std::get<2>(s); \
  Mp = std::get<3>(s); \
  Rp = std::get<4>(s); \
  Vp = std::get<5>(s); \
  dt = std::get<6>(s); \
  t_expect = std::get<7>(s);


  SECTION ("Vitesses parallèles, pas d'intersection")
  {
    TestData testData[] = {
      {Pt(0, 0), 1, Sp(1, 0), Pt(3, 0), 1, Sp(1, 0), 100, -1}, // Normal
      {Pt(0, 0), 0, Sp(1, 0), Pt(3, 0), .5, Sp(1, 0), 100, -1}, // Un rayon nul
      {Pt(0, 0), 0, Sp(1, 0), Pt(3, 0), 0, Sp(1, 0), 100, -1}, // Deux rayons nuls
    };

    for (const TestData &d : testData)
    {
      AFFECT_SYMBOLS_FROM(d);
      INFO("M : " << M.x << ", " << M.y);
      INFO("R : " << R);
      INFO("V : " << V.x << ", " << V.y);
      INFO("M' : " << Mp.x << ", " << Mp.y);
      INFO("R' : " << Rp);
      INFO("V' : " << Vp.x << ", " << Vp.y);
      INFO("dt : " << dt);
      INFO("t_expect : " << t_expect);

      CHECK( collideTwoCircles(M, R, V, Mp, Rp, Vp, dt) == Approx(t_expect) );
    }
  }

  SECTION ("Vitesses parallèles, intersection")
  {
    TestData testData[] = {
      {Pt(0, 0), 1, Sp(1, 0), Pt(10, 0), 1, Sp(-1, 0), 100, 4}, // Normal
      {Pt(0, 0), 0, Sp(1, 0), Pt(10, 0), 1, Sp(-1, 0), 100, 4.5}, // Un rayon nul
      {Pt(0, 0), 0, Sp(1, 0), Pt(10, 0), 0, Sp(-1, 0), 100, 5}, // Deux rayons nuls
    };

    for (const TestData &d : testData)
    {
      AFFECT_SYMBOLS_FROM(d);
      INFO("M : " << M.x << ", " << M.y);
      INFO("R : " << R);
      INFO("V : " << V.x << ", " << V.y);
      INFO("M' : " << Mp.x << ", " << Mp.y);
      INFO("R' : " << Rp);
      INFO("V' : " << Vp.x << ", " << Vp.y);
      INFO("dt : " << dt);
      INFO("t_expect : " << t_expect);

      CHECK( collideTwoCircles(M, R, V, Mp, Rp, Vp, dt) == Approx(t_expect) );
    }
  }

  SECTION ("Vitesses quelconques, pas d'intersection")
  {
    TestData testData[] = {
      {Pt(0, 0), 1, Sp(.2, .3), Pt(10, 0), 1, Sp(.2, -.1), 100, -1},
      {Pt(0, 0), 1, Sp(.2, .3), Pt(10, 0), 1, Sp(.2, .1), 100, -1},
    };

    for (const TestData &d : testData)
    {
      AFFECT_SYMBOLS_FROM(d);
      INFO("M : " << M.x << ", " << M.y);
      INFO("R : " << R);
      INFO("V : " << V.x << ", " << V.y);
      INFO("M' : " << Mp.x << ", " << Mp.y);
      INFO("R' : " << Rp);
      INFO("V' : " << Vp.x << ", " << Vp.y);
      INFO("dt : " << dt);
      INFO("t_expect : " << t_expect);

      CHECK( collideTwoCircles(M, R, V, Mp, Rp, Vp, dt) == Approx(t_expect) );
    }
  }

  SECTION ("Vitesses quelconques, intersection")
  {
    TestData testData[] = {
      {Pt(0, 0), 1, Sp(1, .2), Pt(5, 0), 1, Sp(0, .2), 3, 3},
    };

    for (const TestData &d : testData)
    {
      AFFECT_SYMBOLS_FROM(d);
      INFO("M : " << M.x << ", " << M.y);
      INFO("R : " << R);
      INFO("V : " << V.x << ", " << V.y);
      INFO("M' : " << Mp.x << ", " << Mp.y);
      INFO("R' : " << Rp);
      INFO("V' : " << Vp.x << ", " << Vp.y);
      INFO("dt : " << dt);
      INFO("t_expect : " << t_expect);

      CHECK( collideTwoCircles(M, R, V, Mp, Rp, Vp, dt) == Approx(t_expect) );
    }
  }
}
