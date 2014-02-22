package tools.point.utils 
{
	import flash.display.BitmapData;
	import flash.geom.Point;
	import flash.utils.getQualifiedClassName;
	
	/**
	 * 元数据, 元数据内保存的点都是以GL坐标系为基础的
	 * @author Zhenyu Yao
	 */
	public final class Metadata 
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Properties
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 图片元数据
		 * @author Zhenyu Yao
		 */
		public function get bitmapData() : BitmapData
		{
			return m_bitmapData;
		}
		
		public function set bitmapData(bitmapData : BitmapData) : void
		{
			m_bitmapData = bitmapData;
		}
		
		/**
		 * 点的数据
		 * @author Zhenyu Yao
		 */
		public function get points() : Vector.<Vector.<Vector.<Point>>>
		{
			return m_points;
		}
		
		/**
		 * 行数量
		 * @author Zhenyu Yao
		 */
		public function get rows() : int
		{
			if (m_points == null)
			{
				return 0;
			}
			
			return m_points.length;
		}
		
		/**
		 * 列数量
		 * @author Zhenyu Yao
		 */
		public function get cols() : int
		{
			if (m_points == null)
			{
				return 0;
			}
			
			// 每行的列数都是相同的
			return m_points[0].length;
		}
		
		/**
		 * 锚点模式
		 * @author ZhenyuYoa 
		 */
		public function set anchorMode(value : Boolean) : void
		{
			m_anchorMode = value;
		}
		
		public function get anchorMode() : Boolean
		{
			return m_anchorMode;
		}
		
		/**
		 * 锚点
		 */
		public function get anchorPoint() : Point
		{
			if (m_anchorPoint == null) 
			{
				m_anchorPoint = new Point(0.5, 0.5);
			}
			
			return m_anchorPoint;
		}

		public function set anchorPoint(value : Point) : void
		{
			if (value.x < 0) 
			{
				value.x = 0;
			}
			
			if (value.x > 1)
			{
				value.x = 1;
			}
			
			if (value.y < 0)
			{
				value.y = 0;
			}
			
			if (value.y > 1)
			{
				value.y = 1;
			}
			
			m_anchorPoint = value;
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @author Zhenyu Yao
		 */
		public function Metadata() 
		{
		}
		
		/**
		 * 清空所有的点, 但是不改变行列数量
		 * @author Zhenyu Yao
		 */
		public function cleanup() : void
		{
			for each (var cols : Vector.<Vector.<Point>> in m_points)
			{
				for each (var cell : Vector.<Point> in cols)
				{
					cell.splice(0, cell.length);
				}
			}
		}
		
		/**
		 * 获得指定格子中的所有点
		 * @param	row 行
		 * @param	col 列
		 * @return 格子内的所有数组
		 * @author Zhenyu Yao
		 */
		public function getPoints(row : int, col : int) : Vector.<Point>
		{
			return m_points[row][col];
		}
		
		/**
		 * 弹出指定网格中的最新添加的点
		 * @param	row 行
		 * @param	col 列
		 * @return 被删除的点
		 * @author Zhenyu Yao
		 */
		public function pop(row : int, col : int) : Point
		{
			return m_points[row][col].pop();
		}
		
		/**
		 * 向指定的网格中添加点
		 * @param	p 添加的点
		 * @param	row 行
		 * @param	col 列
		 * @author Zhenyu Yao
		 */
		public function push(p : Point, row : int, col : int) : void
		{
			m_points[row][col].push(p);
		}
		
		/**
		 * 重新设置网格的行列数值, 原来的点将被全部删除
		 * @param	row 新的行
		 * @param	col 新的列
		 * @author Zhenyu Yao
		 */
		public function reset(row : int, col : int) : void
		{
			m_points = new Vector.<Vector.<Vector.<Point>>>(row, true);
			for (var i : int = 0; i < m_points.length; ++i)
			{
				m_points[i] = new Vector.<Vector.<Point>>(col, true);
				for (var j : int = 0; j < col; ++j)
				{
					m_points[i][j] = new Vector.<Point>();
				}
			}
		}
		
		/**
		 * 创建一个自身的副本, 深度复制
		 * @return Metadata 对象
		 * @author Zhenyu Yao
		 */
		public function copy() : Metadata
		{
			var copyData : Metadata = new Metadata();
			copyData.reset(rows, cols);
			copyData.bitmapData = m_bitmapData != null ? m_bitmapData.clone() : null;
			copyData.anchorPoint = m_anchorPoint;
			copyData.anchorMode = m_anchorMode;
			
			for (var i : int = 0; i < rows; ++i)
			{
				for (var j : int = 0; j < cols; ++j)
				{
					var points : Vector.<Point> = getPoints(i, j);
					for each (var p : Point in points)
					{
						copyData.push(p.clone(), i, j);
					}
				}
			}
			
			return copyData;
		}
		
		/**
		 * 元数据的描述文本
		 * @return 描述文本
		 * @author Zhenyu Yao
		 */
		public function toString() : String
		{
			var str : String = getQualifiedClassName(this) + ": ";
			if (m_bitmapData == null)
			{
				str += "BitmapData == null\n";
			}
			else
			{
				str += "<Width = " + m_bitmapData.width + ", Height = " + m_bitmapData.height + ">\n";
			}
			
			str += "{\n";
			for (var i : int = 0; i < m_points.length; ++i)
			{
				for (var j : int = 0; j < m_points[i].length; ++j)
				{
					var cell : Vector.<Point> = m_points[i][j];
					str += "\t" + "[" + i + "]" + "[" + j + "]\n";
					str += "\t" + "{\n";
					for each (var p : Point in cell)
					{
						str += "\t\t{" + p.x + ", " + p.y + "}\n"; 
					}
					str += "\t" + "}\n";
				}
				
				// 每行用一排分割线分开
				if (i != m_points.length - 1)
				{
					str += "<";
					for (var k : int = 0; k < 40; ++k)
					{
						str += "-";
					}
					str += ">\n";
				}
			}
			str += "}";
			
			return str;
		}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Vars
////////////////////////////////////////////////////////////////////////////////////////////////////

		private var m_points : Vector.<Vector.<Vector.<Point>>> = null;
		private var m_bitmapData : BitmapData = null;
		private var m_anchorPoint : Point = null;
		private var m_anchorMode : Boolean = false;
	}

}