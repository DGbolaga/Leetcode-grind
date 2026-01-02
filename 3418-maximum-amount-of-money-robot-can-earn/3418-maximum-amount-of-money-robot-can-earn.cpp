class Solution {
public:
    int fR(vector<vector<int>>& coins, int i, int j, int k) {
        // recursive.
        // base case.
        if (i < 0 || j < 0) return -1e8;
        if (i == 0 && j == 0) {
            if (coins[i][j] < 0 && k > 0) return 0;
            return coins[i][j];
        }
        
        //explore paths.
        // for each cell (up or left) there are 2 options - neutralize or
        // not.
        int u = coins[i][j] + fR(coins, i-1, j, k);
        int un = -1e8;
        if (coins[i][j] < 0 && k > 0) un = fR(coins, i-1, j, k-1); // neutralize

        int l = coins[i][j] + fR(coins, i, j-1, k);
        int ln = -1e8;
        if (coins[i][j] < 0 && k > 0) ln = fR(coins, i, j-1, k-1); // neutralize

        return max(max(u, un), max(l, ln));
    }

    int fM(vector<vector<int>>& coins, int i, int j, int k, 
            vector<vector<vector<int>>>& dp) {
        // recursive.
        // base case.
        if (i < 0 || j < 0) return -1e8;
        if (i == 0 && j == 0) {
            if (coins[i][j] < 0 && k > 0) return 0;
            return coins[i][j];
        }
        if (dp[i][j][k] != -1) return dp[i][j][k]; //dp check

        //explore paths.
        // for each cell (up or left) there are 2 options - neutralize or
        // not.
        int u = coins[i][j] + fM(coins, i-1, j, k, dp);
        int un = -1e8;
        if (coins[i][j] < 0 && k > 0) un = fM(coins, i-1, j, k-1, dp); // neutralize

        int l = coins[i][j] + fM(coins, i, j-1, k, dp);
        int ln = -1e8;
        if (coins[i][j] < 0 && k > 0) ln = fM(coins, i, j-1, k-1, dp); // neutralize

        return dp[i][j][k] = max(max(u, un), max(l, ln));
    }

    int fT(vector<vector<int>>& coins) {
        //Tabulation - our memoization solution gave tle.
        // In this case, we'll be going from top-left to bottom right in
        // filling the table.
        int m = coins.size();
        int n = coins[0].size();
        int K = 3;
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(K, -1)));

        //base cases.
        // initial starting point. 
        for (int k = 0; k < K; k++){
            if (coins[0][0] < 0 && k > 0) dp[0][0][k] = 0;
            else dp[0][0][k] = coins[0][0];
        }

        // first row. 
        for (int j = 1; j < n; j++)  {
            for (int k = 0; k < K; k++) {
                int t = coins[0][j] + dp[0][j-1][k]; //take
                int nt = -1e8; // neutralize.
                if (coins[0][j] < 0 && k > 0) {
                    nt = dp[0][j-1][k-1]; // use the result of previous
                }
                dp[0][j][k] = max(t, nt);
            }
        }

        // first column,
        for (int i = 1; i < m; i++) {
            for (int k = 0; k < K; k++) {
                int t = coins[i][0] + dp[i-1][0][k]; //same logic
                int nt = -1e8;
                if (coins[i][0] < 0 && k > 0) {
                    nt = dp[i-1][0][k-1]; // use prev.
                }
                dp[i][0][k] = max(t, nt);
            }
        }

        // fill table starting from second row & second column.
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                for (int k = 0; k < K; k++) {
                    int u = coins[i][j] + dp[i-1][j][k];
                    int un = -1e8;
                    if (coins[i][j] < 0 && k > 0) un = dp[i-1][j][k-1]; // neutralize

                    int l = coins[i][j] + dp[i][j-1][k];
                    int ln = -1e8;
                    if (coins[i][j] < 0 && k > 0) ln = dp[i][j-1][k-1]; // neutralize          
                    dp[i][j][k] = max(max(u, un), max(l, ln));
                }
            }
        }

        return dp[m-1][n-1][K-1];
    }


    int maximumAmount(vector<vector<int>>& coins) {

        // it's a dp on grid problem.
        // I'll walk through the:
        // -recursive
        // -memoization

        // Steps:
        // - explain everything in terms of index (i, j, k)
        // - explore all paths/ do stuffs.
        // - take global optimum - in this case (max_profit)

        int m = coins.size();
        int n = coins[0].size();
        int k = 3; //dp size for tabulation

        // For memoization; 3D array
        //vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k, -1)));

        //return fM(coins, m-1, n-1, k-1, dp); // k=2 options only

        return fT(coins);
    }
};