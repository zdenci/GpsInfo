import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"
import "content"

ApplicationWindow
{
    initialPage: Component { MainPage{} }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
//    initialPage: Component { FirstPage { } }
//    cover: Qt.resolvedUrl("cover/CoverPage.qml")
//}

}
