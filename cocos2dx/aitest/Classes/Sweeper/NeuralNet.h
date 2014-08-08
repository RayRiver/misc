#ifndef NeuralNet_h__
#define NeuralNet_h__

#include "utils/Fixed.h"

#include <vector>

typedef std::vector<Fixed> NeuralNetInputs;
typedef std::vector<Fixed> NeuralNetOutputs;

#include "GeneticAlgorithm.h"

// ��ϸ��;
struct Neuron
{
	int nInputs;						// �������;
	std::vector<Fixed> weights;			// Ȩ���б�;
	Neuron(int _nInputs);
};

// ��ϸ����;
struct NeuronLayer
{
	int num;							// �������ϸ����;
	std::vector<Neuron> neurons;		// ��ϸ���б�;
	NeuronLayer(int _num, int _nInputsPerLayer);
};

// ������;
class NeuralNet
{
public:
	NeuralNet();
	~NeuralNet();

	// ��������;
	void createNet();

	// ���û���;
	void setGenome(const Genome &chromo);
	Genome &getGenome() { return *m_genome; }

	// ���·���;
	NeuralNetOutputs update(const NeuralNetInputs &inputs);

private:
	// S�κ���;
	Fixed sigmoid(Fixed input, Fixed response);

private:
	int m_nInputs;						// ������;
	int m_nOutputs;						// �����;
	int m_nHiddenLayers;				// ���ز���;
	int m_nNeuronsPerHiddenLayer;		// ÿ�����ز��ϸ����;

	std::vector<NeuronLayer> m_layers;	// ������;

	Genome *m_genome;

};

#endif // NeuralNet_h__
