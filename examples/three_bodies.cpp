#include <thing/context.hpp>
#include <thing/ref.hpp>
#include <thing/adapt.hpp>
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

      planet.acc = float3 {};
      for (auto& planet2 : system) {
         float3 dr = sub(planet2.pos, planet.pos);
         double r2 = dr.x*dr.x + dr.y*dr.y + dr.z*dr.z + eps;
         double r = std::sqrt(r2);
         double rinv3 = 1.0 / (r*r2);
         double mrinv3 = planet2.mass * rinv3;

         add(mul(dr, mrinv3 * MPS_TO_AUPH), planet.acc);
      }
   }
}

template <typename T>
void kick(T& system, double dt) {
   for (auto& planet : system) {
      add(mul(planet.acc, dt), planet.vel);
   }
}

template <typename T>
void drift(T& system) {
   for (auto& planet : system) {
      add(planet.vel, planet.pos);
   }
}


struct planet : thing::adaptor<thing::property<Mass, double>,
                               thing::property<Pos, float3>,
                               thing::property<Vel, float3>,
                               thing::property<Acc, float3>>
{
   template <typename TSystem>
   planet(thing::entity<TSystem>& e)
      : mass(ref<Mass>(e)),
        pos(ref<Pos>(e)),
        vel(ref<Vel>(e)),
        acc(ref<Acc>(e))
   {
   }

   thing::ref<Mass, double> mass;
   thing::ref<Pos, float3> pos;
   thing::ref<Vel, float3> vel;
   thing::ref<Acc, float3> acc;
};

}

int main () {
   auto system = thing::adaptive_system<planet> {};

   // Sun, Earth, Moon
   system.resize(3);

   auto body = system.begin();

   body->mass = 1;
   body->pos = float3 {};
   body->vel = float3 {};
   body->acc = float3 {};
   body++;

   body->mass = 3e-6;
   body->pos = float3 { 1. };
   body->vel = float3 { 0., 7e-4 };
   body->acc = float3 { };
   body++;

   body->mass = 3.7e-8;
   body->pos = float3 { 1.00257 };
   body->vel = float3 { 0.,  7.25e-4 };
   body->acc = float3 { };
   body++;

   auto fs = std::ofstream("three_bodies.pos");

   double t = 0;
   acc(system);
   kick(system, 0.5);
   while (t < 10000.0) {
      drift(system);

      for (auto& planet : system) {
         float3& p = planet.pos;
         fs << p.x << " " << p.y << " " << p.z << " ";
      }
      fs << std::endl;
      t += 1.0;

      acc(system);
      kick(system, 1.0);
   }

}
