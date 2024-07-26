//Generalised Balance Online
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

    // Input number of bidders
    cout << "Enter the number of bidders:" << endl;
    int numBidders;
    cin >> numBidders;
    
    // Input details for each bidder
    for (int i = 0; i < numBidders; i++) {
        string bidderName;
        double bidderBudget;
        cout << "Enter Bidder name: ";
        cin >> bidderName; // Input bidder name
        cout << "Enter Bidder's budget: ";
        cin >> bidderBudget; // Input bidder's budget
        budget[bidderName] = bidderBudget;
        originalBudget[bidderName] = bidderBudget;

        unordered_map<char, double> bids; // Map to store bids for each query
        cout << "Enter Bidder's queries and respective bids (enter $ to finish):" << endl;
        while (true) {
            char query;
            double bidAmount;
            cin >> query;
            if (query == '$') break; // End input if '$' is entered
            cin >> bidAmount;
            bids[query] = bidAmount; // Store bid amount for the query
        }
        bidders.push_back({bidderName, bids}); // Add bidder and their bids to the vector
    }

    // Map to store which bidders want which queries
    map<char, vector<string>> queryBidders;
    for (const auto &bidder : bidders) {
        for (const auto &bid : bidder.second) {
            queryBidders[bid.first].push_back(bidder.first); // Populate queryBidders map
        }
    }

    // String to store the allocated bidders for each query
    cout << "Enter the query one character at a time, Enter $ to exit" << endl;
    char queryChar;
    string allocatedQueries = "";
    bool budgetAvailable = hasRemainingBudget(budget); // Check if any budget is available

    // Process each query entered by the user
    while (budgetAvailable) {
        cin >> queryChar;
        if (queryChar == '$') {
            break; // End input if '$' is entered
        } else {
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

                // Check if this bidder has the highest Psi value and can afford the bid
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

                // Check if budget is still non-negative
                if (budget[bestBidder] >= 0) {
                    allocatedQueries += bestBidder; // Assign the query to this bidder
                    cout << "Best Bidder: " << bestBidder << " with remaining budget " << budget[bestBidder] << endl;
                    isAllocated = true;
                } else {
                    budget[bestBidder] = 0;
                }
            }

            // If no bidder could be allocated (budget exhausted), mark the query with '_'
            if (!isAllocated) {
                allocatedQueries += '_';
            }
        }
        cout << allocatedQueries << endl; // Output the current allocation of queries

        budgetAvailable = hasRemainingBudget(budget); // Check if any budget is still available
        if (!budgetAvailable) {
            cout << endl << "All budgets exhausted." << endl;
            break;
        }
    }

    return 0;
}