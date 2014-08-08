#include "NeuralNet.h"

#include "utils/helper.h"
#include "SweeperConstants.h"

using namespace std;

Neuron::Neuron( int _nInputs )
{
	// Ϊƫ��ֵ����һ��Ȩ�أ�����������Ŀ+1;
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
	// �������л�ȡ����;
	m_nInputs = CONSTANTS.InputNumber;
	m_nOutputs = CONSTANTS.OutputNumber;
	m_nHiddenLayers = CONSTANTS.HiddenLayerNumber;
	m_nNeuronsPerHiddenLayer = CONSTANTS.NeuronNumberPerHiddenLayer;

	m_genome = nullptr;

	// ��������;
	this->createNet();
}

NeuralNet::~NeuralNet()
{

}

void NeuralNet::createNet()
{
	if (m_nHiddenLayers > 0)
	{
		// ���������;
		m_layers.push_back(NeuronLayer(m_nNeuronsPerHiddenLayer, m_nInputs));	

		// �������ز�;
		for (int i=0; i<m_nHiddenLayers; ++i)
		{
			m_layers.push_back(NeuronLayer(m_nNeuronsPerHiddenLayer, m_nNeuronsPerHiddenLayer));
		}

		// ���������;
		m_layers.push_back(NeuronLayer(m_nOutputs, m_nNeuronsPerHiddenLayer));	
	}
	//else
	//{
	//	m_layers.push_back(NeuronLayer(m_nOutputs, m_nInputs));	
	//}
}

NeuralNetOutputs NeuralNet::update( const NeuralNetInputs &inputs )
{
	// �������ĸ����Ƿ���ȷ;
	if (inputs.size() != m_nInputs)
	{
		assert(false);
		return NeuralNetOutputs();
	}

	NeuralNetInputs internalInputs = inputs;
	NeuralNetOutputs internalOutputs;

	// ������;
	for (int layerIndex=0; layerIndex<m_nHiddenLayers+2; ++layerIndex)
	{
		// ������㣬ǰһ��������Ϊ�Լ�������;
		if (layerIndex > 0)
		{
			internalInputs = internalOutputs;
			internalOutputs.clear();
		}

		// �����ܺ�;
		for (int i=0; i<m_layers[layerIndex].num; ++i)
		{
			auto &neuron = m_layers[layerIndex].neurons[i];

			Fixed total = 0.0;
			int weightIndex = 0;

			// ����ÿһ�� ���� �� Ȩ��;
			for (int inputIndex=0; inputIndex<neuron.nInputs-1; ++inputIndex)
			{
				total += neuron.weights[inputIndex] * internalInputs[weightIndex++];
			}

			// ����ƫ��ֵ;
			total += neuron.weights[neuron.nInputs-1] * (-1);

			// �ۼӵļ���ֵ��Ҫͨ��S�κ����Ĺ��ˣ��������;
			Fixed result = this->sigmoid(total, 1);
			internalOutputs.push_back(result);
		}
	}

	// �����������Ƿ���ȷ;
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
	// ÿһ��;
	for (int i=0; i<m_nHiddenLayers+2; ++i)
	{
		// ÿ��ϸ��;
		for (int j=0; j<m_layers[i].num; ++j)
		{
			int index = 0;

			// ÿ��������;
			for (int k=0; k<m_layers[i].neurons[j].nInputs-1; ++k)
			{
				m_layers[i].neurons[j].weights[k] = chromo.genes[index++];
			}
		}
	}

	m_genome = (Genome *)&chromo;
}
