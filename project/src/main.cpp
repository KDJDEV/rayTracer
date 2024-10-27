#include "color.h"
#include "vec3.h"

#include <iostream>
#include <fstream>

int main() {
     std::ofstream imageFile("./image.ppm");

    int imageWidth = 256;
    int imageHeight = 256;

    imageFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++){
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            auto pixelColor = color(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0);
            writeColor(imageFile, pixelColor);
        }
    }
    
    imageFile.close();
    std::clog << "\rDone.\n";
}
