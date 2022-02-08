#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include "../include/debugopen.hpp"

/*
    Perceptron III

    [goal]

    (1) AND, OR, XOR '구분' 실험

    - 일단 이전 주차 과제는 Single layer였기 때문에 XOR 학습이 불가능했음.

    - 한 모델로 분류기를 만들 수가 있나? 가능할 거 같은데? cat or dog 같은 느낌 아닐까?

    - 아래 아이디어가 맞는 것 같은데 배운 적이 없다. ㅅㅂ?

    - AND, OR, XOR을 학습시킨 후, 얘내 중 가장 높은 가중치를 뱉으면 되는 것 아닌가?
    - 아, 이걸 3개의 output으로 두면 되는 거 같은데?
        - 근데 이걸 어떻게 해야 되는 거임..;;
        - 오류를 3번 고치면 되는 거 아닐까?

    (2) 도우넛 모양 구분 실험 (다음 데이터 이용)

    - Layer 수, Layer 당 node 수는 변수로 지정할 것

    - 한 층 계산이 하나의 함수가 되도록 구현 (LeCun delta 방식으로...)

    - weight는 행렬 형식으로 파일에 저장 ( ????? 꼭 이랬어야 했나 ? )

    - Learning 과정을 그래프로 보여주기 (X1, X2 2차원 직선 그래프).

    - 각 노드마다 직선을 그림으로 표시.

    - iteration에 따른 Error 그래프

    [impl. way]

    1. Learning 과정이 있어야 한다.
        - 현재 activation function = step function(theta=0) 이므로, f'=1로 정의한다.
        - deltaWk = c * (t - o) * xk (delta rule에 의한 결과)

*/

using namespace std;

#define LEARNING_RATE 0.009f

float sigmoid(float y)
{
    return (float)1 / (1 + exp(y * -1));
}

float sigmoidDerivate(float y)
{
    return (1 - sigmoid(y)) * sigmoid(y);
}

//float (*activateFunction)(float *w, float *x);
float sigmoidAsActivationFunction(float *w, float *x, int length)
{
    float sum = 0.0f;
    for (int i = 0; i < length; i++)
    {
        sum += w[i] * x[i];
    }
    return sigmoid(sum);
}

//float (*activateFunction)(float *w, float *x);
float stepFunction(float *w, float *x, int length)
{
    float sum = 0.0f;
    for (int i = 0; i < length; i++)
    {
        sum += w[i] * x[i];
    }
    return sum > 1.0f ? 1.0f : 0.0f;
}

/*

고민 끝에 이전 노드에서의 가중치를 현재(이전 노드 입장에선 출력 대상인) 노드가 갖기로 했다.

Why?

    1. Layer 단위로 계산을 할 때, deltaN-1를 계산할 때 deltaN과 weightsForInputValues가 모두 필요하기 때문에,
       둘을 Layer N에서 Layer N-1로 모두 전달하는 게 보기 좋고, 응집성 있기 때문이다.

    2. (위에서의 정의한) '현재' 노드가 weightsForInputValues를 갖고 있어도 문제가 없기 때문이다.

*/
class MultiLayeredNode
{
private:
    float *weights;
    int inputLength;
    int recentOutput; // 최소 한 번의 forward Propagation을 통해 output을 계산 후 저장해서 backward Propagation에서 활용할 수 있어야 한다.
    float (*activateFunction)(float *w, float *x, int inputLength) = stepFunction;
    float calcMyDelta(float *prevDelta);

public:
    MultiLayeredNode()
    {
    }
    MultiLayeredNode(float *weightsForInputValues, int inputLength);
    float activate(float *inputValues);
    float *calcArrayOfMyDeltaW();
};

MultiLayeredNode::MultiLayeredNode(float *weightsForInputValues, int inputLength)
{
    this->weights = weightsForInputValues;
    this->inputLength = inputLength;
}

float MultiLayeredNode::activate(float *inputValues)
{
    return this->activateFunction(this->weights, inputValues, this->inputLength);
}

float MultiLayeredNode::calcMyDelta()
{
    // dE/dnet = dE/dy * dy/dnet 이다.
    // dE/dnet =
    return sigmoidDerivate(this->recentOutput);
}

