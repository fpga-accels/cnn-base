#include "cnn_top.h"
void conv_1(data_t din[128][128][3], data_t dout[32][32][16],
		data_t weight[3][3][3][16], data_t bias[16]) {
	data_t kernel[3][3][3];
	data_t dtemp[128][128][16];
	int nexi = -1;
	int nexj = 0;
	conv_1_label2: for (int ii = -1; ii < 127; ++ii) {
		nexi++;
		nexj = 0;
		conv_1_label3: for (int jj = -1; jj < 127; ++jj) {
			conv_1_label0: for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					if (ii + i < 0 or ii + i >= 128 or jj + j < 0
							or jj + j >= 128) {
						for (int c = 0; c < 3; ++c) {
							kernel[i][j][c] = 0;
						}
					} else {
						for (int c = 0; c < 3; ++c) {
							kernel[i][j][c] = din[ii + i][jj + j][c];
						}
					}
				}
			}
			conv_1_label1: for (int cho = 0; cho < 16; ++cho) {
				dtemp[nexi][nexj][cho] = bias[cho];
				for (int i = 0; i < 3; ++i) {
					for (int j = 0; j < 3; ++j) {
						for (int chi = 0; chi < 3; ++chi) {
							dtemp[nexi][nexj][cho] += kernel[i][j][chi]
									* weight[i][j][chi][cho];
						}
					}
				}
				if (dtemp[nexi][nexj][cho] < 0) {
					dtemp[nexi][nexj][cho] = 0;
				}
			}
		}
	}
	for (int ii = 0; ii < 128; ii += 4) {
		for (int jj = 0; jj < 128; jj += 4) {
			for (int cho = 0; cho < 16; ++cho) {
				dout[ii / 4][jj / 4][cho] = 0;
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 4; ++j) {
						if (dtemp[ii + i][jj + j][cho]
								> dout[ii / 4][jj / 4][cho]) {
							dout[ii / 4][jj / 4][cho] =
									dtemp[ii + i][jj + j][cho];
						}

					}
				}
			}
		}
	}

}
void conv_2(data_t din[32][32][16], data_t dout[4][4][32],
		data_t weight[3][3][16][32], data_t bias[32]) {
	data_t kernel[3][3][16];
	data_t dtemp[32][32][32];
	int nexi = -1;
	int nexj = 0;
	conv_2_label1: for (int ii = -1; ii < 31; ++ii) {
		nexi++;
		nexj = 0;
		conv_2_label2: for (int jj = -1; jj < 31; ++jj) {
			conv_2_label3: for (int i = 0; i < 3; ++i) {
				conv_2_label4: for (int j = 0; j < 3; ++j) {
					if (ii + i < 0 or ii + i >= 32 or jj + j < 0
							or jj + j >= 32) {
						conv_2_label5: for (int chi = 0; chi < 16; ++chi) {
							kernel[i][j][chi] = 0;
						}
					} else {
						for (int chi = 0; chi < 16; ++chi) {
							kernel[i][j][chi] = din[i][j][chi];
						}
					}
				}
			}

			conv_2_label6: for (int cho = 0; cho < 32; ++cho) {
				dtemp[nexi][nexj][cho] = bias[cho];
				conv_2_label7: for (int i = 0; i < 3; ++i) {
					conv_2_label8: for (int j = 0; j < 3; ++j) {
						conv_2_label9: for (int chi = 0; chi < 16; ++chi) {
							dtemp[nexi][nexj][cho] += kernel[i][j][chi]
									* weight[i][j][chi][cho];
						}
					}
				}
				if (dtemp[nexi][nexj][cho] < 0) {
					dtemp[nexi][nexj][cho] = 0;
				}
			}
		}
	}

	conv_2_label0: for (int ii = 0; ii < 32; ii += 8) {
		for (int jj = 0; jj < 32; jj += 8) {
			for (int cho = 0; cho < 32; ++cho) {
				dout[ii / 8][jj / 8][cho] = 0;
				for (int i = 0; i < 8; ++i) {
					for (int j = 0; j < 8; ++j) {
						if (dtemp[ii + i][jj + j][cho]
								> dout[ii / 8][jj / 8][cho]) {
							dout[ii / 8][jj / 8][cho] =
									dtemp[ii + i][jj + j][cho];
						}

					}
				}
			}
		}
	}
}

void fc_layer(data_t din[4][4][32], data_t dout[11],
		data_t weight[4][4][32][11], data_t bias[11]) {
	fc_layer_label0: for (int cho = 0; cho < 11; ++cho) {
		dout[cho] = bias[cho];
		fc_layer_label1: for (int i = 0; i < 4; ++i) {
			fc_layer_label2: for (int j = 0; j < 4; ++j) {
				fc_layer_label3: for (int chi = 0; chi < 32; ++chi) {
					dout[cho] += din[i][j][chi] * weight[i][j][chi][cho];
				}
			}
		}
	}
}

void cnn_top(data_t din[128][128][3], data_t dout[11],
		data_t conv1_weight[3][3][3][16], data_t conv1_bias[16],
		data_t conv2_weight[3][3][16][32], data_t conv2_bias[32],
		data_t fc_weight[4][4][32][11], data_t fc_bias[11]) {
	data_t conv1_temp[32][32][16];
	data_t conv2_temp[4][4][32];
	conv_1(din, conv1_temp, conv1_weight, conv1_bias);
	conv_2(conv1_temp, conv2_temp, conv2_weight, conv2_bias);
	fc_layer(conv2_temp, dout, fc_weight, fc_bias);
}
