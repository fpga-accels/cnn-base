#ifndef _CNN_TOP_H_
#define _CNN_TOP_H_
#include <hls_stream.h>
#include <string.h>
#include "ap_fixed.h"
#define HEIGHT 128
#define WIDTH 128
#define CH_IN 3
#define KSIZE 3
#define CH_OUT 16

typedef float data_t;

void conv_1(data_t din[128][128][3], data_t dout[32][32][16],
		data_t weight[3][3][3][16], data_t bias[16]);

void conv_2(data_t din[32][32][16], data_t dout[4][4][32],
		data_t weight[3][3][16][32], data_t bias[32]);

void fc_layer(data_t din[4][4][32], data_t dout[11],
		data_t weight[4][4][32][11], data_t bias[11]);

void cnn_top(data_t din[128][128][3], data_t dout[11],
		data_t conv1_weight[3][3][3][16], data_t conv1_bias[16],
		data_t conv2_weight[3][3][16][32], data_t conv2_bias[32],
		data_t fc_weight[4][4][32][11], data_t fc_bias[11]);
#endif	// _CNN_TOP_H_
