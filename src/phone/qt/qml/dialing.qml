import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window{
	id: phone 
	height: Screen.height
	maximumHeight: Screen.height
	minimumHeight: Screen.height
	width: 480 
	minimumWidth: 480
	maximumWidth: 480
	title: "Calling"
	visible: true
		
	function getNumber(){
		call_number.text +=  window.getNumber()
	}

	Rectangle{
		id: call_info
		color: "blue"
		border.color: "black"
		border.width: 5
		anchors{
			top: parent.top
		}
		height: Screen.height / 2
		width: 480

		Text {
			id: call_number
			objectName: "call_number"
			color: "#fbf1c7"
			text: ""
		}
	}
}
