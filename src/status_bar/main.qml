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

	Text {
	    id: time
	    objectName: "time"
	    text:Qt.formatTime(new Date, "hh:mm:ss") 
        font.pixelSize: 20 
        color: "#ffffff"
        wrapMode: Text.WrapAnywhere
		anchors{
			left: parent.left
			leftMargin: parent.width / 2 - time.width
			horizontalCenter: parent.HorizontalCenter
			verticalCenter: parent.verticalCenter
		}
	}

	Text {
		id: battery
		objectName: "battery"
		font.pixelSize: 20 
		text: "batt"
		anchors {
			right: parent.right
			horizontalCenter: parent.HorizontalCenter
			verticalCenter: parent.verticalCenter
		}
	}

	function getTime(){
		status.getTime()
	}

	function getBatteryState(){
		status.getBatteryState()
	}

	Timer {
		interval: 10000
		running: true
		repeat: true
		onTriggered: getBatteryState()
	}

	Timer {
		interval: 1000
		running: true
		repeat: true
		onTriggered: getTime()
	}

}
