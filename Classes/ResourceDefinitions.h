#ifndef __RESOURCE_DEFINITIONS_H__
#define __RESOURCE_DEFINITIONS_H__

#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"

/*
 Flow chart:
 [Opening] - audio: MUSICLAUNCH
 
    0: Launch
    1: Menu - Credits
 
 [Before Room] - audio: MUSICWAIT
 
    2: NameTag (Scene02) - DrawName
    3: WaitingRoom (Scene04) - PuzzleScene
    4: Elevator (Scene06)
 
 [Pre-Op] - audio: MUSICPREOP
 
    5: Scale (Scene07)
    6: Room (Scene08) - CloserLook (Scene09)
    7: OR Doors (Scene11)
 
 [OR] - audio: MUSICOR
 
    8: OR (Scene10) - Closer (Scene12)
    9: Choose Flavor (Scene13)
 
 [Post-Op] - audio: MUSICPOSTOP
 
    10: Room (Scene14) - PopsicleScene
    11: Congrats! (Scene15)
 
 [FrameNav]
 [IconBar]
 */

// A macro that does the same thing as "using namespace cocos2d;"
USING_NS_CC;

// Size of the game
static cocos2d::Size designResolutionSize = cocos2d::Size(2048.0/2, 1536.0/2);
static cocos2d::Size smallResolutionSize = cocos2d::Size(512.0, 384.0);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024.0, 768.0);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048.0, 1536.0);

// General
const float TEMPO = 1.0f / 1.0f; // works inversely to control app speed
const float SCENETRANSITIONTIME = 2.0f*TEMPO; // times for screen wipes
const float LAUNCHTRANSITIONTIME = 0.2f*TEMPO;
const float DRAWSCENEBRUSHSIZE = 0.01f; // 0.004 too small?

// Script
const std::string SCRIPT = "scripts/masterscript.txt";
const std::string FELTFONT = "fonts/Coiny-Regular.ttf";
const std::string COUNTERFONT = "fonts/Coiny-Regular.ttf"; // Scene font
const float TEXTSIZE = 1.0f / 30; // 20

// Audio
const float VOLUMEMUSIC = 0.8f;
const char MUSICLAUNCH[19] = "audio/surgeryu.wav";
const char MUSICWAIT[19] = "audio/ch3music.wav";
const char MUSICPREOP[19] = "audio/surgeryu.wav";
const char MUSICOR[19] = "audio/ch3music.wav";
const char MUSICPOSTOP[19] = "audio/surgeryu.wav";
const char MUSICDH[13] = "audio/dh.wav";

// General Sprites
const std::string STARSHINE = "res/Star.png"; // Scene Sprite
const std::string BIGRIDICULOUSARROW = "res/arrow.png"; // Scene Sprite
const std::string TEXTBOX = "res/TextBox.png"; // Scene TextBox
const std::string DONEBUTTON = "res/doneButton.png"; // Navigation Sprite
const std::string BACKBUTTON = "res/backButton.png"; // Navigation Sprite

// 0: Launch
const std::string LAUNCHIMAGE = "res/0Launch/title_background.png"; // Scene Sprite
const std::string HELICOPTER = "res/0Launch/helicopter.png"; // Scene Sprite
const std::string SCOOTER = "res/0Launch/gatorscooter.png"; // Scene Sprite
const std::string STARTBUTTON = "res/0Launch/start_button.png"; // Scene Sprite
const std::string STARTTEXT = "res/0Launch/start.png"; // Scene Sprite
const std::string WELCOMEBUTTON = "res/0Launch/welcome_bubble.png"; // Scene Sprite
const std::string WELCOMETEXT = "res/0Launch/welcome_shands.png"; // Scene Sprite

// 1: Menu
const std::string MENUBKGD = "res/1Menu/Background.png"; // Background Sprite
const std::string WELCOMEBUTTON01 = "res/1Menu/WelcomeBubble.png"; // Scene Script
const std::string CAREGIVERBUTTON01 = "res/1Menu/CaregiverButton.png"; // Scene Sprite
const std::string GAMEBUTTON01 = "res/1Menu/IspyButton.png"; // Scene Sprite
const std::string ICONGAME = "res/1Menu/IconGame.png"; // popup sprite
const std::string GAMEGOTIT = "res/1Menu/got_it.png"; // popup sprite button
const std::string CLIPBOARD = "res/1Menu/Clipboard.png"; // popup sprite
const std::string CLIPGOTIT = "res/1Menu/clip-got-it.png"; // popup sprite button

