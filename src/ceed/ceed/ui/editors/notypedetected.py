# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/v/filer4b/v38q001/ama/CS354R/PONG-PING/src/ceed/ceed/ui/editors/NoTypeDetected.ui'
#
# Created: Wed Mar 23 14:28:35 2016
#      by: pyside-uic 0.2.15 running on PySide 1.2.1
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_NoTypeDetectedDialog(object):
    def setupUi(self, NoTypeDetectedDialog):
        NoTypeDetectedDialog.setObjectName("NoTypeDetectedDialog")
        NoTypeDetectedDialog.setWindowModality(QtCore.Qt.ApplicationModal)
        NoTypeDetectedDialog.resize(400, 300)
        self.verticalLayout = QtGui.QVBoxLayout(NoTypeDetectedDialog)
        self.verticalLayout.setObjectName("verticalLayout")
        self.label = QtGui.QLabel(NoTypeDetectedDialog)
        self.label.setWordWrap(True)
        self.label.setObjectName("label")
        self.verticalLayout.addWidget(self.label)
        self.typeChoice = QtGui.QListWidget(NoTypeDetectedDialog)
        self.typeChoice.setObjectName("typeChoice")
        self.verticalLayout.addWidget(self.typeChoice)
        self.buttonBox = QtGui.QDialogButtonBox(NoTypeDetectedDialog)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.verticalLayout.addWidget(self.buttonBox)

        self.retranslateUi(NoTypeDetectedDialog)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL("accepted()"), NoTypeDetectedDialog.accept)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL("rejected()"), NoTypeDetectedDialog.reject)
        QtCore.QMetaObject.connectSlotsByName(NoTypeDetectedDialog)

    def retranslateUi(self, NoTypeDetectedDialog):
        NoTypeDetectedDialog.setWindowTitle(QtGui.QApplication.translate("NoTypeDetectedDialog", "No type detected!", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("NoTypeDetectedDialog", "The data type of the file you are trying to open wasn\'t successfuly auto detected. Please choose the type of the file manually from the listbox below.", None, QtGui.QApplication.UnicodeUTF8))

