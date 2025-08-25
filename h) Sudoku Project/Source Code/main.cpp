#include <iostream>
#include <cctype>
#include <conio.h>
#include <algorithm>
#include <Windows.h>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

struct notes {
    bool layer1[9][9];
    bool layer2[9][9];
    bool layer3[9][9];
    bool layer4[9][9];
    bool layer5[9][9];
    bool layer6[9][9];
    bool layer7[9][9];
    bool layer8[9][9];
    bool layer9[9][9];
    string editType = "N/A";
    string segment = "N/A";
    int location = 0;
};

struct returnType {
    int cellX = 0;
    int cellY = 0;
    int updatedNumber = 0;
    string ruleUsed = "N/A";
};

notes setStructValue(notes noteStruct, int x, int y, int z, bool value) {
    switch (z) {
    case 0:
        noteStruct.layer1[x][y] = value;
        break;
    case 1:
        noteStruct.layer2[x][y] = value;
        break;
    case 2:
        noteStruct.layer3[x][y] = value;
        break;
    case 3:
        noteStruct.layer4[x][y] = value;
        break;
    case 4:
        noteStruct.layer5[x][y] = value;
        break;
    case 5:
        noteStruct.layer6[x][y] = value;
        break;
    case 6:
        noteStruct.layer7[x][y] = value;
        break;
    case 7:
        noteStruct.layer8[x][y] = value;
        break;
    case 8:
        noteStruct.layer9[x][y] = value;
        break;
    default:
        break;
    }
    return noteStruct;
}

bool readStructValue(notes noteStruct, int x, int y, int z) {
    switch (z) {
    case 0:
        return noteStruct.layer1[x][y];
    case 1:
        return noteStruct.layer2[x][y];
    case 2:
        return noteStruct.layer3[x][y];
    case 3:
        return noteStruct.layer4[x][y];
    case 4:
        return noteStruct.layer5[x][y];
    case 5:
        return noteStruct.layer6[x][y];
    case 6:
        return noteStruct.layer7[x][y];
    case 7:
        return noteStruct.layer8[x][y];
    case 8:
        return noteStruct.layer9[x][y];
    default:
        return true;
    }
}

notes createNotes(int board[9][9], notes disallowedNotes) {
    notes noteStruct{};
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (board[x][y] != 0) {
                for (int i = 0; i < 9; i++) {
                    noteStruct = setStructValue(noteStruct, x, y, i, 0);
                }
            }
            else {
                for (int i = 0; i < 9; i++) {
                    noteStruct = setStructValue(noteStruct, x, y, i, !readStructValue(disallowedNotes, x, y, i));
                }
                for (int z = 0; z < 9; z++) {
                    noteStruct = setStructValue(noteStruct, x, y, board[z][y] - 1, 0);
                    noteStruct = setStructValue(noteStruct, x, y, board[x][z] - 1, 0);
                    noteStruct = setStructValue(noteStruct, x, y, board[3 * (x / 3) + z % 3][3 * (y / 3) + z / 3] - 1, 0);
                }
            }
        }
    }
    return noteStruct;
}

