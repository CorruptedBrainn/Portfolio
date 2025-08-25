"""
Name: home_container.py
Version: 0.0.3-alpha
Description: The file that allows me to manage the main home page
Author: Nicolas Martens
"""

import sys
from functools import partial

from PySide6.QtCore import ( # type: ignore
    Slot,
    )
from PySide6.QtWidgets import ( # type: ignore
    QStackedWidget,
    QPushButton,
    QStackedLayout,
    QLabel,
    QGridLayout,
    )

from widget_helper import (
    loadWidget,
    changeScreen,
    updateSaveStats,
    )
from file_helper import (
    createSave,
    updateSaveLoad,
    deleteSave,
    )

# The main class for the home page
class TVHomeContainer(QStackedWidget):
    # Initialise...
    def __init__(self, parent:QStackedLayout):
        # Load the main pages
        super().__init__()
        page0 = loadWidget("home_page.ui")
        page1 = loadWidget("save_page.ui")
        self.addWidget(page0)
        self.addWidget(page1)

        # Load start button
        startButton:QPushButton = page0.findChild(QPushButton, "startButton") # type: ignore
        startButton.clicked.connect(partial(changeScreen, parent, 0, 1))

        # Load our save widgets
        page1Layout:QGridLayout = page1.layout() # type: ignore
        self.saveWidgets = []
        saveButtons = []
        saveDeletes = []
        saveNumbers = []

        # Connect save widgets to commands
        for i in range(3):
            self.saveWidgets.append(loadWidget("save_slot_widget.ui"))
            updateSaveStats(self.saveWidgets[i], i + 1)
            page1Layout.addWidget(self.saveWidgets[i], 1, i + 1)
            saveButtons.append(self.saveWidgets[i].findChild(QPushButton, "saveLoadButton"))
            saveButtons[i].clicked.connect(partial(updateSaveLoad, i + 1))
            saveButtons[i].clicked.connect(partial(createSave, parent))
            saveDeletes.append(self.saveWidgets[i].findChild(QPushButton, "saveDeleteButton"))
            saveDeletes[i].clicked.connect(partial(deleteSave, i + 1, self.saveWidgets[i]))
            saveDeletes[i].clicked.connect(partial(changeScreen, parent, 0, 1))
            saveNumbers.append(self.saveWidgets[i].findChild(QLabel, "saveNumber"))
            saveNumbers[i].setText("Save " + str(i + 1))