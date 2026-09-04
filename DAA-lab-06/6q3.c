#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

// Complex number structure and basic operators
typedef struct {
    double real;
    double imag;
} Complex;

Complex complex_add(Complex a, Complex b) {
    return (Complex){a.real + b.real, a.imag + b.imag};
}

Complex complex_sub(Complex a, Complex b) {
    return (Complex){a.real - b.real, a.imag - b.imag};
}

Complex complex_mul(Complex a, Complex b) {
    return (Complex){
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
}

// Bit-reversal helper function for in-place iterative FFT
unsigned int reverse_bits(unsigned int x, int log2n) {
    unsigned int n = 0;
    for (int i = 0; i < log2n; i++) {
        n = (n << 1) | (x & 1);
        x >>= 1;
    }
    return n;
}

// Coolely-Tukey Divide and Conquer FFT Algorithm - O(N log N)
// invert = 0 for Forward FFT, invert = 1 for Inverse FFT
void fft(Complex *a, int n, int invert) {
    int log2n = 0;
    while ((1 << log2n) < n) log2n++;

    // Bit-reversal permutation
    for (int i = 0; i < n; i++) {
        int rev = reverse_bits(i, log2n);
        if (i < rev) {
            Complex temp = a[i];
            a[i] = a[rev];
            a[rev] = temp;
        }
    }

    // Iterative Divide and Conquer (Butterfly computation)
    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (invert ? 1 : -1);
        Complex wlen = {cos(angle), sin(angle)};

        for (int i = 0; i < n; i += len) {
            Complex w = {1.0, 0.0};
            for (int j = 0; j < len / 2; j++) {
                Complex u = a[i + j];
                Complex v = complex_mul(a[i + j + len / 2], w);

                a[i + j] = complex_add(u, v);
                a[i + j + len / 2] = complex_sub(u, v);

                w = complex_mul(w, wlen);
            }
        }
    }

    // Scale values if inverse FFT
    if (invert) {
        for (int i = 0; i < n; i++) {
            a[i].real /= n;
            a[i].imag /= n;
        }
    }
}

// Convolution using FFT - O(N log N)
double* fast_convolution(const double *A, int m, const double *B, int n, int *out_size) {
    *out_size = m + n - 1;

    // Find smallest power of two >= m + n - 1
    int N = 1;
    while (N < *out_size) N <<= 1;

    // Allocate zero-padded complex array buffers
    Complex *ca = (Complex *)calloc(N, sizeof(Complex));
    Complex *cb = (Complex *)calloc(N, sizeof(Complex));

    for (int i = 0; i < m; i++) ca[i].real = A[i];
    for (int i = 0; i < n; i++) cb[i].real = B[i];

    // Step 1 & 2: Transform vectors to frequency domain
    fft(ca, N, 0);
    fft(cb, N, 0);

    // Step 3: Pointwise multiplication
    for (int i = 0; i < N; i++) {
        ca[i] = complex_mul(ca[i], cb[i]);
    }

    // Step 4: Inverse FFT to return to spatial domain
    fft(ca, N, 1);

    // Extract real output values
    double *result = (double *)malloc((*out_size) * sizeof(double));
    for (int i = 0; i < *out_size; i++) {
        result[i] = ca[i].real;
    }

    free(ca);
    free(cb);
    return result;
}

// Naive O(m * n) convolution for validation comparison
double* naive_convolution(const double *A, int m, const double *B, int n) {
    int out_size = m + n - 1;
    double *result = (double *)calloc(out_size, sizeof(double));

    for (int k = 0; k < out_size; k++) {
        for (int j = 0; j < m; j++) {
            if (k - j >= 0 && k - j < n) {
                result[k] += A[j] * B[k - j];
            }
        }
    }
    return result;
}

void print_vector(const char *name, const double *vec, int size) {
    printf("%s = [", name);
    for (int i = 0; i < size; i++) {
        printf("%.2f%s", vec[i], i == size - 1 ? "" : ", ");
    }
    printf("]\n");
}

int main() {
    int m = 4; // Length of A
    int n = 6; // Length of B (n >= m)

    double A[] = {1.0, 2.0, 3.0, 4.0};
    double B[] = {0.5, 1.0, 1.5, 2.0, 2.5, 3.0};

    printf("Input Vector A (m = %d):\n", m);
    print_vector("A", A, m);

    printf("\nInput Vector B (n = %d):\n", n);
    print_vector("B", B, n);

    // Fast FFT Convolution - O((n+m) log(n+m))
    int out_size;
    double *C_fft = fast_convolution(A, m, B, n, &out_size);

    // Naive Convolution - O(m * n)
    double *C_naive = naive_convolution(A, m, B, n);

    printf("\n--- Convolution Results (Output Size = %d) ---\n", out_size);
    print_vector("FFT Convolution  ", C_fft, out_size);
    print_vector("Naive Convolution", C_naive, out_size);

    free(C_fft);
    free(C_naive);
    return 0;
}
