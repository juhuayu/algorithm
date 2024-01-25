class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int col = grid[0].size();
        int row = grid.size();
        vector<vector<int>> temp(row, vector<int>(col, 0));
        temp[0][0] = grid[0][0];
        for(int i=1; i<col; i++) {
            temp[0][i] = temp[0][i-1] + grid[0][i];
        }
        for(int i=1; i<row; i++) {
            temp[i][0] = temp[i-1][0] + grid[i][0];
        }
        for(int i=1; i<row; ++i) {
            for(int j=1; j<col; ++j) {
                temp[i][j] = (temp[i-1][j] > temp[i][j-1]? temp[i][j-1]: temp[i-1][j]) + grid[i][j];
            }
        }
        cout << temp[row-1][col-1] << endl;
        return temp[row-1][col-1];
    }
};