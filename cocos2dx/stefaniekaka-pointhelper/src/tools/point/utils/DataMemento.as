package tools.point.utils 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Loader;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.utils.ByteArray;
	import mx.utils.StringUtil;
	
	/**
	 * 数据备忘录, 负责 Metadata 与 String 对象的相互转化 
	 * @author Zhenyu Yao
	 */
	public final class DataMemento 
	{
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @author Zhenyu Yao
		 */
		public function DataMemento() 
		{
		}
		
		/**
		 * 从以 XML 格式的字符串获得 Metadata对象
		 * @param	strXML XML格式的字符串
		 * @return Metadata 对象
		 * @author Zhenyu Yao
		 */
		public function dataFromString(strXML : String) : Metadata
		{
			// 得到行/列数据
			var data : Metadata = new Metadata();
			var xml : XML = new XML(strXML);
			var dataXML : XML = xml.Metadata[0];
			data.reset(dataXML.@row, dataXML.@col);
			
			// 读取图片数据
			var strContent : String = dataXML.Content[0];
			var bytes : ByteArray = Base64.decodeToByteArray(strContent);
			bytes.uncompress();
			var bitmapData : BitmapData = new BitmapData(bytes.readUnsignedInt(), bytes.readUnsignedInt(), true, 0);
			bitmapData.setPixels(new Rectangle(0, 0, bitmapData.width, bitmapData.height), bytes);
			data.bitmapData = bitmapData;
			
			// 读取锚点数据
			if (dataXML.AnchorPoint[0] != null)
			{
				data.anchorPoint = new Point(dataXML.AnchorPoint[0].@x, dataXML.AnchorPoint[0].@y);
				if (dataXML.AnchorPoint[0].@mode != null)
				{
					data.anchorMode = dataXML.AnchorPoint[0].@mode == "true";
				}
			}
			else
			{
				data.anchorPoint = new Point(0.5, 0.5);
			}
			
			// 读取列中点的数据
			var rows : int = data.rows;
			var cols : int = data.cols;
			for (var i : int = 0; i < rows; ++i)
			{
				for (var j : int = 0; j < cols; ++j)
				{
					var rowXML : XML = dataXML.Row[i];
					var colXML : XML = rowXML.Col[j];
					var pointsXML : XMLList = colXML.Point;
					for each (var p : XML in pointsXML)
					{
						data.push(new Point(p.@x, p.@y), i, j);
					}
				}
			}
			
			return data;
		}
		
		/**
		 * 将 Metadata 对象转化为 XML 格式的字符串
		 * @param	data Metadata 对象
		 * @return 转化的XML格式字符串
		 * @author Zhenyu Yao
		 */
		public function stringFromData(data : Metadata) : String
		{
			// 存储行/列数据
			var xml : XML = 
			<root>
				<Metadata row={data.rows} col={data.cols}>
				</Metadata>
			</root>;
			
			// 保存图片数据
			var dataXML : XMLList = xml.Metadata;
			var strContent : String = "<Content>{0}</Content>\n";
			var bytes : ByteArray = new ByteArray();
			bytes.writeUnsignedInt(data.bitmapData.width);
			bytes.writeUnsignedInt(data.bitmapData.height);
			bytes.writeBytes(data.bitmapData.getPixels(new Rectangle(0, 0, data.bitmapData.width, data.bitmapData.height)));
			bytes.compress();
			var encodeString : String = Base64.encodeByteArray(bytes);
			strContent = StringUtil.substitute(strContent, encodeString);
			dataXML.appendChild(new XML(strContent));
			
			// 保存锚点信息
			var strAnchorPoint : String = "<AnchorPoint x=\"{0}\" y=\"{1}\" mode=\"{2}\"/>\n";
			strAnchorPoint = StringUtil.substitute(strAnchorPoint, data.anchorPoint.x, data.anchorPoint.y, data.anchorMode);
			dataXML.appendChild(new XML(strAnchorPoint));
			
			// 装入行/列数据
			for (var i : int = 0; i < data.rows; ++i)
			{
				var strRow : String = "<Row>{0}</Row>";
				var strCols : String = "";
				for (var j : int = 0; j < data.cols; ++j)
				{
					var strCol : String = "<Col>{0}</Col>\n";
					var strPoints : String = "";
					var points : Vector.<Point> = data.getPoints(i, j);
					for each (var p : Point in points)
					{
						var strPoint : String = "<Point x=\"{0}\" y=\"{1}\"/>\n";
						strPoint = StringUtil.substitute(strPoint, p.x, p.y);
						strPoints += strPoint;
					}
					
					strCol = StringUtil.substitute(strCol, strPoints);
					strCols += strCol;
				}
				
				strRow = StringUtil.substitute(strRow, strCols);
				dataXML.appendChild(new XML(strRow));
			}
			
			return xml.toXMLString();
		}
		
		/**
		 * 将二进制数据转换成 Metadata 对象
		 * @param	bytes 二进制数据对象
		 * @return Metadata 对象
		 * @author Zhenyu Yao
		 */
		public function dataFromBytes(bytes : ByteArray) : Metadata
		{
			var txt : String = bytes.readUTFBytes(bytes.bytesAvailable);
			return dataFromString(txt);
		}
		
		/**
		 * 将 Metadata 对象转换成二进制数据
		 * @param	data Metadata 对象
		 * @return 二进制数据对象
		 * @author Zhenyu Yao
		 */
		public function bytesFromData(data : Metadata) : ByteArray
		{
			var txt : String = stringFromData(data);
			var bytes : ByteArray = new ByteArray();
			bytes.writeUTFBytes(txt);
			return bytes;
		}
		
	}

}