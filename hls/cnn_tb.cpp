#include "cnn_top.h"

int main() {
	data_t din[128][128][3];

	data_t conv1_weight[3][3][3][16];
	data_t conv1_bias[16];

	data_t conv2_weight[3][3][16][32];
	data_t conv2_bias[32];

	data_t fc_weight[4][4][32][11];
	data_t fc_bias[11];

	data_t dout[11];
	cnn_top(din, dout,
			conv1_weight, conv1_bias,
			conv2_weight, conv2_bias,
			fc_weight, fc_bias);
	return 0;
}
