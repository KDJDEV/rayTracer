#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>

#include "main.h"
#include "hittable.h"


class HittableList : public Hittable {
   public:
    std::vector<shared_ptr<Hittable>> objects;

    HittableList() {}
    HittableList(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<Hittable> object) { objects.push_back(object); }

    bool hit(const Ray& r, double rayTMin, double rayTMax,
             HitRecord& rec) const override {
        HitRecord tempRec;
        bool hitAnything = false;
        auto closestSoFar = rayTMax;

        for (const auto& object : objects) {
            if (object->hit(r, rayTMin, closestSoFar, tempRec)) {
                hitAnything = true;
                closestSoFar = tempRec.t;
                rec = tempRec;
            }
        }
        return hitAnything;
    }
};

#endif