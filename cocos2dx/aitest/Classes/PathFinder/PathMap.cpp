#include "PathMap.h"

PathMap::PathMap()
	: m_map(nullptr)
	, m_memory(nullptr)
	, m_w(0)
	, m_h(0)
{

}

PathMap::PathMap( const PathMap &other )
{
	this->copy(other);
}

void PathMap::copy( const PathMap &other )
{
	m_w = other.m_w;
	m_h = other.m_h;
	m_startX = other.m_startX;
	m_startY = other.m_startY;
	m_endX = other.m_endX;
	m_endY = other.m_endY;

	m_map = new int[m_w*m_h];
	memcpy((char *)m_map, (char *)other.m_map, sizeof(int)*m_w*m_h);
	m_memory = new int[m_w*m_h];
	memcpy((char *)m_memory, (char *)other.m_memory, sizeof(int)*m_w*m_h);
}

void PathMap::operator=( const PathMap &other )
{
	this->copy(other);
}

PathMap::~PathMap()
{
	clear();
}

void PathMap::init( int *m, int w, int h )
{
	clear();

	m_w = w;
	m_h = h;
	m_map = new int[m_w*m_h];
	memcpy((char *)m_map, (char *)m, sizeof(int)*m_w*m_h);
	m_memory = new int[m_w*m_h];
	memset((char *)m_memory, 0, sizeof(int)*m_w*m_h);

	for (int row=0; row<m_h; ++row)
	{
		for (int col=0; col<m_w; ++col)
		{
			switch (m_map[row*m_w+col])
			{
			case GridType::Start:
				m_startX = col;
				m_startY = row;
				break;
			case GridType::End:
				m_endX = col;
				m_endY = row;
				break;
			default:
				break;
			}
		}
	}

}

void PathMap::clear()
{
	if (m_map)
	{
		delete[] m_map;
		m_map = nullptr;
	}
	if (m_memory)
	{
		delete[] m_memory;
		m_memory = nullptr;
	}
}

PathMap PathMap::testRoute( const std::vector<int> &path, double &fitness )
{
	PathMap foundPathMap;
	foundPathMap.init(m_map, m_w, m_h);

	int posX = m_startX;
	int posY = m_startY;

	for (int i=0; i<path.size(); ++i)
	{
		int dir = path[i];
		switch (dir)
		{
		case 0: // 北;
			{
				if (posY-1<0 || m_map[(posY-1)*m_w+posX] == (int)GridType::Barrier)
				{
					// 边界或障碍;
					break;
				}
				else
				{
					posY -= 1;
				}
				break;
			}
		case 1: // 南;
			{
				if (posY+1>=m_h || m_map[(posY+1)*m_w+posX] == (int)GridType::Barrier)
				{
					// 边界或障碍;
					break;
				}
				else
				{
					posY += 1;
				}
				break;
			}
		case 2: // 东;
			{
				if (posX+1>=m_w || m_map[posY*m_w+posX+1] == (int)GridType::Barrier)
				{
					// 边界或障碍;
					break;
				}
				else
				{
					posX += 1;
				}
				break;	
			}
		case 3: // 西;
			{
				if (posX-1<0 || m_map[posY*m_w+posX-1] == (int)GridType::Barrier)
				{
					// 边界或障碍;
					break;
				}
				else
				{
					posX -= 1;
				}
				break;	
			}
		default:
			break;
		}

		// 记录路径;
		foundPathMap.setMemory(posX, posY, 1);
	}

	int diffX = abs(posX - m_endX);
	int diffY = abs(posY - m_endY);

	// 当达到目标地点时，适应值为1.0;
	fitness = 1/(double)(diffX+diffY+1);

	return foundPathMap;
}

void PathMap::resetMemory()
{
	memset((char *)m_memory, 0, sizeof(int)*m_w*m_h);
}

void PathMap::setMemory( int x, int y, int flag )
{
	m_memory[y*m_w + x] = flag;
}


