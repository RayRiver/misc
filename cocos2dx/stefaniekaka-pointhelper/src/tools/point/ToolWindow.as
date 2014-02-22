package tools.point 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObject;
	import flash.display.DisplayObjectContainer;
	import flash.display.NativeWindow;
	import flash.display.NativeWindowInitOptions;
	import flash.display.Shape;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.display.StageQuality;
	import flash.desktop.NativeApplication;
	import flash.events.Event;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import tools.point.mediator.FileViewCommandMediator;
	import tools.point.mediator.MenuMediator;
	import tools.point.mediator.DisplayMediator;
	import tools.point.utils.CommandManager;
	import tools.point.utils.FileManager;
	import tools.point.utils.WindowDefaultOptions;
	import tools.point.view.PrintMessageView;
	import tools.point.view.ToolWindowMenu;
	import tools.point.view.PictureView;
	import tools.point.view.PictureOperationView;
	import tools.point.mediator.ViewCommandMediator;
	import tools.point.mediator.ViewMenuMediator;
	
	/**
	 * 工具的窗口
	 * @author 姚振宇
	 */
	public final class ToolWindow extends NativeWindow
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @author Zhenyu Yao
		 */
		public function ToolWindow() 
		{
			super(WindowDefaultOptions.defaultWindowOptions);
			
			// 窗口的默认配置
			var size : Point = WindowDefaultOptions.defaultWindowSize;
			this.width = size.x;
			this.height = size.y;
			this.title = WindowDefaultOptions.defaultWindowTitle;
			this.stage.align = StageAlign.TOP_LEFT;
			this.stage.scaleMode = StageScaleMode.NO_SCALE;
			this.stage.quality = StageQuality.BEST;
			this.stage.frameRate = 60;
			
			// 生成菜单
			m_menu = ToolWindowMenu.generateMenu();
			m_fileManager = new FileManager();
			m_commandManager = new CommandManager();
			
			var root : DisplayObjectContainer = this.stage.root as DisplayObjectContainer;
			
			// 生成视图
			m_pictureView = new PictureView();
			m_operationView = new PictureOperationView();
			m_messageView = new PrintMessageView();
			m_operationView.y += 5;
			root.addChild(m_operationView);
			m_pictureView.y += 32;
			root.addChild(m_pictureView);
			m_messageView.x = 6.18;
			m_messageView.y += 400;
			root.addChild(m_messageView);
			
			// 初始化各种中介者
			m_menuMediator = new MenuMediator(m_menu, m_fileManager, m_commandManager);
			m_viewCommandMediator = new ViewCommandMediator(m_pictureView, m_messageView, m_commandManager);
			m_displayMediator = new DisplayMediator(m_pictureView, m_operationView);
			m_viewMenuMediator = new ViewMenuMediator(m_menu, m_pictureView);
			m_fileViewCommandMediator = new FileViewCommandMediator(m_fileManager, m_pictureView, m_messageView, m_commandManager);
			
			if (NativeWindow.supportsMenu)
			{
				this.menu = m_menu;
			}
			else if (NativeApplication.supportsMenu)
			{
				NativeApplication.nativeApplication.menu = m_menu;
			}
			
			this.visible = true;
			
			this.addEventListener(Event.ACTIVATE, onActivateHandler);
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private 
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 激活窗口事件
		 * @author Zhenyu Yao
		 */
		public function onActivateHandler(evt : Event) : void
		{
			m_menuMediator.resetMenuEventListener();
		}

		private var m_menu : ToolWindowMenu = null;
		private var m_fileManager : FileManager = null;
		private var m_commandManager : CommandManager = null;
		
		private var m_pictureView : PictureView = null;
		private var m_operationView : PictureOperationView = null;
		private var m_messageView : PrintMessageView = null;
		
		private var m_menuMediator : MenuMediator = null;
		private var m_viewCommandMediator : ViewCommandMediator = null;
		private var m_displayMediator : DisplayMediator = null;
		private var m_viewMenuMediator : ViewMenuMediator = null;
		private var m_fileViewCommandMediator : FileViewCommandMediator = null;
	}

}