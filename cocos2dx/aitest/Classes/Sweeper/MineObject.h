#ifndef MineObject_h__
#define MineObject_h__

#include "utils/Fixed.h"

class MineView;
class MineObject
{
public:
	MineObject();
	~MineObject();

	static MineObject *create(MineView *view);

	inline MineView *getView() { return m_view; }

	inline const FixedVec2 &getFixedPosition() const { return m_fixedPosition; }
	void setFixedPosition(const FixedVec2 &p);

private:
	bool init(MineView *view);

private:
	MineView *m_view;

	FixedVec2 m_fixedPosition;

};

#endif // MineObject_h__
