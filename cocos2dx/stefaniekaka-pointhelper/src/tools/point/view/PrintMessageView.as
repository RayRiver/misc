package tools.point.view 
{
	import fl.controls.CheckBox;
	import flash.display.Sprite;
	import flash.events.Event;
	import fl.controls.TextInput;
	import fl.controls.Label;
	import fl.controls.ComboBox;
	import fl.controls.TextArea;
	import flash.geom.Point;
	import tools.point.events.ChangeAnchorModeEvent;
	import tools.point.events.ChangeDivideValueEvent;
	import tools.point.events.ChangeRowAndColEvent;
	import tools.point.utils.Metadata;
	
	/**
	 * 打印信息窗口
	 * @author Zhenyu Yao
	 */
	public final class PrintMessageView extends Sprite 
	{

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		 * 构造函数
		 * @author Zhenyu Yao
		 */
		public function PrintMessageView() 
		{
			// Row
			m_label1 = new Label();
			m_label1.text = "Row:";
			this.addChild(m_label1);
			
			m_txtRow = new TextInput();
			m_txtRow.restrict = "0123456789";
			m_txtRow.text = "1";
			m_txtRow.x = 32;
			m_txtRow.width = 50;
			m_txtRow.addEventListener(Event.CHANGE, onRowOrColValueChangeHandler);
			this.addChild(m_txtRow);
			
			// Col
			m_label2 = new Label();
			m_label2.text = "Col:";
			m_label2.x = 85;
			this.addChild(m_label2);
			
			m_txtCol = new TextInput();
			m_txtCol.restrict = "0123456789";
			m_txtCol.text = "1";
			m_txtCol.x = 112;
			m_txtCol.width = 50;
			m_txtCol.addEventListener(Event.CHANGE, onRowOrColValueChangeHandler);
			this.addChild(m_txtCol);
			
			// Anchor Point CheckBox
			m_anchorModeCheckBox = new CheckBox();
			m_anchorModeCheckBox.label = "Anchor Mode";
			m_anchorModeCheckBox.selected = false;
			m_anchorModeCheckBox.x = 0;
			m_anchorModeCheckBox.y = 28;
			m_anchorModeCheckBox.addEventListener(Event.CHANGE, onAnchorModeChangeHandler);
			this.addChild(m_anchorModeCheckBox);
			
			// Print type combobox
			var lblPrintType : Label = new Label();
			lblPrintType.text = "PrintType:";
			lblPrintType.y = 56;
			this.addChild(lblPrintType);
			
			m_comboBoxPrintType = new ComboBox();
			m_comboBoxPrintType.addItem({label: "Coordinate"});
			m_comboBoxPrintType.addItem({label: "Divide Value"});
			m_comboBoxPrintType.x = 60;
			m_comboBoxPrintType.y = 56;
			m_comboBoxPrintType.addEventListener(Event.CHANGE, onComboBoxPrintTypeChangeHandler);
			this.addChild(m_comboBoxPrintType);
			
			// Divide value
			m_valueContainer = new Sprite();
			m_valueContainer.y = 84;
			this.addChild(m_valueContainer);
			
			var lblDivideValue : Label = new Label();
			lblDivideValue.text = "Divide value:";
			m_valueContainer.addChild(lblDivideValue);
			
			m_txtDivideValue = new TextInput();
			m_txtDivideValue.restrict = "0123456789.";
			m_txtDivideValue.text = "1";
			m_txtDivideValue.x = 80;
			m_valueContainer.addEventListener(Event.CHANGE, onDivideValueChangeHandler);
			m_valueContainer.addChild(m_txtDivideValue);
			m_valueContainer.visible = false;
			
			// Message area
			m_txtMessage = new TextArea();
			m_txtMessage.width = 800;
			m_txtMessage.height = 268;
			m_txtMessage.x = 180;
			m_txtMessage.editable = false;
			this.addChild(m_txtMessage); 
		}
		
		/**
		 * 打印输出数据
		 * @param	data 元数据
		 * @author Zhenyu Yao
		 */
		public function printData(data : Metadata) : void
		{
			if (m_anchorModeCheckBox.selected != data.anchorMode)
			{
				m_anchorModeCheckBox.selected = data.anchorMode;
			}
			
			if (data.anchorMode) 
			{
				m_label1.text = "AX:";
				m_label2.text = "AY:";
				m_txtCol.editable = false;
				m_txtRow.editable = false;
				m_txtCol.text = data.anchorPoint.y.toString();
				m_txtRow.text = data.anchorPoint.x.toString();
			}
			else 
			{
				m_label1.text = "Row:";
				m_label2.text = "Col:";
				m_txtCol.editable = true;
				m_txtRow.editable = true;
				m_txtCol.text = data.cols.toString();
				m_txtRow.text = data.rows.toString();
			}
			
			m_txtMessage.text = "{\n";
			var rows : int = data.rows;
			var cols : int = data.cols;
			var divideValue : Number = parseFloat(m_txtDivideValue.text);
			var anchor : Point = new Point(data.anchorPoint.x * data.bitmapData.width, data.anchorPoint.y * data.bitmapData.height);
			var center : Point = new Point(data.bitmapData.width * 0.5, data.bitmapData.height * 0.5);
			var offset : Point = new Point(anchor.x - center.x, anchor.y - center.y);
			
			for (var i : int = 0; i < rows; ++i)
			{
				for (var j : int = 0; j < cols; ++j)
				{
					//m_txtMessage.appendText("\t[" + i + "][" + j + "]\n");
					//m_txtMessage.appendText("\t{\n");
					
					var points : Vector.<Point> = data.getPoints(i, j);

					var count : int = 0;
					for each (var _p : Point in points)
					{
						count = count + 1;
					}

					var t : String = null;
					t = "\t\"num\": " + count + ",\n";
					m_txtMessage.appendText(t);

					m_txtMessage.appendText("\t\"vertexes\": [\n");

					var index : int = 0
					for each (var p : Point in points)
					{
						m_txtMessage.appendText("\t\t");
						
						var tmp : String = null;
						var tmpPoint : Point = null;
						if (data.anchorMode)
						{
							tmpPoint = new Point(p.x - offset.x, p.y - offset.y);
						}
						else
						{
							tmpPoint = new Point(p.x, p.y);
						}
						//tmp = "{" + tmpPoint.x / divideValue + ", " + tmpPoint.y / divideValue + "},\n";
						tmp = "{ \"x\": " + tmpPoint.x / divideValue + ", \"y\": " + tmpPoint.y / divideValue;
						if (index == count-1)
						{
							tmp = tmp + " }\n";
						}
						else
						{
							tmp = tmp + " },\n";
						}
						m_txtMessage.appendText(tmp);
						
						index = index + 1
					}
					m_txtMessage.appendText("\t]\n");
					//m_txtMessage.appendText("\t}\n");
				}
				
				if (i != rows - 1)
				{
					m_txtMessage.appendText("<-------------------------------------------- [行]分割线 -------------------------------------------->\n");
				}
			}
			m_txtMessage.appendText("}\n");
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////	
		
		/**
		 * 行或列的文本框文本改变事件
		 * @param	evt 事件对象
		 * @author Zhenyu Yao
		 */
		private function onRowOrColValueChangeHandler(evt : Event) : void
		{
			checkTextInput(m_txtRow);
			checkTextInput(m_txtCol);
			
			var row : int = parseInt(m_txtRow.text);
			var col : int = parseInt(m_txtCol.text);
			
			var changeRowAndColEvent : ChangeRowAndColEvent = new ChangeRowAndColEvent(ChangeRowAndColEvent.CHANGE_ROW_AND_COL, row, col);
			this.dispatchEvent(changeRowAndColEvent);
		}
		
		/**
		 * 输出类型的组合框选项改变事件
		 * @param	evt 事件对象
		 * @author Zhenyu Yao
		 */
		private function onComboBoxPrintTypeChangeHandler(evt : Event) : void
		{
			m_valueContainer.visible = m_comboBoxPrintType.selectedIndex > 0;
			m_txtDivideValue.text = "1";
			
			var divideValue : Number = parseFloat(m_txtDivideValue.text);
			var changeDivideValueEvt : ChangeDivideValueEvent = new ChangeDivideValueEvent(ChangeDivideValueEvent.CHANGE_DIVIDE_VALUE, divideValue);
			this.dispatchEvent(changeDivideValueEvt);
		}
		
		/**
		 * 除值的文本框文本改变事件
		 * @param	evt 事件对象
		 * @author Zhenyu Yao
		 */
		private function onDivideValueChangeHandler(evt : Event) : void
		{
			checkTextInput(m_txtDivideValue);
			
			var divideValue : Number = parseFloat(m_txtDivideValue.text);
			var changeDivideValueEvt : ChangeDivideValueEvent = new ChangeDivideValueEvent(ChangeDivideValueEvent.CHANGE_DIVIDE_VALUE, divideValue);
			this.dispatchEvent(changeDivideValueEvt);
		}
		
		/**
		 * Anchor Mode CheckBox 改变事件
		 * @param	evt 事件对象
		 * @author Zhenyu Yao
		 */
		private function onAnchorModeChangeHandler(evt : Event) : void
		{
			var anchorMode : Boolean = m_anchorModeCheckBox.selected;
			evt = new ChangeAnchorModeEvent(ChangeAnchorModeEvent.CHANGE_ANCHOR_MODE, anchorMode);
			this.dispatchEvent(evt);
		}
		
		/**
		 * 检测输入框的操作
		 * @param	txtInput 输入框对象
		 * @author Zhenyu Yao
		 */
		private function checkTextInput(txtInput : TextInput) : void
		{
			if (txtInput.text == ""
				|| txtInput.text.charAt(0) == "0"
				|| txtInput.text.charAt(0) == ".")
			{
				txtInput.text = "1";
			}
		}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private vars
////////////////////////////////////////////////////////////////////////////////////////////////////
		
		private var m_label1 : Label = null;
		private var m_label2 : Label = null;
		private var m_txtRow : TextInput = null;
		private var m_txtCol : TextInput = null;
		private var m_txtDivideValue: TextInput = null;
		private var m_comboBoxPrintType : ComboBox = null;
		private var m_valueContainer : Sprite = null;
		private var m_txtMessage : TextArea = null;
		private var m_anchorModeCheckBox : CheckBox = null;
	}

}