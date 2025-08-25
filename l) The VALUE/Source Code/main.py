"""
Name: main.py
Version: 0.0.3-alpha
Description: Program execution starts and ends here -- this file contains and manages the overall top level application objects
Author: Nicolas Martens
"""

import sys
from functools import partial

from PySide6.QtCore import ( # type: ignore
	Slot,
	Qt,
	)
from PySide6.QtWidgets import ( # type: ignore
	QApplication,
	QStackedLayout,
	QMainWindow,
	)
from PySide6.QtGui import ( # type: ignore
	QAction,
	)

from home_container import TVHomeContainer
from game_container import TVGameContainer
from dialog_container import TVSettingsDialog
from widget_helper import (
	loadWidget,
	changeScreen,
	showSettings,
	)
from file_helper import setupWorkspace, storeSave

# Another function to quit the application
@Slot(QApplication)
def quitApp(app: QApplication):
	storeSave()
	return app.exit()

# Check that this is the startpoint for execution
if __name__ == "__main__":
	# Create the application
	app = QApplication(sys.argv)
	setupWorkspace()

	# Load some windows and deal with heirachy
	window:QMainWindow = loadWidget("main_window.ui") # type: ignore
	mainLayout = QStackedLayout()
	homeContainer = TVHomeContainer(mainLayout)
	gameContainer = TVGameContainer(mainLayout)
	settingsDialog = TVSettingsDialog(loadWidget("settings_dialog.ui"))
	mainLayout.addWidget(homeContainer)
	mainLayout.addWidget(gameContainer)
	window.centralWidget().setLayout(mainLayout)
	window.centralWidget().layout().currentChanged.connect(partial(gameContainer.startState))

	# Load and connect buttons
	actionQuit:QAction = window.findChild(QAction, "actionQuit") # type: ignore
	actionQuit.triggered.connect(partial(storeSave))
	actionQuit.triggered.connect(partial(quitApp, app))
	actionMain_Menu:QAction = window.findChild(QAction, "actionMain_Menu") # type: ignore
	actionMain_Menu.triggered.connect(partial(storeSave))
	actionMain_Menu.triggered.connect(partial(changeScreen, mainLayout, 0, 0))
	actionLoad_Save:QAction = window.findChild(QAction, "actionLoad_Save") # type: ignore
	actionLoad_Save.triggered.connect(partial(storeSave))
	actionLoad_Save.triggered.connect(partial(changeScreen, mainLayout, 0, 1))
	actionSettings:QAction = window.findChild(QAction, "actionOptions") # type: ignore
	actionSettings.triggered.connect(partial(showSettings, settingsDialog))

	# Show the window
	window.setWindowState(Qt.WindowState.WindowFullScreen)
	window.show()

	# Start the application loop
	sys.exit(app.exec())
