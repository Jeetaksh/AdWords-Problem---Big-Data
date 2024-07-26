//Generalised Balance Offline
#include <bits/stdc++.h>
using namespace std;

// Function to calculate the Psi value based on bid and remaining budget fraction
double calculatePsi(double bid, double remainingFraction) {
    return bid * (1 - exp(-remainingFraction));
}

// Function to check if any bidder still has budget remaining
bool hasRemainingBudget(unordered_map<string, double> &budget) {
    for (auto &entry : budget) {
        if (entry.second > 0) {
            return true;
        }
    }
    return false;
}

int main() {
    vector<pair<string, unordered_map<char, double>>> bidders; // Vector to store bidders and their bids per query
    unordered_map<string, double> budget, originalBudget; // Maps to store bidders' budgets and original budgets

    // Define the number of bidders
    int numBidders = 2;
    
    // Define bidders, their budgets, and their bids
    vector<tuple<string, double, unordered_map<char, double>>> bidderData = {
        {"A", 110.0, {{'p', 10.0}}},
        {"B", 100.0, {{'p', 1.0}}},
    };
    
    // Populate bidders and their bids from the defined data
    for (const auto& entry : bidderData) {
        string bidderName;
        double bidderBudget;
        unordered_map<char, double> bids;
        tie(bidderName, bidderBudget, bids) = entry;
        
        budget[bidderName] = bidderBudget;
        originalBudget[bidderName] = bidderBudget;
        bidders.push_back({bidderName, bids});
    }

    // Map to store which bidders want which queries
    map<char, vector<string>> queryBidders;
    for (const auto &bidder : bidders) {
        for (const auto &bid : bidder.second) {
            queryBidders[bid.first].push_back(bidder.first);
        }
    }

    // String to store the queries and allocated bidders
    string queries = "pppppppppppppp";
    string allocatedBidders = "";
    bool budgetAvailable = hasRemainingBudget(budget); // Check if any budget is available

    // Process each query character
    for (char queryChar : queries) {
        if (!budgetAvailable) break;

        bool isAllocated = false;
        double maxPsi = -1.0;
        string bestBidder;

        // Check each bidder who is interested in the current query character
        for (const auto &bidder : queryBidders[queryChar]) {
            double remainingFraction = budget[bidder] / originalBudget[bidder];
            double bidAmount = bidders[find_if(bidders.begin(), bidders.end(),
                                                [&](const pair<string, unordered_map<char, double>> &p) { return p.first == bidder; })
                                      - bidders.begin()]
                                .second[queryChar];
            double psi = calculatePsi(bidAmount, remainingFraction);

            if (budget[bidder] >= bidAmount && psi > maxPsi) {
                bestBidder = bidder;
                maxPsi = psi;
            }
        }

        // If a valid bidder is found, allocate the query to that bidder
        if (maxPsi != -1.0) {
            budget[bestBidder] -= bidders[find_if(bidders.begin(), bidders.end(),
                                                  [&](const pair<string, unordered_map<char, double>> &p) { return p.first == bestBidder; })
                                        - bidders.begin()].second[queryChar];
            
            allocatedBidders += bestBidder; // Assign the query to this bidder
            cout << "Best Bidder: " << bestBidder << " with remaining budget " << budget[bestBidder] << endl;
            isAllocated = true;
        }

        // If no bidder could be allocated (budget exhausted), mark the query with '_'
        if (!isAllocated) {
            allocatedBidders += '_';
        }

        cout << "Allocated so far: " << allocatedBidders << endl;
        budgetAvailable = hasRemainingBudget(budget); // Check if any budget is still available
    }

    // Check if all budgets are exhausted
    if (!budgetAvailable) {
        cout << "All budgets exhausted." << endl;
    }

    return 0;
}