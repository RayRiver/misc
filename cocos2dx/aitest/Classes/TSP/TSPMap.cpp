#include "TSPMap.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;

TSPMap *TSPMap::s_instance = nullptr;

TSPMap * TSPMap::instance()
{
	if (!s_instance)
	{
		s_instance = new TSPMap;
		s_instance->init();
	}
	return s_instance;
}

void TSPMap::destroy()
{
	if (s_instance)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

TSPMap::TSPMap()
	: m_bestPossibleRoute(0.0)
	, m_ui(nullptr)

	, m_pointRenderer(nullptr)
	, m_routeRenderer(nullptr)

	, m_generationInterval(0.016)
	, m_crossoverRate(0)
	, m_mutateRate(0)
	, m_populationNumber(1)
	, m_nPoints(3)
	, m_nBestToAdd(0)
{

}

TSPMap::~TSPMap()
{

}

bool TSPMap::init()
{
	if (!BaseScene::init())
	{
		return false;
	}

	// 加载ui布局;
	m_ui = GUIReader::getInstance()->widgetFromJsonFile("ui/ui_tsp.json");
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

			// 种群数量变化，复制到子代的精英数量也会变化;
			auto label_best_to_add = dynamic_cast<ui::Text *>(m_ui->getChildByName("label_best_to_add"));
			auto slider_best_to_add = dynamic_cast<ui::Slider *>(m_ui->getChildByName("slider_best_to_add"));
			if (m_nBestToAdd > m_populationNumber)
			{
				m_nBestToAdd = m_populationNumber;

				char s[32];
				sprintf(s, "%d", m_nBestToAdd);
				label_best_to_add->setString(s);
			}
			int percent_best_to_add = m_nBestToAdd * 100 / m_populationNumber;
			slider_best_to_add->setPercent(percent_best_to_add);
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
			int val = (200-3)*percent/100+3;

			m_nPoints = val;

			char s[32];
			sprintf(s, "%d", val);
			label_gene_number->setString(s);
		}
	});
	label_gene_number->setString("3");

	// 注册复制到子代精英数量滚动条事件;
	auto label_best_to_add = dynamic_cast<ui::Text *>(m_ui->getChildByName("label_best_to_add"));
	auto slider_best_to_add = dynamic_cast<ui::Slider *>(m_ui->getChildByName("slider_best_to_add"));
	slider_best_to_add->addEventListener([=](Ref *sender, ui::Slider::EventType type) {
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)	
		{
			int percent = slider_best_to_add->getPercent();	
			int val = (m_populationNumber-0)*percent/100+0;

			m_nBestToAdd = val;

			char s[32];
			sprintf(s, "%d", val);
			label_best_to_add->setString(s);
		}
	});

	// 注册开始按钮事件;
	auto button_start = dynamic_cast<ui::Button *>(m_ui->getChildByName("button_start"));
	button_start->addTouchEventListener([=](Ref *sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			this->start();
		}
	});

	// 创建路线渲染器;
	m_pointRenderer = DrawNode::create();
	this->addChild(m_pointRenderer);
	m_routeRenderer = DrawNode::create();
	this->addChild(m_routeRenderer);

	return true;
}

void TSPMap::start()
{
	// 创建点;
	this->createPoints();
	this->renderPoints();
	this->calcBestPossibleRoute();

	// 初始化算法对象;
	m_algorithm.init(m_crossoverRate, m_mutateRate, m_populationNumber, m_nPoints, m_nBestToAdd);

	// 创建定时器来更新地图信息;
	this->schedule(schedule_selector(TSPMap::nextGeneration), m_generationInterval);
}

void TSPMap::nextGeneration( float dt )
{
	m_algorithm.epoch();

	// 绘制当代适应值最高的路径;
	m_routeRenderer->clear();
	auto genome = m_algorithm.getFittestGenome();
	for (int i=0; i<genome.bits.size()-1; ++i)
	{
		Vec2 &p1 = m_points[genome.bits[i]];
		Vec2 &p2 = m_points[genome.bits[i+1]];
		m_routeRenderer->drawSegment(p1, p2, 1.0f, Color4F(1.0f, 1.0f, 1.0f, 0.5f));
	}
	m_routeRenderer->drawSegment(m_points[genome.bits[genome.bits.size()-1]], m_points[genome.bits[0]], 1.0f, Color4F(1.0f, 1.0f, 1.0f, 0.5f));

	// 刷新时代计数器;
	auto lbl = dynamic_cast<ui::Text *>(m_ui->getChildByName("label_generation"));
	char s[32];
	sprintf(s, "%d", m_algorithm.getGeneration());
	lbl->setString(s);

	// 是否已经找到了最短路径;
	if (m_algorithm.hasSolution())
	{
		this->unscheduleAllSelectors();
	}
}

void TSPMap::createPoints()
{
	double radius = 200;
	Vec2 origin(650, 350);
	
	double everyAngle = 2 * M_PI / m_nPoints;

	m_points.clear();

	int i = 0;
	double angle = 0;
	while (angle < 2*M_PI)
	{
		Vec2 p;
		p.x = radius * sin(angle) + origin.x;
		p.y = radius * cos(angle) + origin.y;
		m_points.push_back(p);
		angle += everyAngle;
		++i;
		if (i >= m_nPoints)
		{
			break;
		}
	}
}

void TSPMap::renderPoints()
{
	m_pointRenderer->clear();
	for (auto label : m_pointLabelRenderers)
	{
		this->removeChild(label);
	}
	m_pointLabelRenderers.clear();

	int index = 1;
	for (auto p : m_points)
	{
		m_pointRenderer->drawDot(p, 5.0f, Color4F(0.0f, 1.0f, 0.0f, 0.5f));

		char s[32];
		sprintf(s, "%d", index);
		Label *label = Label::createWithSystemFont(s, "Arial", 12);
		label->setPosition(p.x, p.y-12);
		this->addChild(label);
		m_pointLabelRenderers.push_back(label);

		++index;
	}
}

void TSPMap::calcBestPossibleRoute()
{
	m_bestPossibleRoute = 0;

	for (int i=0; i<m_points.size()-1; ++i)
	{
		m_bestPossibleRoute += m_points[i].getDistance(m_points[i+1]);

		//add in a small amount to cover any precision errors we may have made
		m_bestPossibleRoute += MATH_EPSILON;
	}

	// 再加上最后一个点到第一个点的距离;
	m_bestPossibleRoute += m_points[m_points.size()-1].getDistance(m_points[0]);
}

double TSPMap::getTotalLength( const std::vector<int> &path )
{
	double total = 0.0;
	
	for (int i=0; i<path.size()-1; ++i)
	{
		int p1 = path[i];
		int p2 = path[i+1];

		total += m_points[p1].getDistance(m_points[p2]);
	}

	total += m_points[path[path.size()-1]].getDistance(m_points[path[0]]);

	return total;
}