notes editNotes(int board[9][9], notes noteStruct, notes disallowedNotes) {
    vector<int> nums, disallowed, store1, store2;
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (board[3 * (y % 3) + x % 3][3 * (y / 3) + x / 3] == 0) {
                nums.clear();
                disallowed.clear();
                for (int i = 0; i < 9; i++) {
                    if (readStructValue(noteStruct, 3 * (y % 3) + x % 3, 3 * (y / 3) + x / 3, i)) nums.push_back(i + 1);
                    if (!readStructValue(disallowedNotes, 3 * (y % 3) + x % 3, 3 * (y / 3) + x / 3, i)) disallowed.push_back(i + 1);
                }
                if (nums != disallowed) {
                    store1 = nums;
                    for (int z = x + 1; z < 9; z++) {
                        if (board[3 * (y % 3) + z % 3][3 * (y / 3) + z / 3] == 0) {
                            nums = store1;
                            for (int i = 0; i < 9; i++) {
                                if (readStructValue(noteStruct, 3 * (y % 3) + z % 3, 3 * (y / 3) + z / 3, i)) nums.push_back(i + 1);
                            }
                            sort(nums.begin(), nums.end());
                            nums.erase(unique(nums.begin(), nums.end()), nums.end());
                            if (nums.size() == 2) {
                                for (int w = 0; w < 9; w++) {
                                    if (board[3 * (y % 3) + w % 3][3 * (y / 3) + w / 3] == 0) {
                                        if (w != x && w != z) {
                                            for (int i = 0; i < 2; i++) {
                                                disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + w % 3, 3 * (y / 3) + w / 3, nums[i] - 1, 1);
                                            }
                                        }
                                        else {
                                            for (int i = 0; i < 9; i++) {
                                                disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + w % 3, 3 * (y / 3) + w / 3, i, 1);
                                            }
                                            for (int i = 0; i < 2; i++) {
                                                disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + w % 3, 3 * (y / 3) + w / 3, nums[i] - 1, 0);
                                            }
                                        }
                                    }
                                }
                                disallowedNotes.editType = "Obvious Pairs";
                                disallowedNotes.segment = "Square";
                                disallowedNotes.location = y + 1;
                                return disallowedNotes;
                            }
                            else if (nums.size() == 3 && nums != disallowed) {
                                store2 = nums;
                                for (int w = z + 1; w < 9; w++) {
                                    if (board[3 * (y % 3) + w % 3][3 * (y / 3) + w / 3] == 0) {
                                        nums = store2;
                                        for (int i = 0; i < 9; i++) {
                                            if (readStructValue(noteStruct, 3 * (y % 3) + w % 3, 3 * (y / 3) + w / 3, i)) nums.push_back(i + 1);
                                        }
                                        sort(nums.begin(), nums.end());
                                        nums.erase(unique(nums.begin(), nums.end()), nums.end());
                                        if (nums.size() == 3) {
                                            for (int v = 0; v < 9; v++) {
                                                if (board[3 * (y % 3) + v % 3][3 * (y / 3) + v / 3] == 0) {
                                                    if (v != x && v != z && v != w) {
                                                        for (int i = 0; i < 3; i++) {
                                                            disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + v % 3, 3 * (y / 3) + v / 3, nums[i] - 1, 1);
                                                        }
                                                    }
                                                    else {
                                                        for (int i = 0; i < 9; i++) {
                                                            disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + v % 3, 3 * (y / 3) + v / 3, i, 1);
                                                        }
                                                        for (int i = 0; i < 3; i++) {
                                                            disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + v % 3, 3 * (y / 3) + v / 3, nums[i] - 1, 0);
                                                        }
                                                    }
                                                }
                                            }
                                            disallowedNotes.editType = "Obvious Triples";
                                            disallowedNotes.segment = "Square";
                                            disallowedNotes.location = y + 1;
                                            return disallowedNotes;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vector<int> cellR, cellC, cellS, finalR, finalC, finalS, disallowedR, disallowedC, disallowedS, storeR, storeC, storeS;
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            cellR.clear();
            cellC.clear();
            cellS.clear();
            disallowedR.clear();
            disallowedC.clear();
            disallowedS.clear();
            for (int i = 0; i < 9; i++) {
                if (readStructValue(noteStruct, x, y, i)) cellR.push_back(i + 1);
                if (!readStructValue(disallowedNotes, x, y, i)) disallowedR.push_back(i + 1);
                if (readStructValue(noteStruct, y, x, i)) cellC.push_back(i + 1);
                if (!readStructValue(disallowedNotes, y, x, i)) disallowedC.push_back(i + 1);
                if (readStructValue(noteStruct, 3 * (y % 3) + x % 3, 3 * (y / 3) + x / 3, i)) cellS.push_back(i + 1);
                if (!readStructValue(disallowedNotes, 3 * (y % 3) + x % 3, 3 * (y / 3) + x / 3, i)) disallowedS.push_back(i + 1);
            }
            storeR = disallowedR;
            storeC = disallowedC;
            storeS = disallowedS;
            for (int z = x + 1; z < 9; z++) {
                finalR.clear();
                finalC.clear();
                finalS.clear();
                disallowedR = storeR;
                disallowedC = storeC;
                disallowedS = storeS;
                for (int i = 0; i < cellR.size(); i++) {
                    if (readStructValue(noteStruct, z, y, cellR[i] - 1)) {
                        finalR.push_back(cellR[i]);
                        for (int w = 0; w < 9; w++) {
                            if (w != x && w != z && readStructValue(noteStruct, w, y, cellR[i] - 1)) {
                                finalR.pop_back();
                                break;
                            }
                        }
                    }
                }
                for (int i = 0; i < cellC.size(); i++) {
                    if (readStructValue(noteStruct, y, z, cellC[i] - 1)) {
                        finalC.push_back(cellC[i]);
                        for (int w = 0; w < 9; w++) {
                            if (w != x && w != z && readStructValue(noteStruct, y, w, cellC[i] - 1)) {
                                finalC.pop_back();
                                break;
                            }
                        }
                    }
                }
                for (int i = 0; i < cellS.size(); i++) {
                    if (readStructValue(noteStruct, 3 * (y % 3) + z % 3, 3 * (y / 3) + z / 3, cellS[i] - 1)) {
                        finalS.push_back(cellS[i]);
                        for (int w = 0; w < 9; w++) {
                            if (w != x && w != z && readStructValue(noteStruct, 3 * (y % 3) + w % 3, 3 * (y / 3) + w / 3, cellS[i] - 1)) {
                                finalS.pop_back();
                                break;
                            }
                        }
                    }
                }
                if (finalR.size() == 2 && finalR != disallowedR) {
                    for (int i = 0; i < 9; i++) {
                        disallowedNotes = setStructValue(disallowedNotes, x, y, i, 1);
                        disallowedNotes = setStructValue(disallowedNotes, z, y, i, 1);
                    }
                    for (int i = 0; i < 2; i++) {
                        disallowedNotes = setStructValue(disallowedNotes, x, y, finalR[i] - 1, 0);
                        disallowedNotes = setStructValue(disallowedNotes, z, y, finalR[i] - 1, 0);
                    }
                    disallowedNotes.editType = "Hidden Pairs";
                    disallowedNotes.segment = "Row";
                    disallowedNotes.location = y + 1;
                    return disallowedNotes;
                }
                if (finalC.size() == 2 && finalC != disallowedC) {
                    for (int i = 0; i < 9; i++) {
                        disallowedNotes = setStructValue(disallowedNotes, y, x, i, 1);
                        disallowedNotes = setStructValue(disallowedNotes, y, z, i, 1);
                    }
                    for (int i = 0; i < 2; i++) {
                        disallowedNotes = setStructValue(disallowedNotes, y, x, finalC[i] - 1, 0);
                        disallowedNotes = setStructValue(disallowedNotes, y, z, finalC[i] - 1, 0);
                    }
                    disallowedNotes.editType = "Hidden Pairs";
                    disallowedNotes.segment = "Column";
                    disallowedNotes.location = y + 1;
                    return disallowedNotes;
                }
                if (finalS.size() == 2 && finalS != disallowedS) {
                    for (int i = 0; i < 9; i++) {
                        disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + x % 3, 3 * (y / 3) + x / 3, i, 1);
                        disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + z % 3, 3 * (y / 3) + z / 3, i, 1);
                    }
                    for (int i = 0; i < 2; i++) {
                        disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + x % 3, 3 * (y / 3) + x / 3, finalS[i] - 1, 0);
                        disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + z % 3, 3 * (y / 3) + z / 3, finalS[i] - 1, 0);
                    }
                    disallowedNotes.editType = "Hidden Pairs";
                    disallowedNotes.segment = "Square";
                    disallowedNotes.location = y + 1;
                    return disallowedNotes;
                }
                for (int i = 0; i < 9; i++) {
                    if (readStructValue(noteStruct, z, y, i)) cellR.push_back(i + 1);
                    if (!readStructValue(disallowedNotes, z, y, i)) disallowedR.push_back(i + 1);
                    if (readStructValue(noteStruct, y, z, i)) cellC.push_back(i + 1);
                    if (!readStructValue(disallowedNotes, y, z, i)) disallowedC.push_back(i + 1);
                    if (readStructValue(noteStruct, 3 * (y % 3) + z % 3, 3 * (y / 3) + z / 3, i)) cellS.push_back(i + 1);
                    if (!readStructValue(disallowedNotes, 3 * (y % 3) + z % 3, 3 * (y / 3) + z / 3, i)) disallowedS.push_back(i + 1);
                }
                sort(cellR.begin(), cellR.end());
                sort(disallowedR.begin(), disallowedR.end());
                sort(cellC.begin(), cellC.end());
                sort(disallowedC.begin(), disallowedC.end());
                sort(cellS.begin(), cellS.end());
                sort(disallowedS.begin(), disallowedS.end());
                cellR.erase(unique(cellR.begin(), cellR.end()), cellR.end());
                disallowedR.erase(unique(disallowedR.begin(), disallowedR.end()), disallowedR.end());
                cellC.erase(unique(cellC.begin(), cellC.end()), cellC.end());
                disallowedC.erase(unique(disallowedC.begin(), disallowedC.end()), disallowedC.end());
                cellS.erase(unique(cellS.begin(), cellS.end()), cellS.end());
                disallowedS.erase(unique(disallowedS.begin(), disallowedS.end()), disallowedS.end());
                for (int w = z + 1; w < 9; w++) {
                    finalR.clear();
                    finalC.clear();
                    finalS.clear();
                    for (int i = 0; i < cellR.size(); i++) {
                        if (readStructValue(noteStruct, w, y, cellR[i] - 1)) {
                            finalR.push_back(cellR[i]);
                            for (int v = 0; v < 9; v++) {
                                if (v != x && v != z && v != w && readStructValue(noteStruct, v, y, cellR[i] - 1)) {
                                    finalR.pop_back();
                                    break;
                                }
                            }
                        }
                    }
                    for (int i = 0; i < cellC.size(); i++) {
                        if (readStructValue(noteStruct, y, w, cellC[i] - 1)) {
                            finalC.push_back(cellC[i]);
                            for (int v = 0; v < 9; v++) {
                                if (v != x && v != z && v != w && readStructValue(noteStruct, y, v, cellC[i] - 1)) {
                                    finalC.pop_back();
                                    break;
                                }
                            }
                        }
                    }
                    for (int i = 0; i < cellS.size(); i++) {
                        if (readStructValue(noteStruct, 3 * (y % 3) + w % 3, 3 * (y / 3) + w / 3, cellS[i] - 1)) {
                            finalS.push_back(cellS[i]);
                            for (int v = 0; v < 9; v++) {
                                if (v != x && v != z && v != w && readStructValue(noteStruct, 3 * (y % 3) + v % 3, 3 * (y / 3) + v / 3, cellS[i] - 1)) {
                                    finalS.pop_back();
                                    break;
                                }
                            }
                        }
                    }
                    if (finalR.size() == 3 && !includes(disallowedR.begin(), disallowedR.end(), finalR.begin(), finalR.end())) {
                        for (int i = 0; i < 9; i++) {
                            disallowedNotes = setStructValue(disallowedNotes, x, y, i, 1);
                            disallowedNotes = setStructValue(disallowedNotes, z, y, i, 1);
                            disallowedNotes = setStructValue(disallowedNotes, w, y, i, 1);
                        }
                        for (int i = 0; i < 3; i++) {
                            disallowedNotes = setStructValue(disallowedNotes, x, y, finalR[i] - 1, 0);
                            disallowedNotes = setStructValue(disallowedNotes, z, y, finalR[i] - 1, 0);
                            disallowedNotes = setStructValue(disallowedNotes, w, y, finalR[i] - 1, 0);
                        }
                        disallowedNotes.editType = "Hidden Triples";
                        disallowedNotes.segment = "Row";
                        disallowedNotes.location = y + 1;
                        return disallowedNotes;
                    }
                    if (finalC.size() == 3 && !includes(disallowedC.begin(), disallowedC.end(), finalC.begin(), finalC.end())) {
                        for (int i = 0; i < 9; i++) {
                            disallowedNotes = setStructValue(disallowedNotes, y, x, i, 1);
                            disallowedNotes = setStructValue(disallowedNotes, y, z, i, 1);
                            disallowedNotes = setStructValue(disallowedNotes, y, w, i, 1);
                        }
                        for (int i = 0; i < 3; i++) {
                            disallowedNotes = setStructValue(disallowedNotes, y, x, finalC[i] - 1, 0);
                            disallowedNotes = setStructValue(disallowedNotes, y, z, finalC[i] - 1, 0);
                            disallowedNotes = setStructValue(disallowedNotes, y, w, finalC[i] - 1, 0);
                        }
                        disallowedNotes.editType = "Hidden Triples";
                        disallowedNotes.segment = "Column";
                        disallowedNotes.location = y + 1;
                        return disallowedNotes;
                    }
                    if (finalS.size() == 3 && !includes(disallowedS.begin(), disallowedS.end(), finalS.begin(), finalS.end())) {
                        for (int i = 0; i < 9; i++) {
                            disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + x % 3, 3 * (y / 3) + x / 3, i, 1);
                            disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + z % 3, 3 * (y / 3) + z / 3, i, 1);
                            disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + w % 3, 3 * (y / 3) + w / 3, i, 1);
                        }
                        for (int i = 0; i < 3; i++) {
                            disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + x % 3, 3 * (y / 3) + x / 3, finalS[i] - 1, 0);
                            disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + z % 3, 3 * (y / 3) + z / 3, finalS[i] - 1, 0);
                            disallowedNotes = setStructValue(disallowedNotes, 3 * (y % 3) + w % 3, 3 * (y / 3) + w / 3, finalS[i] - 1, 0);
                        }
                        disallowedNotes.editType = "Hidden Triples";
                        disallowedNotes.segment = "Square";
                        disallowedNotes.location = y + 1;
                        return disallowedNotes;
                    }
                }
            }
        }
    }
    vector<int> xCoords, yCoords;
    bool present;
    for (int y = 0; y < 9; y++) {
        for (int i = 0; i < 9; i++) {
            xCoords.clear();
            yCoords.clear();
            present = false;
            for (int x = 0; x < 9; x++) {
                if (readStructValue(noteStruct, 3 * (y % 3) + x % 3, 3 * (y / 3) + x / 3, i)) {
                    xCoords.push_back(3 * (y % 3) + x % 3);
                    yCoords.push_back(3 * (y / 3) + x / 3);
                }
            }
            if (xCoords.size() == 2) {
                if (xCoords[0] == xCoords[1]) {
                    for (int x = 0; x < 9; x++) {
                        if (x != yCoords[0] && x != yCoords[1] && readStructValue(noteStruct, xCoords[0], x, i)) {
                            present = true;
                            disallowedNotes = setStructValue(disallowedNotes, xCoords[0], x, i, 1);
                        }
                    }
                    if (present) {
                        disallowedNotes.editType = "Pointing Pairs";
                        disallowedNotes.segment = "Column";
                        disallowedNotes.location = xCoords[0] + 1;
                        return disallowedNotes;
                    }
                }
                if (yCoords[0] == yCoords[1]) {
                    for (int x = 0; x < 9; x++) {
                        if (x != xCoords[0] && x != xCoords[1] && readStructValue(noteStruct, x, yCoords[0], i)) {
                            present = true;
                            disallowedNotes = setStructValue(disallowedNotes, x, yCoords[0], i, 1);
                        }
                    }
                    if (present) {
                        disallowedNotes.editType = "Pointing Pairs";
                        disallowedNotes.segment = "Row";
                        disallowedNotes.location = yCoords[0] + 1;
                        return disallowedNotes;
                    }
                }
            }
            if (xCoords.size() == 3) {
                if (xCoords[0] == xCoords[1] && xCoords[1] == xCoords[2]) {
                    for (int x = 0; x < 9; x++) {
                        if (x != yCoords[0] && x != yCoords[1] && x != yCoords[2] && readStructValue(noteStruct, xCoords[0], x, i)) {
                            present = true;
                            disallowedNotes = setStructValue(disallowedNotes, xCoords[0], x, i, 1);
                        }
                    }
                    if (present) {
                        disallowedNotes.editType = "Pointing Triples";
                        disallowedNotes.segment = "Column";
                        disallowedNotes.location = xCoords[0] + 1;
                        return disallowedNotes;
                    }
                }
                if (yCoords[0] == yCoords[1] && yCoords[1] == yCoords[2]) {
                    for (int x = 0; x < 9; x++) {
                        if (x != xCoords[0] && x != xCoords[1] && x != xCoords[2] && readStructValue(noteStruct, x, yCoords[0], i)) {
                            present = true;
                            disallowedNotes = setStructValue(disallowedNotes, x, yCoords[0], i, 1);
                        }
                    }
                    if (present) {
                        disallowedNotes.editType = "Pointing Triples";
                        disallowedNotes.segment = "Row";
                        disallowedNotes.location = yCoords[0] + 1;
                        return disallowedNotes;
                    }
                }
            }
        }
    }
    
    disallowedNotes.editType = "N/A";
    return disallowedNotes;
}

