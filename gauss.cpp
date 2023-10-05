// This function will solve system of linear equations
// A should be the augmented matrix of n rows and n+1 columns
// where n is the number of unknowns
// Returns a vector of n elements which is the answer
template<typename T>
vector<T> gauss(vector<vector<T>>& A) {
    int n = A.size();

    for (int j = 0; j < n - 1; ++j) {
        for (int i = j+1; i < n; ++i) {
            T t = A[i][j] / A[j][j];
            for (int k = 0; k <= n; ++k) {
                A[i][k] -= A[j][k] * t;
            }
        }
    }

    vector<T> ans(n, 0.0);

    for (int i = n - 1; i >= 0; --i) {
        T s = 0;
        for (int j = i+1; j < n; ++j) {
            s += A[i][j] * ans[j];
        }
        ans[i] = (A[i][n] - s) / A[i][i];
    }
    return ans;
}

