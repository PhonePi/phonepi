import QtQuick.Window 2.0
import QtQuick.Controls 1.4

Window{
	id: phone
	height: 800
	maximumHeight: 800
	minimumHeight: 800
	width: 480 
	minimumWidth: 480
	maximumWidth: 480
	title: "Phone"
	visible: true

	Label {
		id: phoneNumber
		objectName: "number"
		text: ""
		font.pixelSize: 40
		width: 200
		anchors {
			horizontalCenter: parent.horizontalCenter
			top: parent.top
			topMargin: 20
		}

	}

	Button {
		id: button1
		width: 100
		height: 20
		text: "1"

		anchors{
			top: phoneNumber.bottom
			topMargin: 20
			left: parent.left
			leftMargin: 40
		}

		onClicked: phoneNumber.text += "1"
	}

		Button {
		id: button2
		width: 100
		height: 20
		text: "2"

		anchors{
			top: phoneNumber.bottom
			topMargin: 20
			left: button1.right
			leftMargin: 40
		}

		onClicked: phoneNumber.text += "2"
	}

	Button {
		id: button3
		width: 100
		height: 20
		text: "3"

		anchors{
			top: phoneNumber.bottom
			topMargin: 20
			left: button2.right
			leftMargin: 40
		}

		onClicked: phoneNumber.text += "3"
	}

	Button {
		id: button4
		width: 100
		height: 20
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
		height: 20
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
		height: 20
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
		height: 20
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
		height: 20
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
		height: 20
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
		height: 20
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
		height: 20
		text: "0/+"

		anchors{
			top: button8.bottom
			topMargin: 20
			left: buttonStar.right
			leftMargin: 40
		}

		onClicked: phoneNumber.text += "0"
	}

	Button {
		id: buttonSharp
		width: 100
		height: 20
		text: "#"

		anchors{
			top: button9.bottom
			topMargin: 20
			left: button0.right
			leftMargin: 40
		}

		onClicked: phoneNumber.text += "#"
	}

	Button {
		id: buttonDelete
		width: 170
		height: 20
		text: "x"

		anchors{
			top: buttonStar.bottom
			topMargin: 20
			left: parent.left
			leftMargin: 40
		}

		onClicked: phoneNumber.text = ""
	}

	function dial(object){
		window.DialNumber(object.text);
	}


	Button {
		id: dialButton
		width: 170
		height: 20
		text: "dial"

		anchors {
			top: buttonSharp.bottom
			topMargin: 20
			left: buttonDelete.right
			leftMargin: 40
		}

		onClicked: dial(phoneNumber)
	}

}
