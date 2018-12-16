#include <vector>
#include<algorithm>
#include<string>
#include <iomanip>
#include<fstream>
#include<iostream>
#include "Netlist.h"

class Simulator {
private:
    double **G;
    double **B;
    double **C;
    double **D;
    double **Z;
    double **X;
    double **A;
    double **AInverse;
    int nVoltageSource;
    int nNodes;
    bool initialRun = true;
    std::vector<std::vector<double>> result;
public:
    Netlist netlist;

    Simulator(std::string netlistFile) {
        netlist.parseFile(netlistFile);
    }

    void initializeModelParameters() {
        nVoltageSource = netlist.getVoltageSourceCount();
        nNodes = netlist.getNodesCount();
        // Initialize matricies.
        Matrix::initilzeMatrix(A, nNodes + nVoltageSource, nNodes + nVoltageSource);
        Matrix::initilzeMatrix(AInverse, nNodes + nVoltageSource, nNodes + nVoltageSource);
        Matrix::initilzeMatrix(G, nNodes, nNodes);
        Matrix::initilzeMatrix(B, nNodes, nVoltageSource);
        Matrix::initilzeMatrix(C, nVoltageSource, nNodes);
        Matrix::initilzeMatrix(D, nVoltageSource, nVoltageSource);
        Matrix::initilzeMatrix(Z, nNodes + nVoltageSource, 1);
        Matrix::initilzeMatrix(X, nNodes + nVoltageSource, 1);

    }

    void updateModelState() {
        int voltageSourceCounter = 0;
        // Build matricies.
        for (Component component : netlist.components) {
            // Build G.
            if (component.type == RESISTANCE) {
                if (component.src > 0) {
                    G[component.src - 1][component.src - 1] += 1 / component.value;

                    if (component.dst > 0) {
                        G[component.src - 1][component.dst - 1] -= 1 / component.value;
                    }
                }
                if (component.dst > 0) {
                    G[component.dst - 1][component.dst - 1] += 1 / component.value;

                    if (component.src > 0) {
                        G[component.dst - 1][component.src - 1] -= 1 / component.value;
                    }
                }
            } else if (component.type == VOLTAGE_SOURCE) {

                if (!initialRun && component.needEvaluation) {
                    //std::cout << " from inductor: constant part : " <<component.constantPart<<" "<< std::endl;
                    component.value = X[nNodes + voltageSourceCounter][0] * component.constantPart;
                }

                // If it is voltage source only because it is generated from a inductor.
                if (component.generatedFromInductor) {
                    D[voltageSourceCounter][voltageSourceCounter] = component.constantPart;
                }

                if (component.src > 0) {
                    B[component.src - 1][voltageSourceCounter] = -1;
                    C[voltageSourceCounter][component.src - 1] = -1;
                }
                if (component.dst > 0) {
                    B[component.dst - 1][voltageSourceCounter] = 1;
                    C[voltageSourceCounter][component.dst - 1] = 1;
                }

                Z[nNodes + voltageSourceCounter][0] = component.value;
                voltageSourceCounter++;
            } else if (component.type == CURRENT_SOURCE) {
                if (!initialRun && component.needEvaluation) {
                    //std::cout << " comp src " << component.src << " comp dest " << component.dst << std::endl;
                    double vSrc = (component.src == 0) ? 0 : X[component.src - 1][0];
                    double vDst = (component.dst == 0) ? 0 : X[component.dst - 1][0];
                    component.value = (vDst - vSrc) * component.constantPart;
                }

                if (component.src > 0) {
                    Z[component.src - 1][0] -= component.value;
                }
                if (component.dst > 0) {
                    Z[component.dst - 1][0] += component.value;
                }
            }

        }

        // Add G.
        for (int r = 0; r < nNodes; r++) {
            for (int c = 0; c < nNodes; c++) {
                A[r][c] = G[r][c];
            }
        }

        // add B, C.
        for (int r = 0; r < nNodes; r++) {
            for (int c = nNodes; c < nNodes + nVoltageSource; c++) {
                A[r][c] = B[r][c - nNodes];
                A[c][r] = C[c - nNodes][r];
            }
        }

        // add D.
        for (int r = nNodes; r < nNodes + nVoltageSource; r++) {
            for (int c = nNodes; c < nNodes + nVoltageSource; c++) {
                A[r][c] = D[r - nNodes][c - nNodes];
            }
        }

        int f = 5;
        initialRun = false;
    }

