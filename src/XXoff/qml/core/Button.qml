import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Rectangle {

	property string caption: ""
	property int spacing

	id: button1
	width: 40
	height: 20
			
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
		onClicked: {
			if(caption != "Yes") window.shutTheFuckUpKhmOff()
			window.close()
		}
	}
}
