#ifndef SweeperObject_h__
#define SweeperObject_h__

#include <vector>

#include "utils/Fixed.h"
#include "NeuralNet.h"

class SweeperView;
class SweeperObject
{
public:
	static SweeperObject *create(SweeperView *view);
	SweeperObject();
	~SweeperObject();

	inline SweeperView *getView() { return m_view; }

	bool update(const FixedVec2 &closestPos);

	bool checkCollision(const FixedVec2& mine);

	inline const FixedVec2 &getFixedPosition() const { return m_fixedPosition; }
	void setFixedPosition(const FixedPoint &p);

	inline const FixedSize &getFixedSize() const { return m_size; }
	void setFixedSize(const FixedSize &size);

	inline const Fixed &getFixedRotation() const { return m_rotation; }
	void setFixedRotation(const Fixed &rotation);

	void resetFitness();
	void increaseFitness();

	// 设置基因;
	void setGenome(const Genome &chromo) { m_brain.setGenome(chromo); }


private:
	bool init(SweeperView *view);

private:
	SweeperView *m_view;

	NeuralNet m_brain;						// 神经网络;
	Fixed m_speed;							// 速度;

	FixedSize m_size;

	FixedVec2 m_fixedPosition;
	FixedVec2 m_lookat;
	Fixed m_rotation;
	
	Fixed m_lTrack, m_rTrack;
};

#endif // SweeperObject_h__