    void simulate(int numIterations) {
        result.clear();
        if (!this->netlist.hasActiveComponents) {
            numIterations = 1;
        }
        int iterationsCounter = 1;
        while (numIterations--) {
            this->resetAll();
            this->updateModelState();
            Matrix::MatrixInversion(A, nNodes + nVoltageSource, AInverse);
            Matrix::MatrixMultiplication(AInverse, nNodes + nVoltageSource, Z, X);

            // Adding result.
            std::vector<double> res;
            for (int i = 0; i < nNodes + nVoltageSource; i++) {
                res.push_back(X[i][0]);
            }
            result.push_back(res);
            std::cout << " iteration: " << iterationsCounter++ << std::endl;
            printX();
        }
    }

    void logResult(std::string file) {

        std::ofstream outputFile;
        outputFile.open(file, std::ios::out | std::ios::binary);
        for (int i = 0; i < nNodes; i++) {
            double h = 0.1;
            outputFile << "V_" << (i + 1) << std::endl;
            for (auto x : result) {
                if (this->netlist.hasActiveComponents) {
                    outputFile << std::setprecision(3) << h << " ";
                    h += 0.1;
                }
                outputFile << std::setprecision(10) << x[i] << std::endl;
            }
            outputFile << std::endl;
        }
        outputFile << std::endl;

        for (int i = 0; i < nVoltageSource; i++) {
            double h = 0.1;
            outputFile << "I_" << (i + 1) << std::endl;
            for (auto x : result) {
                if (this->netlist.hasActiveComponents) {
                    outputFile << std::setprecision(3) << h << " ";
                    h += 0.1;
                }
                outputFile << std::setprecision(10) << x[nNodes + i] << std::endl;
            }
            outputFile << std::endl;
        }

        outputFile.close();
    }

    void resetAll() {
        for (int r = 0; r < nNodes; r++) {
            for (int c = 0; c < nNodes; c++) {
                G[r][c] = 0;
            }
        }

        for (int r = 0; r < nNodes; r++) {
            for (int c = 0; c < nVoltageSource; c++) {
                B[r][c] = 0;
            }
        }

        for (int r = 0; r < nVoltageSource; r++) {
            for (int c = 0; c < nNodes; c++) {
                C[r][c] = 0;
            }
        }

        for (int r = 0; r < nVoltageSource; r++) {
            for (int c = 0; c < nVoltageSource; c++) {
                D[r][c] = 0;
            }
        }

        for (int r = 0; r < nNodes + nVoltageSource; r++) {
            Z[r][0] = 0;
        }

        for (int r = 0; r < nNodes + nVoltageSource; r++) {
            for (int c = 0; c < nNodes + nVoltageSource; c++) {
                A[r][c] = 0;
            }
        }

        for (int r = 0; r < nNodes + nVoltageSource; r++) {
            for (int c = 0; c < nNodes + nVoltageSource; c++) {
                AInverse[r][c] = 0;
            }
        }

    }

    void printMatricies() {
        std::cout << "G = \n[ \n ";
        for (int r = 0; r < nNodes; r++) {
            for (int c = 0; c < nNodes; c++) {
                std::cout << G[r][c] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "]" << std::endl << std::endl;
        std::cout << "B = \n[\n";
        for (int r = 0; r < nNodes; r++) {
            for (int c = 0; c < nVoltageSource; c++) {
                std::cout << B[r][c] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "]" << std::endl << std::endl;

        std::cout << "C = \n[\n";
        for (int r = 0; r < nVoltageSource; r++) {
            for (int c = 0; c < nNodes; c++) {
                std::cout << C[r][c] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "]" << std::endl << std::endl;

        std::cout << "Z = \n[\n";
        for (int r = 0; r < nNodes + nVoltageSource; r++) {
            std::cout << Z[r][0] << " ";
            std::cout << std::endl;
        }
        std::cout << "]" << std::endl << std::endl;

        std::cout << "A = \n[\n";
        for (int r = 0; r < nNodes + nVoltageSource; r++) {
            for (int c = 0; c < nNodes + nVoltageSource; c++) {
                std::cout << A[r][c] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "]" << std::endl << std::endl;


        std::cout << "AInverse = \n[\n";
        for (int r = 0; r < nNodes + nVoltageSource; r++) {
            for (int c = 0; c < nNodes + nVoltageSource; c++) {
                std::cout << AInverse[r][c] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "]" << std::endl << std::endl;

        std::cout << "X = \n[\n";
        for (int r = 0; r < nNodes + nVoltageSource; r++) {
            std::cout << X[r][0] << " ";
            std::cout << std::endl;
        }
        std::cout << "]" << std::endl << std::endl;

    }

    void printX() {
        std::cout << "X = \n[\n";
        for (int r = 0; r < nNodes + nVoltageSource; r++) {
            std::cout << X[r][0] << " ";
            std::cout << std::endl;
        }
        std::cout << "]" << std::endl << std::endl;
    }


};