// 2: NameTag
const std::string NAMETAGBKGD = "res/2NameTagScene/Background.png"; // Background Sprite
const std::string BRACELET = "res/2NameTagScene/Bracelet.png"; // Scene Sprite
const std::string BRACELETCLICKED = "res/2NameTagScene/braceletClicked.png"; // Scene Sprite
const std::string DRAWBACKGROUND = "res/2NameTagScene/BackgroundDraw.png"; // Background Sprite

const std::string BLUEDOT = "res/2NameTagScene/BlueDot.png";
const std::string GREENDOT = "res/2NameTagScene/GreenDot.png";
const std::string ORANGEDOT = "res/2NameTagScene/OrangeDot.png";
const std::string REDDOT = "res/2NameTagScene/RedDot.png";
const std::string YELLOWDOT = "res/2NameTagScene/YellowDot.png";

// 3: Waiting Room
const std::string WAITINGBKGD = "res/3WaitingRoom/Background.png"; // Background Sprite
const std::string GAMEBUTTON04 = "res/3WaitingRoom/playbutton.png"; // Scene sprite

const std::string YELLOWBKGD = "res/3WaitingRoom/PuzzleBackground.png"; // Background Sprite
const std::string PUZZLESW = "res/3WaitingRoom/PuzzleSW.png"; // Puzzle Sprite
const std::string PUZZLENE = "res/3WaitingRoom/PuzzleNE.png"; // Puzzle Sprite
const std::string PUZZLESE = "res/3WaitingRoom/PuzzleSE.png"; // Puzzle Sprite
const std::string PUZZLENW = "res/3WaitingRoom/PuzzleNW.png"; // Puzzle Sprite

// 4: Elevator
const std::string ELEVATORBKGD = "res/4Elevator/Background.png"; // Background Sprite
const std::string PATIENT05 = "res/4Elevator/Gator.png"; // Character Sprite
const std::string MOM05 = "res/4Elevator/Parent.png"; // Character Sprite
const std::string NURSE05 = "res/4Elevator/Nurse.png"; // Character Sprite
const std::string GREENELEVATORBUTTON = "res/4Elevator/elevatorGreen.png";
const std::string ELEVATORBUTTONUP = "res/4Elevator/elevatorUp.png";
const std::string ELEVATORBUTTONDOWN = "res/4Elevator/elevatorDown.png";
const std::string BUTTON06 = "res/4Elevator/meetyournursebutton.png";
const std::string HINURSE = "res/4Elevator/nurseScreenshot.png"; // Replace this!!

// 5: Scale
const std::string SCALEBKGD = "res/5Scale/Background.png"; // Background Sprite
const std::string Gown = "res/5Scale/Gown.png";
const std::string DressedGator = "res/5Scale/GatorwGown.png";
const std::string Gator = "res/5Scale/GatornoGown.png";

// 6: Room
const std::string ROOMBKGD = "res/6Room/Background.png"; //New Background Sprite
const std::string MOMROOM = "res/6Room/ParentRoom.png"; // Scene Sprite
const std::string WINDOW = "res/6Room/window.png"; //Window Sprite
const std::string takeACloserLook = "res/6Room/closerlookButton.png";
const std::string meetyouranestesiologist = "res/6Room/DoctorButton.png";
const std::string HIANES = "res/6Room/anesScreenshot.png"; // Replace this!!

const std::string CLOSERLOOKBKGD = "res/6Room/BackgroundCloser.png"; // Background Sprite
const std::string cuff = "res/6Room/cuff.png";
const std::string thermometer = "res/6Room/thermometer.png";
const std::string thermometerclicked = "res/6Room/thermometerClicked.png";
const std::string electrodes = "res/6Room/electrodes.png";
const std::string electrodesclicked = "res/6Room/electrodesClicked.png";
const std::string pulseox = "res/6Room/pulseox.png";
const std::string pulseoxclicked = "res/6Room/pulseoxClicked.png";

// 7: OR Doors
const std::string ORDOORSBKGD = "res/7ORDoors/Background.png"; // Background Sprite
const std::string S11DOORS = "res/7ORDoors/doors.png"; // Background Sprite
const std::string S11PPL = "res/7ORDoors/people.png"; // Background Sprite

// 8: OR Room
const std::string ORBKGD = "res/8OR/Background.png"; // Background Sprite
const std::string SleepMach = "res/8OR/machine.png";
const std::string Bed = "res/8OR/GatorBed.png";
const std::string Nurse = "res/8OR/nurse.png";
const std::string LightOn = "res/8OR/lightOn.png";
const std::string LightOff = "res/8OR/lightOff.png";
const std::string Anes = "res/8OR/anesthesiologist.png";

