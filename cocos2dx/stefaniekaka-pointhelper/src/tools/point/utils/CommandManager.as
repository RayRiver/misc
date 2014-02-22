package tools.point.utils 
{
	import flash.display.BitmapData;
	import flash.events.EventDispatcher;
	import flash.geom.Point;
	import flash.utils.getQualifiedClassName;
	import tools.point.events.OperationEvent;
	
	/**
	 * 操作命令管理器, 要求加入的点的坐标系统都是GL坐标系统
	 * @author Zhenyu Yao
	 */
	public final class CommandManager extends EventDispatcher
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Properties
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 获得当前正在使用的元数据
		 * @author Zhenyu Yao
		 */
		public function get currentMetadata() : Metadata
		{
			return m_metadatas.length == 0 ? null : m_metadatas[m_currentIndex];
		}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @author Zhenyu Yao
		 */
		public function CommandManager() 
		{
			m_metadatas = new Vector.<Metadata>();
		}
		
		/**
		 * 撤销
		 * @author Zhenyu Yao
		 */
		public function undo() : void
		{
			if (m_currentIndex > 0)
			{
				--m_currentIndex;
				
				var evt : OperationEvent = new OperationEvent(OperationEvent.UNDO, currentMetadata);
				this.dispatchEvent(evt);
			}
		}
		
		/**
		 * 重做
		 * @author Zhenyu Yao
		 */
		public function redo() : void
		{
			if (m_currentIndex < m_metadatas.length - 1)
			{
				++m_currentIndex;
				
				var evt : OperationEvent = new OperationEvent(OperationEvent.REDO, currentMetadata);
				this.dispatchEvent(evt);
			}	
		}
		
		/**
		 * 添加图片
		 * @param	bitmapData 添加图片的元数据
		 * @author Zhenyu Yao
		 */
		public function addImage(bitmapData : BitmapData) : void
		{
			var data : Metadata = new Metadata();
			data.bitmapData = bitmapData;
			data.reset(1, 1);
			
			updateMetadatas(data);
		}
		
		/**
		 * 直接在当前使用的元数据上添加点
		 * @param	p 添加的点
		 * @param	row 行
		 * @param	col 列
		 * @author Zhenyu Yao
		 */
		public function addPoint(p : Point, row : int, col : int) : void
		{
			var data : Metadata = currentMetadata.copy();
			data.push(p, row, col);
			updateMetadatas(data);
		}
		
		/**
		 * 添加元数据
		 * @param	data 元数据
		 * @author Zhenyu Yao
		 */
		public function addMetadata(data : Metadata) : void
		{
			updateMetadatas(data.copy());
		}
		
		/**
		 * 重新排列
		 * @param	row 行
		 * @param	col 列
		 * @author Zhenyu Yao
		 */
		public function realign(row : int, col : int) : void
		{
			var data : Metadata = currentMetadata.copy();
			data.reset(row, col);
			updateMetadatas(data);
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Override Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 描述文本
		 * @return 描述文本
		 * @author Zhenyu Yao
		 */
		override public function toString() : String
		{
			var str : String = getQualifiedClassName(this) + ": <Metadatas = " + m_metadatas.length + ">\n";
			return str;
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 更新元数据数组, 如果当前指向的是最后一个元数据对象, 那么直接将新的元数据添加进来;
		 * 但是如果当前指向的是其中一个元数据对象, 那么将删除当前指向元数据之后的所有元数据对象(不包括当前指向的元数据对象)
		 * @param	metadata 新加入的元数据对象
		 * @author Zhenyu Yao
		 */
		private function updateMetadatas(metadata : Metadata) : void
		{
			// 如果当前的索引指向的元数据不是最后一个, 而是其中的某个元数据, 那么将删除当前所以之后的全部元数据(不包括当前索引元数据)
			if (m_metadatas.length != m_currentIndex + 1)
			{
				m_metadatas.splice(m_currentIndex + 1, 0xffffffff);
			}
			
			// 记录新加入的元数据
			m_metadatas.push(metadata);
			++m_currentIndex;
		}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Vars
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		private var m_currentIndex : int = -1;
		private var m_metadatas : Vector.<Metadata> = null;
	}

}