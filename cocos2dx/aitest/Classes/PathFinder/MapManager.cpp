#include "MapManager.h"

#include <string>

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "PathGenome.h"
#include "GenomeManager.h"
#include "PathMap.h"
#include "utils/helper.h"

USING_NS_CC;
using namespace std;
using namespace cocostudio;

MapManager *MapManager::s_instance = nullptr;

MapManager * MapManager::instance()
{
	if (!s_instance)
	{
		s_instance = new MapManager;
		s_instance->init();
	}
	return s_instance;
}

void MapManager::destroy()
{
	if (s_instance)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

MapManager::MapManager()
	: m_genomeManager(nullptr)
	, m_generationInterval(0.016)
	, m_crossoverRate(0)
	, m_mutateRate(0)
	, m_populationNumber(1)
	, m_geneNumber(1)
{

}

MapManager::~MapManager()
{
	this->clear();
}

bool MapManager::init()
{
	if (!BaseScene::init())
	{
		return false;
	}

	// 加载ui布局;
	m_ui = GUIReader::getInstance()->widgetFromJsonFile("ui/ui_pathfinder.json");
	this->addChild(m_ui);

	// 注册时代间隔滚动条事件;
	auto label_generation_interval = dynamic_cast<ui::Text *>(m_ui->getChildByName("label_generation_interval"));
	auto slider_generation_interval = dynamic_cast<ui::Slider *>(m_ui->getChildByName("slider_generation_interval"));
	slider_generation_interval->addEventListener([=](Ref *sender, ui::Slider::EventType type) {
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)	
		{
			int percent = slider_generation_interval->getPercent();	
			float val = (2-0.016)*percent/100+0.016;

			m_generationInterval = val;

			char s[32];
			sprintf(s, "%.03f", val);
			label_generation_interval->setString(s);
		}
	});
	label_generation_interval->setString("0.016");

	// 注册杂交率滚动条事件;
	auto label_crossover_rate = dynamic_cast<ui::Text *>(m_ui->getChildByName("label_crossover_rate"));
	auto slider_crossover_rate = dynamic_cast<ui::Slider *>(m_ui->getChildByName("slider_crossover_rate"));
	slider_crossover_rate->addEventListener([=](Ref *sender, ui::Slider::EventType type) {
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)	
		{
			int percent = slider_crossover_rate->getPercent();	
			int val = (100-0)*percent/100+0;

			m_crossoverRate = val/100.0f;

			char s[32];
			sprintf(s, "%d", val);
			label_crossover_rate->setString(s);
		}
	});

	// 注册变异率滚动条事件;
	auto label_mutate_rate = dynamic_cast<ui::Text *>(m_ui->getChildByName("label_mutate_rate"));
	auto slider_mutate_rate = dynamic_cast<ui::Slider *>(m_ui->getChildByName("slider_mutate_rate"));
	slider_mutate_rate->addEventListener([=](Ref *sender, ui::Slider::EventType type) {
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)	
		{
			int percent = slider_mutate_rate->getPercent();	
			int val = (100-0)*percent/100+0;

			m_mutateRate = val/100.0f;

			char s[32];
			sprintf(s, "%d", val);
			label_mutate_rate->setString(s);
		}
	});

	// 注册种群数量滚动条事件;
	auto label_population_number = dynamic_cast<ui::Text *>(m_ui->getChildByName("label_population_number"));
	auto slider_population_number = dynamic_cast<ui::Slider *>(m_ui->getChildByName("slider_population_number"));
	slider_population_number->addEventListener([=](Ref *sender, ui::Slider::EventType type) {
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)	
		{
			int percent = slider_population_number->getPercent();	
			int val = (100-1)*percent/100+1;

			m_populationNumber = val;

			char s[32];
			sprintf(s, "%d", val);
			label_population_number->setString(s);
		}
	});
	label_population_number->setString("1");

	// 注册基因组数量滚动条事件;
	auto label_gene_number = dynamic_cast<ui::Text *>(m_ui->getChildByName("label_gene_number"));
	auto slider_gene_number = dynamic_cast<ui::Slider *>(m_ui->getChildByName("slider_gene_number"));
	slider_gene_number->addEventListener([=](Ref *sender, ui::Slider::EventType type) {
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)	
		{
			int percent = slider_gene_number->getPercent();	
			int val = (200-1)*percent/100+1;

			m_geneNumber = val;

			char s[32];
			sprintf(s, "%d", val);
			label_gene_number->setString(s);
		}
	});
	label_gene_number->setString("1");

	// 注册开始按钮事件;
	auto button_start = dynamic_cast<ui::Button *>(m_ui->getChildByName("button_start"));
	button_start->addTouchEventListener([=](Ref *sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			this->start();
		}
	});

	// 读取地图数据;
	auto w = helper::getIntSetting("pathfinder_map_w", 1);
	auto h = helper::getIntSetting("pathfinder_map_h", 1);
	auto data = helper::getSetting("pathfinder_map_data");
	auto _map = new int[w*h];
	memset(_map, 0, sizeof(int)*w*h);
	int i = 0;
	for (rapidjson::Value::ConstValueIterator it=data->onBegin(); it!=data->onEnd(); ++it)
	{
		const auto &member = *it;
		int val = member.GetInt();
		_map[i++] = val;
	} 

	// 创建地图;
	m_currentMap.init((int *)_map, w, h);
	m_memoryMap.init((int *)_map, w, h);
	this->createRenderers(m_memoryMap);

	delete[] _map;


	return true;
}

