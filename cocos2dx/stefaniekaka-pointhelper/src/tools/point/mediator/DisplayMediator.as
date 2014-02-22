package tools.point.mediator 
{
	import tools.point.events.AddPointEvent;
	import tools.point.events.ChangeEditModeEvent;
	import tools.point.events.ChangeImageSizeEvent;
	import tools.point.view.PictureOperationView;
	import tools.point.view.PictureView;
	
	/**
	 * 放大缩小控制视图与图片显示视图的中介者
	 * @author Zhenyu Yao
	 */
	public final class DisplayMediator 
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @param pictureView 装载图片的视图
		 * @param operationView 操作视图
		 * @author Zhenyu Yao
		 */
		public function DisplayMediator(pictureView : PictureView, operationView : PictureOperationView) 
		{
			m_pictureView = pictureView;
			m_operationView = operationView;
			m_pictureView.editMode = m_operationView.editMode;
			
			m_operationView.addEventListener(ChangeImageSizeEvent.CHANGE_SIZE, onChangeImageSizeHandler);
			m_operationView.addEventListener(ChangeImageSizeEvent.FIXED_SIZE, onChangeImageSizeHandler);
			m_operationView.addEventListener(ChangeEditModeEvent.CHANGE_EDIT_MODE, onChangeEditModeHandler);
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 改变图片大小事件
		 * @param	evt 改变图片大小事件对象
		 * @author Zhenyu Yao
		 */
		private function onChangeImageSizeHandler(evt : ChangeImageSizeEvent) : void
		{
			if (evt.type == ChangeImageSizeEvent.CHANGE_SIZE)
			{
				if (m_pictureView.container != null)
				{
					m_pictureView.container.scaleX *= evt.changedScale;
					m_pictureView.container.scaleY *= evt.changedScale;
				}
			}
			else if (evt.type == ChangeImageSizeEvent.FIXED_SIZE)
			{
				if (m_pictureView.container != null)
				{
					m_pictureView.container.scaleX = 1.0;
					m_pictureView.container.scaleY = 1.0;
				}
			}
		}
		
		/**
		 * 改变编辑模式事件
		 * @param	evt 改变模式事件对象
		 * @author Zhenyu Yao
		 */
		private function onChangeEditModeHandler(evt : ChangeEditModeEvent) : void
		{
			m_pictureView.editMode = m_operationView.editMode;
		}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private vars
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		private var m_pictureView : PictureView = null;
		private var m_operationView : PictureOperationView = null;

	}

}