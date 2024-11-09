#include <fstream>
#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3.h"

color rayColor(const ray& r) {
    vec3 unitDirection = r.direction();
    auto a = 0.5 * (unitDirection.y() + 1.0);
    //std::cout << "This is a: " << a << '\n';
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
    std::ofstream imageFile("./image.ppm");

    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // Camera
    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    auto cameraCenter = point3(0, 0, 0);

    auto viewPortU = vec3(viewportWidth, 0, 0);
    auto viewPortV = vec3(0, -viewportHeight, 0);

    auto pixelDeltaU = viewPortU / imageWidth;
    auto pixelDeltaV = viewPortV / imageHeight;

    auto viewportUpperLeft =
        cameraCenter - vec3(0, 0, focalLength) - viewPortU / 2 - viewPortV / 2;
    auto pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    imageFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' '
                  << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            auto pixelCenter =
                pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            ray r(cameraCenter, rayDirection);

            auto pixelColor = rayColor(r);
            writeColor(imageFile, pixelColor);
        }
    }

    imageFile.close();
    std::clog << "\rDone.\n";
}
