import QtQuick 2.5
import QtQuick.Window 2.2

Item {
    visible: true
    width: 480
    height: 640

    function properties_change(msg) {
        main_form.lbl_status.text = msg
    }

    function reload_image() {
        main_form.img.source = "image://stream/reload_img"
    }

    function reset_image() {
        main_form.img.source = "image://stream/reset_img"
    }

    MainForm {
        id: main_form

        bt_browse.onClicked: {
            main_qml.bt_browse_clicked()
        }

        slider_threshold.onValueChanged: {
            main_qml.threshold_change(slider_threshold.value)
        }

        slider_scale.onValueChanged: {
            main_qml.scale_change(slider_scale.value)
        }
    }
}
