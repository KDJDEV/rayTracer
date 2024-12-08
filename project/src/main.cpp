#include "main.h"

#include "camera.h"
#include "hittable.h"
#include "hittableList.h"
#include "sphere.h"

int main() {
    HittableList world;

    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    Camera cam;
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;
    cam.samplesPerPixel = 100;

    cam.render(world);
}
