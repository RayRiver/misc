#include "NeuralNet.h"

#include "utils/helper.h"
#include "SweeperConstants.h"

using namespace std;

Neuron::Neuron( int _nInputs )
{
	// 为偏移值附加一个权重，所以输入数目+1;
	nInputs = _nInputs + 1;

	for (int i=0; i<nInputs; ++i)
	{
		weights.push_back(helper::randClamped());
	}
}

NeuronLayer::NeuronLayer( int _num, int _nInputsPerLayer )
{
	num = _num;
	for (int i=0; i<num; ++i)
	{
		neurons.push_back(Neuron(_nInputsPerLayer));
	}
}

NeuralNet::NeuralNet()
{
	// 从配置中获取参数;
	m_nInputs = CONSTANTS.InputNumber;
	m_nOutputs = CONSTANTS.OutputNumber;
	m_nHiddenLayers = CONSTANTS.HiddenLayerNumber;
	m_nNeuronsPerHiddenLayer = CONSTANTS.NeuronNumberPerHiddenLayer;

	m_genome = nullptr;

	// 创建网络;
	this->createNet();
}

NeuralNet::~NeuralNet()
{

}

void NeuralNet::createNet()
{
	if (m_nHiddenLayers > 0)
	{
		// 创建输入层;
		m_layers.push_back(NeuronLayer(m_nNeuronsPerHiddenLayer, m_nInputs));	

		// 创建隐藏层;
		for (int i=0; i<m_nHiddenLayers; ++i)
		{
			m_layers.push_back(NeuronLayer(m_nNeuronsPerHiddenLayer, m_nNeuronsPerHiddenLayer));
		}

		// 创建输出层;
		m_layers.push_back(NeuronLayer(m_nOutputs, m_nNeuronsPerHiddenLayer));	
	}
	//else
	//{
	//	m_layers.push_back(NeuronLayer(m_nOutputs, m_nInputs));	
	//}
}

NeuralNetOutputs NeuralNet::update( const NeuralNetInputs &inputs )
{
	// 检查输入的个数是否正确;
	if (inputs.size() != m_nInputs)
	{
		assert(false);
		return NeuralNetOutputs();
	}

	NeuralNetInputs internalInputs = inputs;
	NeuralNetOutputs internalOutputs;

	// 遍历层;
	for (int layerIndex=0; layerIndex<m_nHiddenLayers+2; ++layerIndex)
	{
		// 非输入层，前一层的输出作为自己的输入;
		if (layerIndex > 0)
		{
			internalInputs = internalOutputs;
			internalOutputs.clear();
		}

		// 计算总和;
		for (int i=0; i<m_layers[layerIndex].num; ++i)
		{
			auto &neuron = m_layers[layerIndex].neurons[i];

			Fixed total = 0.0;
			int weightIndex = 0;

			// 计算每一个 输入 × 权重;
			for (int inputIndex=0; inputIndex<neuron.nInputs-1; ++inputIndex)
			{
				total += neuron.weights[inputIndex] * internalInputs[weightIndex++];
			}

			// 加入偏移值;
			total += neuron.weights[neuron.nInputs-1] * (-1);

			// 累加的激励值需要通过S形函数的过滤，才能输出;
			Fixed result = this->sigmoid(total, 1);
			internalOutputs.push_back(result);
		}
	}

	// 检查输出个数是否正确;
	if (internalOutputs.size() != m_nOutputs)
	{
		assert(false);
	}

	return internalOutputs;
}

Fixed NeuralNet::sigmoid( Fixed input, Fixed response )
{
	return ( 1 / ( 1 + FixedExp(-input / response) ) );
}

void NeuralNet::setGenome( const Genome &chromo )
{
	// 每一层;
	for (int i=0; i<m_nHiddenLayers+2; ++i)
	{
		// 每个细胞;
		for (int j=0; j<m_layers[i].num; ++j)
		{
			int index = 0;

			// 每个基因组;
			for (int k=0; k<m_layers[i].neurons[j].nInputs-1; ++k)
			{
				m_layers[i].neurons[j].weights[k] = chromo.genes[index++];
			}
		}
	}

	m_genome = (Genome *)&chromo;
}
