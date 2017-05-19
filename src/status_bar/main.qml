import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window{
	id: satatus_bar 
	objectName: "status_bar"
	height: 30
	maximumHeight: 30
	minimumHeight: 30
	width: Screen.width
	maximumWidth: Screen.width 
	minimumWidth: Screen.width
 	visible: true
	color: "#cc241d"
	x: 0
	y: 0

	Text {
	    id: status_text
	    objectName: "status_text"
	    text:Qt.formatTime(new Date, "hh:mm:ss") 
        font.pixelSize: 20 
        color: "#ffffff"
        wrapMode: Text.WrapAnywhere
		x: parent.width / 2 - parent.width / 8
	}

	function date(){
		window.setValue()
	}

	Timer {
		interval: 1000
		running: true
		repeat: true
		onTriggered: date()
	}

}
