#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <set>
#include <algorithm>

struct Triplet
{
    int head;
    int tail;
    int relation;

    bool operator<(Triplet rhs) const
    {
        if (this->head != rhs.head) return this->head < rhs.head;
        if (this->tail != rhs.tail) return this->tail < rhs.tail;
        return this->relation < rhs.relation;
    }
};

struct PredictResult
{
    int tail;
    double score;

    bool operator<(PredictResult rhs) const
    {
        return this->score < rhs.score;
    }
};

std::array<double, 100> addArray(const std::array<double, 100> & lhs, const std::array<double, 100> & rhs)
{
    std::array<double, 100> ret;
    for (int i = 0; i < 100; ++i) ret[i] = lhs[i] + rhs[i];
    return ret;
}

std::array<double, 100> subArray(const std::array<double, 100> & lhs, const std::array<double, 100> & rhs)
{
    std::array<double, 100> ret;
    for (int i = 0; i < 100; ++i) ret[i] = lhs[i] - rhs[i];
    return ret;
}

double normArray(const std::array<double, 100> & x)
{
    double sum = 0;
    for (int i = 0; i < 100; ++i) sum += x[i] * x[i];
    return sum;
}

int main()
{
    std::ifstream entityFile("./entity_vectors.txt");
    std::ifstream relationFile("./relation_vectors.txt");
    std::ifstream filterFile("./div0-9-sorted_by_relation.txt");
    std::ifstream testFile("../dataset/util/div10.txt");
    std::ofstream hit5File("./hit5.txt");

    int entityN = 0;
    entityFile >> entityN;
    std::vector<std::array<double, 100>> entities(entityN);
    for (int i = 0; i < entityN; ++i)
    {
        for (int j = 0; j < 100; ++j) entityFile >> entities[i][j];
    }

    int relationN = 0;
    relationFile >> relationN;
    std::vector<std::array<double, 100>> relations(entityN);
    for (int i = 0; i < relationN; ++i)
    {
        for (int j = 0; j < 100; ++j) relationFile >> relations[i][j];
    }

    int filterN = 0;
    filterFile >> filterN;
    std::set<Triplet> filters;
    for (int i = 0; i < filterN; ++i)
    {
        Triplet temp;
        filterFile >> temp.head >> temp.tail >> temp.relation;
        filters.insert(temp);
    }

    int testN = 0;
    testFile >> testN;
    for (int i = 0; i < testN; ++i)
    {
        Triplet test;
        testFile >> test.head >> test.tail >> test.relation;

        std::array<double, 100> headArray = entities[test.head];
        std::array<double, 100> realationArray = relations[test.relation];
        std::array<double, 100> predictTailArray = addArray(headArray, realationArray);

        std::vector<PredictResult> predictResults;
        predictResults.reserve(entityN);
        for (int j = 0; j < entityN; ++j)
        {
            std::array<double, 100> tailArray = entities[j];
            std::array<double, 100> diffArray = subArray(tailArray, predictTailArray);
            double score = normArray(diffArray);
            predictResults.push_back({ j, score });
        }

        std::sort(predictResults.begin(), predictResults.end());

        hit5File << i << '\t' << test.head << ' ' << test.relation << '\t';
        for (int j = 0; j < 5; ++j)
            hit5File << predictResults[j].tail << ' ' << predictResults[j].score << ' ';
        hit5File << '\n';

        std::cout << i << '\n';
    }

    return 0;
}
