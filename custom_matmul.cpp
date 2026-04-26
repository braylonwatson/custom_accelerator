#define N_MAX 32
#define TILE_SIZE 16

extern "C" {

void custom_matmul_kernel(
    const int *A,
    const int *B,
    int *C,
    int N
) {
#pragma HLS INTERFACE m_axi port=A offset=slave bundle=gmem0
#pragma HLS INTERFACE m_axi port=B offset=slave bundle=gmem1
#pragma HLS INTERFACE m_axi port=C offset=slave bundle=gmem2

#pragma HLS INTERFACE s_axilite port=A bundle=control
#pragma HLS INTERFACE s_axilite port=B bundle=control
#pragma HLS INTERFACE s_axilite port=C bundle=control
#pragma HLS INTERFACE s_axilite port=N bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    int A_tile[TILE_SIZE][TILE_SIZE];
    int B_tile[TILE_SIZE][TILE_SIZE];
    int C_tile[TILE_SIZE][TILE_SIZE];

#pragma HLS ARRAY_PARTITION variable=A_tile complete dim=2
#pragma HLS ARRAY_PARTITION variable=B_tile complete dim=1
#pragma HLS ARRAY_PARTITION variable=C_tile complete dim=2

    for (int i_t = 0; i_t < N; i_t += TILE_SIZE) {
        for (int j_t = 0; j_t < N; j_t += TILE_SIZE) {

            for (int i = 0; i < TILE_SIZE; i++) {
                for (int j = 0; j < TILE_SIZE; j++) {
#pragma HLS PIPELINE II=1
                    C_tile[i][j] = 0;
                }
            }

            for (int k_t = 0; k_t < N; k_t += TILE_SIZE) {

                for (int i = 0; i < TILE_SIZE; i++) {
                    for (int k = 0; k < TILE_SIZE; k++) {
#pragma HLS PIPELINE II=1
                        int row = i_t + i;
                        int col = k_t + k;
                        if (row < N && col < N)
                            A_tile[i][k] = A[row * N + col];
                        else
                            A_tile[i][k] = 0;
                    }
                }

                for (int k = 0; k < TILE_SIZE; k++) {
                    for (int j = 0; j < TILE_SIZE; j++) {
#pragma HLS PIPELINE II=1
                        int row = k_t + k;
                        int col = j_t + j;
                        if (row < N && col < N)
                            B_tile[k][j] = B[row * N + col];
                        else
                            B_tile[k][j] = 0;
                    }
                }

                for (int i = 0; i < TILE_SIZE; i++) {
                    for (int k = 0; k < TILE_SIZE; k++) {
#pragma HLS PIPELINE II=1
                        int a_val = A_tile[i][k];

                        for (int j = 0; j < TILE_SIZE; j++) {
#pragma HLS UNROLL
                            C_tile[i][j] += a_val * B_tile[k][j];
                        }
                    }
                }
            }

            for (int i = 0; i < TILE_SIZE; i++) {
                for (int j = 0; j < TILE_SIZE; j++) {
#pragma HLS PIPELINE II=1
                    int row = i_t + i;
                    int col = j_t + j;
                    if (row < N && col < N)
                        C[row * N + col] = C_tile[i][j];
                }
            }
        }
    }
}

}