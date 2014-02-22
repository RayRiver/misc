package tools.point.mediator 
{
	import flash.events.Event;
	import flash.geom.Point;
	import tools.point.view.PictureView;
	import tools.point.view.PrintMessageView;
	import tools.point.utils.CommandManager;
	import tools.point.utils.Metadata;
	import tools.point.events.AddPointEvent;
	import tools.point.events.AddImageEvent;
	import tools.point.events.GeneratePointsForGridsEvent;
	import tools.point.events.ChangeDivideValueEvent;
	import tools.point.events.ChangeRowAndColEvent;
	import tools.point.events.ChangeAnchorModeEvent;
	import tools.point.events.OperationEvent;
	import tools.point.events.MoveAnchorPointEvent;
	
	/**
	 * 视图与命令的中介者
	 * @author Zhenyu Yao
	 */
	public final class ViewCommandMediator 
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @param	pictureView 包含图片的视图
		 * @param	messageView 输出打印消息的视图
		 * @param	commandManager 命令管理器
		 * @author Zhenyu Yao
		 */
		public function ViewCommandMediator(pictureView : PictureView, messageView : PrintMessageView, commandManager : CommandManager) 
		{
			m_pictureView = pictureView;
			m_messageView = messageView;
			m_commandManager = commandManager;
			
			m_pictureView.addEventListener(AddPointEvent.ADD_POINT, onAddPointHandler);
			m_pictureView.addEventListener(AddImageEvent.ADD_IMAGE, onAddImageHandler);
			m_pictureView.addEventListener(GeneratePointsForGridsEvent.GENERATE_POINTS_FOR_GRIDS, onGeneratePointsForGridsHandler);
			m_pictureView.addEventListener(MoveAnchorPointEvent.MOVE_ANCHOR_POINT, onMoveAnchorPointHandler);
			m_pictureView.addEventListener(MoveAnchorPointEvent.CONFIRM_ANCHOR_POINT, onMoveAnchorPointHandler);
			m_messageView.addEventListener(ChangeRowAndColEvent.CHANGE_ROW_AND_COL, onChangeRowAndColHandler);
			m_messageView.addEventListener(ChangeDivideValueEvent.CHANGE_DIVIDE_VALUE, onChangeDivideValueHandler);
			m_messageView.addEventListener(ChangeAnchorModeEvent.CHANGE_ANCHOR_MODE, onChangeAnchorModeHandler);
			m_commandManager.addEventListener(OperationEvent.UNDO, onOperationHandler);
			m_commandManager.addEventListener(OperationEvent.REDO, onOperationHandler);
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 添加点事件
		 * @param	evt AddPointEvent 对象
		 * @author Zhenyu Yao
		 */
		private function onAddPointHandler(evt : AddPointEvent) : void
		{
			// 转化为 GL 坐标系
			var p : Point = evt.point;
			p.y *= -1;
			
			m_commandManager.addPoint(p, evt.row, evt.col);
			m_messageView.printData(m_commandManager.currentMetadata);
		}
		
		/**
		 * 添加图片事件
		 * @param	evt AddImageEvent 对象
		 * @author Zhenyu Yao
		 */
		private function onAddImageHandler(evt : AddImageEvent) : void
		{
			m_commandManager.addImage(evt.bitmapData);
			m_messageView.printData(m_commandManager.currentMetadata);
		}
		
		/**
		 * 生成点适应网格事件
		 * @param	evt GeneratePointsForGridsEvent 对象
		 * @author Zhenyu Yao
		 */
		private function onGeneratePointsForGridsHandler(evt : GeneratePointsForGridsEvent) : void
		{
			m_commandManager.addMetadata(evt.metadata);
			m_messageView.printData(m_commandManager.currentMetadata);
		}
		
		/**
		 * 移动锚点事件
		 * @param	evt MoveAnchorPointEvent 对象
		 * @author Zhenyu Yao
		 */
		private function onMoveAnchorPointHandler(evt : MoveAnchorPointEvent) : void
		{
			if (evt.type == MoveAnchorPointEvent.CONFIRM_ANCHOR_POINT) 
			{
				var data : Metadata = m_commandManager.currentMetadata.copy();
				m_commandManager.addMetadata(data);
			}
			
			m_commandManager.currentMetadata.anchorPoint = evt.anchorPoint;
			m_messageView.printData(m_commandManager.currentMetadata);
		}
		
		/**
		 * 改变行和列事件
		 * @param	evt ChangeRowAndColEvent 对象
		 * @author Zhenyu Yao
		 */
		private function onChangeRowAndColHandler(evt : ChangeRowAndColEvent) : void
		{
			if (m_pictureView.picture != null)
			{
				m_pictureView.resetRowAndCol(evt.row, evt.col);
				m_commandManager.realign(evt.row, evt.col);
				m_messageView.printData(m_commandManager.currentMetadata);
			}
		}
		
		/**
		 * 改变除值事件
		 * @param	evt ChangeDivideValueEvent 对象
		 * @author Zhenyu Yao
		 */
		private function onChangeDivideValueHandler(evt : ChangeDivideValueEvent) : void
		{
			if (m_commandManager.currentMetadata != null)
			{
				m_messageView.printData(m_commandManager.currentMetadata);
			}
		}
		
		/**
		 * 改变 AnchorMode 事件
		 * @param	evt ChangeAnchorModeEvent 对象
		 * @author Zhenyu Yao
		 */
		private function onChangeAnchorModeHandler(evt : ChangeAnchorModeEvent) : void
		{
			if (m_pictureView.container != null) 
			{
				m_pictureView.anchorSprite.visible = evt.anchorMode;
				m_commandManager.currentMetadata.anchorMode = evt.anchorMode;
			
				m_pictureView.updateAnchorPoint(m_commandManager.currentMetadata);
				m_messageView.printData(m_commandManager.currentMetadata);
			}
		}
		
		/**
		 * 操作处理事件
		 * @param	evt OperationEvent 对象
		 * @author Zhenyu Yao
		 */
		private function onOperationHandler(evt : OperationEvent) : void
		{
			m_pictureView.redraw(evt.metadata);
			m_messageView.printData(evt.metadata);
		}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private vars
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		private var m_pictureView : PictureView = null;
		private var m_messageView : PrintMessageView = null;
		private var m_commandManager : CommandManager = null;

	}

}