// Tool: Boundary Layer Inflation Calculator
// Method: Bisection Method for Geometric Growth Ratio

#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// --- Constants ---
const double TOLERANCE = 1e-6;
const int MAX_ITERATIONS = 1000;

// --- Physics Functions ---

// Calculates the residual of the geometric series equation.
// We want to find G such that this function equals 0.
// Formula: TotalHeight = first_cell_height * ( (1 - G^N) / (1 - G) )
double calculate_residual(double G, double first_cell_height, double N_layers, double total_BL_height) {
    if (abs(G - 1.0) < 1e-9) return -1.0; // Avoid division by zero

    double calculated_height = first_cell_height * ((1 - pow(G, N_layers)) / (1 - G));
    return calculated_height - total_BL_height;
}

// Solves for the Growth Ratio (G) using the Bisection Method
double solve_growth_ratio(double first_cell_height, double N_layers, double total_BL_height) {
    double lower = 1.0001; // Growth ratio must be > 1
    double upper = 2.0;    // Initial guess for upper bound

    // Step 1: Expand the bracket until the root is contained
    // We need f(lower) and f(upper) to have opposite signs
    while (calculate_residual(lower, first_cell_height, N_layers, total_BL_height) * calculate_residual(upper, first_cell_height, N_layers, total_BL_height) > 0) {
        upper += 0.5;
        if (upper > 100.0) { // Safety break
            cout << "Error: Could not bracket the root. Check inputs." << endl;
            return -1;
        }
    }

    // Step 2: Bisection Loop
    double mid = 0;
    int iter = 0;

    while ((upper - lower) >= TOLERANCE && iter < MAX_ITERATIONS) {
        mid = (lower + upper) / 2.0;

        double f_lower = calculate_residual(lower, first_cell_height, N_layers, total_BL_height);
        double f_mid = calculate_residual(mid, first_cell_height, N_layers, total_BL_height);

        if (f_mid == 0.0) break; // Exact match found

        if (f_lower * f_mid < 0) {
            upper = mid; // Root is in the lower half
        }
        else {
            lower = mid; // Root is in the upper half
        }
        iter++;
    }

    cout << "Converged in " << iter << " iterations." << endl;
    return mid;
}

int main() {
    double first_cell_height;
    double N_layers;
    double total_BL_height;
    char user_choice;

    do {
        cout << "\n--- Inflation Layer Calculator ---\n";
        cout << "Enter estimated number of layers (N): ";
        cin >> N_layers;
        cout << "Enter first layer height (yH): ";
        cin >> first_cell_height;
        cout << "Enter max boundary-layer height (Total Height): ";
        cin >> total_BL_height;

        double growth_ratio = solve_growth_ratio(first_cell_height, N_layers, total_BL_height);

        cout << "------------------------------------------\n";
        cout << "Calculated Growth Ratio: " << growth_ratio << endl;
        cout << "------------------------------------------\n";

        cout << "Does this result meet your requirements? (y/n): ";
        cin >> user_choice;

        if (user_choice == 'n' || user_choice == 'N') {
            cout << "Let's recalculate. Please re-enter parameters below." << endl;
            // The loop will simply restart, allowing entry of new, cleaner data
        }

    } while (user_choice == 'n' || user_choice == 'N');

    cout << "Design accepted. Good luck with the mesh!" << endl;
    return 0;
}
