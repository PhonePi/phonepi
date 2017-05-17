import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.4

Window{
	id: satatus_bar 
	height: 30
	maximumHeight: 30
	minimumHeight: 30
	width: 480 
	minimumWidth: 480
	maximumWidth: 480
	visible: true
	color: "#cc241d"

	MouseArea {
		id: status
		objectName: "status"
		width: 120
		height: 25
		anchors {
			left: parent.left
			leftMargin: 180
			top: parent.top
			topMargin: 2
		}
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
            anchors.fill: parent
		}
	}

	function exec(){
	    return window.execCom();
    }
}
