# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/v/filer4b/v38q001/ama/CS354R/PONG-PING/src/ceed/ceed/ui/CEGUIDebugInfo.ui'
#
# Created: Wed Mar 23 14:28:35 2016
#      by: pyside-uic 0.2.15 running on PySide 1.2.1
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_CEGUIWidgetInfo(object):
    def setupUi(self, CEGUIWidgetInfo):
        CEGUIWidgetInfo.setObjectName("CEGUIWidgetInfo")
        CEGUIWidgetInfo.resize(792, 800)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(CEGUIWidgetInfo.sizePolicy().hasHeightForWidth())
        CEGUIWidgetInfo.setSizePolicy(sizePolicy)
        self.verticalLayout = QtGui.QVBoxLayout(CEGUIWidgetInfo)
        self.verticalLayout.setObjectName("verticalLayout")
        self.scrollArea = QtGui.QScrollArea(CEGUIWidgetInfo)
        self.scrollArea.setWidgetResizable(True)
        self.scrollArea.setObjectName("scrollArea")
        self.scrollAreaWidgetContents_2 = QtGui.QWidget()
        self.scrollAreaWidgetContents_2.setGeometry(QtCore.QRect(0, 0, 772, 751))
        self.scrollAreaWidgetContents_2.setObjectName("scrollAreaWidgetContents_2")
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.scrollAreaWidgetContents_2)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.info = QtGui.QLabel(self.scrollAreaWidgetContents_2)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.info.sizePolicy().hasHeightForWidth())
        self.info.setSizePolicy(sizePolicy)
        self.info.setTextFormat(QtCore.Qt.PlainText)
        self.info.setScaledContents(False)
        self.info.setAlignment(QtCore.Qt.AlignHCenter|QtCore.Qt.AlignTop)
        self.info.setWordWrap(True)
        self.info.setObjectName("info")
        self.verticalLayout_2.addWidget(self.info)
        self.renderingPerformance = QtGui.QGroupBox(self.scrollAreaWidgetContents_2)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.renderingPerformance.sizePolicy().hasHeightForWidth())
        self.renderingPerformance.setSizePolicy(sizePolicy)
        self.renderingPerformance.setObjectName("renderingPerformance")
        self.gridLayout_3 = QtGui.QGridLayout(self.renderingPerformance)
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.currentFPSBox = QtGui.QLineEdit(self.renderingPerformance)
        self.currentFPSBox.setFrame(True)
        self.currentFPSBox.setReadOnly(True)
        self.currentFPSBox.setObjectName("currentFPSBox")
        self.gridLayout_3.addWidget(self.currentFPSBox, 0, 1, 1, 1)
        self.currentFPSLabel = QtGui.QLabel(self.renderingPerformance)
        self.currentFPSLabel.setObjectName("currentFPSLabel")
        self.gridLayout_3.addWidget(self.currentFPSLabel, 0, 0, 1, 1)
        self.verticalLayout_2.addWidget(self.renderingPerformance)
        self.log = QtGui.QGroupBox(self.scrollAreaWidgetContents_2)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.log.sizePolicy().hasHeightForWidth())
        self.log.setSizePolicy(sizePolicy)
        self.log.setObjectName("log")
        self.gridLayout_4 = QtGui.QGridLayout(self.log)
        self.gridLayout_4.setObjectName("gridLayout_4")
        self.errorsLabel = QtGui.QLabel(self.log)
        self.errorsLabel.setObjectName("errorsLabel")
        self.gridLayout_4.addWidget(self.errorsLabel, 1, 0, 1, 1)
        self.errorsBox = QtGui.QLineEdit(self.log)
        self.errorsBox.setReadOnly(True)
        self.errorsBox.setObjectName("errorsBox")
        self.gridLayout_4.addWidget(self.errorsBox, 1, 1, 1, 1)
        self.warningsLabel = QtGui.QLabel(self.log)
        self.warningsLabel.setObjectName("warningsLabel")
        self.gridLayout_4.addWidget(self.warningsLabel, 2, 0, 1, 1)
        self.warningsBox = QtGui.QLineEdit(self.log)
        self.warningsBox.setReadOnly(True)
        self.warningsBox.setObjectName("warningsBox")
        self.gridLayout_4.addWidget(self.warningsBox, 2, 1, 1, 1)
        self.othersBox = QtGui.QLineEdit(self.log)
        self.othersBox.setReadOnly(True)
        self.othersBox.setObjectName("othersBox")
        self.gridLayout_4.addWidget(self.othersBox, 3, 1, 1, 1)
        self.label = QtGui.QLabel(self.log)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label.sizePolicy().hasHeightForWidth())
        self.label.setSizePolicy(sizePolicy)
        self.label.setObjectName("label")
        self.gridLayout_4.addWidget(self.label, 0, 1, 1, 1)
        self.othersLabel = QtGui.QLabel(self.log)
        self.othersLabel.setObjectName("othersLabel")
        self.gridLayout_4.addWidget(self.othersLabel, 3, 0, 1, 1)
        self.verticalLayout_2.addWidget(self.log)
        self.logViewArea = QtGui.QWidget(self.scrollAreaWidgetContents_2)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.logViewArea.sizePolicy().hasHeightForWidth())
        self.logViewArea.setSizePolicy(sizePolicy)
        self.logViewArea.setMinimumSize(QtCore.QSize(0, 100))
        self.logViewArea.setObjectName("logViewArea")
        self.verticalLayout_2.addWidget(self.logViewArea)
        self.scrollArea.setWidget(self.scrollAreaWidgetContents_2)
        self.verticalLayout.addWidget(self.scrollArea)
        self.bottomButtonBox = QtGui.QWidget(CEGUIWidgetInfo)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.bottomButtonBox.sizePolicy().hasHeightForWidth())
        self.bottomButtonBox.setSizePolicy(sizePolicy)
        self.bottomButtonBox.setObjectName("bottomButtonBox")
        self.horizontalLayout_2 = QtGui.QHBoxLayout(self.bottomButtonBox)
        self.horizontalLayout_2.setSpacing(0)
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        spacerItem = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem)
        self.closeButton = QtGui.QPushButton(self.bottomButtonBox)
        self.closeButton.setObjectName("closeButton")
        self.horizontalLayout_2.addWidget(self.closeButton)
        self.verticalLayout.addWidget(self.bottomButtonBox)
        self.currentFPSLabel.setBuddy(self.currentFPSBox)
        self.errorsLabel.setBuddy(self.errorsBox)
        self.warningsLabel.setBuddy(self.warningsBox)
        self.othersLabel.setBuddy(self.othersBox)

        self.retranslateUi(CEGUIWidgetInfo)
        QtCore.QObject.connect(self.closeButton, QtCore.SIGNAL("clicked()"), CEGUIWidgetInfo.close)
        QtCore.QMetaObject.connectSlotsByName(CEGUIWidgetInfo)

    def retranslateUi(self, CEGUIWidgetInfo):
        CEGUIWidgetInfo.setWindowTitle(QtGui.QApplication.translate("CEGUIWidgetInfo", "CEGUI Debug Info", None, QtGui.QApplication.UnicodeUTF8))
        self.info.setText(QtGui.QApplication.translate("CEGUIWidgetInfo", "This dock widget is suitable for finding problems with the CEGUI instance inside the editor. You should not need to use this unless you experience difficulties.", None, QtGui.QApplication.UnicodeUTF8))
        self.renderingPerformance.setTitle(QtGui.QApplication.translate("CEGUIWidgetInfo", "Rendering performance", None, QtGui.QApplication.UnicodeUTF8))
        self.currentFPSBox.setToolTip(QtGui.QApplication.translate("CEGUIWidgetInfo", "FPS means how many times the CEGUI widget gets rerendered per second", None, QtGui.QApplication.UnicodeUTF8))
        self.currentFPSBox.setText(QtGui.QApplication.translate("CEGUIWidgetInfo", "0", None, QtGui.QApplication.UnicodeUTF8))
        self.currentFPSLabel.setText(QtGui.QApplication.translate("CEGUIWidgetInfo", "Current FPS", None, QtGui.QApplication.UnicodeUTF8))
        self.log.setTitle(QtGui.QApplication.translate("CEGUIWidgetInfo", "Log", None, QtGui.QApplication.UnicodeUTF8))
        self.errorsLabel.setText(QtGui.QApplication.translate("CEGUIWidgetInfo", "Errors", None, QtGui.QApplication.UnicodeUTF8))
        self.errorsBox.setText(QtGui.QApplication.translate("CEGUIWidgetInfo", "0", None, QtGui.QApplication.UnicodeUTF8))
        self.warningsLabel.setText(QtGui.QApplication.translate("CEGUIWidgetInfo", "Warnings", None, QtGui.QApplication.UnicodeUTF8))
        self.warningsBox.setText(QtGui.QApplication.translate("CEGUIWidgetInfo", "0", None, QtGui.QApplication.UnicodeUTF8))
        self.othersBox.setText(QtGui.QApplication.translate("CEGUIWidgetInfo", "0", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("CEGUIWidgetInfo", "Number of messages", None, QtGui.QApplication.UnicodeUTF8))
        self.othersLabel.setText(QtGui.QApplication.translate("CEGUIWidgetInfo", "Others", None, QtGui.QApplication.UnicodeUTF8))
        self.closeButton.setText(QtGui.QApplication.translate("CEGUIWidgetInfo", "Close", None, QtGui.QApplication.UnicodeUTF8))

