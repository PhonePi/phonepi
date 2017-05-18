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

/*	Rectangle {
		id: buttons
		width: parent.width
		height: 2 *  parent.height / 3
		color: "#fbf1c7"
		anchors{
			bottom: parent.bottom
		}
		
		Rectangle{
			id: table
			width: parent.width - parent.width * 0.0583 * 2
			height: 206
			color: "#282828"
			
			anchors{
				top: parent.top
				left: parent.left
				leftMargin: parent.width * 0.0583
				rightMargin: parent.width * 0.0583
			}

			Column {
				id: numbers
				spacing: 2
				width: parent.width

				Row{
					id: row1
					spacing: 2
					Button {caption : "1"; width: parent.width/3 - 2 * row1.spacing }
					Button {caption : "2"; width: parent.width/3 - 2 * row1.spacing }
					Button {caption : "3"; width: parent.width/3 - 2 * row1.spacing }
				}

				Row{
					id: row2
					spacing: 2
					Button {caption : "4"; width: parent.width/3 - 2 * row2.spacing }
					Button {caption : "5"; width: parent.width/3 - 2 * row2.spacing }
					Button {caption : "6"; width: parent.width/3 - 2 * row2.spacing }
				}

				Row{
					id: row3
					spacing: 2
					Button {caption : "7"; width: parent.width/3 - 2 * row3.spacing }
					Button {caption : "8"; width: parent.width/3 - 2 * row3.spacing }
					Button {caption : "9"; width: parent.width/3 - 2 * row3.spacing }
				}

				Row{
					id: row4
					spacing: 2
					Button {caption : "*"; width: parent.width/3 - 2 * row4.spacing }
					Button {caption : "0"; width: parent.width/3 - 2 * row4.spacing }
					Button {caption : "#"; width: parent.width/3 - 2 * row4.spacing }
				}

			}
		}
		Button {
				id: button2
				width: 100
				height: 50
				text: "2"

				anchors{
					top: parent.top
					topMargin: 10
					left: button1.right
					leftMargin: 40
				}

				onClicked: phoneNumber.text += "2"
			}

			Button {
				id: button3
				width: 100
				height: 50
				text: "3"

				anchors{
					top: parent.top
					topMargin: 10
					left: button2.right
					leftMargin: 40
				}

				onClicked: phoneNumber.text += "3"
			}

			Button {
				id: button4
				width: 100
				height: 50
				text: "4"

				anchors{
					top: button1.bottom
					topMargin: 20
					left: parent.left
					leftMargin: 40
				}

				onClicked: phoneNumber.text += "4"
			}

			Button {
				id: button5
				width: 100
				height: 50
				text: "5"

				anchors{
					top: button2.bottom
					topMargin: 20
					left: button4.right
					leftMargin: 40
				}

				onClicked: phoneNumber.text += "5"
			}

			Button {
				id: button6
				width: 100
				height: 50
				text: "6"

				anchors{
					top: button3.bottom
					topMargin: 20
					left: button5.right
					leftMargin: 40
				}

				onClicked: phoneNumber.text += "6"
			}

			Button {
				id: button7
				width: 100
				height: 50
				text: "7"

				anchors{
					top: button4.bottom
					topMargin: 20
					left: parent.left
					leftMargin: 40
				}

				onClicked: phoneNumber.text += "7"
			}
			
			Button {
				id: button8
				width: 100
				height: 50
				text: "8"

				anchors{
					top: button5.bottom
					topMargin: 20
					left: button7.right
					leftMargin: 40
				}

				onClicked: phoneNumber.text += "8"
			}

			Button {
				id: button9
				width: 100
				height: 50
				text: "9"

				anchors{
					top: button6.bottom
					topMargin: 20
					left: button8.right
					leftMargin: 40
				}

				onClicked: phoneNumber.text += "9"
			}

			Button {
				id: buttonStar
				width: 100
				height: 50
				text: "*"

				anchors{
					top: button7.bottom
					topMargin: 20
					left: parent.left
					leftMargin: 40
				}

				onClicked: phoneNumber.text += "*"
			}


			Button {
				id: button0
				width: 100
				height: 50
				text: "0/+"

				anchors{
					top: button8.bottom
					topMargin: 20
					left: buttonStar.right
					leftMargin: 40
				}

				MouseArea {
					anchors.fill: parent
					onClicked: phoneNumber.text += "0"
					onDoubleClicked: {
						phoneNumber.text = phoneNumber.text.substr(0, phoneNumber.text.length-1)
						phoneNumber.text += "+"
					}
				}
			}

			Button {
				id: buttonSharp
				width: 100
				height: 50
				text: "#"

				anchors{
					top: button9.bottom
					topMargin: 20
					left: button0.right
					leftMargin: 40
				}

				onClicked: phoneNumber.text += "#"
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

		}*/
}
