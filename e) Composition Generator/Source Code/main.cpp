#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

void generateComposition();
void keySignatureIndividual(int composition);
void keySignaturesAll();
void timeSignatureIndividual(int composition);
void tempoIndividual(int composition);
void chordProgressionIndividual(int composition);
void instrumentGenerate(int composition);
void melodyIndividual(int composition);

std::fstream CompositionGenerator_Results;

std::string keySignaturesList[21] = { "Ab", "A", "A#", "Bb", "B", "B#", "Cb", "C", "C#", "Db", "D", "D#", "Eb", "E", "E#", "Fb", "F", "F#", "Gb", "G", "G#", };
std::string scaleTypeList[2] = { "Minor", "Major" };
std::string baseNotesList[14] = { "A", "B", "C", "D", "E", "F", "G", "A", "B", "C", "D", "E", "F", "G" };
std::string timeSignatureNotesList[7] = { "Semibreve", "Minum", "Crotchet", "Quaver", "Semiquaver", "Demisemiquaver", "Hemidemisemiquaver"};
std::string tempoNotesList[14] = { "Dotted Semibreve", "Semibreve", "Dotted Minum", "Minum", "Dotted Crotchet", "Crotchet", "Dotted Quaver", "Quaver", "Dotted Semiquaver", "Semiquaver", "Dotted Demisemiquaver", "Demisemiquaver", "Dotted Hemidemisemiquaver", "Hemidemisemiquaver" };
int baseNotesSemitoneList[13] = { 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2 };
int minorSemitoneList[7] = { 2, 1, 2, 2, 1, 2, 2 };
int majorSemitoneList[7] = { 2, 2, 1, 2, 2, 2, 1 };
int timeSignatureValuesList[7] = { 1, 2, 4, 8, 16, 32, 64 };
std::string scaleNotesList[8];
char keyPressContinue = '?';
int keySignatureIndex = 22;
int scaleTypeIndex = 5;
int baseNoteIndex;
int keySignatureAccidental;
int individualNoteAccidental = 0;
int timeSignatureIndex;
int timeSignatureNumerator;
int tempoNote;
double beatsPerMinute;
int timeSignatureToNumerator;
double dottedNoteMultiplier;
int chordProgressionArrayIndex[10];
int compositionMinLength;
int compositionMaxLength;
int chordProgressionCurrentChord;
int chordProgressionNewChord;
int chordProgressionSelectionCheck;
int chordProgressionOptions;
int chordProgressionAvailRows;

// NOTE: AFTER WRITTEN TEST NEGATIVE VALUES

