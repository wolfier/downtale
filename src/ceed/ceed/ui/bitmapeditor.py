# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/v/filer4b/v38q001/ama/CS354R/PONG-PING/src/ceed/ceed/ui/BitmapEditor.ui'
#
# Created: Wed Mar 23 14:28:35 2016
#      by: pyside-uic 0.2.15 running on PySide 1.2.1
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_BitmapEditor(object):
    def setupUi(self, BitmapEditor):
        BitmapEditor.setObjectName("BitmapEditor")
        BitmapEditor.resize(489, 384)
        self.horizontalLayout = QtGui.QHBoxLayout(BitmapEditor)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.preview = QtGui.QLabel(BitmapEditor)
        self.preview.setText("")
        self.preview.setObjectName("preview")
        self.horizontalLayout.addWidget(self.preview)
        self.buttons = QtGui.QWidget(BitmapEditor)
        self.buttons.setObjectName("buttons")
        self.verticalLayout = QtGui.QVBoxLayout(self.buttons)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.launchExternal = QtGui.QPushButton(self.buttons)
        self.launchExternal.setFlat(False)
        self.launchExternal.setObjectName("launchExternal")
        self.verticalLayout.addWidget(self.launchExternal)
        self.horizontalLayout.addWidget(self.buttons)

        self.retranslateUi(BitmapEditor)
        QtCore.QMetaObject.connectSlotsByName(BitmapEditor)

    def retranslateUi(self, BitmapEditor):
        BitmapEditor.setWindowTitle(QtGui.QApplication.translate("BitmapEditor", "Form", None, QtGui.QApplication.UnicodeUTF8))
        self.launchExternal.setText(QtGui.QApplication.translate("BitmapEditor", "Launch external editor", None, QtGui.QApplication.UnicodeUTF8))

