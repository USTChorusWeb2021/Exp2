#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream localTestFile("./div10.txt");

    int n = 0;
    localTestFile >> n;

    int hit1 = 0;
    int hit5 = 0;

    for (int i = 0; i < n; ++i)
    {
        int trash = 0;

        int ans = 0;
        localTestFile >> trash >> ans >> trash;

        std::cin >> trash >> trash >> trash;
        for (int j = 0; j < 5; ++j)
        {
            int tail = 0;
            double score = 0.0;
            std::cin >> tail >> score;

            if (tail == ans)
            {
                ++hit5;
                if (j == 0) ++hit1;
                std::cout << "Hit " << i << ' ' << j << '\n';
            }
        }
    }

    std::cout << "Hit5: " << double(hit5) / n << '\n';
    std::cout << "Hit: " << double(hit1) / n << '\n';
    
    return 0;
}