void MapManager::clear()
{
	if (m_genomeManager)
	{
		delete m_genomeManager;
		m_genomeManager = nullptr;
	}

	this->unscheduleAllSelectors();
}

void MapManager::start()
{
	this->clear();

	// 创建群体;
	m_genomeManager = new GenomeManager(m_crossoverRate, m_mutateRate, m_populationNumber, 2*m_geneNumber, 2);

	// 创建定时器来更新地图信息;
	this->schedule(schedule_selector(MapManager::nextGeneration), m_generationInterval);

}

void MapManager::nextGeneration( float dt )
{
	if (!m_genomeManager) return;

	m_genomeManager->epoch();

	this->renderMemory(m_memoryMap);

	if (m_genomeManager->hasSolution())
	{
		this->unscheduleAllSelectors();
	}

	// 刷新时代计数器;
	auto lbl = dynamic_cast<ui::Text *>(m_ui->getChildByName("label_generation"));
	char s[32];
	sprintf(s, "%d", m_genomeManager->getGeneration());
	lbl->setString(s);
}

void MapManager::createRenderers( const PathMap &m )
{
	// 清空所有渲染节点;
	for (auto it : m_mapRenderers)
	{
		auto drawnode = it.second;
		this->removeChild(drawnode);
	}
	m_mapRenderers.clear();
	for (auto it : m_memoryRenderers)
	{
		auto drawnode = it.second;
		this->removeChild(drawnode);
	}
	m_memoryRenderers.clear();

	// 创建渲染节点;
	int w = m.getMapW();
	int h = m.getMapH();
	for (int row=0; row<h; ++row)
	{
		for (int col=0; col<w; ++col)
		{
			int key = row * w + col;
			Vec2 v = Vec2(450+42*col+21, 150+42*(h-row-1)+21);

			// 创建地图显示节点;
			auto mapRenderer = DrawNode::create();
			mapRenderer->setPosition(v);	
			this->addChild(mapRenderer);
			m_mapRenderers[key] = mapRenderer;

			// 填充地图显示节点;
			Vec2 verts[] = { Vec2(-20, -20), Vec2(-20, +20), Vec2(+20, +20), Vec2(+20, -20) };
			const int rect_points = 4;
			float border_width = 1.0f;
			Color4F fillColor, borderColor;
			switch (m.getMap(col, row))
			{
			case GridType::None:
				fillColor = Color4F(0.0f, 1.0f, 0.0f, 0.2f);
				borderColor = fillColor;
				break;
			case GridType::Barrier:
				fillColor = Color4F(1.0f, 0.0f, 0.0f, 0.4f);
				borderColor = fillColor;
				break;
			case GridType::Start:
				fillColor = Color4F(1.0f, 1.0f, 0.0f, 0.2f);
				borderColor = Color4F(1.0f, 1.0f, 1.0f, 0.5f);
				break;
			case GridType::End:
				fillColor = Color4F(0.0f, 1.0f, 1.0f, 0.2f);
				borderColor = Color4F(1.0f, 1.0f, 1.0f, 0.5f);
				break;
			}
			mapRenderer->drawPolygon(verts, rect_points, fillColor, border_width, borderColor);

			// 创建路线显示节点;
			auto memoryRenderer = DrawNode::create();
			memoryRenderer->setPosition(v);	
			this->addChild(memoryRenderer);
			m_memoryRenderers[key] = memoryRenderer;

			// 填充路线显示节点;
			{
				Vec2 verts[] = { Vec2(-15, -15), Vec2(-15, +15), Vec2(+15, +15), Vec2(+15, -15) };
				const int rect_points = 4;
				float border_width = 1.0f;
				Color4F fillColor = Color4F(1.0f, 1.0f, 1.0f, 0.5f);
				Color4F borderColor = Color4F(1.0f, 1.0f, 1.0f, 0.5f);
				memoryRenderer->drawPolygon(verts, rect_points, fillColor, border_width, borderColor);
			}

			// 隐藏路线;
			memoryRenderer->setVisible(false);

		}
	}
}

void MapManager::renderMemory( const PathMap &m )
{
	int w = m.getMapW();
	int h = m.getMapH();
	for (int row=0; row<h; ++row)
	{
		for (int col=0; col<w; ++col)
		{
			int key = row * w + col;
			if (m_memoryRenderers[key])
			{
				auto drawnode = m_memoryRenderers[key];
				drawnode->setVisible(m.getMemory(col, row));
			}
		}
	}
}


