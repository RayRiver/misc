#ifndef NeuralNet_h__
#define NeuralNet_h__

#include "utils/Fixed.h"

#include <vector>

typedef std::vector<Fixed> NeuralNetInputs;
typedef std::vector<Fixed> NeuralNetOutputs;

#include "GeneticAlgorithm.h"

// 神经细胞;
struct Neuron
{
	int nInputs;						// 输入个数;
	std::vector<Fixed> weights;			// 权重列表;
	Neuron(int _nInputs);
};

// 神经细胞层;
struct NeuronLayer
{
	int num;							// 本层的神经细胞数;
	std::vector<Neuron> neurons;		// 神经细胞列表;
	NeuronLayer(int _num, int _nInputsPerLayer);
};

// 神经网络;
class NeuralNet
{
public:
	NeuralNet();
	~NeuralNet();

	// 创建网络;
	void createNet();

	// 设置基因;
	void setGenome(const Genome &chromo);
	Genome &getGenome() { return *m_genome; }

	// 更新方法;
	NeuralNetOutputs update(const NeuralNetInputs &inputs);

private:
	// S形函数;
	Fixed sigmoid(Fixed input, Fixed response);

private:
	int m_nInputs;						// 输入数;
	int m_nOutputs;						// 输出数;
	int m_nHiddenLayers;				// 隐藏层数;
	int m_nNeuronsPerHiddenLayer;		// 每个隐藏层的细胞数;

	std::vector<NeuronLayer> m_layers;	// 层容器;

	Genome *m_genome;

};

#endif // NeuralNet_h__
