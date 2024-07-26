//Balance Online
#include <bits/stdc++.h>
using namespace std;

// Function to check if any bidder still has budget remaining
bool hasRemainingBudget(unordered_map<string, int> &budget) {
    for (auto &entry : budget) {
        if (entry.second > 0) {
            return true;
        }
    }
    return false;
}

int main() {
    vector<pair<string, string>> bidders; // Vector to store bidders and their queries
    unordered_map<string, int> budget; // Map to store bidders and their budgets

    // Input number of bidders
    cout << "Enter the number of bidders:" << endl;
    int numBidders;
    cin >> numBidders;
    
    // Input details for each bidder
    for (int i = 0; i < numBidders; i++) {
        string name;
        string queries;
        int budgetAmount;
        cout << "Enter Bidder name:" << endl;
        cin >> name; // Input bidder name
        cout << "Enter Bidder's queries:" << endl;
        cin >> queries; // Input queries the bidder is interested in
        cout << "Enter Bidder's budget:" << endl;
        cin >> budgetAmount; // Input budget of the bidder
        bidders.push_back({name, queries}); // Add bidder and their queries to the vector
        budget[name] = budgetAmount; // Add bidder and their budget to the map
    }
    
    // Sort bidders based on their names (optional if necessary)
    sort(bidders.begin(), bidders.end());

    // Map to store which bidders want which queries
    map<char, vector<string>> queryBidders;

    // Populate the queryBidders map
    for (const auto &bidder : bidders) {
        for (char query : bidder.second) {
            queryBidders[query].push_back(bidder.first);
        }
    }

    // String to store the allocated bidders for each query
    string allocatedQueries = "";
    
    // Input queries one character at a time
    cout << "Enter the query one character at a time, enter $ to exit:" << endl;
    char queryChar;
    bool budgetAvailable = hasRemainingBudget(budget); // Check if any budget is available
    
    while (true && budgetAvailable) {
        cin >> queryChar;
        if (queryChar == '$') {
            break;
        } else {
            bool isAllocated = false;

            // Check each bidder who is interested in the current query character
            int maxBid = -1;
            string selectedBidder;
            for (const auto &bidder : queryBidders[queryChar]) {
                if (budget[bidder] > 0 && budget[bidder] > maxBid) {
                    selectedBidder = bidder;
                    maxBid = budget[bidder];
                }
            }

            // If a valid bidder is found, allocate the query to that bidder
            if (maxBid != -1) {
                budget[selectedBidder]--; // Deduct one unit from the bidder's budget
                allocatedQueries += selectedBidder[0]; // Assign the query to this bidder
                isAllocated = true;
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