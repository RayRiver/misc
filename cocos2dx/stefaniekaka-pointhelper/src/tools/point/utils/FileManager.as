package tools.point.utils 
{
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.events.InvokeEvent;
	import flash.filesystem.File;
	import flash.filesystem.FileMode;
	import flash.filesystem.FileStream;
	import flash.net.FileFilter;
	import flash.net.URLLoader;
	import flash.net.URLRequest;
	import flash.utils.ByteArray;
	import flash.desktop.NativeApplication;
	import tools.point.events.LoadFileEvent;
	import tools.point.utils.Metadata;
	import tools.point.utils.DataMemento;
	
	/**
	 * 文件管理类
	 * @author Zhenyu Yao
	 */
	public final class FileManager extends EventDispatcher
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Properties
////////////////////////////////////////////////////////////////////////////////////////////////////

		/**
		 * 文件名
		 * @author Zhenyu Yao
		 */
		public function get defaultFile() : String
		{
			if (m_path == null)
			{
				return null;
			}
			
			var startIndex : int = m_path.lastIndexOf("\\");
			return m_path.substr(startIndex);
		}
		
		/**
		 * 默认存储路径
		 * @author Zhenyu Yao
		 */
		public function get defaultPath() : String
		{
			return m_path;
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @author Zhenyu Yao
		 */
		public function FileManager() 
		{
			NativeApplication.nativeApplication.addEventListener(InvokeEvent.INVOKE, onInvokeHandler);
		}
		
		/**
		 * 打开文件
		 * @author Zhenyu Yao
		 */
		public function open() : void
		{
			var file : File = new File();
			var filters : Array = new Array();
			filters.push(new FileFilter("Metadata", "*.cpt", "*.cpt"));
			file.browseForOpen("打开", filters);
			file.addEventListener(Event.SELECT, onOpenFileHandler);
		}
		
		/**
		 * 以默认路径存储文件
		 * @param	points 元数据
		 * @author Zhenyu Yao
		 */
		public function save(points : Metadata) : void
		{
			m_data = points;
			
			if (m_path == null)
			{
				saveAs(points);
			}
			else
			{
				saveFile();
			}
		}
		
		/**
		 * 文件另存为, 另存之后的路径为默认路径
		 * @param	points 元数据
		 * @author Zhenyu Yao
		 */
		public function saveAs(points : Metadata) : void
		{
			m_data = points;
			var file : File = new File();
			file.browseForSave("存储");
			file.addEventListener(Event.SELECT, onSaveFileHandler);
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 点击关联文件打开程序事件
		 * @param	evt InvokeEvent 事件
		 * @author Zhenyu Yao
		 */
		private function onInvokeHandler(evt : InvokeEvent) : void
		{
			if (evt.arguments.length != 0)
			{
				m_path = evt.arguments[0] as String;
				
				openFile();
			}
		}

		/**
		 * 打开文件事件
		 * @param	evt 事件对象
		 * @author Zhenyu Yao
		 */
		private function onOpenFileHandler(evt : Event) : void
		{
			var file : File = evt.target as File;
			m_path = checkPath(file.nativePath);
			
			openFile();
		}

		/**
		 * 存储文件事件
		 * @param	evt 事件对象
		 * @author Zhenyu Yao
		 */
		private function onSaveFileHandler(evt : Event) : void
		{
			var file : File = evt.target as File;
			m_path = checkPath(file.nativePath);
			
			saveFile();
		}
		
		/**
		 * 打开文件
		 * @author Zhenyu Yao
		 */
		private function openFile() : void
		{
			var file : File = new File(m_path);
			var fileStream : FileStream = new FileStream();
			fileStream.open(file, FileMode.READ);
			var bytes : ByteArray = new ByteArray();
			fileStream.readBytes(bytes);
			fileStream.close();
			
			var dataMemenote : DataMemento = new DataMemento();
			var metadata : Metadata = dataMemenote.dataFromBytes(bytes);
			this.dispatchEvent(new LoadFileEvent(LoadFileEvent.COMPLETE, metadata));
		}
		
		/**
		 * 存储文件
		 * @author Zhenyu Yao
		 */
		private function saveFile() : void
		{
			var file : File = new File(m_path);
			var fileStream : FileStream = new FileStream();
			fileStream.open(file, FileMode.WRITE);
			
			var dataMemente : DataMemento = new DataMemento();
			var bytes : ByteArray = dataMemente.bytesFromData(m_data);
			fileStream.writeBytes(bytes);
			fileStream.close();
		}
		
		/**
		 * 检测路径是否正确
		 * @param	path 待检测的路径
		 * @return 修正后的路径
		 * @author Zhenyu Yao
		 */
		private function checkPath(path : String) : String
		{
			if (path.lastIndexOf(".cpt") == -1)
			{
				return path + ".cpt";
			}
			
			return path;
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Vars
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		private var m_path : String = null;
		private var m_data : Metadata = null;
	}

}