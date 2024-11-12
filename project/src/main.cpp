#include "main.h"

#include "hittable.h"
#include "hittableList.h"
#include "sphere.h"

Color rayColor(const Ray& r, const Hittable& world) {
    HitRecord rec;
    if (world.hit(r, 0, infinity, rec)){
        return 0.5 * (rec.normal + Color(1,1,1));
    }

    Vec3 unitDirection = r.direction();
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main() {
    std::ofstream imageFile("./image.ppm");

    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    //World

    HittableList world;

    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    auto cameraCenter = Point3(0, 0, 0);

    auto viewPortU = Vec3(viewportWidth, 0, 0);
    auto viewPortV = Vec3(0, -viewportHeight, 0);

    auto pixelDeltaU = viewPortU / imageWidth;
    auto pixelDeltaV = viewPortV / imageHeight;

    auto viewportUpperLeft =
        cameraCenter - Vec3(0, 0, focalLength) - viewPortU / 2 - viewPortV / 2;
    auto pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    imageFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' '
                  << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            auto pixelCenter =
                pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            Ray r(cameraCenter, rayDirection);

            auto pixelColor = rayColor(r, world);
            writeColor(imageFile, pixelColor);
        }
    }

    imageFile.close();
    std::clog << "\rDone.\n";
}