float *MultiLayeredNode::calcArrayOfMyDeltaW()
{

    float deltaW;
    this->calcMyDelta();
    // 이 개수만큼 deltaW가 계산돼야 한다.
    // deltaW = this->calcMyDelta() * inputValue[i] 인데, inputValue를 곱해주긴 참 그렇다;
    // 어차피 자신의 recentOutput는 자신이 갖고 있으니 delta만 받아가면 될 것으로 보이는데?
    for (int i = 0; i < this->inputLength; i++)
    {
        deltaW = 0;
    }
}

// 한 층 계산이 하나의 함수가 되도록 구현하는 것이 요구 사항.
// 해당 구현의 응집성을 높이기 위해 데이터까지 넣어 객체로 정의
class HiddenLayer
{
private:
    MultiLayeredNode *nodeList;
    int inputLength;

public:
    HiddenLayer()
    {
    }
    HiddenLayer(MultiLayeredNode *nodeList, int inputLength);
    float *forwardProp(float *inputValues);
    float *backwardProp(float *arrayOfDeltaWs);
};

HiddenLayer::HiddenLayer(MultiLayeredNode *nodeList, int inputLength)
{
    this->nodeList = nodeList;
    this->inputLength = inputLength;
}

/*

    => 이제 애매해졌다. 
       첫 입력 Layer 구성을 모든 weight=1로 초기화하고,
       inputValues는 1차원으로 준비한 후 노드 개수만큼 복제해야 할듯.
       그럼 첫 입력 Layer를 어떻게 구성해야 하는가?
       float *inputValues를 그대로 각 노드에 전달하면 끝이다! 어차피 가중치는 그 다음 레이어에 있으니깐.
       같은 원리로 마지막 Layer의 경우 노드가 하나이므로 특수하게 처리한다.
       이렇게 되면 우리가 말하는 'Layer'란 Hidden Layer가 된다!
    
    => 두 번째 레이어부터는?
       inputValues[]을 받고 노드마다 inputValues[]을 전달하고 outputValues[]을 취합한다. 
       이 outputValues[]이 다음 레이어의 inputValues[]가 된다.

    => 마지막 레이어는 어떻게 해야?
       train_set_y가 [10*1] 이므로 출력은 하나이다.
       따라서 AND, OR, XOR을 위한 DNN이 존재하면 된다.

    => 레이어 별 노드 개수는 2개면 충분한가?
       AND, OR, XOR은 그게 충분하다. 입력 레이어부터 Node=2이므로 그렇게 하도록 하자.

    => 학습은 어떻게 해야?
       1. Result를 Error Function에 넣어 Error를 구한다.
         - 항상 train_set_x = [4*2] 이므로 Error 값은 4개가 나온다.

       2. 해당 Error의 미분값에서 시작해서, BackProp을 수행한다. 이 때 delta를 사용한다.
       3. LeCun 방법을 써서 Layer 별로 계산을 독립시킨다. 우리의 경우 f'(net) = 1 로 정의할 것이므로 다른 건 없다.
       4. 각 Wk에 대해 delta Wk가 계산되면 W를 갱신한다.
       5. 다시 (1)로 돌아가 반복한다.

    => threshold도 학습 대상인가? 애매하긴 한데 일단 신경 쓰지 말자. 구현이 어느 정도 된 후에 신경 쓰도록 하자.

1. 입력 레이어에서 각 노드는 weights[]를 받아 초기화되고, input[]을 받아 output[]을 반환한다.
2. 입력 레이어는 (1)의 결과를 취합해 output[][]으로 만들어 다음 레이어로 전달한다.

*/
float *HiddenLayer::forwardProp(float *inputValues)
{
    // 2차원 배열에 대한 포인터
    // 1차원 배열을 가리키는 포인터에 대한 포인터
    float *outputValues = new float[this->inputLength];
    for (int i = 0; i < this->inputLength; i++)
    {
        outputValues[i] = this->nodeList[i].activate(inputValues);
    }
    return outputValues;
}

