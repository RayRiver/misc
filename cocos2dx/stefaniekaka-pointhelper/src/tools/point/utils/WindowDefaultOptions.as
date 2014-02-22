package tools.point.utils 
{
	import flash.display.NativeWindowInitOptions;
	import flash.display.NativeWindowSystemChrome;
	import flash.geom.Point;
	
	/**
	 * 窗口的默认配置
	 * @author Zhenyu Yao
	 */
	public final class WindowDefaultOptions 
	{
		/**
		 * 默认窗口配置
		 * @author Zhenyu Yao
		 */
		public static function get defaultWindowOptions() : NativeWindowInitOptions
		{
			var options : NativeWindowInitOptions = new NativeWindowInitOptions();
			options.maximizable = false;
			options.minimizable = true;
			options.resizable = false;
			options.systemChrome = NativeWindowSystemChrome.STANDARD;
			options.transparent = false;
			return options;
		}
		
		/**
		 * 默认的窗口大小
		 * @author Zhenyu Yao
		 */
		public static function get defaultWindowSize() : Point
		{
			return new Point(1000, 720);
		}
		
		/**
		 * 默认的窗口标题
		 * @author Zhenyu Yao
		 */
		public static function get defaultWindowTitle() : String
		{
			return "未命名";
		}
	}

}