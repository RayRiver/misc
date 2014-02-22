package tools.point.events 
{
	import flash.events.Event;
	
	/**
	 * 描点模式改变事件
	 * @author Zhenyu Yao
	 */
	public class ChangeAnchorModeEvent extends Event 
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Static Vars
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/// 改变 AnchorMode 
		public static const CHANGE_ANCHOR_MODE : String				= "ChangeAnchorMode";

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions 
////////////////////////////////////////////////////////////////////////////////////////////////////

		public function ChangeAnchorModeEvent(type : String, anchorMode : Boolean) 
		{ 
			super(type);
			m_anchorMode = anchorMode;
		} 
		
		public override function clone():Event 
		{ 
			return new ChangeAnchorModeEvent(type, m_anchorMode);
		} 
		
		public function get anchorMode() : Boolean
		{
			return m_anchorMode;
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		private var m_anchorMode : Boolean = false;
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// end file