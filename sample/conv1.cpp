#include <bits/stdc++.h>

/**
 * T: 数据类型名称
 * K: 卷积核大小
 * ICH: 输入通道数
 * OCH: 输出通道数
 * ISZ: 输入尺寸
 * OSZ: 输出尺寸
 * PADDING: 卷积时添加的边缘
 * STRIDE: 卷积的步幅
 * */
template<typename T, int K, int ICH, int OCH, int ISZ, int OSZ, int PADDING, int STRIDE>
void conv2d(T din[ISZ][ISZ][ICH], T dout[OSZ][OSZ][OCH], T weight[K][K][ICH][OCH], T bias[OCH]) {
    T kernel[K][K][ICH];
    int nexi = -1;
    int nexj = 0;
    for(int ii = -PADDING; ii < ISZ+PADDING; ii+=STRIDE) {
        // 判断kernel是否出界
        if(ii + K > ISZ + PADDING) break;
        nexi++;
        nexj = 0;
        for(int jj = -PADDING; jj < ISZ+PADDING; jj+=STRIDE) {
            //判断kernel是否出界
            if(jj + K > ISZ + PADDING) break;
            for(int i = 0; i < K; ++i) {
                for(int j = 0; j < K; ++j) {
                    // 判断kernel中的元素是否在输入图片范围之内
                    if(ii + i < 0 or ii + i >= ISZ or jj + j < 0 or jj + j >= ISZ) {
                        for(int c = 0; c < ICH; ++c) {
                            kernel[i][j][c] = 0;
                        }
                    } else {
                        for(int c = 0; c < ICH; ++c) {
                            kernel[i][j][c] = din[ii + i][jj + j][c];
                        }
                        //memcpy(kernel[i][j], din[ii+i][jj+j], sizeof(T)*ICH); 
                        //如果把通道放到末尾的话，可以直接整个通道拷贝
                    }
                }
            }
            for(int cho = 0; cho < OCH; ++cho) {
                dout[nexi][nexj][cho] = bias[cho];
                for(int i = 0; i < K; ++i) {
                    for(int j = 0; j < K; ++j) {
                        for(int chi = 0; chi < ICH; ++chi) {
                            dout[nexi][nexj][cho] += kernel[i][j][chi] * weight[i][j][chi][cho];
                        }
                    }
                }
            }
            ++nexj;
        }
    }
}


typedef float data_t;
data_t din[128][128][3];
data_t dout[128][128][16];
data_t weight[3][3][3][16];
data_t bias[16];
int main() {
    conv2d<data_t, 3, 3, 16, 128, 128, 1, 1>(din, dout, weight, bias);
    return 0;
}