class DNN
{
private:
    float learningRate;
    HiddenLayer *layerList;
    int layerLength;
    MultiLayeredNode *outputNode;
    void updateFromError(int error);

public:
    DNN(int numberOfHiddenLayer, int numberOfNodesPerHiddenLayer);
    int predict(float *inputValues);                                              // AND, OR, XOR 구분은 정수로 결과를 반환해도 된다.
    void train(float **trainInputSet, int *trainOutputSet, int trainInputLength); // forward 구현 후 구현 ㄱㄱ
};

DNN::DNN(int numberOfHiddenLayer, int numberOfNodesPerHiddenLayer)
{
    float *initialWeights;

    // 각 Hidden Layer 초기화
    this->layerLength = numberOfHiddenLayer;
    this->layerList = new HiddenLayer[numberOfHiddenLayer];
    for (int i = 0; i < numberOfHiddenLayer; i++)
    {
        // 이렇게 스택 단위인 객체를 참조해도 되나?
        // 순회마다 새 Node 배열 생성
        MultiLayeredNode *nodeList = new MultiLayeredNode[numberOfNodesPerHiddenLayer];
        for (int j = 0; j < numberOfNodesPerHiddenLayer; j++)
        {
            initialWeights = new float[numberOfNodesPerHiddenLayer];
            for (int k = 0; k < numberOfNodesPerHiddenLayer; k++)
                initialWeights[k] = (float)rand() / RAND_MAX;
            nodeList[j] = MultiLayeredNode(initialWeights, numberOfNodesPerHiddenLayer);
        }
        this->layerList[i] = HiddenLayer(nodeList, numberOfNodesPerHiddenLayer);
    }

    // 마지막 출력 노드 초기화
    initialWeights = new float[numberOfNodesPerHiddenLayer];
    for (int k = 0; k < numberOfNodesPerHiddenLayer; k++)
        initialWeights[k] = (float)rand() / RAND_MAX;
    this->outputNode = new MultiLayeredNode(initialWeights, numberOfNodesPerHiddenLayer);
}

int DNN::predict(float *inputValues)
{
    float *outputValues = inputValues;
    for (int i = 1; i < this->layerLength; i++)
    {
        outputValues = this->layerList[i].forwardProp(outputValues);
    }
    return this->outputNode->activate(outputValues);
}

void DNN::train(float **trainInputSet, int *trainOutputSet, int trainInputLength)
{
    const int TARGET_ERROR_RATE = 0;
    float *trainInputValues;
    int output;
    int error;
    // for All training set, get error, and fix, if error exists
    for (int i = 0; i < trainInputLength; i++)
    {
        trainInputValues = trainInputSet[i];
        output = this->predict(trainInputValues);
        error = trainOutputSet[i] - output;
        if (error > TARGET_ERROR_RATE)
        {
            this->updateFromError(error);
        }
    }
}

/*
    주요 생산물:

        1. delta(n, k) = E|net

        2. delta_W(n, k) = E|(x or y)

        * Computational Graph와 다르게, 하나의 노드에 net과 x가 모두 존재한다.
          => 즉 한 노드에서 delta와 delta_W를 모두 구하게 된다.

        * W는 그냥 즉석에서 나만 활용하면 된다.

        * 마지막 노드의 경우도 net과 y가 존재한다.

            1. delta(last, 1) = -(t-y) * sigmoidDerivative(y);

            2. 이 경우 W는 없다. 뒷 노드에 가중치를 곱해서 전달하는 구조가 아니기 때문이다.

        * 애초에 delta를 이전 레이어에 제공할 일이 없다.
          => 이전 레이어에 제공되는 값은 E|w(n-1, k) 뿐이다. 애초에 delta는 E|w를 계산하기 위한 '내부적인' 도구이다.

        * 

*/
void DNN::updateFromError(int error)
{

    // 최초의 delta를 만들어, node 개수만큼 복제
    // MSE를 y에 대해 미분하면 -(t-y) = y-t이므로,
    float *arrayOfDeltaW = this->outputNode->calcArrayOfMyDeltaW(); // lastDelta를 이용해서

    // delta를 계속 앞으로 전달
    for (int i = layerLength - 1; i >= 0; i--)
    {
        arrayOfDeltaW = this->layerList[i].backwardProp(arrayOfDeltaW);
    }
    // TODO: print status of the updated model
}

