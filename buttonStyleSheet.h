#ifndef BUTTONSTYLESHEET_H
#define BUTTONSTYLESHEET_H
//顾名思义，style文件,用了宏定义
#define BUTTON_STYLESHEET "QPushButton\
{\
    background: transparent;\
}\
QPushButton:pressed\
{\
    background-color: rgb(0, 50, 100);\
    border:2px;\
    border-radius:15px;\
    padding 2px 4px;\
}"

#define CHANGE_WHITE_STYLE "QPushButton\
{\
    border:2px;\
    border-radius:15px;\
    padding 2px 4px;\
    background-color: white;\
}"

#define CHANGE_BLACK_STYLE "QPushButton\
{\
    border:2px;\
    border-radius:15px;\
    padding 2px 4px;\
    background-color: black;\
}"
#endif // BUTTONSTYLESHEET_H
