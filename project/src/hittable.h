#ifndef HITTABLE_H
#define HITTABLE_H

class HitRecord {
   public:
    Point3 p;
    Vec3 normal;
    double t;
    bool frontFace;

    void setFaceNormal(const Ray& r, const Vec3& outwardNormal){
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
   public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, double rayTMin, double rayTMax,
                     HitRecord& rec) const = 0;
};

#endif