import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import "core"

Window{
	id: phone
	height: Screen.height
	maximumHeight: Screen.height
	minimumHeight: Screen.height
	width: 480 
	minimumWidth: 480
	maximumWidth: 480
	title: "Phone"
	visible: true

	Text {
		id: phoneNumber
		objectName: "number"
		text: ""
		font.pixelSize: 30
		width: 360
		height: 120
		wrapMode: Text.WrapAnywhere
		anchors {
			left: parent.left
			leftMargin: 10
			top: parent.top
			topMargin: 20
		}
	}

	Image {
		id: buttonDelete
		width: 70
		height: 70
   	    source: "qrc:///pics/erase.png"

   	    anchors{
			top: parent.top
			topMargin: 20
			left: phoneNumber.right
			leftMargin: 10
		}

   	    MouseArea{
   	    	anchors.fill: parent
   	   		onClicked: phoneNumber.text = phoneNumber.text.substr(0, phoneNumber.text.length-1)
   	   	}
   	}

	Rectangle {
		id: buttons
		width: parent.width
		height: 2 *  parent.height / 3
		color: "#fbf1c7"
		anchors{
			bottom: parent.bottom
		}
		
	Rectangle{
			id: table
			width: parent.width - parent.width * 0.07 * 2
			height: 206
			color: "#282828"
			
			anchors{
				top: parent.top
				left: parent.left
				leftMargin: parent.width * 0.07
				rightMargin: parent.width * 0.07
				topMargin: 50
			}

		Grid {
				id: numbers
				spacing: 2 
				columns: 3
				width: parent.width
				height: parent.height
				anchors{
					horizontalCenter: parent.horizontalCenter
					verticalCenter: parent.verticalCenter
				}

				Button {caption : "1"; width: parent.width/3 - 2 * numbers.spacing / 3; color: buttons.color}
				Button {caption : "2"; width: parent.width/3 - 2 * numbers.spacing / 3; color: buttons.color}
				Button {caption : "3"; width: parent.width/3 - 2 * numbers.spacing / 3; color: buttons.color}

				Button {caption : "4"; width: parent.width/3 - 2 * numbers.spacing / 3; color: buttons.color}
				Button {caption : "5"; width: parent.width/3 - 2 * numbers.spacing / 3; color: buttons.color}
				Button {caption : "6"; width: parent.width/3 - 2 * numbers.spacing / 3; color: buttons.color}

				Button {caption : "7"; width: parent.width/3 - 2 * numbers.spacing / 3; color: buttons.color}
				Button {caption : "8"; width: parent.width/3 - 2 * numbers.spacing / 3; color: buttons.color}
				Button {caption : "9"; width: parent.width/3 - 2 * numbers.spacing / 3; color: buttons.color}

				Button {caption : "*"; width: parent.width/3 - 2 * numbers.spacing / 3; color: buttons.color}
				Button {caption : "0"; width: parent.width/3 - 2 * numbers.spacing / 3; color: buttons.color}
				Button {caption : "#"; width: parent.width/3 - 2 * numbers.spacing / 3; color: buttons.color}
			}
		}

		function dial(object){
			window.DialNumber(object.text);
		}

		Image {
			id: buttonDial
			width: 70
			height: 70
			source: "qrc:///pics/dial.png"

			anchors {
				top: table.bottom
				topMargin: 35
				left: parent.left
				leftMargin: 200
			}

			MouseArea{
				anchors.fill: parent
				onClicked: {
					dial(phoneNumber)
				}
			}
		
		}

	}
}
