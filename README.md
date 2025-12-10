# 🚀 Boundary Layer Inflation Calculator

![Language](https://img.shields.io/badge/language-C++-blue.svg) ![Method](https://img.shields.io/badge/method-Bisection-green.svg) ![Context](https://img.shields.io/badge/context-CFD-orange.svg)

A C++ numerical tool designed to calculate the precise **geometric growth ratio** required for CFD boundary layer meshing. This tool ensures the total inflation layer thickness matches the target aerodynamic boundary layer height ($\delta$) while maintaining a specific first-cell height ($y_H$) for $y^+$ requirements.

## 🧮 Theoretical Background

In Computational Fluid Dynamics (CFD), capturing the boundary layer requires a series of prism layers growing geometrically from the wall.

* **$y_H$**: First cell height (determined by desired $y^+$ value, e.g., $y^+ \approx 1$ for SST $k-\omega$).
* **$N$**: Number of prism layers.
* **$\delta$ ($b_{lh}$)**: Total height of the boundary layer mesh.
* **$G$**: The geometric growth ratio (unknown).

The relationship is defined by the sum of a geometric series:

$$\delta = y_H \frac{1 - G^N}{1 - G}$$

Since this equation cannot be solved algebraically for $G$, this tool implements the **Bisection Method** (a numerical root-finding algorithm) to solve for $G$ with high precision.

## 📥 Inputs

1.  **Number of Layers ($N$):** Integer count of inflation layers.
2.  **First Cell Height ($y_H$):** Height of the wall-adjacent cell (meters).
3.  **Total Boundary Layer Height ($b_{lh}$):** The target total thickness of the inflation stack (meters).

## 📤 Output

* **Growth Ratio ($G$):** The constant expansion ratio between consecutive layers.
* **Convergence Info:** Number of iterations required to reach the solution.

## 🛠️ Build & Run

### Prerequisites

* G++ Compiler (or any standard C++ compiler)

### Usage

```bash
# Compile the program
g++ main.cpp -o InflationCalculator

# Run the executable
./InflationCalculator
```

## ✍️ Author

**Kıvanç Apaydın** – Aerospace Engineer 
