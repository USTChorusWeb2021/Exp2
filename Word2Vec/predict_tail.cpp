#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <set>
#include <algorithm>

const int DIM = 100;

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

std::array<double, DIM> addArray(const std::array<double, DIM> & lhs, const std::array<double, DIM> & rhs)
{
    std::array<double, DIM> ret;
    for (int i = 0; i < DIM; ++i) ret[i] = lhs[i] + rhs[i];
    return ret;
}

std::array<double, DIM> subArray(const std::array<double, DIM> & lhs, const std::array<double, DIM> & rhs)
{
    std::array<double, DIM> ret;
    for (int i = 0; i < DIM; ++i) ret[i] = lhs[i] - rhs[i];
    return ret;
}

double normArray(const std::array<double, DIM> & x)
{
    double sum = 0;
    for (int i = 0; i < DIM; ++i) sum += x[i] * x[i];
    return sum;
}

int main()
{
    // std::ifstream entityFile("./entity_vectors.txt");
    // std::ifstream relationFile("./relation_vectors.txt");
    // std::ifstream filterFile("./div0-9-sorted_by_relation.txt");
    // std::ifstream testFile("../dataset/util/div10.txt");
    // std::ofstream hit5File("./hit5.txt");
    std::ifstream entityFile("./entity_vectors.txt");
    std::ifstream relationFile("./relation_vectors.txt");
    std::ifstream filterFile("../dataset/util/div10.txt");
    std::ifstream testFile("../dataset/util/test_release.txt");
    std::ofstream hit5File("./hit5-release.txt");

    int entityN = 0;
    entityFile >> entityN;
    std::vector<std::array<double, DIM>> entities(entityN);
    for (int i = 0; i < entityN; ++i)
    {
        for (int j = 0; j < DIM; ++j) entityFile >> entities[i][j];
    }

    int relationN = 0;
    relationFile >> relationN;
    std::vector<std::array<double, DIM>> relations(entityN);
    for (int i = 0; i < relationN; ++i)
    {
        for (int j = 0; j < DIM; ++j) relationFile >> relations[i][j];
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

        std::array<double, DIM> headArray = entities[test.head];
        std::array<double, DIM> realationArray = relations[test.relation];
        std::array<double, DIM> predictTailArray = addArray(headArray, realationArray);

        std::vector<PredictResult> predictResults;
        predictResults.reserve(entityN);
        for (int j = 0; j < entityN; ++j)
        {
            std::array<double, DIM> tailArray = entities[j];
            std::array<double, DIM> diffArray = subArray(tailArray, predictTailArray);
            double score = normArray(diffArray);
            if (filters.find({ test.head, j, test.relation }) == filters.end())
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
