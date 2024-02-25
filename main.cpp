#include <iostream>
#include <cstring>
#include <climits>
#define CITY_NUM 10

using namespace std;

int main()
{
    string cities[CITY_NUM] = {"IZMIR", "MUGLA", "DENIZLI", "KASTAMONU", "KAYSERI", "SIVAS", "HATAY", "BINGOL", "MARDIN", "VAN"};

    int mesafeler[CITY_NUM][CITY_NUM] =
    {
        0,      226,        234,        832,        851,        1034,       1102,       1425,       1449,       1750,
        226,    0,          151,        852,        833,        1029,       1051,       1406,       1398,       1732,
        234,    151,        0,          725,        706,        902,        958,        1280,       1304,       1605,
        832,    852,        725,        0,          452,        475,        882,        892,        1054,       1217,
        851,    833,        706,        452,        0,          202,        428,        569,        656,        895,
        1034,   1029,       902,        475,        202,        0,          499,        480,        586,        806,
        1102,   1051,       958,        882,        428,        499,        0,          610,        521,        879,
        1425,   1406,       1280,       892,        569,        480,        610,        0,          236,        327,
        1449,   1398,       1304,       1054,       656,        586,        521,        236,        0,          440,
        1750,   1732,       1605,       1217,       895,        806,        879,        327,        440,        0
    };
    
    // distance matrixes. First row has 1 intermediate city,
    //second row has 2, third row has 3, and fourth row has 4.
    int shortestDistances[4][CITY_NUM] = {0};
    int longestDistances[4][CITY_NUM] = {0};
    
    // route matrices. Has the intermediate cities names.
    string shortRoutes[4][CITY_NUM] = {""};
    string longRoutes[4][CITY_NUM] = {""};

    // for the first line of the matrix (With 1 intermediate city)
    for (int x = 1; x < CITY_NUM; x++) // x is an index to represent the destination city (From İzmir to X)
    {
        int min_distance = INT_MAX; // temporary min_distance. INT_MAX because it needs to be bigger than the distance value for the first one.
        int max_distance = INT_MIN; // temporary max_distance. INT_MIN because it needs to be smaller than the distance value for the first one.
        string route = "";
        string best_route, worst_route;
        for (int k = 1; k < CITY_NUM - 1; k++) // k is an index to represent the intermediate cities
        {
            if (k != x) // k cannot be equal to the destination (X)
            {
                int short_distance = mesafeler[0][k] + mesafeler[k][x]; // distance = (izmir to K) + (K to X)
                int long_distance = mesafeler[0][k] + mesafeler[k][x];

                if (short_distance < min_distance) // if the distance is smaller than the previous min distance
                {
                    min_distance = short_distance; // update the min distance
                    route = cities[k]; // update the route           
                    shortestDistances[0][x] = min_distance; // update the shortest distance in matrix
                    shortRoutes[0][x] = route; // update the route in matrix
                }
                if (long_distance > max_distance) // if the distance is bigger than the previous max distance
                {
                    max_distance = long_distance; // update the min distance
                    route = cities[k]; // update the route 
                    longestDistances[0][x] = max_distance; // update the shortest distance in matrix
                    longRoutes[0][x] = route; // update the route in matrix
                    
                }
            }
        }
    }

    // for the 2nd-3rd-4th lines of the matrix (With 2-3-4 intermediate city)
    for (int i = 1; i < 4; i++) // i is an index to represent the number of intermediate city. Also the index of the row number for distance matrices
    {
        for (int x = 1; x < CITY_NUM; x++) // x is an index to represent the destination city (From İzmir to X)
        {
            int min_distance = INT_MAX; // temporary min_distance. INT_MAX because it needs to be bigger than the distance value for the first one.
            int max_distance = INT_MIN; // temporary max_distance. INT_MIN because it needs to be smaller than the distance value for the first one.
            string route = "";
            string best_route, worst_route;
            for (int k = 1; k < CITY_NUM - 1; k++) // k is an index to represent the intermediate cities
            {
                if (k != x && shortRoutes[i - 1][k] != "") // Exclude destination and already visited cities
                {
                    int short_distance = shortestDistances[i - 1][k] + mesafeler[k][x]; // distance = (Shortest way from İzmir to k (with i intermediate city) + (K to X)
                    int long_distance = longestDistances[i - 1][k] + mesafeler[k][x]; // same with longest version

                    if (short_distance < min_distance) // if the distance is smaller than the previous min distance
                    {
                        min_distance = short_distance; // update the min distance
                        route = shortRoutes[i - 1][k] + " - " + cities[k]; // update the route
                        shortestDistances[i][x] = min_distance; // update the shortest distance in matrix
                        shortRoutes[i][x] = route; // update the route in matrix
                    }
                    if (long_distance > max_distance) // if the distance is bigger than the previous max distance
                    {
                        max_distance = long_distance; // update the max distance
                        route = longRoutes[i - 1][k] + " - " + cities[k]; // update the route
                        longestDistances[i][x] = max_distance; // update the longest distance in matrix
                        longRoutes[i][x] = route; // update the route in matrix
                    }
                }
            }
        }
    }
    int how_Many_Intermediate_City = 1; // write here how many intermediate city you want?
    
    // calculations for the incomes
    int bestCaseIncome = (843 * how_Many_Intermediate_City) - shortestDistances[how_Many_Intermediate_City - 1][9];
    int worstCaseIncome = (843 * how_Many_Intermediate_City) - longestDistances[how_Many_Intermediate_City - 1][9];

    cout << "\nShortest way by passing through " << how_Many_Intermediate_City << " cities is " << shortestDistances[how_Many_Intermediate_City - 1][9] << "km\twith the best income of: " << bestCaseIncome << "TL\nRoute: IZMIR - " << shortRoutes[how_Many_Intermediate_City - 1][9] << " - VAN" << endl << endl;
    cout << "\nLongest way by passing through " << how_Many_Intermediate_City << " cities is " << longestDistances[how_Many_Intermediate_City - 1][9] << "km\twith the worst income of: " << worstCaseIncome << "TL\nRoute: IZMIR - " << longRoutes[how_Many_Intermediate_City - 1][9] << " - VAN" << endl << endl;


    return 0;
}