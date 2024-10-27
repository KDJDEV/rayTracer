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
            auto r = double(i) / (imageWidth - 1);
            auto g = double(j) / (imageHeight - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            imageFile << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    
    imageFile.close();
    std::clog << "\rDone.\n";
}
