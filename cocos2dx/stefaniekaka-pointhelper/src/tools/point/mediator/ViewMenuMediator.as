package tools.point.mediator 
{
	import tools.point.view.PictureView;
	import tools.point.view.ToolWindowMenu;
	import tools.point.events.MenuEvent;
	
	/**
	 * 视图与菜单的中介者
	 * @author Zhenyu Yao
	 */
	public final class ViewMenuMediator 
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @param	menu 菜单
		 * @param	view 视图
		 * @author Zhenyu Yao
		 */
		public function ViewMenuMediator(menu : ToolWindowMenu, view : PictureView) 
		{
			m_menu = menu;
			m_view = view;
			
			m_menu.addEventListener(MenuEvent.FIT_FOR_GRIDS, onFitForGridsHandler);
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 顶点适应网格事件
		 * @param	evt MenuEvent 对象
		 * @author Zhenyu Yao
		 */
		private function onFitForGridsHandler(evt : MenuEvent) : void
		{
			if (m_view.picture != null)
			{
				m_view.generatePointsForGrids();
			}
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Vars
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		private var m_menu : ToolWindowMenu = null;
		private var m_view : PictureView = null;
	}

}