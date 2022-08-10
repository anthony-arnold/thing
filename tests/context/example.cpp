#include <thing/context.hpp>
#include <fstream>
#include <cmath>

namespace {

constexpr double eps = 1.0e-30;
constexpr double MPS_TO_AUPH = 7.7e-7;

struct float3 {
   double x, y, z;
};

struct Mass {};
struct Pos {};
struct Vel {};
struct Acc {};

auto sub(const float3& a, const float3& b) {
   return float3 {
      a.x - b.x,
      a.y - b.y,
      a.z - b.z
   };
}

auto mul(const float3& a, double d) {
   return float3 {
      a.x * d,
      a.y * d,
      a.z * d
   };
}

void add(const float3& b, float3& out) {
   out.x += b.x;
   out.y += b.y;
   out.z += b.z;
}

template <typename T>
void acc(T& system) {
   for (auto& planet : system) {
      float3 a = {};
      for (auto& planet2 : system) {
         float3 dr = sub(thing::get<Pos>(planet2), thing::get<Pos>(planet));
         double r2 = dr.x*dr.x + dr.y*dr.y + dr.z*dr.z + eps;
         double r = std::sqrt(r2);
         double rinv3 = 1.0 / (r*r2);
         double mrinv3 = thing::get(planet2, Mass{}) * rinv3;

         add(mul(dr, mrinv3 * MPS_TO_AUPH), a);
      }

      thing::get<Acc>(planet) = a;
   }
}

template <typename T>
void kick(T& system, double dt) {
   for (auto& planet : system) {
      add(mul(thing::get<Acc>(planet), dt),
          thing::get(planet, Vel {}));
   }
}

template <typename T>
void drift(T& system) {
   for (auto& planet : system) {
      add(
         thing::get<Vel>(planet),
         thing::get<Pos>(planet)
         );
   }
}

}

int main () {
   auto system = thing::default_system<
      thing::property<Mass, double>,
      thing::property<Pos, float3>,
      thing::property<Vel, float3>,
      thing::property<Acc, float3>> {};

   // Sun, Earth, Moon
   system.resize(3);

   auto it = system.begin();
   thing::get(*it, Mass{}) = 1.0;
   thing::get(*it, Pos{}) = float3 {};
   thing::get(*it, Vel{}) = float3 {};
   thing::get(*it, Acc{}) = float3 {};
   it++;

   thing::get(*it, Mass{}) = 3e-6;
   thing::get(*it, Pos{}) = float3 { 1.0, 0.0, 0.0 };
   thing::get(*it, Vel{}) = float3 { 0.0, 7e-4 };
   thing::get(*it, Acc{}) = float3 { };
   it++;

   thing::get(*it, Mass{}) = 3.7e-8;
   thing::get(*it, Pos{}) = float3 { 1.00257, 0.0, 0.0 };
   thing::get(*it, Vel{}) = float3 { 0.0, 7.25e-4 };
   thing::get(*it, Acc{}) = float3 { };
   it++;

   auto fs = std::ofstream("example.pos");

   double t = 0;
   acc(system);
   kick(system, 0.5);
   while (t < 10000.0) {
      drift(system);

      for (auto& planet : system) {
         const auto& p = thing::get(planet, Pos{});

         fs << p.x << " " << p.y << " " << p.z << " ";
      }
      fs << std::endl;
      t += 1.0;

      acc(system);
      kick(system, 1.0);
   }

}