returnType solve(int board[9][9], notes noteStruct) {
    returnType returnStruct;
    int count, number = 0;
    int rCount, cCount, sCount;
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            count = 0;
            for (int i = 0; i < 9; i++) {
                if (readStructValue(noteStruct, x, y, i)) {
                    count++;
                    number = i + 1;
                }
            }
            if (count == 1) {
                returnStruct.cellX = x + 1;
                returnStruct.cellY = y + 1;
                returnStruct.updatedNumber = number;
                returnStruct.ruleUsed = "Obvious Singles";
                return returnStruct;
            }
            if (board[x][y] == 0) {
                for (int i = 0; i < 9; i++) {
                    if (readStructValue(noteStruct, x, y, i)) {
                        rCount = cCount = sCount = 0;
                        for (int z = 0; z < 9; z++) {
                            if (readStructValue(noteStruct, z, y, i)) rCount++;
                            if (readStructValue(noteStruct, x, z, i)) cCount++;
                            if (readStructValue(noteStruct, 3 * (x / 3) + z % 3, 3 * (y / 3) + z / 3, i)) sCount++;
                        }
                        if (rCount == 1 || cCount == 1 || sCount == 1) {
                            returnStruct.cellX = x + 1;
                            returnStruct.cellY = y + 1;
                            returnStruct.updatedNumber = i + 1;
                            returnStruct.ruleUsed = "Hidden Singles";
                            return returnStruct;
                        }
                    }
                }
            }
        }
    }
    returnStruct.ruleUsed = "N/A";
    return returnStruct;
}

