# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/v/filer4b/v38q001/ama/CS354R/PONG-PING/src/ceed/ceed/ui/editors/animation_list/AnimationListDockWidget.ui'
#
# Created: Wed Mar 23 14:28:35 2016
#      by: pyside-uic 0.2.15 running on PySide 1.2.1
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_AnimationListDockWidget(object):
    def setupUi(self, AnimationListDockWidget):
        AnimationListDockWidget.setObjectName("AnimationListDockWidget")
        AnimationListDockWidget.setEnabled(True)
        AnimationListDockWidget.resize(290, 300)
        self.dockWidgetContents = QtGui.QWidget()
        self.dockWidgetContents.setObjectName("dockWidgetContents")
        self.verticalLayout = QtGui.QVBoxLayout(self.dockWidgetContents)
        self.verticalLayout.setContentsMargins(-1, 0, -1, -1)
        self.verticalLayout.setObjectName("verticalLayout")
        self.list = QtGui.QListWidget(self.dockWidgetContents)
        self.list.setObjectName("list")
        self.verticalLayout.addWidget(self.list)
        AnimationListDockWidget.setWidget(self.dockWidgetContents)

        self.retranslateUi(AnimationListDockWidget)
        QtCore.QMetaObject.connectSlotsByName(AnimationListDockWidget)

    def retranslateUi(self, AnimationListDockWidget):
        AnimationListDockWidget.setWindowTitle(QtGui.QApplication.translate("AnimationListDockWidget", "List of animations", None, QtGui.QApplication.UnicodeUTF8))

