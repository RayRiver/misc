package tools.point.events
{
	import flash.events.Event;
	
	/**
	 * 菜单事件
	 * @author Zhenyu Yao
	 */
	public class MenuEvent extends Event
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// 事件类型定义
////////////////////////////////////////////////////////////////////////////////////////////////////

		/// 新建
		public static const NEW				: String = "New";
				
		/// 打开		
		public static const OPEN			: String = "Open";
				
		/// 存储		
		public static const SAVE			: String = "Save";
				
		/// 另存为		
		public static const SAVE_AS			: String = "SaveAs";
				
		/// Undo		
		public static const UNDO			: String = "Undo";
				
		/// Redo		
		public static const REDO			: String = "Redo";
		
		/// 适合网格的方式确定顶点
		public static const FIT_FOR_GRIDS	: String = "FitForGrids";
		
		/// 关于
		public static const ABOUT			: String = "About";
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @param	type 事件类型
		 * @author Zhenyu Yao
		 */
		public function MenuEvent(type : String) 
		{ 
			super(type);
		} 
		
		/**
		 * 克隆事件
		 * @return MenuEvent 对象
		 * @author Zhenyu Yao
		 */
		public override function clone() : Event 
		{ 
			return new MenuEvent(type);
		} 
	
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// end file