/*
* 1D: Major / Minor
* 2D: Chord I / i
* 3D: Chord II / ii
* 4D: Chord III / iii
* 5D: Chord IV / iv
* 6D: Chord V / v
* 7D: Chord VI / vi
* 8D: Chord VII / vii
* 9D: Starting Chord
* 10D: Ending Chord
* 
* 1D decides the chords based on major / minor
* 2D-8D restricts the chord usage
* 9D will be the chord that is being jumped from
* 10D is the chord being jumped to
* 
* NOTE TO ENSURE HARMONY OVER RANDOM JUMPING
*/
std::string chordProgressionArray[2][2][2][2][2][2][2][2][20][20] = {
    { // Major
        { // No Chord 1
            { // No Chord 2
                { // No Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "N/A" }, // Starting Chord
                                    { "N/A" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "viio" }, // Starting Chord
                                    { "N/A" } // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "vi" }, // Starting Chord
                                    { "N/A" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "vi",     "viio", "viio/vi" }, // Starting Chord
                                    { "N/A",    "N/A",  "vi" } // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "V",      "V/V" }, // Starting Chord
                                    { "N/A",    "V" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "V",      "viio", "V/V",  "viio/V" }, // Starting Chord
                                    { "N/A",    "V",    "V",    "V" }, // Ending Chord
                                    { "N/A",    "N/A",  "viio", "viio" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "V",      "vi",   "V/V",  "V/vi" }, // Starting Chord
                                    { "vi",     "V",    "V",    "vi" }, // Ending Chord
                                    { "N/A",    "V/V",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "V",      "vi",       "viio", "V/V",  "V/vi", "viio/V",   "viio/vi" }, // Starting Chord
                                    { "vi",     "V",        "V",    "V",    "vi",   "V",        "vi" }, // Ending Chord
                                    { "N/A",    "V/V",      "N/A",  "viio", "N/A",  "viio",     "N/A" },
                                    { "N/A",    "viio/V",   "N/A",  "N/A",  "N/A",  "N/A",      "N/A" }
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "IV" }, // Starting Chord
                                    { "N/A" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "IV",     "viio", "viio/IV" }, // Starting Chord
                                    { "viio",   "N/A",  "IV" } // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "IV",     "vi" }, // Starting Chord
                                    { "N/A",    "IV" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "IV",     "vi",   "viio", "viio/IV",  "viio/vi" }, // Starting Chord
                                    { "viio",   "IV",   "N/A",  "IV",       "vi" } // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "IV",     "V",    "V/IV", "V/V" }, // Starting Chord
                                    { "V",      "N/A",  "IV",   "V" }, // Ending Chord
                                    { "V/V",    "N/A",  "N/A",  "V/VI" }
                                },
                                { // Yes Chord 7
                                    { "IV",     "V",    "viio", "V/IV", "V/V",      "viio/IV",  "viio/V" }, // Starting Chord
                                    { "V",      "N/A",  "V",    "IV",   "V",        "IV",       "V" }, // Ending Chord
                                    { "viio",   "N/A",  "N/A",  "N/A",  "viio",     "N/A",      "viio" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "V/IV",     "N/A",      "V/IV" },
                                    { "viio/V", "N/A",  "N/A",  "N/A",  "viio/IV",  "N/A",      "viio/IV" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "IV",     "V",    "vi",   "V/IV", "V/V",  "V/vi" }, // Starting Chord
                                    { "V",      "vi",   "IV",   "IV",   "V",    "vi" }, // Ending Chord
                                    { "V/V",    "N/A",  "V",    "N/A",  "V/IV", "N/A" },
                                    { "N/A",    "N/A",  "V/V",  "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "IV",     "V",    "vi",       "viio", "V/IV", "V/V",      "V/vi", "viio/IV",  "viio/V",   "viio/vi" }, // Starting Chord
                                    { "V",      "vi",   "IV",       "V",    "IV",   "V",        "vi",   "IV",       "V",        "vi" }, // Ending Chord
                                    { "viio",   "N/A",  "V",        "N/A",  "N/A",  "viio",     "N/A",  "N/A",      "viio",     "N/A" },
                                    { "V/V",    "N/A",  "V/V",      "N/A",  "N/A",  "V/IV",     "N/A",  "N/A",      "V/IV",     "N/A" },
                                    { "viio/V", "N/A",  "viio/V",   "N/A",  "N/A",  "viio/IV",  "N/A",  "N/A",      "viio/IV",  "N/A" }
                                }
                            }
                        }
                    }
                },
                { // Yes Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "iii" }, // Starting Chord
                                    { "N/A" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "iii",    "viio", "viio/iii" }, // Starting Chord
                                    { "N/A",    "N/A",  "iii" } // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "iii",    "vi" }, // Starting Chord
                                    { "vi",     "N/A" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "iii",        "vi",   "viio", "viio/iii", "viio/vi" }, // Starting Chord
                                    { "vi",         "N/A",  "N/A",  "iii",      "vi" }, // Ending Chord
                                    { "viio/vi",    "N/A",  "N/A",  "viio/vi",  "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "iii",    "V",    "V/iii",    "V/V" }, // Starting Chord
                                    { "N/A",    "N/A",  "iii",      "V" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "iii",    "V",    "viio", "V/iii",    "V/V",  "viio/iii", "viio/V" }, // Starting Chord
                                    { "N/A",    "N/A",  "V",    "iii",      "V",    "iii",      "V" }, // Ending Chord
                                    { "N/A",    "N/A",  "N/A",  "N/A",      "viio", "N/A",      "viio" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "iii",    "V",    "vi",   "V/iii",    "V/V",  "V/vi" }, // Starting Chord
                                    { "vi",     "vi",   "V",    "iii",      "V",    "vi" }, // Ending Chord
                                    { "V/vi",   "N/A",  "V/V",  "V/vi",     "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "iii",        "V",    "vi",       "viio", "V/iii",    "V/V",  "V/vi", "viio/iii", "viio/V",   "viio/vi" }, // Starting Chord
                                    { "vi",         "vi",   "V",        "V",    "iii",      "V",    "vi",   "iii",      "V",        "vi" }, // Ending Chord
                                    { "V/vi",       "N/A",  "V/V",      "N/A",  "V/vi",     "viio", "N/A",  "V/vi",     "viio",     "N/A" },
                                    { "viio/vi",    "N/A",  "viio/V",   "N/A",  "viio/vi",  "N/A",  "N/A",  "viio/vi",  "N/A",      "N/A" }
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "iii",    "IV" }, // Starting Chord
                                    { "IV",     "N/A" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "iii",    "IV",   "viio", "viio/iii", "viio/IV" }, // Starting Chord
                                    { "IV",     "viio", "N/A",  "iii",      "IV" } // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "iii",    "IV",   "vi" }, // Starting Chord
                                    { "IV",     "N/A",  "IV" }, // Ending Chord
                                    { "vi",     "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "iii",        "IV",   "vi",   "viio", "viio/iii", "viio/IV",  "viio/vi" }, // Starting Chord
                                    { "IV",         "viio", "IV",   "N/A",  "iii",      "IV",       "vi" }, // Ending Chord
                                    { "vi",         "N/A",  "N/A",  "N/A",  "viio/vi",  "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",  "N/A",  "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "iii",    "IV",   "V",    "V/iii",    "V/IV", "V/V" }, // Starting Chord
                                    { "IV",     "V",    "N/A",  "iii",      "IV",   "V" }, // Ending Chord
                                    { "N/A",    "V/V",  "N/A",  "N/A",      "N/A",  "V/IV" }
                                },
                                { // Yes Chord 7
                                    { "iii",    "IV",       "V",    "viio", "V/iii",    "V/IV", "V/V",      "viio/iii", "viio/IV",  "viio/V" }, // Starting Chord
                                    { "IV",     "V",        "N/A",  "V",    "iii",      "IV",   "V",        "iii",      "IV",       "V" }, // Ending Chord
                                    { "N/A",    "viio",     "N/A",  "N/A",  "N/A",      "N/A",  "viio",     "N/A",      "N/A",      "viio" },
                                    { "N/A",    "V/V",      "N/A",  "N/A",  "N/A",      "N/A",  "V/IV",     "N/A",      "N/A",      "V/IV" },
                                    { "N/A",    "viio/V",   "N/A",  "N/A",  "N/A",      "N/A",  "viio/IV",  "N/A",      "N/A",      "viio/IV" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "iii",    "IV",   "V",    "vi",   "V/iii",    "V/IV", "V/V",  "V/vi" }, // Starting Chord
                                    { "IV",     "V",    "vi",   "IV",   "iii",      "IV",   "V",    "vi" }, // Ending Chord
                                    { "vi",     "V/V",  "N/A",  "V",    "V/vi",     "N/A",  "V/IV", "N/A" },
                                    { "V/vi",   "N/A",  "N/A",  "V/V",  "N/A",      "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "iii",        "IV",       "V",    "vi",       "viio", "V/iii",    "V/IV", "V/V",      "V/vi", "viio/iii", "viio/IV",  "viio/V",   "viio/vi" }, // Starting Chord
                                    { "IV",         "V",        "vi",   "IV",       "V",    "iii",      "IV",   "V",        "vi",   "iii",      "IV",       "V",        "vi" }, // Ending Chord
                                    { "vi",         "viio",     "N/A",  "V",        "N/A",  "V/vi",     "N/A",  "viio",     "N/A",  "V/vi",     "N/A",      "viio",     "N/A" },
                                    { "V/vi",       "V/V",      "N/A",  "V/V",      "N/A",  "viio/vi",  "N/A",  "V/IV",     "N/A",  "viio/vi",  "N/A",      "V/IV",     "N/A" },
                                    { "viio/vi",    "viio/V",   "N/A",  "viio/V",   "N/A",  "N/A",      "N/A",  "viio/IV",  "N/A",  "N/A",      "N/A",      "viio/IV",  "N/A" }
                                }
                            }
                        }
                    }
                }
            },
            { // Yes Chord 2
                { // No Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "ii" }, // Starting Chord
                                    { "N/A" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "ii",     "viio", "viio/ii" }, // Starting Chord
                                    { "viio",   "N/A",  "ii" } // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "ii",     "vi" }, // Starting Chord
                                    { "N/A",    "ii" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "ii",     "vi",       "viio", "viio/ii",  "viio/vi" }, // Starting Chord
                                    { "viio",   "ii",       "N/A",  "ii",       "vi" }, // Ending Chord
                                    { "N/A",    "viio/ii",  "N/A",  "N/A",      "viio/ii" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "ii",     "V",    "V/ii", "V/V" }, // Starting Chord
                                    { "V",      "N/A",  "ii",   "V" }, // Ending Chord
                                    { "V/V",    "N/A",  "V/V",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "ii",     "V",    "viio", "V/ii",     "V/V",  "viio/ii",  "viio/V" }, // Starting Chord
                                    { "V",      "N/A",  "V",    "ii",       "V",    "ii",       "V" }, // Ending Chord
                                    { "viio",   "N/A",  "N/A",  "V/V",      "viio", "V/V",      "viio" },
                                    { "V/V",    "N/A",  "N/A",  "viio/V",   "N/A",  "viio/V",   "N/A" },
                                    { "viio/V", "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "ii",     "V",    "vi",   "V/ii", "V/V",  "V/vi" }, // Starting Chord
                                    { "V",      "vi",   "ii",   "ii",   "V",    "vi" }, // Ending Chord
                                    { "V/V",    "N/A",  "V",    "V/V",  "N/A",  "V/ii" },
                                    { "N/A",    "N/A",  "V/ii", "N/A",  "N/A",  "N/A" },
                                    { "N/A",    "N/A",  "V/V",  "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "ii",     "V",    "vi",       "viio", "V/ii",     "V/V",  "V/vi",     "viio/ii",  "viio/V",   "viio/vi" }, // Starting Chord
                                    { "V",      "vi",   "ii",       "V",    "ii",       "V",    "vi",       "ii",       "V",        "vi" }, // Ending Chord
                                    { "viio",   "N/A",  "V",        "N/A",  "V/V",      "viio", "V/ii",     "V/V",      "viio",     "V/ii" },
                                    { "V/V",    "N/A",  "V/ii",     "N/A",  "viio/V",   "N/A",  "viio/ii",  "viio/V",   "N/A",      "viio/ii" },
                                    { "viio/V", "N/A",  "V/V",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "N/A",    "N/A",  "viio/ii",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "N/A",    "N/A",  "viio/V",   "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "ii",     "IV" }, // Starting Chord
                                    { "N/A",    "ii" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "ii",     "IV",   "viio", "viio/ii",  "viio/IV" }, // Starting Chord
                                    { "viio",   "ii",   "N/A",  "ii",       "IV" }, // Ending Chord
                                    { "N/A",    "viio", "N/A",  "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "ii",     "IV",   "vi" }, // Starting Chord
                                    { "N/A",    "ii",   "ii" }, // Ending Chord
                                    { "N/A",    "N/A",  "IV" }
                                },
                                { // Yes Chord 7
                                    { "ii",     "IV",   "vi",       "viio", "viio/ii",  "viio/IV",  "viio/vi" }, // Starting Chord
                                    { "viio",   "ii",   "ii",       "N/A",  "ii",       "IV",       "vi" }, // Ending Chord
                                    { "N/A",    "viio", "IV",       "N/A",  "N/A",      "N/A",      "viio/ii" },
                                    { "N/A",    "N/A",  "viio/ii",  "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "ii",     "IV",   "V",    "V/ii", "V/IV", "V/V" }, // Starting Chord
                                    { "V",      "ii",   "N/A",  "ii",   "IV",   "V" }, // Ending Chord
                                    { "V/V",    "V",    "N/A",  "V/V",  "N/A",  "V/IV" },
                                    { "N/A",    "V/V",  "N/A",  "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "ii",     "IV",       "V",    "viio", "V/ii",     "V/IV", "V/V",      "viio/ii",  "viio/IV",  "viio/V" }, // Starting Chord
                                    { "V",      "ii",       "N/A",  "V",    "ii",       "IV",   "V",        "ii",       "IV",       "V" }, // Ending Chord
                                    { "viio",   "V",        "N/A",  "N/A",  "V/V",      "N/A",  "viio",     "V/V",      "N/A",      "viio" },
                                    { "V/V",    "viio",     "N/A",  "N/A",  "viio/V",   "N/A",  "V/IV",     "viio/V",   "N/A",      "V/IV" },
                                    { "viio/V", "V/V",      "N/A",  "N/A",  "N/A",      "N/A",  "viio/IV",  "N/A",      "N/A",      "viio/IV" },
                                    { "N/A",    "viio/V",   "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "ii",     "IV",   "V",    "vi",   "V/ii", "V/IV", "V/V",  "V/vi" }, // Starting Chord
                                    { "V",      "ii",   "vi",   "ii",   "ii",   "IV",   "V",    "vi" }, // Ending Chord
                                    { "V/V",    "V",    "N/A",  "IV",   "V/V",  "N/A",  "V/IV", "V/ii" },
                                    { "N/A",    "V/V",  "N/A",  "V",    "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "N/A",    "N/A",  "N/A",  "V/ii", "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "N/A",    "N/A",  "N/A",  "V/V",  "N/A",  "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "ii",     "IV",       "V",    "vi",       "viio", "V/ii",     "V/IV", "V/V",      "V/vi",     "viio/ii",  "viio/IV",  "viio/V",   "viio/vi" }, // Starting Chord
                                    { "V",      "ii",       "vi",   "ii",       "V",    "ii",       "IV",   "V",        "vi",       "ii",       "IV",       "V",        "vi" }, // Ending Chord
                                    { "viio",   "V",        "N/A",  "IV",       "N/A",  "V/V",      "N/A",  "viio",     "V/ii",     "V/V",      "N/A",      "viio",     "V/ii" },
                                    { "V/V",    "viio",     "N/A",  "V",        "N/A",  "viio/V",   "N/A",  "V/IV",     "viio/ii",  "viio/V",   "N/A",      "V/IV",     "viio/ii" },
                                    { "viio/V", "V/V",      "N/A",  "V/ii",     "N/A",  "N/A",      "N/A",  "viio/IV",  "N/A",      "N/A",      "N/A",      "viio/IV",  "N/A" },
                                    { "N/A",    "viio/V",   "N/A",  "V/V",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "N/A",    "N/A",      "N/A",  "viio/ii",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "N/A",    "N/A",      "N/A",  "viio/V",   "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            }
                        }
                    }
                },
                { // Yes Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "ii",     "iii" }, // Starting Chord
                                    { "N/A",    "ii" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "ii",     "iii",      "viio", "viio/ii",  "viio/iii" }, // Starting Chord
                                    { "viio",   "ii",       "N/A",  "ii",       "iii" }, // Ending Chord
                                    { "N/A",    "viio/ii",  "N/A",  "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "ii",     "iii",  "vi" }, // Starting Chord
                                    { "N/A",    "ii",   "ii" }, // Ending Chord
                                    { "N/A",    "vi",   "N/A" }
                                },
                                { // Yes Chord 7
                                    { "ii",     "iii",      "vi",       "viio", "viio/ii",  "viio/iii", "viio/vi" }, // Starting Chord
                                    { "viio",   "ii",       "ii",       "N/A",  "ii",       "iii",      "vi" }, // Ending Chord
                                    { "N/A",    "vi",       "viio/ii",  "N/A",  "N/A",      "viio/vi",  "viio/ii" },
                                    { "N/A",    "viio/ii",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "N/A",    "viio/vi",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "ii",     "iii",  "V",    "V/ii", "V/iii",    "V/V" }, // Starting Chord
                                    { "V",      "ii",   "N/A",  "ii",   "iii",      "V" }, // Ending Chord
                                    { "V/V",    "V/ii", "N/A",  "V/V",  "N/A",      "N/A" }
                                },
                                { // Yes Chord 7
                                    { "ii",     "iii",      "V",    "viio", "V/ii",     "V/iii",    "V/V",  "viio/ii",  "viio/iii", "viio/V" }, // Starting Chord
                                    { "V",      "ii",       "N/A",  "V",    "ii",       "iii",      "V",    "ii",       "iii",      "V" }, // Ending Chord
                                    { "viio",   "V/ii",     "N/A",  "N/A",  "V/V",      "N/A",      "viio", "V/V",      "N/A",      "viio" },
                                    { "V/V",    "viio/ii",  "N/A",  "N/A",  "viio/V",   "N/A",      "N/A",  "viio/V",   "N/A",      "N/A" },
                                    { "viio/V", "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "ii",     "iii",  "V",    "vi",   "V/ii", "V/iii",    "V/V",  "V/vi" }, // Starting Chord
                                    { "V",      "ii",   "vi",   "ii",   "ii",   "iii",      "V",    "vi" }, // Ending Chord
                                    { "V/V",    "vi",   "N/A",  "V",    "V/V",  "V/vi",     "N/A",  "V/ii" },
                                    { "N/A",    "V/ii", "N/A",  "V/ii", "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "N/A",    "V/vi", "N/A",  "V/V",  "N/A",  "N/A",      "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "ii",     "iii",      "V",    "vi",       "viio", "V/ii",     "V/iii",    "V/V",  "V/vi",     "viio/ii",  "viio/iii", "viio/V",   "viio/vi" }, // Starting Chord
                                    { "V",      "ii",       "vi",   "ii",       "V",    "ii",       "iii",      "V",    "vi",       "ii",       "iii",      "V",        "vi" }, // Ending Chord
                                    { "viio",   "vi",       "N/A",  "V",        "N/A",  "V/V",      "V/vi",     "viio", "V/ii",     "V/V",      "V/vi",     "viio",     "V/ii" },
                                    { "V/V",    "V/ii",     "N/A",  "V/ii",     "N/A",  "viio/V",   "viio/vi",  "N/A",  "viio/ii",  "viio/V",   "viio/vi",  "N/A",      "viio/ii" },
                                    { "viio/V", "V/vi",     "N/A",  "V/V",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "N/A",    "viio/ii",  "N/A",  "viio/ii",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "N/A",    "viio/vi",  "N/A",  "viio/vi",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "ii",     "iii",  "IV" }, // Starting Chord
                                    { "N/A",    "ii",   "ii" }, // Ending Chord
                                    { "N/A",    "IV",   "N/A" }
                                },
                                { // Yes Chord 7
                                    { "ii",     "iii",      "IV",   "viio", "viio/ii",  "viio/iii", "viio/IV" }, // Starting Chord
                                    { "viio",   "ii",       "ii",   "N/A",  "ii",       "iii",      "IV" }, // Ending Chord
                                    { "N/A",    "IV",       "viio", "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "N/A",    "viio/ii",  "N/A",  "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "ii",     "iii",  "IV",   "vi" }, // Starting Chord
                                    { "N/A",    "ii",   "ii",   "ii" }, // Ending Chord
                                    { "N/A",    "IV",   "N/A",  "IV" },
                                    { "N/A",    "vi",   "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "ii",     "iii",      "IV",   "vi",       "viio", "viio/ii",  "viio/iii", "viio/IV",  "viio/vi" }, // Starting Chord
                                    { "viio",   "ii",       "ii",   "ii",       "N/A",  "ii",       "iii",      "IV",       "vi" }, // Ending Chord
                                    { "N/A",    "IV",       "viio", "IV",       "N/A",  "N/A",      "viio/vi",  "N/A",      "viio/ii" },
                                    { "N/A",    "vi",       "N/A",  "viio/ii",  "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "N/A",    "viio/ii",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "N/A",    "viio/vi",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "ii",     "iii",  "IV",   "V",    "V/ii", "V/iii",    "V/IV", "V/V" }, // Starting Chord
                                    { "V",      "ii",   "ii",   "N/A",  "ii",   "iii",      "IV",   "V" }, // Ending Chord
                                    { "V/V",    "IV",   "V",    "N/A",  "V/V",  "N/A",      "N/A",  "V/IV" },
                                    { "N/A",    "V/ii", "V/V",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "ii",     "iii",      "IV",       "V",    "viio", "V/ii",     "V/iii",    "V/IV", "V/V",      "viio/ii",  "viio/iii", "viio/IV",  "viio/V" }, // Starting Chord
                                    { "V",      "ii",       "ii",       "N/A",  "V",    "ii",       "iii",      "IV",   "V",        "ii",       "iii",      "IV",       "V" }, // Ending Chord
                                    { "viio",   "IV",       "V",        "N/A",  "N/A",  "V/V",      "N/A",      "N/A",  "viio",     "V/V",      "N/A",      "N/A",      "viio" },
                                    { "V/V",    "V/ii",     "viio",     "N/A",  "N/A",  "viio/V",   "N/A",      "N/A",  "V/IV",     "viio/V",   "N/A",      "N/A",      "V/IV" },
                                    { "viio/V", "viio/ii",  "V/V",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "viio/IV",  "N/A",      "N/A",      "N/A",      "viio/IV" },
                                    { "N/A",    "N/A",      "viio/V",   "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A,"      "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "ii",     "iii",  "IV",   "V",    "vi",   "V/ii", "V/iii",    "V/IV", "V/V",  "V/vi" }, // Starting Chord
                                    { "V",      "ii",   "ii",   "vi",   "ii",   "ii",   "iii",      "IV",   "V",    "vi" }, // Ending Chord
                                    { "V/V",    "IV",   "V",    "N/A",  "IV",   "V/V",  "V/vi",     "N/A",  "V/IV", "V/ii" },
                                    { "N/A",    "vi",   "V/V",  "N/A",  "V",    "N/A",  "N/A",      "N/A",  "N/A",  "N/A" },
                                    { "N/A",    "V/ii", "N/A",  "N/A",  "V/ii", "N/A",  "N/A",      "N/A",  "N/A",  "N/A" },
                                    { "N/A",    "V/vi", "N/A",  "N/A",  "V/V",  "N/A",  "N/A",      "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "ii",     "iii",      "IV",       "V",    "vi",       "viio", "V/ii",     "V/iii",    "V/IV", "V/V",      "V/vi",     "viio/ii",  "viio/iii", "viio/IV",  "viio/V",   "viio/vi" }, // Starting Chord
                                    { "V",      "ii",       "ii",       "vi",   "ii",       "V",    "ii",       "iii",      "IV",   "V",        "vi",       "ii",       "iii",      "IV",       "V",        "vi" }, // Ending Chord
                                    { "viio",   "IV",       "V",        "N/A",  "IV",       "N/A",  "V/V",      "V/vi",     "N/A",  "viio",     "V/ii",     "V/V",      "V/vi",     "N/A",      "viio",     "V/ii" },
                                    { "V/V",    "vi",       "viio",     "N/A",  "V",        "N/A",  "viio/V",   "viio/vi",  "N/A",  "V/IV",     "viio/ii",  "viio/V",   "viio/vi",  "N/A",      "V/IV",     "viio/ii" },
                                    { "viio/V", "V/ii",     "V/V",      "N/A",  "V/ii",     "N/A",  "N/A",      "N/A",      "N/A",  "viio/IV",  "N/A",      "N/A",      "N/A",      "N/A",      "viio/IV",  "N/A" },
                                    { "N/A",    "V/vi",     "viio/V",   "N/A",  "V/V",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "N/A",    "viio/ii",  "N/A",      "N/A",  "viio/ii",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "N/A",    "viio/vi",  "N/A",      "N/A",  "viio/V",   "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            }
                        }
                    }
                }
            }
        },
        { // Yes Chord 1
            { // No Chord 2
                { // No Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I" }, // Starting Chord
                                    { "N/A" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "I",      "viio" }, // Starting Chord
                                    { "viio",   "I"} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",  "vi"}, // Starting Chord
                                    { "vi", "N/A" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "I",          "vi",   "viio", "viio/vi" }, // Starting Chord
                                    { "vi",         "N/A",  "I",    "vi" }, // Ending Chord
                                    { "viio",       "N/A",  "N/A",  "N/A" },
                                    { "viio/vi",    "N/A",  "N/A",  "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",      "V",    "V/V" }, // Starting Chord
                                    { "V",      "I",    "V" }, // Ending Chord
                                    { "V/V",    "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",      "V",    "viio", "V/V",  "viio/V" }, // Starting Chord
                                    { "V",      "I",    "I",    "V",    "V" }, // Ending Chord
                                    { "viio",   "N/A",  "V",    "viio", "viio" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "viio/V", "N/A",  "N/A",  "N/A",  "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",      "V",    "vi",   "V/V",  "V/vi" }, // Starting Chord
                                    { "V",      "I",    "V",    "V",    "vi" }, // Ending Chord
                                    { "vi",     "vi",   "V/V",  "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "V/vi",   "N/A",  "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "V",    "vi",       "viio", "V/V",  "V/vi", "viio/V",   "viio/vi" }, // Starting Chord
                                    { "V",          "I",    "V",        "I",    "V",    "vi",   "V",        "vi" }, // Ending Chord
                                    { "vi",         "vi",   "V/V",      "V",    "viio", "N/A",  "viio",     "N/A" },
                                    { "viio",       "N/A",  "viio/V",   "N/A",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "V/V",        "N/A",  "N/A",      "N/A",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "V/vi",       "N/A",  "N/A",      "N/A",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "viio/V",     "N/A",  "N/A",      "N/A",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",  "N/A",      "N/A",  "N/A",  "N/A",  "N/A",      "N/A" }
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",  "IV" }, // Starting Chord
                                    { "IV", "I" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "I",          "IV",   "viio", "viio/IV" }, // Starting Chord
                                    { "IV",         "I",    "I",    "IV" }, // Ending Chord
                                    { "viio",       "viio", "N/A",  "N/A" },
                                    { "viio/IV",    "N/A",  "N/A",  "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",  "IV",   "vi" }, // Starting Chord
                                    { "IV", "I",    "IV" }, // Ending Chord
                                    { "vi", "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "IV",   "vi",   "viio", "viio/IV",  "viio/vi" }, // Starting Chord
                                    { "IV",         "I",    "IV",   "I",    "IV",       "vi" }, // Ending Chord
                                    { "vi",         "viio", "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "viio",       "N/A",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",  "N/A",  "N/A",  "N/A",      "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",      "IV",   "V",    "V/IV", "V/V" }, // Starting Chord
                                    { "IV",     "I",    "I",    "IV",   "V" }, // Ending Chord
                                    { "V",      "V",    "N/A",  "N/A",  "V/VI" },
                                    { "V/IV",   "V/V",  "N/A",  "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "IV",       "V",    "viio", "V/IV", "V/V",      "viio/IV",  "viio/V" }, // Starting Chord
                                    { "IV",         "I",        "I",    "I",    "IV",   "V",        "IV",       "V" }, // Ending Chord
                                    { "V",          "V",        "N/A",  "V",    "N/A",  "viio",     "N/A",      "viio" },
                                    { "viio",       "viio",     "N/A",  "N/A",  "N/A",  "V/IV",     "N/A",      "V/IV" },
                                    { "V/IV",       "V/V",      "N/A",  "N/A",  "N/A",  "viio/IV",  "N/A",      "viio/IV" },
                                    { "V/V",        "viio/V",   "N/A",  "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",      "N/A",  "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/V",     "N/A",      "N/A",  "N/A",  "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",      "IV",   "V",    "vi",   "V/IV", "V/V",  "V/vi" }, // Starting Chord
                                    { "IV",     "I",    "I",    "IV",   "IV",   "V",    "vi" }, // Ending Chord
                                    { "V",      "V",    "vi",   "V",    "N/A",  "V/IV", "N/A" },
                                    { "vi",     "V/V",  "N/A",  "V/V",  "N/A",  "N/A",  "N/A" },
                                    { "V/IV",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "V/vi",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "IV",       "V",    "vi",       "viio", "V/IV", "V/V",      "V/vi", "viio/IV",  "viio/V",   "viio/vi" }, // Starting Chord
                                    { "IV",         "I",        "I",    "IV",       "I",    "IV",   "V",        "vi",   "IV",       "V",        "vi" }, // Ending Chord
                                    { "V",          "V",        "vi",   "V",        "V",    "N/A",  "viio",     "N/A",  "N/A",      "viio",     "N/A" },
                                    { "vi",         "viio",     "N/A",  "V/V",      "N/A",  "N/A",  "V/IV",     "N/A",  "N/A",      "V/IV",     "N/A" },
                                    { "viio",       "V/V",      "N/A",  "viio/V",   "N/A",  "N/A",  "viio/IV",  "N/A",  "N/A",      "viio/IV",  "N/A" },
                                    { "V/IV",       "viio/V",   "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "V/V",        "N/A",      "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "V/vi",       "N/A",      "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",      "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/V",     "N/A",      "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",      "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            }
                        }
                    }
                },
                { // Yes Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",      "iii" }, // Starting Chord
                                    { "iii",    "N/A" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "I",          "iii",  "viio", "viio/iii" }, // Starting Chord
                                    { "iii",        "N/A",  "I",    "iii" }, // Ending Chord
                                    { "viio",       "N/A",  "N/A",  "N/A" },
                                    { "viio/iii",   "N/A",  "N/A",  "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",      "iii",  "vi" }, // Starting Chord
                                    { "iii",    "vi",   "N/A" }, // Ending Chord
                                    { "vi",     "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "iii",      "vi",   "viio", "viio/iii", "viio/vi" }, // Starting Chord
                                    { "iii",        "vi",       "N/A",  "I",    "iii",      "vi" }, // Ending Chord
                                    { "vi",         "viio/vi",  "N/A",  "N/A",  "viio/vi",  "N/A" },
                                    { "viio",       "N/A",      "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",      "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",      "N/A",  "N/A",  "N/A",      "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",      "iii",  "V",    "V/iii",    "V/V" }, // Starting Chord
                                    { "iii",    "N/A",  "I",    "iii",      "V" }, // Ending Chord
                                    { "V",      "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "V/iii",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",      "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "iii",  "V",    "viio", "V/iii",    "V/V",  "viio/iii", "viio/V" }, // Starting Chord
                                    { "iii",        "N/A",  "I",    "I",    "iii",      "V",    "iii",      "V" }, // Ending Chord
                                    { "V",          "N/A",  "N/A",  "V",    "N/A",      "viio", "N/A",      "viio" },
                                    { "viio",       "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A" },
                                    { "V/iii",      "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A" },
                                    { "V/V",        "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A" },
                                    { "viio/V",     "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",      "iii",  "V",    "vi",   "V/iii",    "V/V",  "V/vi" }, // Starting Chord
                                    { "iii",    "vi",   "I",    "V",    "iii",      "V",    "vi" }, // Ending Chord
                                    { "V",      "V/vi", "vi",   "V/V",  "V/vi",     "N/A",  "N/A" },
                                    { "vi",     "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/iii",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/vi",   "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "iii",      "V",    "vi",       "viio", "V/iii",    "V/V",  "V/vi", "viio/iii", "viio/V",   "viio/vi" }, // Starting Chord
                                    { "iii",        "vi",       "I",    "V",        "I",    "iii",      "V",    "vi",   "iii",      "V",        "vi" }, // Ending Chord
                                    { "V",          "V/vi",     "vi",   "V/V",      "V",    "V/vi",     "viio", "N/A",  "V/vi",     "viio",     "N/A" },
                                    { "vi",         "viio/vi",  "N/A",  "viio/V",   "N/A",  "viio/vi",  "N/A",  "N/A",  "viio/vi",  "N/A",      "N/A" },
                                    { "viio",       "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "V/iii",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "V/V",        "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "V/vi",       "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/V",     "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",      "iii",  "IV" }, // Starting Chord
                                    { "iii",    "IV",   "I" }, // Ending Chord
                                    { "IV",     "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "iii",  "IV",   "viio", "viio/iii", "viio/IV" }, // Starting Chord
                                    { "iii",        "IV",   "I",    "I",    "iii",      "IV" }, // Ending Chord
                                    { "IV",         "N/A",  "viio", "N/A",  "N/A",      "N/A" },
                                    { "viio",       "N/A",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",  "N/A",  "N/A",  "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",      "iii",  "IV",   "vi" }, // Starting Chord
                                    { "iii",    "IV",   "I",    "IV" }, // Ending Chord
                                    { "IV",     "vi",   "N/A",  "N/A" },
                                    { "vi",     "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "iii",      "IV",   "vi",   "viio", "viio/iii", "viio/IV",  "viio/vi" }, // Starting Chord
                                    { "iii",        "IV",       "I",    "IV",   "I",    "iii",      "IV",       "vi" }, // Ending Chord
                                    { "IV",         "vi",       "viio", "N/A",  "N/A",  "viio/vi",  "N/A",      "N/A" },
                                    { "vi",         "viio/vi",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio",       "N/A",      "N/A",  "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",      "N/A",  "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",      "N/A",  "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",      "N/A",  "N/A",  "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",      "iii",  "IV",   "V",    "V/iii",    "V/IV", "V/V" }, // Starting Chord
                                    { "iii",    "IV",   "I",    "I",    "iii",      "IV",   "V" }, // Ending Chord
                                    { "IV",     "N/A",  "V",    "N/A",  "N/A",      "N/A",  "V/IV" },
                                    { "V",      "N/A",  "V/V",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/iii",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/IV",   "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "iii",  "IV",       "V",    "viio", "V/iii",    "V/IV", "V/V",      "viio/iii", "viio/IV",  "viio/V" }, // Starting Chord
                                    { "iii",        "IV",   "I",        "I",    "I",    "iii",      "IV",   "V",        "iii",      "IV",       "V" }, // Ending Chord
                                    { "IV",         "N/A",  "V",        "N/A",  "V",    "N/A",      "N/A",  "viio",     "N/A",      "N/A",      "viio" },
                                    { "V",          "N/A",  "viio",     "N/A",  "N/A",  "N/A",      "N/A",  "V/IV",     "N/A",      "N/A",      "V/IV" },
                                    { "viio",       "N/A",  "V/V",      "N/A",  "N/A",  "N/A",      "N/A",  "viio/IV",  "N/A",      "N/A",      "viio/IV" },
                                    { "V/iii",      "N/A",  "viio/V",   "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/IV",       "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/V",        "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/V",     "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",      "iii",  "IV",   "V",    "vi",   "V/iii",    "V/IV", "V/V",  "V/vi" }, // Starting Chord
                                    { "iii",    "IV",   "I",    "I",    "IV",   "iii",      "IV",   "V",    "vi" }, // Ending Chord
                                    { "IV",     "vi",   "V",    "vi",   "V",    "V/vi",     "N/A",  "V/IV", "N/A" },
                                    { "V",      "V/vi", "V/V",  "N/A",  "V/V",  "N/A",      "N/A",  "N/A",  "N/A" },
                                    { "vi",     "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A",  "N/A" },
                                    { "V/iii",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A",  "N/A" },
                                    { "V/IV",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A",  "N/A" },
                                    { "V/vi",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "iii",      "IV",       "V",    "vi",       "viio", "V/iii",    "V/IV", "V/V",      "V/vi", "viio/iii", "viio/IV",  "viio/V",   "viio/vi" }, // Starting Chord
                                    { "iii",        "IV",       "I",        "I",    "IV",       "I",    "iii",      "IV",   "V",        "vi",   "iii",      "IV",       "V",        "vi" }, // Ending Chord
                                    { "IV",         "vi",       "V",        "vi",   "V",        "V",    "V/vi",     "N/A",  "viio",     "N/A",  "V/vi",     "N/A",      "viio",     "N/A" },
                                    { "V",          "V/vi",     "viio",     "N/A",  "V/V",      "N/A",  "viio/vi",  "N/A",  "V/IV",     "N/A",  "viio/vi",  "N/A",      "V/IV",     "N/A" },
                                    { "vi",         "viio/vi",  "V/V",      "N/A",  "viio/V",   "N/A",  "N/A",      "N/A",  "viio/IV",  "N/A",  "N/A",      "N/A",      "viio/IV",  "N/A" },
                                    { "viio",       "N/A",      "viio/V",   "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/iii",      "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/IV",       "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/V",        "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/vi",       "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/V",     "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            }
                        }
                    }
                }
            },
            { // Yes Chord 2
                { // No Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",  "ii" }, // Starting Chord
                                    { "ii", "N/A" } // Ending Chord
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",   "viio", "viio/ii" }, // Starting Chord
                                    { "ii",         "viio", "I",    "ii" }, // Ending Chord
                                    { "viio",       "N/A",  "N/A",  "N/A" },
                                    { "viio/ii",    "N/A",  "N/A",  "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",  "ii",   "vi" }, // Starting Chord
                                    { "ii", "N/A",  "ii" }, // Ending Chord
                                    { "vi", "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",   "vi",       "viio", "viio/ii",  "viio/vi" }, // Starting Chord
                                    { "ii",         "viio", "ii",       "I",    "ii",       "vi" }, // Ending Chord
                                    { "viio",       "N/A",  "viio/ii",  "N/A",  "N/A",      "viio/ii" },
                                    { "viio/ii",    "N/A",  "N/A",      "N/A",  "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",  "N/A",      "N/A",  "N/A",      "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",      "ii",   "V",    "V/ii", "V/V" }, // Starting Chord
                                    { "ii",     "V",    "I",    "ii",   "V" }, // Ending Chord
                                    { "V",      "V/V",  "N/A",  "V/V",  "N/A" },
                                    { "V/ii",   "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",       "V",    "viio", "V/ii",     "V/V",  "viio/ii",  "viio/V" }, // Starting Chord
                                    { "ii",         "V",        "I",    "I",    "ii",       "V",    "ii",       "V" }, // Ending Chord
                                    { "V",          "viio",     "N/A",  "V",    "V/V",      "viio", "V/V",      "viio" },
                                    { "viio",       "V/V",      "N/A",  "N/A",  "viio/V",   "N/A",  "viio/V",   "N/A" },
                                    { "V/ii",       "viio/V",   "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A" },
                                    { "V/V",        "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A" },
                                    { "viio/V",     "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",      "ii",   "V",    "vi",   "V/ii", "V/V",  "V/vi" }, // Starting Chord
                                    { "ii",     "V",    "I",    "ii",   "ii",   "V",    "vi" }, // Ending Chord
                                    { "V",      "V/V",  "vi",   "V",    "V/V",  "N/A",  "V/ii" },
                                    { "vi",     "N/A",  "N/A",  "V/ii", "N/A",  "N/A",  "N/A" },
                                    { "V/ii",   "N/A",  "N/A",  "V/V",  "N/A",  "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "V/vi",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",       "V",    "vi",       "viio", "V/ii",     "V/V",  "V/vi",     "viio/ii",  "viio/V",   "viio/vi" }, // Starting Chord
                                    { "ii",         "V",        "I",    "ii",       "I",    "ii",       "V",    "vi",       "ii",       "V",        "vi" }, // Ending Chord
                                    { "V",          "viio",     "vi",   "V",        "V",    "V/V",      "viio", "V/ii",     "V/V",      "viio",     "V/ii" },
                                    { "vi",         "V/V",      "N/A",  "V/ii",     "N/A",  "viio/V",   "N/A",  "viio/ii",  "viio/V",   "N/A",      "viio/ii" },
                                    { "viio",       "viio/V",   "N/A",  "V/V",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/ii",       "N/A",      "N/A",  "viio/ii",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/V",        "N/A",      "N/A",  "viio/V",   "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/vi",       "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/V",     "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",  "ii",   "IV" }, // Starting Chord
                                    { "ii", "N/A",  "I" }, // Ending Chord
                                    { "IV", "N/A",  "ii" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",   "IV",   "viio", "viio/ii",  "viio/IV" }, // Starting Chord
                                    { "ii",         "viio", "I",    "I",    "ii",       "IV" }, // Ending Chord
                                    { "IV",         "N/A",  "ii",   "N/A",  "N/A",      "N/A" },
                                    { "viio",       "N/A",  "viio", "N/A",  "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",  "N/A",  "N/A",  "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",  "ii",   "IV",   "vi" }, // Starting Chord
                                    { "ii", "N/A",  "I",    "ii" }, // Ending Chord
                                    { "IV", "N/A",  "ii",   "IV" },
                                    { "vi", "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",   "IV",   "vi",       "viio", "viio/ii",  "viio/IV",  "viio/vi" }, // Starting Chord
                                    { "ii",         "viio", "I",    "ii",       "I",    "ii",       "IV",       "vi" }, // Ending Chord
                                    { "IV",         "N/A",  "ii",   "IV",       "N/A",  "N/A",      "N/A",      "viio/ii" },
                                    { "vi",         "N/A",  "viio", "viio/ii",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio",       "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",      "ii",   "IV",   "V",    "V/ii", "V/IV", "V/V" }, // Starting Chord
                                    { "ii",     "V",    "I",    "I",    "ii",   "IV",   "V" }, // Ending Chord
                                    { "IV",     "V/V",  "ii",   "N/A",  "V/V",  "N/A",  "V/IV" },
                                    { "V",      "N/A",  "V",    "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "V/ii",   "N/A",  "V/V",  "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "V/IV",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",       "IV",       "V",    "viio", "V/ii",     "V/IV", "V/V",      "viio/ii",  "viio/IV",  "viio/V" }, // Starting Chord
                                    { "ii",         "V",        "I",        "I",    "I",    "ii",       "IV",   "V",        "ii",       "IV",       "V" }, // Ending Chord
                                    { "IV",         "viio",     "ii",       "N/A",  "V",    "V/V",      "N/A",  "viio",     "V/V",      "N/A",      "viio" },
                                    { "V",          "V/V",      "V",        "N/A",  "N/A",  "viio/V",   "N/A",  "V/IV",     "viio/V",   "N/A",      "V/IV" },
                                    { "viio",       "viio/V",   "viio",     "N/A",  "N/A",  "N/A",      "N/A",  "viio/IV",  "N/A",      "N/A",      "viio/IV" },
                                    { "V/ii",       "N/A",      "V/V",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/IV",       "N/A",      "viio/V",   "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/V",        "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/V",     "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",      "ii",   "IV",   "V",    "vi",   "V/ii", "V/IV", "V/V",  "V/vi" }, // Starting Chord
                                    { "ii",     "V",    "I",    "I",    "ii",   "ii",   "IV",   "V",    "vi" }, // Ending Chord
                                    { "IV",     "V/V",  "ii",   "vi",   "IV",   "V/V",  "N/A",  "V/IV", "V/ii" },
                                    { "V",      "N/A",  "V",    "N/A",  "V",    "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "vi",     "N/A",  "V/V",  "N/A",  "V/ii", "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "V/ii",   "N/A",  "N/A",  "N/A",  "V/V",  "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "V/IV",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A" },
                                    { "V/vi",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",       "IV",       "V",    "vi",       "viio", "V/ii",     "V/IV", "V/V",      "V/vi",     "viio/ii",  "viio/IV",  "viio/V",   "viio/vi" }, // Starting Chord
                                    { "ii",         "V",        "I",        "I",    "ii",       "I",    "ii",       "IV",   "V",        "vi",       "ii",       "IV",       "V",        "vi" }, // Ending Chord
                                    { "IV",         "viio",     "ii",       "vi",   "IV",       "V",    "V/V",      "N/A",  "viio",     "V/ii",     "V/V",      "N/A",      "viio",     "V/ii" },
                                    { "V",          "V/V",      "V",        "N/A",  "V",        "N/A",  "viio/V",   "N/A",  "V/IV",     "viio/ii",  "viio/V",   "N/A",      "V/IV",     "viio/ii" },
                                    { "vi",         "viio/V",   "viio",     "N/A",  "V/ii",     "N/A",  "N/A",      "N/A",  "viio/IV",  "N/A",      "N/A",      "N/A",      "viio/IV",  "N/A" },
                                    { "viio",       "N/A",      "V/V",      "N/A",  "V/V",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/ii",       "N/A",      "viio/V",   "N/A",  "viio/ii",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/IV",       "N/A",      "N/A",      "N/A",  "viio/V",   "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/V",        "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/vi",       "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/V",     "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            }
                        }
                    }
                },
                { // Yes Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",      "ii",   "iii" }, // Starting Chord
                                    { "ii",     "N/A",  "ii" }, // Ending Chord
                                    { "iii",    "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",   "iii",      "viio", "viio/ii",  "viio/iii" }, // Starting Chord
                                    { "ii",         "viio", "ii",       "I",    "ii",       "iii" }, // Ending Chord
                                    { "iii",        "N/A",  "viio/ii",  "N/A",  "N/A",      "N/A" },
                                    { "viio",       "N/A",  "N/A",      "N/A",  "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",  "N/A",      "N/A",  "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",  "N/A",      "N/A",  "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",      "ii",   "iii",  "vi" }, // Starting Chord
                                    { "ii",     "N/A",  "ii",   "ii" }, // Ending Chord
                                    { "iii",    "N/A",  "vi",   "N/A" },
                                    { "vi",     "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",   "iii",      "vi",       "viio", "viio/ii",  "viio/iii", "viio/vi" }, // Starting Chord
                                    { "ii",         "viio", "ii",       "ii",       "I",    "ii",       "iii",      "vi" }, // Ending Chord
                                    { "iii",        "N/A",  "vi",       "viio/ii",  "N/A",  "N/A",      "viio/vi",  "viio/ii" },
                                    { "vi",         "N/A",  "viio/ii",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio",       "N/A",  "viio/vi",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",      "ii",   "iii",  "V",    "V/ii", "V/iii",    "V/V" }, // Starting Chord
                                    { "ii",     "V",    "ii",   "I",    "ii",   "iii",      "V" }, // Ending Chord
                                    { "iii",    "V/V",  "V/ii", "N/A",  "V/V",  "N/A",      "N/A" },
                                    { "V",      "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "V/ii",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "V/iii",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",       "iii",      "V",    "viio", "V/ii",     "V/iii",    "V/V",  "viio/ii",  "viio/iii", "viio/V" }, // Starting Chord
                                    { "ii",         "V",        "ii",       "N/A",  "I",    "ii",       "iii",      "V",    "ii",       "iii",      "V" }, // Ending Chord
                                    { "iii",        "viio",     "V/ii",     "N/A",  "V",    "V/V",      "N/A",      "viio", "V/V",      "N/A",      "viio" },
                                    { "V",          "V/V",      "viio/ii",  "N/A",  "N/A",  "viio/V",   "N/A",      "N/A",  "viio/V",   "N/A",      "N/A" },
                                    { "viio",       "viio/V",   "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "V/ii",       "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "V/iii",      "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "V/V",        "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/V",     "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",      "ii",   "iii",  "V",    "vi",   "V/ii", "V/iii",    "V/V",  "V/vi" }, // Starting Chord
                                    { "ii",     "V",    "ii",   "I",    "ii",   "ii",   "iii",      "V",    "vi" }, // Ending Chord
                                    { "iii",    "V/V",  "vi",   "vi",   "V",    "V/V",  "V/vi",     "N/A",  "V/ii" },
                                    { "V",      "N/A",  "V/ii", "N/A",  "V/ii", "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "vi",     "N/A",  "V/vi", "N/A",  "V/V",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/ii",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/iii",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/vi",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",       "iii",      "V",    "vi",       "viio", "V/ii",     "V/iii",    "V/V",  "V/vi",     "viio/ii",  "viio/iii", "viio/V",   "viio/vi" }, // Starting Chord
                                    { "ii",         "V",        "ii",       "I",    "ii",       "I",    "ii",       "iii",      "V",    "vi",       "ii",       "iii",      "V",        "vi" }, // Ending Chord
                                    { "iii",        "viio",     "vi",       "vi",   "V",        "V",    "V/V",      "V/vi",     "viio", "V/ii",     "V/V",      "V/vi",     "viio",     "V/ii" },
                                    { "V",          "V/V",      "V/ii",     "N/A",  "V/ii",     "N/A",  "viio/V",   "viio/vi",  "N/A",  "viio/ii",  "viio/V",   "viio/vi",  "N/A",      "viio/ii" },
                                    { "vi",         "viio/V",   "V/vi",     "N/A",  "V/V",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio",       "N/A",      "viio/ii",  "N/A",  "viio/ii",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/ii",       "N/A",      "viio/vi",  "N/A",  "viio/vi",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/iii",      "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/V",        "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/vi",       "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/V",     "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",      "ii",   "iii",  "IV" }, // Starting Chord
                                    { "ii",     "N/A",  "ii",   "I" }, // Ending Chord
                                    { "iii",    "N/A",  "IV",   "ii" },
                                    { "IV",     "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",   "iii",      "IV",   "viio", "viio/ii",  "viio/iii", "viio/IV" }, // Starting Chord
                                    { "ii",         "viio", "ii",       "I",    "I",    "ii",       "iii",      "IV" }, // Ending Chord
                                    { "iii",        "N/A",  "IV",       "ii",   "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "IV",         "N/A",  "viio/ii",  "viio", "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio",       "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",  "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",      "ii",   "iii",  "IV",   "vi" }, // Starting Chord
                                    { "ii",     "N/A",  "ii",   "I",    "ii" }, // Ending Chord
                                    { "iii",    "N/A",  "IV",   "ii",   "IV" },
                                    { "IV",     "N/A",  "vi",   "N/A",  "N/A" },
                                    { "vi",     "N/A",  "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",   "iii",      "IV",   "vi",       "viio", "viio/ii",  "viio/iii", "viio/IV",  "viio/vi" }, // Starting Chord
                                    { "ii",         "viio", "ii",       "I",    "ii",       "I",    "ii",       "iii",      "IV",       "vi" }, // Ending Chord
                                    { "iii",        "N/A",  "IV",       "ii",   "IV",       "N/A",  "N/A",      "viio/vi",  "N/A",      "viio/ii" },
                                    { "IV",         "N/A",  "vi",       "viio", "viio/ii",  "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "vi",         "N/A",  "viio/ii",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio",       "N/A",  "viio/vi",  "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",  "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    { "I",      "ii",   "iii",  "IV",   "V",    "V/ii", "V/iii",    "V/IV", "V/V" }, // Starting Chord
                                    { "ii",     "V",    "ii",   "I",    "I",    "ii",   "iii",      "IV",   "V" }, // Ending Chord
                                    { "iii",    "V/V",  "IV",   "ii",   "N/A",  "V/V",  "N/A",      "N/A",  "V/IV" },
                                    { "IV",     "N/A",  "V/ii", "V",    "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V",      "N/A",  "N/A",  "V/V",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/ii",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/iii",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/IV",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",      "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",       "iii",      "IV",       "V",    "viio", "V/ii",     "V/iii",    "V/IV", "V/V",      "viio/ii",  "viio/iii", "viio/IV",  "viio/V" }, // Starting Chord
                                    { "ii",         "V",        "ii",       "I",        "I",    "I",    "ii",       "iii",      "IV",   "V",        "ii",       "iii",      "IV",       "V" }, // Ending Chord
                                    { "iii",        "viio",     "IV",       "ii",       "N/A",  "V",    "V/V",      "N/A",      "N/A",  "viio",     "V/V",      "N/A",      "N/A",      "viio" },
                                    { "IV",         "V/V",      "V/ii",     "V",        "N/A",  "N/A",  "viio/V",   "N/A",      "N/A",  "V/IV",     "viio/V",   "N/A",      "N/A",      "V/IV" },
                                    { "V",          "viio/V",   "viio/ii",  "viio",     "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "viio/IV",  "N/A",      "N/A",      "N/A",      "viio/IV" },
                                    { "viio",       "N/A",      "N/A",      "V/V",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A,"      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/ii",       "N/A",      "N/A",      "viio/V",   "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/iii",      "N/A",      "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/IV",       "N/A",      "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/V",        "N/A",      "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",      "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",      "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",      "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/V",     "N/A",      "N/A",      "N/A",      "N/A",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    { "I",      "ii",   "iii",  "IV",   "V",    "vi",   "V/ii", "V/iii",    "V/IV", "V/V",  "V/vi" }, // Starting Chord
                                    { "ii",     "V",    "ii",   "I",    "I",    "ii",   "ii",   "iii",      "IV",   "V",    "vi" }, // Ending Chord
                                    { "iii",    "V/V",  "IV",   "ii",   "vi",   "IV",   "V/V",  "V/vi",     "N/A",  "V/IV", "V/ii" },
                                    { "IV",     "N/A",  "vi",   "V",    "N/A",  "V",    "N/A",  "N/A",      "N/A",  "N/A",  "N/A" },
                                    { "V",      "N/A",  "V/ii", "V/V",  "N/A",  "V/ii", "N/A",  "N/A",      "N/A",  "N/A",  "N/A" },
                                    { "vi",     "N/A",  "V/vi", "N/A",  "N/A",  "V/V",  "N/A",  "N/A",      "N/A",  "N/A",  "N/A" },
                                    { "V/ii",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "n/A",      "N/A",  "N/A",  "N/A" },
                                    { "V/iii",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "n/A",      "N/A",  "N/A",  "N/A" },
                                    { "V/IV",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "n/A",      "N/A",  "N/A",  "N/A" },
                                    { "V/V",    "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "n/A",      "N/A",  "N/A",  "N/A" },
                                    { "V/vi",   "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "N/A",  "n/A",      "N/A",  "N/A",  "N/A" }
                                },
                                { // Yes Chord 7
                                    { "I",          "ii",       "iii",      "IV",       "V",   "vi",       "viio", "V/ii",     "V/iii",    "V/IV", "V/V",      "V/vi",     "viio/ii",  "viio/iii", "viio/IV",  "viio/V",   "viio/vi" }, // Starting Chord
                                    { "ii",         "V",        "ii",       "I",        "I",   "ii",        "I",    "ii",       "iii",      "IV",   "V",        "vi",       "ii",       "iii",      "IV",       "V",        "vi" }, // Ending Chord
                                    { "iii",        "viio",     "IV",       "ii",       "vi",  "IV",        "V",    "V/V",      "V/vi",     "N/A",  "viio",     "V/ii",     "V/V",      "V/vi",     "N/A",      "viio",     "V/ii" },
                                    { "IV",         "V/V",      "vi",       "V",        "N/A",  "V",        "N/A",  "viio/V",   "viio/vi",  "N/A",  "V/IV",     "viio/ii",  "viio/V",   "viio/vi",  "N/A",      "V/IV",     "viio/ii" },
                                    { "V",          "viio/V",   "V/ii",     "viio",     "N/A",  "V/ii",     "N/A",  "N/A",      "N/A",      "N/A",  "viio/IV",  "N/A",      "N/A",      "N/A",      "N/A",      "viio/IV",  "N/A" },
                                    { "vi",         "N/A",      "V/vi",     "V/V",      "N/A",  "V/V",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio",       "N/A",      "viio/ii",  "viio/V",   "N/A",  "viio/ii",  "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/ii",       "N/A",      "viio/vi",  "N/A",      "N/A",  "viio/V",   "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/iii",      "N/A",      "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/IV",       "N/A",      "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/V",        "N/A",      "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "V/vi",       "N/A",      "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/ii",    "N/A",      "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/iii",   "N/A",      "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/IV",    "N/A",      "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/V",     "N/A",      "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" },
                                    { "viio/vi",    "N/A",      "N/A",      "N/A",      "N/A",  "N/A",      "N/A",  "N/A",      "N/A",      "N/A",  "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A",      "N/A" }
                                }
                            }
                        }
                    }
                }
            }
        }
    },
    { // Minor
        { // No Chord 1
            { // No Chord 2
                { // No Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    }
                },
                { // Yes Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    }
                }
            },
            { // Yes Chord 2
                { // No Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    }
                },
                { // Yes Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    }
                }
            }
        },
        { // Yes Chord 1
            { // No Chord 2
                { // No Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    }
                },
                { // Yes Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    }
                }
            },
            { // Yes Chord 2
                { // No Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    }
                },
                { // Yes Chord 3
                    { // No Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    },
                    { // Yes Chord 4
                        { // No Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        },
                        { // Yes Chord 5
                            { // No Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            },
                            { // Yes Chord 6
                                { // No Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                },
                                { // Yes Chord 7
                                    {}, // Starting Chord
                                    {} // Ending Chord
                                }
                            }
                        }
                    }
                }
            }
        }
    }
};

// Minor Scale:         Tone, Semitone, Tone, Tone, Semitone, Tone, Tone
// Example:            C     D        Eb     F     G        Ab    Bb    C
// Major Scale:         Tone, Tone, Semitone, Tone, Tone, Tone, Semitone
// Example:            C     D     E         F     G     A     B        C

void generateComposition()
{
    chordProgressionSelectionCheck = 0;
    compositionMinLength = -1;
    compositionMaxLength = -1;
    system("CLS");
    cout << "Composition Random Generator | Config" << endl;
    cout << "Please press the corresponding number keys for the options." << endl;
    cout << "Do you want the key signature to be Major or Minor? [WARNING: MINOR AND RANDOM ARE NOT FINISHED]" << endl;
    cout << "[1] Major Key Signature" << endl;
    cout << "[2] Minor Key Signature" << endl;
    cout << "[3] Choose at random" << endl;
    while (keyPressContinue != '1' && keyPressContinue != '2' && keyPressContinue && '3')
    {
        keyPressContinue = _getch();
    }
    switch (keyPressContinue)
    {
    case '1':
        scaleTypeIndex = 1;
        break;
    case '2':
        scaleTypeIndex = 0;
        break;
    case '3':
        scaleTypeIndex = 2;
        break;
    }
    keyPressContinue = '?';
    system("CLS");
    cout << "Composition Random Generator | Config" << endl;
    cout << "Please press the corresponding number keys for the options." << endl;
    while (chordProgressionSelectionCheck == 0)
    {
        chordProgressionSelectionCheck = 1;
        cout << "\nWhat chords are allowed to be used? [1] for Yes, [0] for No.";
        for (int i = 1; i < 8; i++)
        {
            chordProgressionArrayIndex[i] = 2;
            cout << "\nChord " << i << ": ";
            while (chordProgressionArrayIndex[i] != 0 && chordProgressionArrayIndex[i] != 1)
            {
                chordProgressionArrayIndex[i] = _getch() - '0';
            }
            cout << chordProgressionArrayIndex[i];
        }
        for (int i = 0; i < 20; i++)
        {
            if (chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][1][i] == "N/A")
            {
                chordProgressionSelectionCheck = 0;
                cout << "\n\nYour chord selection was invalid and can't create a harmonic progression. Try some other chords.\n";
                break;
            }
        }
    }
    keyPressContinue = '?';
    system("CLS");
    cout << "Composition Random Generator | Config" << endl;
    cout << "Please press the corresponding number keys for the options." << endl;
    cout << "What is the minimum length of the composition in bars? Enter 0 if there is no minimum length.\nMin Length in bars: ";
    while (1)
    {
        cout << "\n\nWhat is the minimum length of the composition in bars? Hit Enter to continue.\nLength in bars: ";
        keyPressContinue = '?';
        compositionMinLength = 0;
        while (keyPressContinue != '~')
        {
            keyPressContinue = '?';
            keyPressContinue = _getch();
            if (48 <= keyPressContinue && keyPressContinue <= 57)
            {
                compositionMinLength = compositionMinLength * 10 + (keyPressContinue - '0');
                cout << (keyPressContinue - '0');
            }
            if (keyPressContinue == 8 || keyPressContinue == 127)
            {
                compositionMinLength = (compositionMinLength - compositionMinLength % 10) / 10;
                cout << "\b" << " " << "\b";
            }
            if (keyPressContinue == 13)
            {
                keyPressContinue = '~';
            }
        }
        cout << "\nWhat is the maximum length of the composition in bars? Hit Enter to continue, leave it blank if there is no maximum length.\nLength in bars: ";
        keyPressContinue = '?';
        compositionMaxLength = 0;
        while (keyPressContinue != '~')
        {
            keyPressContinue = '?';
            keyPressContinue = _getch();
            if (48 <= keyPressContinue && keyPressContinue <= 57)
            {
                compositionMaxLength = compositionMaxLength * 10 + (keyPressContinue - '0');
                cout << (keyPressContinue - '0');
            }
            if (keyPressContinue == 8 || keyPressContinue == 127)
            {
                compositionMaxLength = (compositionMaxLength - compositionMaxLength % 10) / 10;
                cout << "\b" << " " << "\b";
            }
            if (keyPressContinue == 13)
            {
                keyPressContinue = '~';
            }
        }
        if (compositionMaxLength == 0)
        {
            compositionMaxLength = 1000000;
        }
        if (compositionMaxLength - compositionMinLength < 3)
        {
            cout << "\n\nMake sure there is at least 4 bars of difference between the minimum and maximum lengths.\n";
        }
        else
        {
            break;
        }
    }
    cout << compositionMaxLength << endl;
    system("CLS");
    cout << "Composition Random Generator | Results" << endl;
    keySignatureIndividual(1);
    timeSignatureIndividual(1);
    tempoIndividual(1);
    chordProgressionIndividual(1);
    cout << "Press the number key to execute the command." << endl;
    cout << "[1] Generate a new composition." << endl;
    cout << "[COMING SOON]" << endl; // "[2] Store your generated tempo to save and use." << endl;
    cout << "[0] Exit to main screen." << endl;
    while (keyPressContinue != '1' && keyPressContinue != '2' && keyPressContinue != '0')
    {
        keyPressContinue = _getch();
    }
    switch (keyPressContinue)
    {
    case '1':
        keyPressContinue = '1';
        break;
    case '0':
        keyPressContinue = '?';
        break;
    }
}

void keySignatureIndividual(int composition)
{
    if (composition == 0)
    {
        system("CLS");
    }
    keySignatureIndex = rand() % 21;
    if (scaleTypeIndex == 2)
    {
        scaleTypeIndex = rand() % 2;
    }
    baseNoteIndex = (keySignatureIndex - keySignatureIndex % 3) / 3;
    keySignatureAccidental = keySignatureIndex % 3 - 1;
    scaleNotesList[0] = keySignaturesList[keySignatureIndex];
    for (int i = 1; i < 8; i++)
    {
        if (scaleTypeIndex == 0)
        {
            if (baseNotesSemitoneList[i + baseNoteIndex - 1] == minorSemitoneList[i - 1])
            {
                if (individualNoteAccidental == -1)
                {
                    individualNoteAccidental = -1;
                }
                else
                {
                    individualNoteAccidental = 0;
                }
            }
            else if (baseNotesSemitoneList[i + baseNoteIndex - 1] > minorSemitoneList[i - 1])
            {
                if (individualNoteAccidental != 1)
                {
                    individualNoteAccidental = -1;
                }
                else
                {
                    individualNoteAccidental = 0;
                }
            }
            else if (baseNotesSemitoneList[i + baseNoteIndex - 1] < minorSemitoneList[i - 1])
            {
                if (individualNoteAccidental != -1)
                {
                    individualNoteAccidental = 1;
                }
                else
                {
                    individualNoteAccidental = 0;
                }
            }
        }
        else if (scaleTypeIndex == 1)
        {
            if (baseNotesSemitoneList[i + baseNoteIndex - 1] == majorSemitoneList[i - 1])
            {
                if (individualNoteAccidental == 1)
                {
                    individualNoteAccidental = 1;
                }
                else
                {
                    individualNoteAccidental = 0;
                }
            }
            else if (baseNotesSemitoneList[i + baseNoteIndex - 1] > majorSemitoneList[i - 1])
            {
                if (individualNoteAccidental != 1)
                {
                    individualNoteAccidental = -1;
                }
                else
                {
                    individualNoteAccidental = 0;
                }
            }
            else if (baseNotesSemitoneList[i + baseNoteIndex - 1] < majorSemitoneList[i - 1])
            {
                if (individualNoteAccidental != -1)
                {
                    individualNoteAccidental = 1;
                }
                else
                {
                    individualNoteAccidental = 0;
                }
            }
        }
        switch (keySignatureAccidental + individualNoteAccidental)
        {
        case -2:
            scaleNotesList[i] = baseNotesList[i + baseNoteIndex] + "bb";
            break;
        case -1:
            scaleNotesList[i] = baseNotesList[i + baseNoteIndex] + "b";
            break;
        case 0:
            scaleNotesList[i] = baseNotesList[i + baseNoteIndex];
            break;
        case 1:
            scaleNotesList[i] = baseNotesList[i + baseNoteIndex] + "#";
            break;
        case 2:
            scaleNotesList[i] = baseNotesList[i + baseNoteIndex] + "x";
            break;
        }
    }
    cout << "The key signature the composition will be in is " << keySignaturesList[abs(keySignatureIndex)] << scaleTypeList[abs(scaleTypeIndex)] << "."; // abs() is useless but bypasses MSVC warning
    cout << "\nThe notes in the " << keySignaturesList[abs(keySignatureIndex)] << scaleTypeList[abs(scaleTypeIndex)] << " scale are:" << endl; // Again use abs() to bypass warning
    for (int i = 0; i < 8; i++)
    {
        cout << "Note " << i + 1 << ": " << scaleNotesList[i] << endl;
    }
    cout << endl;
    if (composition == 0)
    {
        cout << "Press the number key to execute the command." << endl;
        cout << "[1] Generate a new key signature." << endl;
        cout << "[COMING SOON]" << endl; // "[9] Store your generated tempo to save and use." << endl;
        cout << "[0] Exit to main screen." << endl;
        while (keyPressContinue != '1' && keyPressContinue != '9' && keyPressContinue != '0')
        {
            keyPressContinue = _getch();
        }
        switch (keyPressContinue)
        {
        case '1':
            keyPressContinue = '2';
            break;
        case '0':
            keyPressContinue = '?';
            break;
        }
    }
}

void keySignaturesAll()
{
    system("CLS");
    for (int x = 0; x < 42; x++)
    {
        keySignatureIndex = x % 21;
        scaleTypeIndex = (x - x % 21) / 21;
        baseNoteIndex = (keySignatureIndex - keySignatureIndex % 3) / 3;
        keySignatureAccidental = keySignatureIndex % 3 - 1;
        scaleNotesList[0] = keySignaturesList[keySignatureIndex];
        for (int i = 1; i < 8; i++)
        {
            if (scaleTypeIndex == 0)
            {
                if (baseNotesSemitoneList[i + baseNoteIndex - 1] == minorSemitoneList[i - 1])
                {
                    if (individualNoteAccidental == -1)
                    {
                        individualNoteAccidental = -1;
                    }
                    else
                    {
                        individualNoteAccidental = 0;
                    }
                }
                else if (baseNotesSemitoneList[i + baseNoteIndex - 1] > minorSemitoneList[i - 1])
                {
                    if (individualNoteAccidental != 1)
                    {
                        individualNoteAccidental = -1;
                    }
                    else
                    {
                        individualNoteAccidental = 0;
                    }
                }
                else if (baseNotesSemitoneList[i + baseNoteIndex - 1] < minorSemitoneList[i - 1])
                {
                    if (individualNoteAccidental != -1)
                    {
                        individualNoteAccidental = 1;
                    }
                    else
                    {
                        individualNoteAccidental = 0;
                    }
                }
            }
            else if (scaleTypeIndex == 1)
            {
                if (baseNotesSemitoneList[i + baseNoteIndex - 1] == majorSemitoneList[i - 1])
                {
                    if (individualNoteAccidental == 1)
                    {
                        individualNoteAccidental = 1;
                    }
                    else
                    {
                        individualNoteAccidental = 0;
                    }
                }
                else if (baseNotesSemitoneList[i + baseNoteIndex - 1] > majorSemitoneList[i - 1])
                {
                    if (individualNoteAccidental != 1)
                    {
                        individualNoteAccidental = -1;
                    }
                    else
                    {
                        individualNoteAccidental = 0;
                    }
                }
                else if (baseNotesSemitoneList[i + baseNoteIndex - 1] < majorSemitoneList[i - 1])
                {
                    if (individualNoteAccidental != -1)
                    {
                        individualNoteAccidental = 1;
                    }
                    else
                    {
                        individualNoteAccidental = 0;
                    }
                }
            }
            switch (keySignatureAccidental + individualNoteAccidental)
            {
            case -2:
                scaleNotesList[i] = baseNotesList[i + baseNoteIndex] + "bb";
                break;
            case -1:
                scaleNotesList[i] = baseNotesList[i + baseNoteIndex] + "b";
                break;
            case 0:
                scaleNotesList[i] = baseNotesList[i + baseNoteIndex];
                break;
            case 1:
                scaleNotesList[i] = baseNotesList[i + baseNoteIndex] + "#";
                break;
            case 2:
                scaleNotesList[i] = baseNotesList[i + baseNoteIndex] + "x";
                break;
            }
        }
        cout << "The key signature: " << keySignaturesList[abs(keySignatureIndex)] << scaleTypeList[abs(scaleTypeIndex)] << "."; // abs() is useless but bypasses MSVC warning
        cout << "\nThe notes in the " << keySignaturesList[abs(keySignatureIndex)] << scaleTypeList[abs(scaleTypeIndex)] << " scale are:" << endl; // Again use abs() to bypass warning
        for (int i = 0; i < 8; i++)
        {
            cout << "Note " << i + 1 << ": " << scaleNotesList[i] << endl;
        }
        cout << endl;
    }
    cout << "Press the number key to execute the command." << endl;
    cout << "[1] Re-generate all key signatures" << endl;
    cout << "[0] Exit to main screen." << endl;
    while (keyPressContinue != '1'&& keyPressContinue != '0')
    {
        keyPressContinue = _getch();
    }
    switch (keyPressContinue)
    {
    case '1':
        keyPressContinue = '3';
        break;
    case '0':
        keyPressContinue = '?';
        break;
    }
}

void timeSignatureIndividual(int composition)
{
    if (composition == 0)
    {
        system("CLS");
    }
    timeSignatureIndex = rand() % 7;
    timeSignatureNumerator = rand() % (4 * timeSignatureValuesList[timeSignatureIndex]) + 1;
    cout << "The time signature that was generated is " << timeSignatureNumerator << "/" << timeSignatureValuesList[timeSignatureIndex] << ".";
    cout << "\nThe " << timeSignatureNumerator << "/" << timeSignatureValuesList[timeSignatureIndex] << " time signature means there is " << timeSignatureNumerator << " " << timeSignatureNotesList[timeSignatureIndex] << " beats per bar.";
    cout << endl << endl;
    if (composition == 0)
    {
        cout << "Press the number key to execute the command." << endl;
        cout << "[1] Generate a new time signature." << endl;
        cout << "[COMING SOON]" << endl; // "[9] Store your generated tempo to save and use." << endl;
        cout << "[0] Exit to main screen." << endl;
        while (keyPressContinue != '1' && keyPressContinue != '9' && keyPressContinue != '0')
        {
            keyPressContinue = _getch();
        }
        switch (keyPressContinue)
        {
        case '1':
            keyPressContinue = '4';
            break;
        case '0':
            keyPressContinue = '?';
            break;
        }
    }
}

void tempoIndividual(int composition)
{
    if (composition == 0)
    {
        system("CLS");
        tempoNote = rand() % 14;
        beatsPerMinute = rand() % 91 + 90;
    }
    else
    {
        tempoNote = rand() % 14;
        beatsPerMinute = rand() % 91 + 90;
        timeSignatureToNumerator = (timeSignatureIndex * 2 + 1) - tempoNote;
        if (timeSignatureToNumerator % 2 != 0)
        {
            dottedNoteMultiplier = 1.5;
        }
        else
        {
            dottedNoteMultiplier = 1;
        }
        if (timeSignatureToNumerator < 0)
        {
            beatsPerMinute = ((beatsPerMinute * pow(2, timeSignatureIndex-2)) / pow(2, ((timeSignatureToNumerator - (timeSignatureToNumerator % 2)) / 2))) * dottedNoteMultiplier;
            // 219 = ? / 2^0
        }
        else
        {
            beatsPerMinute = (beatsPerMinute * pow(2, timeSignatureIndex-2)) / (pow(2, ((timeSignatureToNumerator - (timeSignatureToNumerator % 2)) / 2)) * dottedNoteMultiplier);
        }
    }
    cout << "The tempo that was generated is one " << tempoNotesList[tempoNote] << " = " << beatsPerMinute << ".";
    cout << "\nThis means there are " << beatsPerMinute << " " << tempoNotesList[tempoNote] << " beats per minute.";
    cout << endl << endl;
    if (composition == 0)
    {
        cout << "Press the number key to execute the command." << endl;
        cout << "[1] Generate a new tempo." << endl;
        cout << "[COMING SOON]" << endl; // "[9] Store your generated tempo to save and use." << endl;
        cout << "[0] Exit to main screen." << endl;
        while (keyPressContinue != '1' && keyPressContinue != '9' && keyPressContinue != '0')
        {
            keyPressContinue = _getch();
        }
        switch (keyPressContinue)
        {
        case '1':
            keyPressContinue = '5';
            break;
        case '0':
            keyPressContinue = '?';
            break;
        }
    }
}

void chordProgressionIndividual(int composition)
{
    if (composition == 0)
    {
        chordProgressionSelectionCheck = 0;
        compositionMinLength = -1;
        compositionMaxLength = -1;
        chordProgressionArrayIndex[0] = 0;
        system("CLS");
        cout << "Please enter the corresponding number keys for your chord progression restrictions." << endl;
        cout << "[1] Major Key Signature." << endl;
        cout << "[2] Minor Key Signature." << endl;
        cout << "Choice: ";
        while (chordProgressionArrayIndex[0] != 1 && chordProgressionArrayIndex[0] != 2)
        {
            chordProgressionArrayIndex[0] = _getch() - '0';
        }
        cout << chordProgressionArrayIndex[0];
        chordProgressionArrayIndex[0] = chordProgressionArrayIndex[0] - 1;
        while (chordProgressionSelectionCheck == 0)
        {
            chordProgressionSelectionCheck = 1;
            cout << "\nWhat chords are allowed to be used? [1] for Yes, [0] for No.";
            for (int i = 1; i < 8; i++)
            {
                chordProgressionArrayIndex[i] = 2;
                cout << "\nChord " << i << ": ";
                while (chordProgressionArrayIndex[i] != 0 && chordProgressionArrayIndex[i] != 1)
                {
                    chordProgressionArrayIndex[i] = _getch() - '0';
                }
                cout << chordProgressionArrayIndex[i];
            }
            for (int i = 0; i < 20; i++)
            {
                if (chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][1][i] == "N/A")
                {
                    chordProgressionSelectionCheck = 0;
                    cout << "\n\nYour chord selection was invalid and can't create a harmonic progression. Try some other chords.\n";
                    break;
                }
            }
        }
        while (1)
        {
            cout << "\n\nWhat is the minimum length of the composition in bars? Hit Enter to continue.\nLength in bars: ";
            keyPressContinue = '?';
            compositionMinLength = 0;
            while (keyPressContinue != '~')
            {
                keyPressContinue = '?';
                keyPressContinue = _getch();
                if (48 <= keyPressContinue && keyPressContinue <= 57)
                {
                    compositionMinLength = compositionMinLength * 10 + (keyPressContinue - '0');
                    cout << (keyPressContinue - '0');
                }
                if (keyPressContinue == 8 || keyPressContinue == 127)
                {
                    compositionMinLength = (compositionMinLength - compositionMinLength % 10) / 10;
                    cout << "\b" << " " << "\b";
                }
                if (keyPressContinue == 13)
                {
                    keyPressContinue = '~';
                }
            }
            cout << "\nWhat is the maximum length of the composition in bars? Hit Enter to continue, leave it blank if there is no maximum length.\nLength in bars: ";
            keyPressContinue = '?';
            compositionMaxLength = 0;
            while (keyPressContinue != '~')
            {
                keyPressContinue = '?';
                keyPressContinue = _getch();
                if (48 <= keyPressContinue && keyPressContinue <= 57)
                {
                    compositionMaxLength = compositionMaxLength * 10 + (keyPressContinue - '0');
                    cout << (keyPressContinue - '0');
                }
                if (keyPressContinue == 8 || keyPressContinue == 127)
                {
                    compositionMaxLength = (compositionMaxLength - compositionMaxLength % 10) / 10;
                    cout << "\b" << " " << "\b";
                }
                if (keyPressContinue == 13)
                {
                    keyPressContinue = '~';
                }
            }
            if (compositionMaxLength == 0)
            {
                compositionMaxLength = 1000000;
            }
            if (compositionMaxLength - compositionMinLength < 3)
            {
                cout << "\n\nMake sure there is at least 4 bars of difference between the minimum and maximum lengths.\n";
            }
            else
            {
                break;
            }
        }
        system("CLS");
    }
    else
    {
        switch (scaleTypeIndex)
        {
        case 0:
            chordProgressionArrayIndex[0] = 1;
            break;
        case 1:
            chordProgressionArrayIndex[0] = 0;
            break;
        }
    }
    chordProgressionOptions = 0;
    for (int i = 0; i < 20; i++)
    {
        if (chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][0][i] == "\0")
        {
            break;
        }
        else
        {
            chordProgressionOptions++;
        }
    }
    if (chordProgressionArrayIndex[1] == 1)
    {
        chordProgressionCurrentChord = 0;
    }
    else
    {
        chordProgressionCurrentChord = rand() % chordProgressionOptions;
    }
    cout << "Starting Chord\t(No. 1):\t" << chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][0][chordProgressionCurrentChord] << endl;
    for (int i = 1; i < compositionMaxLength; i++)
    {
        chordProgressionAvailRows = 0;
        for (int x = 1; chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][x][chordProgressionCurrentChord] != "N/A" && chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][x][chordProgressionCurrentChord] != "\0"; x++)
        {
            chordProgressionAvailRows++;
        }
        if (i >= compositionMinLength)
        {
            if (compositionMaxLength - 3 <= i)
            {
                switch (compositionMaxLength - i)
                {
                case 1:
                    if (chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][0][chordProgressionCurrentChord] == "I")
                    {
                        compositionMaxLength = i;
                    }
                    else
                    {
                        chordProgressionNewChord = 1;
                    }
                    break;
                case 2:
                    if (chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][0][chordProgressionCurrentChord] == "I")
                    {
                        compositionMaxLength = i;
                    }
                    else
                    {
                        while (chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][chordProgressionNewChord][chordProgressionCurrentChord] != "I" && chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][chordProgressionNewChord][chordProgressionCurrentChord] != "IV" && chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][chordProgressionNewChord][chordProgressionCurrentChord] != "V" && chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][chordProgressionNewChord][chordProgressionCurrentChord] != "viio")
                        {
                            chordProgressionNewChord = (rand() % (chordProgressionAvailRows - 1)) + 1;
                        }
                    }
                    break;
                case 3:
                    chordProgressionNewChord = 1;
                    break;
                }
            }
             else if (rand() % (compositionMaxLength - compositionMinLength) < i - compositionMinLength)
            {
                compositionMaxLength = i + 3;
                switch (compositionMaxLength - i)
                {
                case 1:
                    chordProgressionNewChord = 1;
                    break;
                case 2:
                    while (chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][chordProgressionNewChord][chordProgressionCurrentChord] != "I" && chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][chordProgressionNewChord][chordProgressionCurrentChord] != "IV" && chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][chordProgressionNewChord][chordProgressionCurrentChord] != "V" && chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][chordProgressionNewChord][chordProgressionCurrentChord] != "viio")
                    {
                        chordProgressionNewChord = (rand() % (chordProgressionAvailRows - 1)) + 1;
                    }
                    break;
                case 3:
                    chordProgressionNewChord = 1;
                    break;
                }
            }
             else
            {
                if (chordProgressionAvailRows == 1)
                {
                    chordProgressionNewChord = 1;
                }
                else
                {
                    chordProgressionNewChord = (rand() % (chordProgressionAvailRows - 1)) + 1;
                }
            }
        }
        else
        {
            if (chordProgressionAvailRows == 1)
            {
                chordProgressionNewChord = 1;
            }
            else
            {
                chordProgressionNewChord = (rand() % (chordProgressionAvailRows - 1)) + 1;
            }
        }
        if (compositionMaxLength == i)
        {
            break;
        }
        chordProgressionArrayIndex[8] = 0;
        while (chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][0][chordProgressionArrayIndex[8]] != chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][chordProgressionNewChord][chordProgressionCurrentChord])
        {
            chordProgressionArrayIndex[8]++;
        }
        chordProgressionCurrentChord = chordProgressionArrayIndex[8];
        cout << "Next Chord\t(No. " << i + 1 << "):\t" << chordProgressionArray[chordProgressionArrayIndex[0]][chordProgressionArrayIndex[1]][chordProgressionArrayIndex[2]][chordProgressionArrayIndex[3]][chordProgressionArrayIndex[4]][chordProgressionArrayIndex[5]][chordProgressionArrayIndex[6]][chordProgressionArrayIndex[7]][0][chordProgressionCurrentChord] << endl;
    }
    if (composition == 0)
    {
        cout << "Press the number key to execute the command." << endl;
        cout << "[1] Generate a chord progression." << endl;
        cout << "[COMING SOON]" << endl; // "[9] Store your generated chord progression to save and use." << endl;
        cout << "[0] Exit to main screen." << endl;
        while (keyPressContinue != '1' && keyPressContinue != '9' && keyPressContinue != '0')
        {
            keyPressContinue = _getch();
        }
        switch (keyPressContinue)
        {
        case '1':
            keyPressContinue = '6';
            break;
        case '0':
            keyPressContinue = '?';
            break;
        }
    }
}

void instrumentGenerate(int composition)
{

}

void melodyIndividual(int composition)
{

}

int main()
{
    srand(time(NULL));
    while (keyPressContinue != '~')
    {
        system("CLS");
        cout << "Composition Random Generator. Press the number key to execute the commands." << endl;
        cout << "[1] Generate all aspects for a composition." << endl;
        cout << "[2] Generate a random Major or Minor key signature." << endl;
        cout << "[3] Print all Major and Minor key signatures." << endl;
        cout << "[4] Generate a random time signature." << endl;
        cout << "[5] Generate a random tempo." << endl;
        cout << "[6] Generate a random chord progression. [COMING SOON]" << endl;
        cout << "[COMING SOON]" << endl; // "[7] Generate some random instruments to use." << endl;
        cout << "[COMING SOON]" << endl; // "[8] Generate a random composition melody." << endl;
        cout << "[COMING SOON]" << endl; // "[9] Print your latest / saved creations and save them in a text file." << endl;
        cout << "[0] Exit Program." << endl;
        while (keyPressContinue != '1' && keyPressContinue != '2' && keyPressContinue != '3' && keyPressContinue != '4' && keyPressContinue != '5' && keyPressContinue != '6' && keyPressContinue != '7' && keyPressContinue && '8' && keyPressContinue != '9' && keyPressContinue != '0')
        {
            keyPressContinue = _getch();
        }
        switch (keyPressContinue)
        {
        case '1':
            keyPressContinue = '?';
            generateComposition();
            break;
        case '2':
            keyPressContinue = '?';
            scaleTypeIndex = 2;
            keySignatureIndividual(0);
            break;
        case '3':
            keyPressContinue = '?';
            keySignaturesAll();
            break;
        case '4':
            keyPressContinue = '?';
            timeSignatureIndividual(0);
            break;
        case '5':
            keyPressContinue = '?';
            tempoIndividual(0);
            break;
        case '6':
            keyPressContinue = '?';
            chordProgressionIndividual(0);
            break;
        case '0':
            keyPressContinue = '~';
            break;
        }
    }
}


/*
    Notes because I'm lazy
    Modes of the Major Scale

    C D E F G A C   -   C Ionian        |   C  D  E  F  G  A  B     |   1  2  3  4  5  6  7     |   Lydian      C  D  E  F# G  A  B     -   GMaj
    D E F G A B C   -   D Dorian        |   D  E  F# G  A  B  C#    |   1  2  b3 4  5  6  b7    |   Ionian      C  D  E  F  G  A  B     -   CMaj
    E F G A B C D   -   E Phrygian      |   E  F# G# A  B  C# D#    |   1  b2 b3 4  5  b6 b7    |   Mixolydian  C  D  E  F  G  A  Bb    -   FMaj
    F G A B C D E   -   F Lydian        |   F  G  A  Bb C  D  E     |   1  2  3  #4 5  6  7     |   Dorian      C  D  Eb F  G  A  Bb    -   BbMaj
    G A B C D E F   -   G Mixolydian    |   G  A  B  C  D  E  F#    |   1  2  3  4  5  6  b7    |   Aeolian     C  D  Eb F  G  Ab Bb    -   EbMaj
    A B C D E F G   -   A Aeolian       |   A  B  C# D  E  F# G#    |   1  2  b3 4  5  b6 b7    |   Phrygian    C  Db Eb F  G  Ab Bb    -   AbMaj
    B C D E F G A   -   B Locrian       |   B  C# D# E  F# G# A#    |   1  b2 b3 4  b5 b6 b7    |   Locrian     C  Db Eb F  Gb Ab Bb    -   DbMaj

    Twinkle Twinkle
    1  1  5  5  6  6  5
    4  4  3  3  2  2  1
    5  5  4  4  3  3  2
    5  5  4  4  3  3  2
    1  1  5  5  6  6  5
    4  4  3  3  2  2  1

    In Phrygian
    C  C  G  G  Ab Ab G
    F  F  Eb Eb Eb Eb C
    G  G  F  F  Eb Eb Db
    G  G  F  F  Eb Eb Db
    C  C  G  G  Ab Ab G
    F  F  Eb Eb Eb Eb C
*/