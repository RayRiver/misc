package tools.point.mediator 
{
	import tools.point.utils.CommandManager;
	import tools.point.utils.FileManager;
	import tools.point.utils.Metadata;
	import tools.point.view.PictureView;
	import tools.point.view.PrintMessageView;
	import tools.point.events.LoadFileEvent;
	
	/**
	 * 文件, 视图, 命令中介者
	 * @author Zhenyu Yao
	 */
	public final class FileViewCommandMediator 
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @author Zhenyu Yao
		 */
		public function FileViewCommandMediator(fileManager : FileManager, pictureView : PictureView, messageView : PrintMessageView, commandManager : CommandManager) 
		{
			m_fileManager = fileManager;
			m_pictureView = pictureView;
			m_messageView = messageView;
			m_commandManager = commandManager;
			
			m_fileManager.addEventListener(LoadFileEvent.COMPLETE, onLoadFileCompleteHandler);
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 侦听装载文件成功事件
		 * @param	evt LoadFileEvent 对象
		 * @author Zhenyu Yao
		 */
		private function onLoadFileCompleteHandler(evt : LoadFileEvent) : void
		{
			var metadata : Metadata = evt.metadata;
			m_pictureView.redraw(metadata);
			m_messageView.printData(metadata);
			m_commandManager.addMetadata(metadata);
		}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Vars
////////////////////////////////////////////////////////////////////////////////////////////////////

		private var m_fileManager : FileManager = null;
		private var m_pictureView : PictureView = null;
		private var m_messageView : PrintMessageView = null;
		private var m_commandManager : CommandManager = null;

	}

}