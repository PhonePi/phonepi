import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import "core"

Window{
	id: dialog
	height: 100
	maximumHeight: 100
	minimumHeight: 100
	width:  300
	minimumWidth: 300
	maximumWidth: 300
	title: "Power off?"
	visible: true

	Rectangle{
		anchors.fill:parent
			Text {
				id: question
				objectName: "question"
				text: "Do you want to poweroff?"
				font.pixelSize: 20
				wrapMode: Text.WrapAnywhere
				anchors {
					horizontalCenter: parent.horizontalCenter
					top: parent.top
					topMargin: 20
				}
			}

			Grid {
				id: numbers
				spacing: 10
				columns: 2
				width: parent.width / 3
				height: parent.height / 3
				anchors{
					bottom: parent.bottom
					bottomMargin: 10
					horizontalCenter: parent.horizontalCenter
				}

				Button {caption : "Yes"; spacing: parent.spacing; color: "#cc241c" }
				Button {caption : "No"; spacing: parent.spacing; color: "#b8bb26" }
			}
	}
}
