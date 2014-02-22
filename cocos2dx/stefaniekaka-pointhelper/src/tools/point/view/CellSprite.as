package tools.point.view 
{
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.geom.Point;
	
	/**
	 * 网格
	 * @author Zhenyu Yao
	 */
	internal final class CellSprite extends Sprite 
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @param	cellX 网格的x坐标
		 * @param	cellY 网格的y坐标
		 * @param	w 网格的宽度
		 * @param	h 网格的高度
		 * @author Zhenyu Yao
		 */
		public function CellSprite(cellX : Number, cellY : Number, w : Number, h : Number)
		{
			this.mouseChildren = false;
			this.mouseEnabled = false;
			
			m_size = new Point(w, h);
			
			// 确定位置
			this.x = cellX;
			this.y = cellY;
			
			// 绘制网格的边框
			this.graphics.lineStyle(1, 0xFF8000);
			this.graphics.drawRect(-w * 0.5, -h * 0.5, w, h);
			
			// 生成绘制连接第一个点与最后一个点的直线对象
			m_line = new Shape();
			this.addChild(m_line);
			
			m_points = new Vector.<Shape>();
		}
		
		/**
		 * 添加点
		 * @param	x 点的x坐标
		 * @param	y 点的y坐标
		 * @author Zhenyu Yao
		 */
		public function addPoint(x : Number, y : Number) : void
		{
			var circle : Shape = new Shape();
			circle.graphics.beginFill(0xFF0000);
			circle.graphics.drawCircle(0, 0, 2);
			circle.graphics.endFill();
			circle.x = x;
			circle.y = y;
			this.addChild(circle);
			m_points.push(circle);
			
			linkPoints();
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 连接所有的点
		 * @author Zhenyu Yao
		 */
		private function linkPoints() : void
		{
			m_line.graphics.clear();
			m_line.graphics.lineStyle(1, 0x00FF00);
			m_line.graphics.moveTo(m_points[0].x, m_points[0].y);
			
			for (var i : int = 1; i < m_points.length; ++i)
			{
				m_line.graphics.lineTo(m_points[i].x, m_points[i].y);
			}
			
			m_line.graphics.lineStyle(1, 0xC0C0C0);
			m_line.graphics.lineTo(m_points[0].x, m_points[0].y);
		}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Vars
////////////////////////////////////////////////////////////////////////////////////////////////////

		private var m_line : Shape = null;
		private var m_points : Vector.<Shape> = null;
		private var m_size : Point = null;
	}

}