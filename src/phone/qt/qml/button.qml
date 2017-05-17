import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


Rectangle {

	property string caption: ""
	property int spacing: 1

	id: button1
	width: parent.width / 3 - 2 * spacing 
	height: 50
			
	Text {
		renderType: Text.NativeRendering
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
		font.family: "SF"
		font.pointSize: 20
		text: caption 
		width: parent.width
		height: parent.height
	 }


	MouseArea{
		opacity:1
		anchors.fill: parent
		onClicked: phoneNumber.text += caption
	}
}
