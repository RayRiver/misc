package tools.point.view 
{
	import flash.display.NativeMenu;
	import flash.display.NativeMenuItem;
	import flash.desktop.NativeApplication;
	import flash.events.Event;
	import flash.ui.Keyboard;
	import tools.point.events.MenuEvent;
	
	/**
	 * 应用程序的菜单
	 * @author Zhenyu Yao
	 */
	public final class ToolWindowMenu extends NativeMenu 
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 生成菜单
		 * @author Zhenyu Yao
		 */
		public static function generateMenu() : ToolWindowMenu
		{
			if (NativeApplication.supportsMenu) 
			{
				if (m_menu == null)
				{
					m_menu = new ToolWindowMenu();
				}
				
				return m_menu;
			}
			else
			{
				return new ToolWindowMenu();
			}
		}
		
		private static var m_menu : ToolWindowMenu = null;

		/**
		 * 构造函数
		 * @author Zhenyu Yao
		 */
		public function ToolWindowMenu() 
		{
			buildFileMenu();
			buildEditMenu();
			buildHelpMenu();
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 创建文件菜单项
		 * @author Zhenyu Yao
		 */
		private function buildFileMenu() : void
		{
			// 文件
			var fileMenu : NativeMenu = new NativeMenu();
			this.addSubmenu(fileMenu, "文件");
			
			// 文件 - 新建
			var createItem : NativeMenuItem = new NativeMenuItem("新建");
			createItem.addEventListener(Event.SELECT, onCreateHandler);
			fileMenu.addItem(createItem);
			
			// 文件 - 打开
			var openItem : NativeMenuItem = new NativeMenuItem("打开");
			openItem.addEventListener(Event.SELECT, onOpenHandler);
			fileMenu.addItem(openItem);
			
			// 分割线
			var seperator : NativeMenuItem = new NativeMenuItem("", true);
			fileMenu.addItem(seperator);
			
			// 文件 - 存储
			var saveItem : NativeMenuItem = new NativeMenuItem("存储");
			saveItem.keyEquivalent = "s";
			saveItem.keyEquivalentModifiers = [Keyboard.CONTROL];
			saveItem.addEventListener(Event.SELECT, onSaveHandler);
			fileMenu.addItem(saveItem);
			
			// 文件 - 另存为
			var saveAsItem : NativeMenuItem = new NativeMenuItem("另存为...");
			saveAsItem.keyEquivalent = "s";
			saveAsItem.keyEquivalentModifiers = [Keyboard.CONTROL, Keyboard.SHIFT];
			saveAsItem.addEventListener(Event.SELECT, onSaveAsHandler);
			fileMenu.addItem(saveAsItem);
		}
		
		/**
		 * 创建编辑菜单
		 * @author Zhenyu Yao
		 */
		private function buildEditMenu() : void
		{
			// 编辑
			var editMenu : NativeMenu = new NativeMenu();
			this.addSubmenu(editMenu, "编辑");
			
			// 编辑 - Undo
			var undoMenuItem : NativeMenuItem = new NativeMenuItem("Undo");
			undoMenuItem.keyEquivalent = "z";
			undoMenuItem.keyEquivalentModifiers = [Keyboard.CONTROL];
			undoMenuItem.addEventListener(Event.SELECT, onUndoHandler);
			editMenu.addItem(undoMenuItem);
			
			// 编辑 - Redo
			var redoMenuItem : NativeMenuItem = new NativeMenuItem("Redo");
			redoMenuItem.keyEquivalent = "z";
			redoMenuItem.keyEquivalentModifiers = [Keyboard.CONTROL, Keyboard.SHIFT];
			redoMenuItem.addEventListener(Event.SELECT, onRedoHandler);
			editMenu.addItem(redoMenuItem);
			
			// 编辑 - 分隔符
			var seperator : NativeMenuItem = new NativeMenuItem("", true);
			editMenu.addItem(seperator);
			
			// 编辑 - 根据网格决定顶点
			var fitForGridsItem : NativeMenuItem = new NativeMenuItem("根据网格决定顶点");
			fitForGridsItem.addEventListener(Event.SELECT, onFitForGridsHandler);
			editMenu.addItem(fitForGridsItem);
		}
		
		/**
		 * 创建 "帮助" 菜单
		 * @author Zhenyu Yao
		 */
		private function buildHelpMenu() : void
		{
			// 帮助
			var helpMenu : NativeMenu = new NativeMenu();
			this.addSubmenu(helpMenu, "帮助");
			
			// 帮助 - 关于
			var aboutItem : NativeMenuItem = new NativeMenuItem("关于");
			aboutItem.addEventListener(Event.SELECT, onAboutHandler);
			helpMenu.addItem(aboutItem);
		}
		
		/// 点击"新建"选项
		private function onCreateHandler(evt : Event) : void
		{
			this.dispatchEvent(new MenuEvent(MenuEvent.NEW));
		}
		
		/// 点击"打开"选项
		private function onOpenHandler(evt : Event) : void
		{
			this.dispatchEvent(new MenuEvent(MenuEvent.OPEN));
		}
		
		/// 点击"存储"选项
		private function onSaveHandler(evt : Event) : void
		{
			this.dispatchEvent(new MenuEvent(MenuEvent.SAVE));
		}
		
		/// 点击"存储为"选项
		private function onSaveAsHandler(evt : Event) : void
		{
			this.dispatchEvent(new MenuEvent(MenuEvent.SAVE_AS));
		}
		
		/// 点击"Undo"选项
		private function onUndoHandler(evt : Event) : void
		{
			this.dispatchEvent(new MenuEvent(MenuEvent.UNDO));
		}
		
		/// 点击"Redo"选项
		private function onRedoHandler(evt : Event) : void
		{
			this.dispatchEvent(new MenuEvent(MenuEvent.REDO));
		}
		
		/// 点击"根据网格决定顶点"选项
		private function onFitForGridsHandler(evt : Event) : void
		{
			this.dispatchEvent(new MenuEvent(MenuEvent.FIT_FOR_GRIDS));
		}
		
		/// 点击"关于"选项
		private function onAboutHandler(evt : Event) : void
		{
			this.dispatchEvent(new MenuEvent(MenuEvent.ABOUT));
		}
	}

}