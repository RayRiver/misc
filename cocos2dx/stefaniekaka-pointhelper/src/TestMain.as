package  
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Sprite;
	import flash.geom.Point;
	import tools.point.view.ToolWindowMenu;
	import tools.point.utils.Metadata;
	import tools.point.utils.DataMemento;
	
	/**
	 * 测试类
	 * @author Zhenyu Yao
	 */
	public final class TestMain extends Sprite 
	{
		
		public function TestMain() 
		{
			var data : Metadata = new Metadata();
			var bitmapData : BitmapData = new BitmapData(300, 150, true, 0xff000000);
			data.bitmapData = bitmapData;
			
			data.reset(2, 2);
			for (var i : int = 0; i < 4; ++i)
			{
				data.push(new Point(100 * i, 100 * i), 0, 1);
			}
			
			var dataMemento : DataMemento = new DataMemento();
			var strXML : String = dataMemento.stringFromData(data);
			
			data = dataMemento.dataFromString(strXML);
			trace(data);
			this.addChild(new Bitmap(data.bitmapData));
		}
		
	}

}