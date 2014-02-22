package tools.point.view 
{
	import flash.display.Sprite;
	import flash.geom.Rectangle;
	
	/**
	 * 描点显示对象
	 * @author Zhenyu Yao
	 */
	public final class AnchorPointSprite extends Sprite 
	{
		
		public function AnchorPointSprite() 
		{
			this.graphics.beginFill(0x00ffff, 0.5);
			this.graphics.lineStyle(1);
			this.graphics.drawRect(-8, -8, 16, 16);
			this.graphics.endFill();
			
			this.graphics.beginFill(0xff0000);
			this.graphics.drawCircle(0, 0, 1);
			this.graphics.endFill();
		}
		
		override public function startDrag(lockCenter:Boolean = false, bounds:Rectangle = null):void 
		{
			super.startDrag(lockCenter, bounds);
			m_moving = true;
		}
		
		override public function stopDrag():void 
		{
			super.stopDrag();
			m_moving = false;
		}
		
		public function get moving() : Boolean
		{
			return m_moving;
		}
		
		private var m_moving : Boolean = false;
	}

}