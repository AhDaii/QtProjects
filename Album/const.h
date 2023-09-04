#ifndef CONST_H
#define CONST_H

enum TreeItemType {
    TreeItemPro = 1, // 项目条目
    TreeItemDir = 2, // 项目文件夹
    TreeItemPic = 3, // 项目图片
};

enum PicBtnState {
    Normal = 1,
    Hover = 2,
    Pressed = 3,
    Normal_2 = 4,
    Hover_2 = 5,
    Pressed_2 = 6
};

const int PROCESS_WIDTH = 300;
const int PROCESS_MAX = 300;

#endif // CONST_H
