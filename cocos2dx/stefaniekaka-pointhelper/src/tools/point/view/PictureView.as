package tools.point.view 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObject;
	import flash.display.Loader;
	import flash.display.LoaderInfo;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.NativeDragEvent;
	import flash.filesystem.File;
	import flash.geom.Point;
	import flash.events.MouseEvent;
	import flash.geom.Rectangle;
	import flash.net.URLRequest;
	import flash.desktop.ClipboardFormats;
	import flash.desktop.NativeDragManager;
	
	import tools.point.events.AddImageEvent;
	import tools.point.events.GeneratePointsForGridsEvent;
	import tools.point.events.AddPointEvent;
	import tools.point.events.MoveAnchorPointEvent;
	import tools.point.utils.Metadata;
	import tools.point.utils.WindowDefaultOptions;
	
	/**
	 * 图片视图
	 * @author Zhenyu Yao
	 */
	public final class PictureView extends Sprite 
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Properties
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 编辑模式
		 * @author Zhenyu Yao
		 */
		public function get editMode() : Boolean
		{
			return m_editMode;
		}
		
		public function set editMode(value : Boolean) : void
		{
			m_editMode = value;
		}
		
		/**
		 * 装载图片资源的容器
		 * @author Zhenyu Yao
		 */
		public function get container() : DisplayObject
		{
			return m_container;
		}
		
		/**
		 * 显示的图片
		 * @author Zhenyu Yao
		 */
		public function get picture() : Bitmap
		{
			return m_picture;
		}
		
		/**
		 * 锚点显示对象
		 * @author Zhenyu Yao
		 */
		public function get anchorSprite() : AnchorPointSprite
		{
			return m_anchorSprite;
		}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @author Zhenyu Yao
		 */
		public function PictureView() 
		{
			m_background = new Sprite();
			m_background.graphics.beginFill(0xbfbfbf);
			m_frameSize = WindowDefaultOptions.defaultWindowSize;
			m_frameSize.y *= 0.5;
			m_background.graphics.drawRect(0, 0, m_frameSize.x, m_frameSize.y);
			m_background.graphics.endFill();
			this.addChild(m_background);
			
			var mask : Shape = new Shape();
			mask.graphics.beginFill(0);
			mask.graphics.drawRect(0, 0, m_frameSize.x, m_frameSize.y);
			mask.graphics.endFill();
			this.addChild(mask);
			this.mask = mask;
			
			this.addEventListener(Event.ADDED_TO_STAGE, onAddedToStageHandler);
		}
		
		/**
		 * 添加图片
		 * @param	bitmap 图片显示对象
		 * @author Zhenyu Yao
		 */
		public function addImage(bitmap : Bitmap) : void
		{
			addImageToContainer(bitmap);
			var evt : AddImageEvent = new AddImageEvent(AddImageEvent.ADD_IMAGE, bitmap.bitmapData);
			this.dispatchEvent(evt);
		}
		
		/**
		 * 重新设置行和列, 在运行此函数前, 必须保证添加了图片
		 * @param	row 行的数量
		 * @param	col 列的数量
		 * @author Zhenyu Yao
		 */
		public function resetRowAndCol(row : int, col : int) : void
		{
			for each (var cols : Vector.<CellSprite> in m_cellContainers)
			{
				for each (var cell : CellSprite in cols)
				{
					if (m_container.contains(cell))
					{
						m_container.removeChild(cell);
					}
				}
			}
			
			var w : Number = m_picture.bitmapData.width / col;
			var h : Number = m_picture.bitmapData.height / row;
			m_cellWidth = w;
			m_cellHeight = h;
			
			m_cellContainers = new Vector.<Vector.<CellSprite>>(row, true);
			for (var i : int = 0; i < row; ++i)
			{
				m_cellContainers[i] = new Vector.<CellSprite>(col, true);
				for (var j : int = 0; j < col; ++j)
				{
					var cellX : Number = j * w + w * 0.5 - m_picture.bitmapData.width * 0.5;
					var cellY : Number = i * h + h * 0.5 - m_picture.bitmapData.height * 0.5;
					m_cellContainers[i][j] = new CellSprite(cellX, cellY, w, h);
					m_container.addChild(m_cellContainers[i][j]);
				}
			}
		}
		
		/**
		 * 添加点到指定的格子中
		 * @param	p 添加的点
		 * @param	row 行
		 * @param	col 列
		 * @author Zhenyu Yao
		 */
		public function addPoint(p : Point, row : int, col : int) : void
		{
			addPointToCell(p, row, col);
			var addPointEvt : AddPointEvent = new AddPointEvent(AddPointEvent.ADD_POINT, p, row, col);
			this.dispatchEvent(addPointEvt);
		}
		
		/**
		 * 根据元数据重新分配图片与网格
		 * @param	data 元数据
		 * @author Zhenyu Yao
		 */
		public function redraw(data : Metadata) : void
		{
			addImageToContainer(new Bitmap(data.bitmapData));
			resetRowAndCol(data.rows, data.cols);
			
			for (var i : int = 0; i < data.rows; ++i)
			{
				for (var j : int = 0; j < data.cols; ++j)
				{
					var points : Vector.<Point> = data.getPoints(i, j);
					for each (var p : Point in points)
					{
						// 转化为屏幕坐标系
						addPointToCell(new Point(p.x, -p.y), i, j);
					}
				}
			}
			
			updateAnchorPoint(data);
		}
		
		/**
		 * 更新锚点的位置
		 * @param	data 原数据
		 * @author Zhenyu Yao
		 */
		public function updateAnchorPoint(data : Metadata) : void
		{
			m_anchorSprite.visible = data.anchorMode;
			if (data.anchorMode)
			{
				m_anchorSprite.x = m_picture.x + data.anchorPoint.x * data.bitmapData.width;
				m_anchorSprite.y = m_picture.y + data.bitmapData.height - data.anchorPoint.y * data.bitmapData.height;
			}
		}
		
		/**
		 * 生成适应于网格的点, 清空原来的点
		 * @author Zhenyu Yao
		 */
		public function generatePointsForGrids() : void
		{
			var rows : int = m_cellContainers.length;
			var cols : int = m_cellContainers[0].length;
			
			var metadata : Metadata = new Metadata();
			metadata.bitmapData = m_picture.bitmapData;
			metadata.reset(rows, cols);
			
			// 清空已经存在的点
			resetRowAndCol(rows, cols);
			
			// 添加适应网格的点
			for (var i : int = 0; i < rows; ++i)
			{
				for (var j : int = 0; j < cols; ++j)
				{
					// 左上
					var lt : Point = new Point(-m_cellWidth * 0.5, -m_cellHeight * 0.5);
					// 左下
					var lb : Point = new Point(-m_cellWidth * 0.5, m_cellHeight * 0.5);
					// 右下
					var rb : Point = new Point(m_cellWidth * 0.5, m_cellHeight * 0.5);
					// 右上
					var rt : Point = new Point(m_cellWidth * 0.5, -m_cellHeight * 0.5);
					
					addPointToCell(lt, i, j);
					addPointToCell(lb, i, j);
					addPointToCell(rb, i, j);
					addPointToCell(rt, i, j);
					
					// 转化为 GL 坐标系
					lt.y *= -1;
					lb.y *= -1;
					rb.y *= -1;
					rt.y *= -1;
					
					metadata.push(lt, i, j);
					metadata.push(lb, i, j);
					metadata.push(rb, i, j);
					metadata.push(rt, i, j);
				}
			}
			
			var evt : GeneratePointsForGridsEvent = new GeneratePointsForGridsEvent(GeneratePointsForGridsEvent.GENERATE_POINTS_FOR_GRIDS, metadata);
			this.dispatchEvent(evt);
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 被添加到舞台事件
		 * @param	evt Event 对象
		 * @author Zhenyu Yao
		 */
		private function onAddedToStageHandler(evt : Event) : void
		{
			this.stage.addEventListener(NativeDragEvent.NATIVE_DRAG_ENTER, onNativeDragEnterHandler);
			this.stage.addEventListener(NativeDragEvent.NATIVE_DRAG_DROP, onNativeDragDropHandler);
		}
		
		/**
		 * 文件拖入事件
		 * @param	evt NativeDragEvent 对象 
		 * @author Zhenyu Yao
		 */
		private function onNativeDragEnterHandler(evt : NativeDragEvent) : void
		{
			if (m_picture == null)
			{
				var files : Array = evt.clipboard.getData(ClipboardFormats.FILE_LIST_FORMAT) as Array;
				if (checkImageFile(files))
				{
					NativeDragManager.acceptDragDrop(this);
				}
			}
		}
		
		/**
		 * 放下拖入文件事件
		 * @param	evt NativeDragEvent 对象
		 * @author Zhenyu Yao
		 */
		private function onNativeDragDropHandler(evt : NativeDragEvent) : void
		{
			var files : Array = evt.clipboard.getData(ClipboardFormats.FILE_LIST_FORMAT) as Array;
			if (checkImageFile(files))
			{
				var file : File = files[0];
				
				var ldr : Loader = new Loader();
				ldr.contentLoaderInfo.addEventListener(Event.COMPLETE, onCompleteHandler);
				ldr.load(new URLRequest(file.url));
			}
		}
		
		/**
		 * 图片装载完成事件
		 * @param	evt Event 对象
		 * @author Zhenyu Yao
		 */
		private function onCompleteHandler(evt : Event) : void
		{
			var ldrInfo : LoaderInfo = evt.target as LoaderInfo;
			addImage(ldrInfo.content as Bitmap);
		}

		/**
		 * 在装载图片的容器内单机鼠标事件
		 * @param	evt 鼠标事件
		 * @author Zhenyu Yao
		 */
		private function onMouseClickHandler(evt : MouseEvent) : void
		{
			if (!m_editMode || m_container == null)
			{
				return;
			}
			
			// 首先计算出, 点击位置的所属网格
			var local : Point = new Point(evt.localX, evt.localY);
			var row : int = (local.y - m_picture.y) / m_cellHeight;
			var col : int = (local.x - m_picture.x) / m_cellWidth;
			
			if (row >= m_cellContainers.length || col >= m_cellContainers[0].length)
			{
				return;
			}
			
			// 得到当前点击所属网格的中心点
			var cellSprite : CellSprite = m_cellContainers[row][col];
			var localCenter : Point = new Point(cellSprite.x, cellSprite.y);
			var pointInCell : Point = new Point(local.x - localCenter.x, local.y - localCenter.y);
			
			addPoint(pointInCell, row, col);
		}
		
		/**
		 * 装载图片的容器内鼠标按下事件
		 * @param	evt 鼠标事件对象
		 * @author Zhenyu Yao
		 */
		private function onMouseDownHandler(evt : MouseEvent) : void
		{
			if (!m_editMode && m_container != null)
			{
				if (!m_anchorSprite.visible)
				{
					m_container.startDrag(false);
				}
				else
				{
					var rect : Rectangle = m_anchorSprite.getRect(m_anchorSprite);
					if (rect.contains(m_anchorSprite.mouseX, m_anchorSprite.mouseY))
					{
						m_anchorSprite.startDrag(false, m_picture.getRect(m_container));
						
						var anchorPoint : Point = calculateAnchorPoint();
						var tmpEvt : MoveAnchorPointEvent = new MoveAnchorPointEvent(MoveAnchorPointEvent.CONFIRM_ANCHOR_POINT, anchorPoint); 
						this.dispatchEvent(tmpEvt);
					}
				}
			}
		}
		
		/**
		 * 鼠标抬起事件
		 * @param	evt MouseEvent 对象
		 * @author Zhenyu Yao
		 */
		private function onMouseUpHandler(evt : MouseEvent) : void
		{
			m_container.stopDrag();
			m_anchorSprite.stopDrag();
		}
		
		/**
		 * 每一帧更新
		 * @param	evt Event 对象
		 * @author Zhenyu Yao
		 */
		private function onEnterFrameHandler(evt : Event) : void
		{
			if (m_anchorSprite != null && m_anchorSprite.moving)
			{
				var mousePosition : Point = new Point(m_container.mouseX, m_container.mouseY);
				var edge : uint = 0;
				
				if (mousePosition.x < m_picture.x)
				{
					mousePosition.x = m_picture.x;
					edge = 0x01;
				}
				else if (mousePosition.x > m_picture.x + m_picture.bitmapData.width)
				{
					mousePosition.x = m_picture.x + m_picture.bitmapData.width;
					edge = 0x01;
				}
				
				if (mousePosition.y < m_picture.y)
				{
					mousePosition.y = m_picture.y;
					edge |= 0x02;
				}
				else if (mousePosition.y > m_picture.y + m_picture.bitmapData.height)
				{
					mousePosition.y = m_picture.y + m_picture.bitmapData.height;
					edge |= 0x02;
				}
				
				if (edge == 0x03)
				{
					m_anchorSprite.stopDrag();
					m_anchorSprite.x = mousePosition.x;
					m_anchorSprite.y = mousePosition.y;
				}
				
				var anchorPoint : Point = calculateAnchorPoint();
				var tmpEvt : MoveAnchorPointEvent = new MoveAnchorPointEvent(MoveAnchorPointEvent.MOVE_ANCHOR_POINT, anchorPoint);
				this.dispatchEvent(tmpEvt);
			}
		}
		
		/**
		 * 向网格中添加点
		 * @param	p 添加的点
		 * @param	row 指定的行
		 * @param	col 指定的列
		 * @author Zhenyu Yao
		 */
		private function addPointToCell(p : Point, row : int, col : int) : void
		{
			var cell : CellSprite = m_cellContainers[row][col];
			cell.addPoint(p.x, p.y);
		}
		
		/**
		 * 添加图片到容器中
		 * @param	bitmap 添加的图片
		 * @author Zhenyu Yao
		 */
		private function addImageToContainer(bitmap : Bitmap) : void
		{
			if (m_container != null)
			{
				this.removeChild(m_container);
			}
			
			m_picture = bitmap;
			m_picture.x = -m_picture.bitmapData.width * 0.5;
			m_picture.y = -m_picture.bitmapData.height * 0.5;
			
			m_container = new Sprite();
			m_container.addChild(m_picture);
			m_container.x = m_frameSize.x * 0.5;
			m_container.y = m_frameSize.y * 0.5;
			this.addChild(m_container);
			m_container.addEventListener(MouseEvent.CLICK, onMouseClickHandler);
			m_container.addEventListener(MouseEvent.MOUSE_DOWN, onMouseDownHandler);
			m_container.addEventListener(MouseEvent.MOUSE_UP, onMouseUpHandler);
			m_container.addEventListener(Event.ENTER_FRAME, onEnterFrameHandler);
			
			resetRowAndCol(1, 1);
			
			m_anchorSprite = new AnchorPointSprite();
			m_anchorSprite.visible = false;
			m_container.addChild(m_anchorSprite);
		}

		/**
		 * 检测是否包含图像文件
		 * @param	files 拖入的所有文件
		 * @return 包含返回 true, 否则返回 false
		 * @author Zhenyu Yao
		 */
		private function checkImageFile(files : Array) : Boolean
		{
			var file : File = files[0];
			if (file.extension.indexOf("png".toLowerCase()) != -1
				|| file.extension.indexOf("jpg".toLowerCase()) != -1
				|| file.extension.indexOf("jpeg".toLowerCase()) != -1
				|| file.extension.indexOf("gif".toLowerCase()) != -1)
			{
				return true;
			}
			
			return false;
		}
		
		/**
		 * 计算锚点
		 * @return Point 对象
		 * @author Zhenyu Yao
		 */
		private function calculateAnchorPoint() : Point
		{
			var anchorPoint : Point = new Point(int(m_anchorSprite.x - m_picture.x) / m_picture.bitmapData.width, 
												int(m_anchorSprite.y - m_picture.y) / m_picture.bitmapData.height);
			anchorPoint.y = 1.0 - anchorPoint.y;
			return anchorPoint;
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private vars
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		private var m_frameSize : Point = null;
		private var m_background : Sprite = null;
		private var m_container : Sprite = null;
		private var m_picture : Bitmap = null;
		private var m_cellWidth : Number = 0.0;
		private var m_cellHeight : Number = 0.0;
		private var m_cellContainers : Vector.<Vector.<CellSprite>> = null;
		private var m_editMode : Boolean = false;
		private var m_anchorSprite : AnchorPointSprite = null;
	}

}