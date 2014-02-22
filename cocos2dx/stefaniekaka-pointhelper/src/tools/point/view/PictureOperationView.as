package tools.point.view 
{
	import flash.display.Sprite;
	import fl.controls.Button;
	import fl.controls.ButtonLabelPlacement;
	import fl.controls.CheckBox;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import tools.point.events.ChangeEditModeEvent;
	import tools.point.events.ChangeImageSizeEvent;
	
	/**
	 * 图片操作视图
	 * @author Zhenyu Yao
	 */
	public final class PictureOperationView extends Sprite 
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Properties
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 选中编辑模式检查框
		 * @author Zhenyu Yao
		 */
		public function get editMode() : Boolean
		{
			return m_chkEdit.selected;
		}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @author Zhenyu Yao
		 */
		public function PictureOperationView() 
		{
			// 放大按钮
			m_btnZoomIn = new Button();
			m_btnZoomIn.label = "放大";
			m_btnZoomIn.addEventListener(MouseEvent.CLICK, onZoomInHandler);
			this.addChild(m_btnZoomIn);
			
			// 缩小按钮
			m_btnZoomOut = new Button();
			m_btnZoomOut.x = 120;
			m_btnZoomOut.label = "缩小";
			m_btnZoomOut.addEventListener(MouseEvent.CLICK, onZoomOutHandler);
			this.addChild(m_btnZoomOut);
			
			// 实际大小
			m_btnActualSize = new Button();
			m_btnActualSize.x = 240;
			m_btnActualSize.label = "实际大小";
			m_btnActualSize.addEventListener(MouseEvent.CLICK, onActualSizeHandler);
			this.addChild(m_btnActualSize);
			
			// 检查框
			m_chkEdit = new CheckBox();
			m_chkEdit.x = 305;
			m_chkEdit.label = "编辑";
			m_chkEdit.labelPlacement = ButtonLabelPlacement.LEFT;
			m_chkEdit.addEventListener(MouseEvent.CLICK, onChangeEditModeHandler);
			m_chkEdit.selected = false;
			this.addChild(m_chkEdit);
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/// 点击放大按钮
		private function onZoomInHandler(evt : MouseEvent) : void
		{
			var changeSizeEvent : ChangeImageSizeEvent = new ChangeImageSizeEvent(ChangeImageSizeEvent.CHANGE_SIZE, 1.25);
			this.dispatchEvent(changeSizeEvent);
		}
		
		/// 点击缩小按钮
		private function onZoomOutHandler(evt : MouseEvent) : void
		{
			var changeSizeEvent : ChangeImageSizeEvent = new ChangeImageSizeEvent(ChangeImageSizeEvent.CHANGE_SIZE, 0.8);
			this.dispatchEvent(changeSizeEvent);
		}
		
		/// 点击实际大小按钮
		private function onActualSizeHandler(evt : MouseEvent) : void
		{
			var changeSizeEvent : ChangeImageSizeEvent = new ChangeImageSizeEvent(ChangeImageSizeEvent.FIXED_SIZE, 1.0);
			this.dispatchEvent(changeSizeEvent);
		}
		
		/// 改变编辑模式检查框
		private function onChangeEditModeHandler(evt : MouseEvent) : void
		{
			var changeEditModeEvt : ChangeEditModeEvent = new ChangeEditModeEvent(ChangeEditModeEvent.CHANGE_EDIT_MODE);
			this.dispatchEvent(changeEditModeEvt);
		}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private vars
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		private var m_btnZoomIn : Button = null;
		private var m_btnZoomOut : Button = null;
		private var m_btnActualSize : Button = null;
		private var m_chkEdit : CheckBox = null;
	}

}