import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window{
	id: satatus_bar 
	height: 30
	maximumHeight: 30
	minimumHeight: 30
	width: Screen.width
	maximumWidth: Screen.width 
	minimumWidth: Screen.width
 	visible: true
	color: "#cc241d"

	MouseArea {
		id: status
		objectName: "status"
		anchors.fill: parent
		onPressed: status_text.color = "#000000"
		onClicked: status_text.text = exec()
		onReleased: status_text.color = "#ffffff"

		Text {
		    id: status_text
		    objectName: "status_text"
		    text: ""
            font.pixelSize: 20 
            color: "#ffffff"
            wrapMode: Text.WrapAnywhere
			x: parent.width / 2 - parent.width / 8
		}
	}

	function exec(){
	    return window.execCom();
    }
}
