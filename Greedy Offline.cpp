// Greedy Offline
#include <bits/stdc++.h>
using namespace std;

int main() {
    string queries = "xxxxyyyy";
    vector<pair<string, string>> Bidders;
    unordered_map<string, int> Budget;

    // Input bidders and their budgets
    Bidders.push_back({"A", "xy"});
    Bidders.push_back({"B", "x"});
    Budget["A"] = 4;
    Budget["B"] = 4;

    // Sort bidders based on their names (optional if necessary)
    sort(Bidders.begin(), Bidders.end());

    // Map to store which bidders want which queries
    map<char, vector<string>> querybidders;

    for (const auto &bidder : Bidders) {
        for (char c : bidder.second) {
            querybidders[c].push_back(bidder.first);
        }
    }

    // String to store the allocated bidders
    string allocated = queries;

    // Iterate over each character in the queries
    for (int i = 0; i < queries.size(); i++) {
        char query = queries[i];
        bool allocatedFlag = false;

        // Check each bidder who is interested in the current query character
        for (const auto &bidder : querybidders[query]) {
            if (Budget[bidder] > 0) {
                Budget[bidder]--;
                allocated[i] = bidder[0]; // Assign the query to this bidder
                allocatedFlag = true;
                break; // Stop after assigning to one valid bidder
            }
        }

        // If no bidder could be allocated (budget exhausted), keep the original character
        if (!allocatedFlag) {
            allocated[i] = '_';
        }
    }

    cout << allocated << endl;

    return 0;
}