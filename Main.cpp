#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

MatrixXd spectralEmbedding(MatrixXd adjacencyMatrix, int numDimensions) {
    // Step 1: Compute the graph Laplacian matrix
    MatrixXd degreeMatrix = adjacencyMatrix.rowwise().sum().asDiagonal();
    MatrixXd laplacianMatrix = degreeMatrix - adjacencyMatrix;

    // Step 2: Compute the eigenvectors corresponding to the smallest eigenvalues
    SelfAdjointEigenSolver<MatrixXd> eigenSolver(laplacianMatrix);
    MatrixXd eigenvectors = eigenSolver.eigenvectors().real();

    // Step 3: Select the desired number of eigenvectors
    MatrixXd embeddingMatrix = eigenvectors.block(0, 0, eigenvectors.rows(), numDimensions);

    // Step 4: Normalize the embedding matrix
    embeddingMatrix = embeddingMatrix.rowwise().normalized();

    return embeddingMatrix;
}

int main() {
    // Example adjacency matrix
    MatrixXd adjacencyMatrix(4, 4);
    adjacencyMatrix << 0, 1, 1, 0,
                       1, 0, 1, 0,
                       1, 1, 0, 1,
                       0, 0, 1, 0;

    int numDimensions = 2; // Number of dimensions for the embedding

    // Perform spectral embedding
    MatrixXd embeddingMatrix = spectralEmbedding(adjacencyMatrix, numDimensions);

    // Print the embedding matrix
    std::cout << "Embedding Matrix:\n" << embeddingMatrix << std::endl;

    return 0;
}
