//Greefy Offline with user input
#include <bits/stdc++.h>
using namespace std;

int main() {
    string queries;
    cout << "Enter the query string" << endl;
    cin >> queries; // Input the string of queries
    
    vector<pair<string, string>> Bidders; // Vector to store bidders and their queries
    unordered_map<string, int> Budget; // Map to store bidders and their budgets
    
    cout << "Enter the number of bidders:-" << endl;
    int n;
    cin >> n; // Input the number of bidders
    
    for(int i = 0; i < n; i++) {
        string str;
        string que;
        int t; 
        cout << "Enter Bidder name" << endl;
        cin >> str; // Input bidder name
        cout << "Enter Bidder's queries" << endl;
        cin >> que; // Input queries the bidder is interested in
        cout << "Enter Bidder's budget" << endl;
        cin >> t; // Input budget of the bidder
        Bidders.push_back({str, que}); // Add bidder and their queries to the vector
        Budget[str] = t; // Add bidder and their budget to the map
    }
    
    // Sort bidders based on their names (optional if necessary)
    sort(Bidders.begin(), Bidders.end());

    // Map to store which bidders want which queries
    map<char, vector<string>> querybidders;

    for (const auto &bidder : Bidders) {
        for (char c : bidder.second) {
            querybidders[c].push_back(bidder.first); // Associate queries with bidders
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
            if (Budget[bidder] > 0) { // Check if bidder has remaining budget
                Budget[bidder]--; // Deduct one unit from the bidder's budget
                allocated[i] = bidder[0]; // Assign the query to this bidder
                allocatedFlag = true;
                break; // Stop after assigning to one valid bidder
            }
        }

        // If no bidder could be allocated (budget exhausted), keep the original character
        if (!allocatedFlag) {
            allocated[i] = ''; // Indicate unallocated query with ''
        }
    } 

    cout << allocated << endl; // Output the final allocation of queries

    return 0;
}