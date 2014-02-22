package tools.point.events 
{
	import flash.events.Event;
	import flash.geom.Point;
	
	/**
	 * 锚点移动事件
	 * @author Zhenyu Yao
	 */
	public class MoveAnchorPointEvent extends Event 
	{
		/// 移动锚点事件
		public static const MOVE_ANCHOR_POINT : String			= "MoveAnchorPoint";
		
		/// 确认锚点位置事件
		public static const CONFIRM_ANCHOR_POINT : String		= "ConfirmAnchorPoint";
		
		public function MoveAnchorPointEvent(type : String, anchorPoint : Point) 
		{ 
			super(type);
			m_anchorPoint = anchorPoint.clone();
		} 
		
		public override function clone():Event 
		{ 
			return new MoveAnchorPointEvent(type, m_anchorPoint);
		} 
		
		public function get anchorPoint() : Point
		{
			return m_anchorPoint.clone();
		}
		
		private var m_anchorPoint : Point = null;
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// end file