//#include <QCoreApplication>
#include "alpr.h"
#include <iostream>

int main()
{


    alpr::Alpr openalpr("br", "/etc/openalpr/openalpr.conf", "/home/cesar/openalpr");

   openalpr.setTopN(20);

    if (openalpr.isLoaded() == false)
    {
        std::cerr << "Error loading OpenALPR" << std::endl;
        return 1;
    }

    alpr::AlprResults results = openalpr.recognize("track.png");

    for (int i = 0; i < results.plates.size(); i++)
    {
        alpr::AlprPlateResult plate = results.plates[i];
        std::cout << "plate" << i << ": " << plate.topNPlates.size() << " results" << std::endl;

        for (int k = 0; k < plate.topNPlates.size(); k++)
        {
            alpr::AlprPlate candidate = plate.topNPlates[k];
            std::cout << "    - " << candidate.characters << "\t confidence: " << candidate.overall_confidence;
            std::cout << "\t pattern_match: " << candidate.matches_template << std::endl;
        }
    }
    return 0;
}