const std::string S12BKGD = "res/8OR/BackgroundMachine.png"; // Background Sprite
const std::string ANES = "res/8OR/anesthesiologistnoMask.png"; // Anesthesiologist Sprite
const std::string MACHINE = "res/8OR/machineGlow.png"; // Anesthesia Machine
const std::string Mask32 = "res/8OR/mask.png";
const std::string PICKFLAVORBUTTON = "res/8OR/pickyourflavor.png";

// 9: Flavor
const std::string FLAVORBKGD = "res/9Flavor/Background.png"; // Background Sprite
const std::string ANESMASK = "res/9Flavor/maskFlavor.png"; // Mask Sprite
const std::string ANESMELON = "res/9Flavor/anes_melon.png"; // Watermelon Flavor Sprite
const std::string ANESGUM = "res/9Flavor/anes_gum.png"; // Bubblegum Flavor Sprite
const std::string ANESBERRY = "res/9Flavor/anes_berry.png"; // Strawberry Flavor Sprite

// 10: Post-OP
const std::string POSTOPBKGD = "res/10PostOp/Background.png"; // Background Sprite
const std::string postIV = "res/10PostOp/IV.png"; // iv bag
const std::string postchair = "res/10PostOp/chair.png"; // chair
const std::string postbed = "res/10PostOp/GatorBedPost.png";
const std::string postdoc = "res/10PostOp/doctor.png";
const std::string postmom = "res/10PostOp/ParentPost.png";
const std::string TRYPOPBUTTON = "res/10PostOp/TryPopsicle.png";

const std::string POPSICLEBKGD = "res/10PostOp/popsicle_bkgd.png"; // Background Sprite
const std::string POP0 = "res/10PostOp/pop.png";
const std::string POP1 = "res/10PostOp/bite1.png";
const std::string POP2 = "res/10PostOp/bite2.png";
const std::string POP3 = "res/10PostOp/bite3.png";
const std::string POP4 = "res/10PostOp/bite4.png";
const std::string POP5 = "res/10PostOp/stick.png";
const std::string YUM = "res/10PostOp/YUM.png";

// 11: Congrats
const std::string S15BKGD = "res/11Congrats/Background.png"; // Background Sprite
const std::string bubble = "res/11Congrats/collectionBubble.png";
const std::string confetti = "res/11Congrats/confetti.png";
const std::string depgator = "res/11Congrats/gatorCongrats.png";
const std::string thankyou = "res/11Congrats/thanks.png";

// Frame Navigation
const std::string MOVEFWD = "res/arrowR.png";
const std::string MOVEBWD = "res/arrowL.png";
const std::string VOLUMEBUTTON = "res/framebuttons/Volume.png";
const std::string TAPTHESCREEN = "res/framebuttons/touchhint.png";
const float SCALEY1 = 0.06f; // Scale Y1 position based on screen size
const float SCALEY2 = 0.94f; // Scale Y2 position based on screen size
const float SCALEX1 = 0.06f; // Scale X1 position based on screen size
const float SCALEX2 = 0.94f; // Scale X2 position based on screen size
const std::string HOMEBUTTON = "res/framebuttons/homeButton.png"; // Button Sprite
const std::string FRAMEFRAME = "res/framebuttons/Frame.png"; // Button Sprite
const std::string EXITBUTTONON = "res/framebuttons/exitButton.png"; // Button Sprite
const std::string EXITBUTTONOFF = "res/framebuttons/Frame-03.png"; // Button Sprite
const int BORDERTAG = 1101; // Child tag to toggle boarder
const int ISPYTAG = 1500; // Child tag for I-SPY game icon bar
const int FRAMEDRAW = 1000; // Control tag for graphy priorty drawing of frame stuff

// Icon Bar
const std::string ICONBAR = "res/IconBar/IconBar.png";
const std::string CUFF  = "res/IconBar/BloodPressureCuff.png";
const std::string BRACE = "res/IconBar/Bracelet.png";
const std::string MASK  = "res/IconBar/Mask.png";
const std::string PULSEOX = "res/IconBar/PulseOX.png";
const std::string EKG = "res/IconBar/EKG.png";
const std::string GOWN =  "res/IconBar/HospitalGown.png";
const std::string THERMO = "res/IconBar/Thermometer.png";
const std::string STAR = "res/IconBar/star.png";

#endif // __RESOURCE_DEFINITIONS_H__
