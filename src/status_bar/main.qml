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
	color: "#1d2021"

	Text {
	    id: operator
	    objectName: "operator"
        font.pixelSize: 15 
        color: "#ffffff"
        wrapMode: Text.WrapAnywhere
		anchors{
			left: parent.left
			leftMargin: 20 
			horizontalCenter: parent.HorizontalCenter
			verticalCenter: parent.verticalCenter
		}
	}

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
			rightMargin: 20
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

	function getOperatorName(){
		status.getOperatorName()
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
