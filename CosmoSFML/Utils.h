#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "globals.h"
#define PI 3.14f
template <class T1>
inline std::vector<v2f> obtain_vertices(T1 a, sf::Transform ta) {
   std::vector<v2f> buf;
   for (size_t i = 0; i < a.getPointCount(); i++) {
      v2f point = a.getPoint(i);
      buf.push_back(ta.transformPoint(point));
   }
   return buf;
}

inline float toRad(float a)
{
   return a * (PI) / 180;
}

inline float distance_beetween(v2f c1, v2f c2)
{
   return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

template<class T1, class T2>
inline float distance_beetween(T1 a, T2 b)
{
   v2f c1 = a.getPosition();
   v2f c2 = b.getPosition();
   return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

template<class T1, class T2>
inline bool check_collisions(T1 a, sf::Transform ta, T2 b, sf::Transform tb)
{
   std::vector<v2f> v1 = obtain_vertices(a, ta);
   std::vector<v2f> v2 = obtain_vertices(b, tb);
   std::vector<v2f>* p1 = &v1;
   std::vector<v2f>* p2 = &v2;

   for (size_t shape = 0; shape < 2; shape++)
   {
      if (shape == 1) {
         p2 = &v1;
         p1 = &v2;
      }
      for (size_t a = 0; a < p1->size(); a++)
      {
         int b = (a + 1) % p1->size();
         v2f axisProj = { -(p1->at(b).y - p1->at(a).y), p1->at(b).x - p1->at(a).x };
         float d = sqrtf(axisProj.x * axisProj.x + axisProj.y * axisProj.y);
         axisProj = { axisProj.x / d, axisProj.y / d };

         float min_r1 = INFINITY, max_r1 = -INFINITY;
         for (size_t p = 0; p < p1->size(); p++)
         {
            float q = (p1->at(p).x * axisProj.x + p1->at(p).y * axisProj.y);
            min_r1 = std::min(min_r1, q);
            max_r1 = std::max(max_r1, q);
         }

         float min_r2 = INFINITY, max_r2 = -INFINITY;
         for (int p = 0; p < p2->size(); p++)
         {
            float q = (p2->at(p).x * axisProj.x + p2->at(p).y * axisProj.y);
            min_r2 = std::min(min_r2, q);
            max_r2 = std::max(max_r2, q);
         }
         if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
            return false;
      }
   }
   return true;

}


template<class T1>
inline bool check_collisions(T1 a, sf::Transform ta, sf::CircleShape circle)
{
   float r = circle.getRadius();
   std::vector<v2f> v = obtain_vertices(a, ta);
   for (auto element : v) {
      float dis = distance_beetween(element, circle.getPosition());
      if (dis <= r)
         return true;
   }
   return false;
}

//funckja ktora liczy kat taki sam do przyspieszenia grawitacyjnego
inline float atgrav(v2f vec) {
   return (atan2(-vec.x, vec.y) * 180 / PI);
}