int checkIfSolved(int board[9][9]) {
    map <int, int> rowNumbers, colNumbers, squareNumbers;

    for (int y1 = 0; y1 < 3; y1++) {
        for (int y2 = 0; y2 < 3; y2++) {
            rowNumbers = colNumbers = squareNumbers = { {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {0, 0} };
            for (int x1 = 0; x1 < 3; x1++) {
                for (int x2 = 0; x2 < 3; x2++) {
                    if (board[3 * x1 + x2][3 * y1 + y2] == 0 || rowNumbers.at(board[3 * x1 + x2][3 * y1 + y2]) > 0) return 0;
                    else rowNumbers.at(board[3 * x1 + x2][3 * y1 + y2])++;

                    if (board[3 * y1 + y2][3 * x1 + x2] == 0 || colNumbers.at(board[3 * y1 + y2][3 * x1 + x2]) > 0) return 0;
                    else colNumbers.at(board[3 * y1 + y2][3 * x1 + x2])++;

                    if (board[3 * y2 + x2][3 * y1 + x1] == 0 || squareNumbers.at(board[3 * y2 + x2][3 * y1 + x1]) > 0) return 0;
                    else squareNumbers.at(board[3 * y2 + x2][3 * y1 + x1])++;
                }
            }
        }
    }
    return 1;
}

template <typename t>
void printBoard(t board[9][9]) {
    for (int y1 = 0; y1 < 3; y1++) {
        cout << "+-------+-------+-------+\n";
        for (int y2 = 0; y2 < 3; y2++) {
            for (int x1 = 0; x1 < 3; x1++) {
                cout << "| ";
                for (int x2 = 0; x2 < 3; x2++) {
                    if (board[3 * x1 + x2][3 * y1 + y2] == 0) cout << "  ";
                    else cout << board[3 * x1 + x2][3 * y1 + y2] << " ";
                }
            }
            cout << "|\n";
        }
    }
    cout << "+-------+-------+-------+";
}

int main() {
    int board[9][9];
    int state = 0;
    char useless;
    returnType updatedCell;
    updatedCell.ruleUsed = "N/A";
    updatedCell.cellX = 1;
    updatedCell.cellY = 1;
    updatedCell.updatedNumber = 0;
    notes disallowedNotes{};

    cout << "Type in the Sudoku Board to solve (row by row), using 0 as a blank.\n\nBOARD:\n\n";

    for (int y1 = 0; y1 < 3; y1++) {
        cout << "+-------+-------+-------+\n";
        for (int y2 = 0; y2 < 3; y2++) {
            for (int x1 = 0; x1 < 3; x1++) {
                cout << "| ";
                for (int x2 = 0; x2 < 3; x2++) {
                    char store = _getch();
                    if (isdigit(store)) {
                        board[3 * x1 + x2][3 * y1 + y2] = store - '0';
                        if (store == '0') cout << "  ";
                        else cout << board[3 * x1 + x2][3 * y1 + y2] << " ";
                        for (int i = 0; i < 9; i++) {
                            disallowedNotes = setStructValue(disallowedNotes, 3 * x1 + x2, 3 * y1 + y2, i, 0);
                        }
                        continue;
                    }
                    x2--;
                }
            }
            cout << "|\n";
        }
    }
    cout << "+-------+-------+-------+";
    
    while (!state) {
        system("CLS");
        cout << /*"Press any key to continue.\n\nNOTES:\n\n"*/ "Press any key to continue.\n\n";
        /*cout << "\nBools for 1:\n";
        printBoard(createNotes(board, disallowedNotes).layer1);
        cout << "\nBools for 2:\n";
        printBoard(createNotes(board, disallowedNotes).layer2);
        cout << "\nBools for 3:\n";
        printBoard(createNotes(board, disallowedNotes).layer3);
        cout << "\nBools for 4:\n";
        printBoard(createNotes(board, disallowedNotes).layer4);
        cout << "\nBools for 5:\n";
        printBoard(createNotes(board, disallowedNotes).layer5);
        cout << "\nBools for 6:\n";
        printBoard(createNotes(board, disallowedNotes).layer6);
        cout << "\nBools for 7:\n";
        printBoard(createNotes(board, disallowedNotes).layer7);
        cout << "\nBools for 8:\n";
        printBoard(createNotes(board, disallowedNotes).layer8);
        cout << "\nBools for 9:\n";
        printBoard(createNotes(board, disallowedNotes).layer9);
        /*cout << "\nDisallowed:\n";
        printBoard(disallowedNotes.layer1);
        printBoard(disallowedNotes.layer2);
        printBoard(disallowedNotes.layer3);
        printBoard(disallowedNotes.layer4);
        printBoard(disallowedNotes.layer5);
        printBoard(disallowedNotes.layer6);
        printBoard(disallowedNotes.layer7);
        printBoard(disallowedNotes.layer8);
        printBoard(disallowedNotes.layer9);*/
        cout << "\n\nBOARD:\n";
        printBoard(board);
        state = checkIfSolved(board);
        cout << "\n\nDATA:\nComplete: " << state;
        if (updatedCell.ruleUsed != "N/A" || disallowedNotes.editType == "N/A") {
            cout << "\nRule Used: " << updatedCell.ruleUsed;
            cout << "\nCoordinates of Edit: (" << updatedCell.cellX << ", " << updatedCell.cellY << ")";
            cout << "\nNew Number: " << updatedCell.updatedNumber;
        }
        else {
            cout << "\nRule Used (Editing Notes): " << disallowedNotes.editType;
            cout << "\nLocation: " << disallowedNotes.segment << " " << disallowedNotes.location;
        }
        while (!_kbhit()) {

        }
        useless = _getch();
        updatedCell = solve(board, createNotes(board, disallowedNotes));
        if (updatedCell.ruleUsed == "N/A") disallowedNotes = editNotes(board, createNotes(board, disallowedNotes), disallowedNotes);
        else board[updatedCell.cellX - 1][updatedCell.cellY - 1] = updatedCell.updatedNumber;
    }
    cout << "\n\nBoard Solved.";
}

// Complete:
// 785931462243856971691724583457612398968573214132498657379285146524167839816349725

// Use:
// 785931462243856971691724583457612398968573214132490007379280006524160009816349725

// Use:
// 000000000000000000000000000008000000000000000000000000000080000060000000910000000

// Use:
// 630150087195802060000003052970080400003701200008030600009060023300910006056008700

// Use:
// 632154987195872364784693152971286435563741298248539671819467523327915846456328719

// Use:
// 000000403026009000005870000009032000000700000162000000010020560000900000050000107

// USE ALL BELOW:
// Obv Singles:
// 008007900042005000000600050003006801000000006900070000080130470000090000010000000
// Obv Pairs:
// 002085004000030060004210030000000052000000310900000000800006000250400008000001600
// Obv Triples:
// 370000090900070000000420006001084200000000000800600050006002010000000039050000400
// Hidden Singles:
// 009032000000700000162000000010020560000900000050000107000000403026009000005870000
// Hidden Pairs:
// 009032000000700000162000000010020560000900000050000107000000403026009000005870000
// Hidden Triples:
// 008007000042005000000000000003006801000000006900000000080130470000090000010000000
// Pointing Pairs:
// 009070000080400000003000028100000670020013040040007800600030000010000000000000284
// Pointing Triples:
// 009070000080400000003000028100000670020013040040007800600030000010000000000000284
// X-Wing:
// 003800510008700930100305728000200849801906257000500163964127385382659471010400692
// Y-Wing:
// 900200750050690231420000000090000000002000000070006000069001000510003000207080009
// Swordfish:
// 908735100010980030000020098805469310090070000043250900250090001089512063001847009