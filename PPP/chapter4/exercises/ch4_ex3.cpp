// Route statistics program using a series of distances as a vector
#include <iostream>

int main()
{
    std::vector<double>distances;
    for(double route; std::cin >> route; ){             // Feed route distance into a placeholder
        distances.push_back(route);                     // Push placeholder into vector
    }

    // Compute the total distance (the sum) of the routes entered
    double sum_routes = 0;
    for (int i = 0; i < distances.size(); ++i){
        sum_routes += distances[i];
    }
    std::cout << "The total distance of all the routes combined is: " << sum_routes << ".\n";

    // Sort the vector to find the smallest and greatest distances
    std::sort(distances.begin(),distances.end());
    std::cout   << "The smallest distance is: " << distances[0] 
                << " and the greatest distance is: " << distances[distances.size()-1] << ".\n";
    
    // Compute the mean (average) of the routes
    std::cout << "The mean average of the routes is: " << sum_routes/distances.size() << ".\n";

    return 0;
}
