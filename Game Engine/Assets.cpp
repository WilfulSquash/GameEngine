#include "Assets.h"

using namespace nu;
namespace assets {
    Mesh playerMesh{ {Vector2{0, 0}, Vector2{1, 1}, Vector2{0, 2}, Vector2{3, 1}, Vector2{0, 0}}, Color{1.0f, 1.0f, 1.0f} };
    Mesh playerMesh2{ {Vector2{1, 1}, Vector2{-1, -1}, Vector2{-1, 3},Vector2{1, 1}}, Color{0.1333333333f, 0.2941176471f, 1.0f} };
    Model playerModel = vector<Mesh>{ {playerMesh, playerMesh2} };
    Model enemyModel = vector<Mesh>{ playerMesh };
    Mesh bulletMesh{
  {
    Vector2{ -1, -1 },
    Vector2{ 1, 0 },
    Vector2{ -1, 1 },
    Vector2{ -1, -1 },
  },
  Color{ 1.0f, 0.0f, 0.0f }
    };
    Model bulletModel{ std::vector<Mesh>{bulletMesh}};
}