int main()
{
    // 입력 변수
    int NUMBER_OF_HIDDEN_LAYER = 1;
    int NUMBER_OF_NODES_PER_HIDDEN_LAYER = 3;

    // PPT에서 제공된 데이터 (x, y) 9건
    // 도넛(?) 데이터셋인 듯하다.
    float train_set_x[][2] = {{0., 0.}, {0., 1.}, {1., 0.}, {1., 1.}, {0.5, 1.}, {1., 0.5}, {0., 0.5}, {0.5, 0.}, {0.5, 0.5}};
    float train_set_y[] = {0, 0, 0, 0, 0, 0, 0, 0, 1};

    srand(time(NULL));
    DNN *dnn_and = new DNN(NUMBER_OF_HIDDEN_LAYER, NUMBER_OF_NODES_PER_HIDDEN_LAYER);

    // float 계산에서 일치는 없는데 어떻게 일치했다는 판단을 할 수 있을까?
    // 일치가 중요한 게 아니고, mse를 기준으로 오차만 줄이면 된다.
    for (int i = 0; i < 9; i++)
        cout << (dnn_and->predict(train_set_x[i]) == train_set_y[i]) << endl;

    return 0;
}

// int Perceptron::calc(int xArr[], int tArr[], bool updateWeights)
// {
//     int i = 0, failCnt = 0;
//     int x[2];
//     int o;
//     int t;

//     // 4개의 (x1, x2)에 대해 오류를 검출한다.
//     for (; i < 4; i++)
//     {
//         t = tArr[i];
//         x[0] = xArr[i * 2];
//         x[1] = xArr[i * 2 + 1];
//         o = step_func(x);

//         if (t - o != 0)
//         {
//             if (updateWeights)
//                 update(x, o, t);
//             failCnt++;
//         }
//     }

//     return failCnt;
// }

// void Perceptron::update(int x[], int o, int t)
// {
//     int i;
//     for (i = 0; i < 2; i++)
//     {
//         // delta rule, f' = 1 (f = step function 이므로, f' 없음)
//         w[i] += C * (t - o) * x[i];
//     }
// }

// /*
//     weights: from -1 to 1
//     theta: from 0 to 1 (not 0)
// */
// Perceptron::Perceptron()
// {
//     w = new float[2];
//     prevW = new float[2];
//     w[0] = (rand() % 11) / 5.0f - 1;
//     w[1] = (rand() % 11) / 5.0f - 1;
//     theta = (rand() % 10 + 1) / 10.0f;
// }

// int Perceptron::step_func(int x[])
// {
//     float sum = w[0] * x[0] + w[1] * x[1] - theta;
//     return (sum > 0) ? 1 : 0;
// }

// void Perceptron::learn(int x[], int t[])
// {
//     int i, error, failCnt = 0;

//     printf("theta: %8f\n", theta);
//     print();
//     error = calc(x, t, false);
//     printf("failCnt: %d\n\n", error);

//     failCnt = 0;
//     while (true)
//     {
//         printf("try: [%d]\n", failCnt++);
//         for (int i = 0; i < 2; i++)
//             prevW[i] = w[i];
//         calc(x, t, true);
//         print();
//         error = calc(x, t, false);
//         printf("Error: %d\n", error);
//         if (error == 0)
//             break;
//     }
//     return;
// }

// void Perceptron::print()
// {
//     printf("w0: %f\n", w[0]);
//     printf("w1: %f\n", w[1]);
// }

// int main()
// {
//     srand(time(NULL));

//     int t_and[4] = {0, 0, 0, 1};
//     int t_or[4] = {0, 1, 1, 1};
//     int x[8] = {
//         0,
//         0,
//         0,
//         1,
//         1,
//         0,
//         1,
//         1,
//     };

//     // OR gate
//     Perceptron p_or;
//     printf("OR Gate:\n");
//     p_or.learn(x, t_or);

//     printf("\n-----Learn is Done!-----\n");

//     // AND gate
//     Perceptron p_and;
//     printf("AND Gate:\n");
//     p_and.learn(x, t_and);

//     printf("\n-----Learn is Done!-----\n");

//     return 0;
// }
