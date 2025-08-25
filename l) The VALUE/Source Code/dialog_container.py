"""
Name: dialog_container.py
Version: 0.0.3-alpha
Description: This file contains classes that show the dialog popups when I need them
Author: Nicolas Martens
"""

from functools import partial

from PySide6.QtCore import ( # type: ignore
    Qt,
    Slot,
    )
from PySide6.QtWidgets import ( # type: ignore
    QStackedWidget,
    QPushButton,
    QDialogButtonBox,
    QDialog,
    QListWidget,
    QListWidgetItem,
    QComboBox,
    QSlider,
    QLineEdit,
    )

from widget_helper import changeScreen, updateSaveStats
from file_helper import (
    closeSettings,
    resetSettings,
    applySettings,
    storeSave,
    createUnit,
    )
import global_storage as gs

# The class for the settings dialog
class TVSettingsDialog(QDialog):
    # When we create a new object
    def __new__(cls, obj:QDialog):
        # Set some initial data
        buttonBox:QDialogButtonBox = obj.findChild(QDialogButtonBox, "buttonBox") # type: ignore
        stack:QStackedWidget = obj.findChild(QStackedWidget, "stackedWidget") # type: ignore
        obj.setWindowModality(Qt.WindowModality.ApplicationModal)
        stack.setCurrentIndex(0)

        # Set the main page button commands
        gameplayButton:QPushButton = obj.findChild(QPushButton, "gameplayButton") # type: ignore
        gameplayButton.clicked.connect(partial(changeScreen, stack, 1))
        audioButton:QPushButton = obj.findChild(QPushButton, "audioButton") # type: ignore
        audioButton.clicked.connect(partial(changeScreen, stack, 2))
        graphicsButton:QPushButton = obj.findChild(QPushButton, "graphicsButton") # type: ignore
        graphicsButton.clicked.connect(partial(changeScreen, stack, 3))

        # Set the back button commands
        obj.finished.connect(partial(changeScreen, stack, 0))
        back1:QPushButton = obj.findChild(QPushButton, "pushButton_4") # type: ignore
        back2:QPushButton = obj.findChild(QPushButton, "pushButton_5") # type: ignore
        back3:QPushButton = obj.findChild(QPushButton, "pushButton_6") # type: ignore
        back1.clicked.connect(partial(changeScreen, stack, 0))
        back2.clicked.connect(partial(changeScreen, stack, 0))
        back3.clicked.connect(partial(changeScreen, stack, 0))

        # Set the restore default button functionality
        restoreDefaults:QPushButton = buttonBox.button(QDialogButtonBox.StandardButton.RestoreDefaults)
        apply:QPushButton = buttonBox.button(QDialogButtonBox.StandardButton.Apply)
        obj.finished.connect(partial(closeSettings))
        restoreDefaults.clicked.connect(partial(resetSettings, obj))
        apply.clicked.connect(partial(applySettings))

        # Set the gameplay button commands
        debuggingMode:QComboBox = obj.findChild(QComboBox, "DebuggingModeComboBox") # type: ignore
        debuggingMode.currentTextChanged.connect(partial(cls.assignSetting, "GPSet", "InfoUtils", "Mode"))
        unitData:QComboBox = obj.findChild(QComboBox, "UnitDataComboBox") # type: ignore
        unitData.currentTextChanged.connect(partial(cls.assignSetting, "GPSet", "InfoUtils", "UDisplay"))
        foeData:QComboBox = obj.findChild(QComboBox, "FoeDataComboBox") # type: ignore
        foeData.currentTextChanged.connect(partial(cls.assignSetting, "GPSet", "InfoUtils", "FDisplay"))

        # Set the volume slider commands
        musicSlider:QSlider = obj.findChild(QSlider, "MusicSlider") # type: ignore
        musicSlider.valueChanged.connect(partial(cls.assignSetting, "AudioSet", "VolSet", "Genval"))
        effectsSlider:QSlider = obj.findChild(QSlider, "EffectsSlider") # type: ignore
        effectsSlider.valueChanged.connect(partial(cls.assignSetting, "AudioSet", "VolSet", "SFXVal"))
        backgroundSlider:QSlider = obj.findChild(QSlider, "BackgroundSlider") # type: ignore
        backgroundSlider.valueChanged.connect(partial(cls.assignSetting, "AudioSet", "VolSet", "ABGVal"))

        # Set the music option commands
        gameMusic:QListWidget = obj.findChild(QListWidget, "GameMusicList") # type: ignore
        gameMusic.itemSelectionChanged.connect(partial(cls.manageList, "AudioSet", "SoundPacks", "GMusic", gameMusic))
        soundEffects:QListWidget = obj.findChild(QListWidget, "SoundEffectsList") # type: ignore
        soundEffects.itemSelectionChanged.connect(partial(cls.manageList, "AudioSet", "SoundPacks", "SFX", soundEffects))
        ambientMusic:QListWidget = obj.findChild(QListWidget, "AmbientList") # type: ignore
        ambientMusic.itemSelectionChanged.connect(partial(cls.manageList, "AudioSet", "SoundPacks", "Amb", ambientMusic))

        # Set the theme option commands
        interfaceTheme:QListWidget = obj.findChild(QListWidget, "InterfaceThemeList") # type: ignore
        interfaceTheme.currentItemChanged.connect(partial(cls.singleSelect, "GraSet", "Themes", "GUI"))
        unitTheme:QListWidget = obj.findChild(QListWidget, "UnitThemeList") # type: ignore
        unitTheme.currentItemChanged.connect(partial(cls.singleSelect, "GraSet", "Themes", "Uni"))
        environmentTheme:QListWidget = obj.findChild(QListWidget, "EnvironmentThemeList") # type: ignore
        environmentTheme.currentItemChanged.connect(partial(cls.singleSelect, "GraSet", "Themes", "Env"))

        return obj

    # Used when I want to change the value of a setting
    @Slot(str, str, str, str)
    @Slot(str, str, str, int)
    def assignSetting(self, keyI:str, keyII:str, keyIII:str, val):
        gs.settingData[keyI][keyII][keyIII] = val
        return

    # Used to help me manage some lists and indexing
    @Slot(str, str, str, QListWidget)
    def manageList(self, keyI:str, keyII:str, keyIII:str, widget:QListWidget):
        arr:list = widget.selectedItems()
        for i in range(len(arr)):
            arr[i] = arr[i].text()
        gs.settingData[keyI][keyII][keyIII] = arr
        return

    # Used to help me select one item
    @Slot(str, str, str, QListWidgetItem, QListWidgetItem)
    def singleSelect(self, keyI:str, keyII:str, keyIII:str, current:QListWidgetItem, former:QListWidgetItem):
        gs.settingData[keyI][keyII][keyIII] = current.text()
        return

# The class for the new save dialog
class TVNewSaveDialog(QDialog):
    slide = 0
    # When we create a new object
    def __new__(cls, obj:QDialog):
        # Set some initial data
        obj.setWindowModality(Qt.WindowModality.ApplicationModal)

        # Set the command to close the dialog
        obj.finished.connect(partial(cls.updateData, obj))

        return obj

    @Slot(QDialog, int)
    def updateData(obj:QDialog, result:int):
        if result == 1:
            gs.createWorld()
            nameEdit:QLineEdit = obj.findChild(QLineEdit, "nameEdit") # type: ignore
            difficultyBox:QComboBox = obj.findChild(QComboBox, "difficultyBox") # type: ignore
            gs.saveData["Name"] = nameEdit.text()
            gs.saveData["Difficulty"] = difficultyBox.currentIndex()
            createUnit(gs.saveData["Index"], gs.saveData["Name"])
            storeSave()
            updateSaveStats(obj.slide.widget(0).saveWidgets[gs.saveData["Index"] - 1], gs.saveData["Index"])
            changeScreen(obj.slide, 1, 0)
        return