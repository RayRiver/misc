#ifndef PathMap_h__
#define PathMap_h__

#include <vector>

class PathMap
{
public:
	enum class GridType
	{
		None = 0,
		Barrier = 1,
		Start = 2,
		End = 3,
	};

	PathMap();
	PathMap(const PathMap &other);
	~PathMap();

	void copy(const PathMap &other);
	void operator =(const PathMap &other);

	void init(int *m, int w, int h);
	void clear();

	PathMap testRoute(const std::vector<int> &path, double &fitness);
	void resetMemory();
	void setMemory(int x, int y, int flag);

	inline int getMap(int x, int y) const { return m_map[y*m_w+x]; }
	inline int getMemory(int x, int y) const { return m_memory[y*m_w+x]; }

	inline int getMapW() const { return m_w; }
	inline int getMapH() const { return m_h; }

private:
	int *m_map;
	int m_w, m_h;
	int m_startX, m_startY;
	int m_endX, m_endY;

	int *m_memory;

};

#endif // PathMap_h__
