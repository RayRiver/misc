package 
{
	import flash.display.Sprite;
	import tools.point.ToolWindow;
	
	/**
	 * 坐标点选取工具的主类
	 * @author 姚振宇
	 */
	public class Main extends Sprite 
	{
		
		public function Main():void 
		{
			var toolWindow : ToolWindow = new ToolWindow();
			this.stage.nativeWindow.close();
		}
		
	}
	
}