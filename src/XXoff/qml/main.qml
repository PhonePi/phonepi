import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import "core"

Window{
	id: dialog
	height: 100
	maximumHeight: Screen.height
	minimumHeight: 100
	width:  300
	minimumWidth: 300
	maximumWidth: Screen.width
	title: "Power off?"
	visible: true

	Text {
		id: question
		objectName: "question"
		text: "Do you want to poweroff?"
		font.pixelSize: 20
		wrapMode: Text.WrapAnywhere
		anchors {
			left: parent.left
			leftMargin: 10
			top: parent.top
			topMargin: 20
		}
	}

	Grid {
		id: numbers
		spacing: 10
		columns: 2
		width: parent.width
		height: parent.height
		anchors{
			bottom: parent.bottom
			bottomMargin: 10
			horizontalCenter: parent.horizontalCenter
		}

		Button {caption : "Yes"; spacing: parent.spacing; color: buttons.color}
		Button {caption : "No"; spacing: parent.spacing; color: buttons.color}
	}
}
