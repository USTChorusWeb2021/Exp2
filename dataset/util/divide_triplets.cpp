#include <iostream>
#include <fstream>
#include <vector>

struct Triplet
{
    int head;
    int tail;
    int relation;
};

int main()
{
    std::ifstream allTripletsFile("../all_triplets.txt");

    int n = 0;
    allTripletsFile >> n;

    // std::vector<std::ofstream> outputFiles(11);
    // for (int i = 0; i < 11; ++i)
    //     outputFiles[i].open("div" + std::to_string(i) + ".txt");

    std::ofstream allBut10File("div0-9.txt");

    std::vector<Triplet> allTriplets;
    for (int i = 0; i < n; ++i)
    {
        Triplet triplet;
        allTripletsFile >> triplet.head >> triplet.tail >> triplet.relation;
        // outputFiles[i % 11] << triplet.head << ' ' << triplet.tail << ' ' << triplet.relation << '\n';
        if (i % 11 != 10)
        {
            allBut10File << triplet.head << ' ' << triplet.tail << ' ' << triplet.relation << '\n';
        }
    }
    
    return 0;
}
